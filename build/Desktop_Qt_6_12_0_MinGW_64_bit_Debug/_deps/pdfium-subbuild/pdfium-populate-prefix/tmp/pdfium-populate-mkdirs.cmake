# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/gyasi/Desktop/ReadHub/build/Desktop_Qt_6_12_0_MinGW_64_bit_Debug/_deps/pdfium-src")
  file(MAKE_DIRECTORY "C:/Users/gyasi/Desktop/ReadHub/build/Desktop_Qt_6_12_0_MinGW_64_bit_Debug/_deps/pdfium-src")
endif()
file(MAKE_DIRECTORY
  "C:/Users/gyasi/Desktop/ReadHub/build/Desktop_Qt_6_12_0_MinGW_64_bit_Debug/_deps/pdfium-build"
  "C:/Users/gyasi/Desktop/ReadHub/build/Desktop_Qt_6_12_0_MinGW_64_bit_Debug/_deps/pdfium-subbuild/pdfium-populate-prefix"
  "C:/Users/gyasi/Desktop/ReadHub/build/Desktop_Qt_6_12_0_MinGW_64_bit_Debug/_deps/pdfium-subbuild/pdfium-populate-prefix/tmp"
  "C:/Users/gyasi/Desktop/ReadHub/build/Desktop_Qt_6_12_0_MinGW_64_bit_Debug/_deps/pdfium-subbuild/pdfium-populate-prefix/src/pdfium-populate-stamp"
  "C:/Users/gyasi/Desktop/ReadHub/build/Desktop_Qt_6_12_0_MinGW_64_bit_Debug/_deps/pdfium-subbuild/pdfium-populate-prefix/src"
  "C:/Users/gyasi/Desktop/ReadHub/build/Desktop_Qt_6_12_0_MinGW_64_bit_Debug/_deps/pdfium-subbuild/pdfium-populate-prefix/src/pdfium-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/gyasi/Desktop/ReadHub/build/Desktop_Qt_6_12_0_MinGW_64_bit_Debug/_deps/pdfium-subbuild/pdfium-populate-prefix/src/pdfium-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/gyasi/Desktop/ReadHub/build/Desktop_Qt_6_12_0_MinGW_64_bit_Debug/_deps/pdfium-subbuild/pdfium-populate-prefix/src/pdfium-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
