#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/provider.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <oqs/oqs.h>

#include <iostream>
#include <vector>

extern "C" OSSL_provider_init_fn oqs_provider_init;

static auto kOQSProviderName = "oqsprovider";

using namespace std;

static int load_oqs_provider(OSSL_LIB_CTX *libctx)
{
    int ret = OSSL_PROVIDER_available(libctx, kOQSProviderName);

    if (ret != 0)
    {
        fprintf(stderr, "`OSSL_PROVIDER_available` returned %i, but 0 was expected\n", ret);
        return -1;
    }

    ret = OSSL_PROVIDER_add_builtin(libctx, kOQSProviderName, oqs_provider_init);
    if (ret != 1)
    {
        fprintf(stderr, "`OSSL_PROVIDER_add_builtin` failed with returned code %i\n", ret);
        return -1;
    }

    const OSSL_PROVIDER *provider = OSSL_PROVIDER_load(libctx, kOQSProviderName);
    if (provider == nullptr)
    {
        fputs("`OSSL_PROVIDER_load` failed\n", stderr);
        return -1;
    }

    ret = OSSL_PROVIDER_available(libctx, kOQSProviderName);
    if (ret != 1)
    {
        fprintf(stderr, "`OSSL_PROVIDER_available` returned %i, but 0 was expected\n", ret);
        return -1;
    }

    ret = OSSL_PROVIDER_self_test(provider);
    if (ret != 1)
    {
        fprintf(stderr, "`OSSL_PROVIDER_self_test` failed with returned code %i\n", ret);
        return -1;
    }

    return 0;
}

int main()
{
    OSSL_LIB_CTX *libctx = OSSL_LIB_CTX_new();
    if (libctx == nullptr)
    {
        fputs("`OSSL_LIB_CTX_new` failed. Cannot initialize OpenSSL.\n", stderr);
        return 1;
    }

    if (const int ret = load_oqs_provider(libctx); ret != 0)
    {
        fputs("`load_oqs_provider` failed. Dumping OpenSSL error queue.\n", stderr);
        ERR_print_errors_fp(stderr);
        return 2;
    }

    EVP_SIGNATURE *sig = EVP_SIGNATURE_fetch(libctx, "dilithium5", nullptr);

    if (sig == nullptr)
    {
        fputs("`EVP_SIGNATURE_fetch` failed. Dumping OpenSSL error queue.\n", stderr);
        ERR_print_errors_fp(stderr);
        return 3;
    }

    cout << EVP_SIGNATURE_get0_name(sig) << endl;

    EVP_SIGNATURE_free(sig);

    OSSL_LIB_CTX_free(libctx);

    return 0;
}
