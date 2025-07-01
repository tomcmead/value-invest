################################
# GTest
################################
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
#set(gtest_force_shared_crt OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(googletest)