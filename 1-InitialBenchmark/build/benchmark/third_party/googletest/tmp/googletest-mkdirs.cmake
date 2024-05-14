# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Alfred/Documents/Github/Lets-Do-Cpp/1-InitialBenchmark/build/benchmark/third_party/googletest/src"
  "C:/Users/Alfred/Documents/Github/Lets-Do-Cpp/1-InitialBenchmark/build/benchmark/third_party/googletest/build"
  "C:/Users/Alfred/Documents/Github/Lets-Do-Cpp/1-InitialBenchmark/build/benchmark/third_party/googletest"
  "C:/Users/Alfred/Documents/Github/Lets-Do-Cpp/1-InitialBenchmark/build/benchmark/third_party/googletest/tmp"
  "C:/Users/Alfred/Documents/Github/Lets-Do-Cpp/1-InitialBenchmark/build/benchmark/third_party/googletest/stamp"
  "C:/Users/Alfred/Documents/Github/Lets-Do-Cpp/1-InitialBenchmark/build/benchmark/third_party/googletest/download"
  "C:/Users/Alfred/Documents/Github/Lets-Do-Cpp/1-InitialBenchmark/build/benchmark/third_party/googletest/stamp"
)

set(configSubDirs Debug;Release;MinSizeRel;RelWithDebInfo)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Alfred/Documents/Github/Lets-Do-Cpp/1-InitialBenchmark/build/benchmark/third_party/googletest/stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Alfred/Documents/Github/Lets-Do-Cpp/1-InitialBenchmark/build/benchmark/third_party/googletest/stamp${cfgdir}") # cfgdir has leading slash
endif()
