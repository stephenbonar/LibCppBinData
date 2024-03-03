# CMakeLists.txt - Builds the LibCppBinData tests.
#
# Copyright (C) 2024 Stephen Bonar
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http ://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissionsand
# limitations under the License.

# Define the source files needed to build the tests.
set(TEST_SOURCES
    IntFieldTests.cpp
    RawFieldTests.cpp
    StringFieldTests.cpp
    IntegrationTests.cpp
    RawFileTests.cpp)

# Define the directories that contain the header files the tests include.
set(TEST_INCLUDES 
    ${PROJECT_SOURCE_DIR}/LibCppBinData)

# Define the libraries the tests need to link against
set(TEST_LIBS
    LibCppBinData
    gtest
    gtest_main
    gmock)

# [Begin GoogleTest Code Snippet]
#
# The following code snippet was obtained from:
# https://github.com/google/googletest/blob/master/googletest/README.md
#
# The following code downloads and adds GoogleTest to the build.

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# [End GoogleTest Code Snippet]

# Configure the binary build target
add_executable(bindatatests ${TEST_SOURCES})

# Include all the directories that contain headers that we need that are not
# in the current directory, otherwise the compiler won't find them
target_include_directories(bindatatests PUBLIC ${TEST_INCLUDES})

# Configure the tunebeepertests target to link to the necessary libraries
target_link_libraries(bindatatests ${TEST_LIBS})

# Copies the test data files to the build directory so the test
# binary can find them when it runs.
if(CMAKE_GENERATOR MATCHES "Visual Studio")
    file(COPY TestReadData DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
else()
    file(COPY TestReadData DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()
