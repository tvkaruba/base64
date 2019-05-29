include_directories(../src)

include_directories(.)

add_executable(tests
        base64Test.cpp

        ../src/base64.h
        ../src/base64.cpp

        gtest/gtest-all.cc
        gtest/gtest_main.cc
        )