cmake_minimum_required ( VERSION 2.8 )

#This code using for tests for specific compiler,
#please does not remove this while library status is developming
#SET(CMAKE_C_COMPILER /usr/local/Cellar/gcc48/4.8.4/bin/gcc-4.8)
#SET(CMAKE_CXX_COMPILER /usr/local/Cellar/gcc48/4.8.4/bin/g++-4.8)

project ( apiai )
enable_testing()

#for portaudio find
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

#OPTION(APIAI_WITH_TESTS "Compile and run tests." ON)
#OPTION(APIAI_WITH_POST_BUILD_UNITTEST "Automatically run unit-tests as a post build step" ON)
OPTION(APIAI_WITH_PKGCONFIG_SUPPORT "Generate and install .pc files" ON)
OPTION(BUILD_SHARED_LIBS "Build apiai as a shared library." ON)
OPTION(BUILD_STATIC_LIBS "Build apiai as a static library." OFF)

SET(CMAKE_BUILD_TYPE Debug)

IF(NOT WIN32)
    IF(NOT CMAKE_BUILD_TYPE)
        SET(CMAKE_BUILD_TYPE Release CACHE STRING
            "Choose the type of build, options are: None b Release RelWithDebInfo MinSizeRel Coverage."
            FORCE)
    ENDIF()
ENDIF()

#-fPIC used for 64-bit platforms (ubuntu 64 bit, for example)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

find_package(CURL REQUIRED)

if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIR})
else(CURL_FOUND)
    message(FATAL_ERROR "Could not find the CURL library and development files.")
endif(CURL_FOUND)

SET(LIB_SUFFIX "" CACHE STRING "Optional arch-dependent suffix for the library installation directory")

SET(RUNTIME_INSTALL_DIR bin
    CACHE PATH "Install dir for executables and dlls")
SET(ARCHIVE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}
    CACHE PATH "Install dir for static libraries")
SET(LIBRARY_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}
    CACHE PATH "Install dir for shared libraries")
SET(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include
    CACHE PATH "Install dir for headers")
SET(PACKAGE_INSTALL_DIR lib${LIB_SUFFIX}/cmake
    CACHE PATH "Install dir for cmake package config files")
MARK_AS_ADVANCED( RUNTIME_INSTALL_DIR ARCHIVE_INSTALL_DIR INCLUDE_INSTALL_DIR PACKAGE_INSTALL_DIR )

IF(APIAI_WITH_PKGCONFIG_SUPPORT)
        CONFIGURE_FILE(
                "pkg-config/apiai.pc.in"
                "pkg-config/apiai.pc"
                @ONLY)
        INSTALL(FILES "${CMAKE_BINARY_DIR}/pkg-config/apiai.pc"
                DESTINATION "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/pkgconfig")
ENDIF()

include_directories(third_party/cJSON)

add_library(cJson STATIC third_party/cJSON/cJSON.c)

add_subdirectory(indent_stream)

add_subdirectory(apiai)

add_subdirectory(examples)
add_subdirectory(tests)
