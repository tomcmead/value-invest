################################
# GTest
################################
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
    FIND_PACKAGE_ARGS 1.14.0
)
set(gtest_force_shared_crt OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(googletest)