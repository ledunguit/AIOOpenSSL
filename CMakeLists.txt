cmake_minimum_required(VERSION 3.28)
project(AIOOpenSSL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os -s")

include_directories(includes)
link_directories(libs)
set(OPENSSL_LIB crypto ssl)
set(OQS_LIB oqs)
set(OQS_PROVIDER_LIB oqsprovider)

add_executable(AIOOpenSSL main.cpp)

target_link_libraries(AIOOpenSSL PRIVATE ${OQS_PROVIDER_LIB} ${OQS_LIB} ${OPENSSL_LIB} pthread)