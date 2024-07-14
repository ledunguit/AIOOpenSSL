cmake_minimum_required(VERSION 3.22)
project(AIOOpenSSL)

set(CMAKE_CXX_STANDARD 17)
include_directories(includes)
link_directories(libs)
set(OPENSSL_LIB crypto ssl)
set(OQS_LIB oqs)
set(OQS_PROVIDER_LIB oqsprovider)

add_executable(AIOOpenSSL main.cpp)


# Using group to resolve circular dependencies, prevent undefined symbols for the libraries
target_link_libraries(AIOOpenSSL "-Wl,--start-group" ${OPENSSL_LIB} ${OQS_PROVIDER_LIB} ${OQS_LIB} "-Wl,--end-group" pthread)