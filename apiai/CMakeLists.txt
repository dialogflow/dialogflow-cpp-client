/**
 * Copyright 2017 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


set( CMAKE_C_FLAGS "-Wall" )

add_subdirectory(src)

include_directories(../indent_stream)

set(SRCS)

set(ALL_SOURCES ${SOURCES})

SET( APIAI_INCLUDE_DIR include )

file (GLOB IO_TESTS_SOUNDS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
   io/tests/sounds/*.wav)

set(SRCS ${SRCS} ${ALL_SOURCES} ${IO_TESTS_SOUNDS})

file(GLOB_RECURSE PUBLIC_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/
    include/*.h
)

SOURCE_GROUP( "Public API" FILES ${PUBLIC_HEADERS} )

set(SRCS ${SRCS} ${ALL_SOURCES})

INSTALL(
        DIRECTORY ${APIAI_INCLUDE_DIR}/
        DESTINATION ${INCLUDE_INSTALL_DIR}/apiai
        FILES_MATCHING
            PATTERN "*.h"
#            ${PUBLIC_HEADERS}
#            PATTERN ".svn" EXCLUDE
#        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

IF(APIAI_WITH_CMAKE_PACKAGE)
    SET(INSTALL_EXPORT EXPORT apiai)
ELSE(APIAI_WITH_CMAKE_PACKAGE)
    SET(INSTALL_EXPORT)
ENDIF()

if(BUILD_SHARED_LIBS)
    add_library(apiai SHARED ${PUBLIC_HEADERS} ${SRCS})

    target_link_libraries(apiai indent_stream_library)
    target_link_libraries(apiai cJson)
    target_link_libraries(apiai curl)

    install( TARGETS apiai ${INSTALL_EXPORT}
             RUNTIME DESTINATION ${RUNTIME_INSTALL_DIR}
             LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR}
             ARCHIVE DESTINATION ${ARCHIVE_INSTALL_DIR})

    if(NOT CMAKE_VERSION VERSION_LESS 2.8.11)
        target_include_directories( apiai PUBLIC
                                   $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}>
                                   $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/${APIAI_INCLUDE_DIR}>)
    endif()
endif(BUILD_SHARED_LIBS)

if(BUILD_STATIC_LIBS)
    add_library(apiai_static STATIC ${PUBLIC_HEADERS} ${SRCS})

    target_link_libraries(apiai_static indent_stream_library)
    target_link_libraries(apiai_static cJson)
    target_link_libraries(apiai_static curl)

    install( TARGETS apiai_static ${INSTALL_EXPORT}
             RUNTIME DESTINATION ${RUNTIME_INSTALL_DIR}
             LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR}
             ARCHIVE DESTINATION ${ARCHIVE_INSTALL_DIR})

    if(NOT CMAKE_VERSION VERSION_LESS 2.8.11)
        target_include_directories( apiai_static PUBLIC
                                   $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}>
                                   $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/${APIAI_INCLUDE_DIR}>)
    endif()
endif(BUILD_STATIC_LIBS)
