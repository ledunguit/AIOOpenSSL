# OpenSSL, LibOQS, OQS-Provider all in one for ... any one need it.

## How to compile?
- Just run
```bash
./build.sh
```
## Or compile yourself 🥲

#### OpenSSL

```bash
git clone https://github.com/openssl/openssl.git
cd openssl
./config no-shared no-docs
make -j8
```
`8` is number of your CPU cores, when it done, there are two files libcrypto.a and libssl.a in the current directory, hope you found it!

#### LibOQS

```bash
 git clone -b main https://github.com/open-quantum-safe/liboqs.git
 cd liboqs
 mkdir build && cd build
 cmake -GNinja ..
 ninja
```

Find the liboqs.a file in build/lib folder.

#### OQS-Provider

```bash
https://github.com/open-quantum-safe/oqs-provider.git
cd oqs-provider
cmake -S . -B _build && cmake --build _build
```
If you want a static library, run this command instead:
```bash
cmake -DOQS_PROVIDER_BUILD_STATIC=on -S . -B _build && cmake --build _build
```

### Any questions?
- Open issue for each repo, not me :V
