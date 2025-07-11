# -*- mode:org; mode:visual-line; coding:utf-8; -*-

CHANGES:
  - Transformed header lib 2 (EXPERIMENTAL) C++ 20 module

---

** A C++ ZLib wrapper

[[http://travis-ci.org/mateidavid/zstr][http://travis-ci.org/mateidavid/zstr.svg?branch=master]] [[https://tldrlegal.com/license/mit-license][http://img.shields.io/:license-mit-blue.svg]]

This C++ header-only library enables the use of C++ standard iostreams to access ZLib-compressed streams.

For input access (decompression), the compression format is auto-detected, and multiple concatenated compressed streams are decompressed seamlessly.

For output access (compression), the only parameter exposed by this API is the compression level.

Alternatives to this library include:

- The original [[http://www.zlib.net/][ZLib]], through its [[http://www.zlib.net/manual.html][C API]]. This does not interact nicely with C++ iostreams.

- The [[http://www.cs.unc.edu/Research/compgeom/gzstream/][GZStream]] library. This library does not auto-detect input compression, and it cannot wrap streams (only files).

- The [[http://www.boost.org/doc/libs/release/libs/iostreams/][Boost IOStreams]] library. The library does not auto-detect input compression (by default, though that can be easily implemented with filters), and more importantly, it is not a header-only Boost library.

- The [[https://github.com/tmaklin/bxzstr][bxzstr]] library, if you want support for BZ2 and/or LZMA as well.

For an example usage, see [[examples/ztxtpipe.cpp]] and [[examples/zc.cpp]].

It is compatible with [[https://github.com/richgel999/miniz][miniz]] in case you don't want to get frustrated with zlib e. g. on Windows.

**** Input Auto-detection

For input access, the library seamlessly auto-detects whether the source stream is compressed or not. The following compressed streams are detected:

- GZip header, when stream starts with =1F 8B=. See [[http://en.wikipedia.org/wiki/Gzip][GZip format]].

- ZLib header, when stream starts with =78 01=, =78 9C=, and =78 DA=. See [[http://stackoverflow.com/a/17176881][answer here]].

If none of these formats are detected, the library assumes the input is not compressed, and it produces a plain copy of the source stream.

**** Classes

The package provides 6 classes for accessing ZLib streams:

- =zstr::istreambuf= is the core decompression class. This is constructed from an existing =std::streambuf= that contains source data. The =zstr::istreambuf= constructor accepts explicit settings for the internal buffer size (default: 1 MB) and the auto-detection option (default: on). ZLib errors cause exceptions to be thrown.

- =zstr::ostreambuf= is the core compression class. This is constructed from an existing =std::streambuf= that contains sink data. The =zstr::ostreambuf= constructor accepts explicit settings for the internal buffer size (default: 1 MB) and the compression option (default: ZLib default). ZLib errors cause exceptions to be thrown.

- =zstr::istream= is a wrapper for a =zstr::istreambuf= that accesses an /external/ =std::streambuf=. It can be constructed from an existing =std::istream= (such as =std::cin=) or =std::streambuf=.

- =zstr::ostream= is a wrapper for a =zstr::ostreambuf= that accesses an /external/ =std::streambuf=. It can be constructed from an existing =std::ostream= (such as =std::cout=) or =std::streambuf=.

- =zstr::ifstream= is a wrapper for a =zstr::istreambuf= that accesses an /internal/ =std::ifstream=. This can be used to open a file and read decompressed data from it.

- =zstr::ofstream= is a wrapper for a =zstr::ostreambuf= that accesses an /internal/ =std::ofstream=. This can be used to open a file and write compressed data to it.

For all stream objects, the =badbit= of their exception mask is turned on in order to propagate exceptions.

**** CMake

There are three simple ways to add zstr to a CMake project.

Method 1. Add zstr as a subdirectory and link to the =zstr::zstr= target

  #+BEGIN_SRC cmake
    add_subdirectory(zstr) # defines INTERFACE target 'zstr::zstr'

    add_executable(YourTarget main.cpp)
    target_link_libraries(YourTarget PRIVATE zstr::zstr)
    # if using cmake < 3.13 you may also need the following line
    # target_include_directories(YourTarget PRIVATE ${ZSTR_INCLUDE_DIRS})
  #+END_SRC

Method 2. Fetch a copy of zstr from an external repository and link to the =zstr::zstr= target

  /NOTE: The FetchContent functions shown here were introduced in CMake 3.14/

  #+BEGIN_SRC cmake
    include(FetchContent)
    FetchContent_Declare(ZStrGitRepo
      GIT_REPOSITORY    "https://github.com/mateidavid/zstr" # can also be a local filesystem path!
      GIT_TAG           "master"
    )
    FetchContent_MakeAvailable(ZStrGitRepo) # defines INTERFACE target 'zstr::zstr'

    add_executable(YourTarget main.cpp)
    target_link_libraries(YourTarget PRIVATE zstr::zstr)
  #+END_SRC

Method 3. Add path containing 'zstr.hpp' to your target's include directories

  /NOTE: With this method you're responsible for finding and linking to ZLIB !/

  #+BEGIN_SRC cmake
    find_package(ZLIB REQUIRED)
    add_executable(YourTarget main.cpp)
    target_link_libraries(YourTarget PRIVATE ZLIB::ZLIB)
    target_include_directories(YourTarget PRIVATE /path/to/zstr/src)
  #+END_SRC

**** Requisites

If you use GCC and want to use the `fs.open()` function, you need to deploy at least GCC version 5.1.

**** License

Released under the [[file:LICENSE][MIT license]].
