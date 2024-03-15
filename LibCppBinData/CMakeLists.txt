# CMakeLists.txt - Builds the LibCppBinData library.
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

# Define the source files needed to build the library
set(LIB_SOURCES
    RawFile.cpp
    Field.cpp
    Format.cpp
    RawField.cpp
    StringField.cpp
    IntField.cpp
    StdFileStream.cpp)

# Configure the library build target.
add_library(LibCppBinData ${LIB_SOURCES})

# Override the default behavior of prefixing "lib" on the library binary so
# we end up with LibCppBinData.a isntead of libLibCppBinData.a.
set_target_properties(LibCppBinData PROPERTIES PREFIX "")

# Include all the directories that contain headers that we need that are not
# in the current directory, otherwise the compiler won't find them.
target_include_directories(LibCppBinData PUBLIC .)