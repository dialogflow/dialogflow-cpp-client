
set( CMAKE_C_FLAGS "-Wall" )

include_directories(../indent_stream)

set(SRCS)

file (GLOB ALL_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *.cpp
    query/*.cpp
    query/**/*.cpp
    JSON/*.cpp
    http/*.cpp
    io/*.cpp
    io/**/*.cpp
)

SET( APIAI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} )

file (GLOB IO_TESTS_SOUNDS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
   io/tests/sounds/*.wav)

set(SRCS ${SRCS} ${ALL_SOURCES} ${IO_TESTS_SOUNDS})

set(PUBLIC_HEADERS
    ${APIAI_INCLUDE_DIR}/http/Request.h
    ${APIAI_INCLUDE_DIR}/JSON/JSONException.h
    ${APIAI_INCLUDE_DIR}/AI.h
    ${APIAI_INCLUDE_DIR}/Credentials.h
    ${APIAI_INCLUDE_DIR}/Exception.h
    ${APIAI_INCLUDE_DIR}/Service.h

    ${APIAI_INCLUDE_DIR}/query/QueryRequest.h
    ${APIAI_INCLUDE_DIR}/query/TextQueryRequest.h

    ${APIAI_INCLUDE_DIR}/query/request/Entity.h
    ${APIAI_INCLUDE_DIR}/query/request/Parameters.h
    ${APIAI_INCLUDE_DIR}/query/request/QueryText.h
    ${APIAI_INCLUDE_DIR}/query/request/RequestContext.h

    ${APIAI_INCLUDE_DIR}/query/response/Context.h
    ${APIAI_INCLUDE_DIR}/query/response/Fulfillment.h
    ${APIAI_INCLUDE_DIR}/query/response/Metadata.h
    ${APIAI_INCLUDE_DIR}/query/response/Response.h
    ${APIAI_INCLUDE_DIR}/query/response/Result.h

    ${APIAI_INCLUDE_DIR}/io/Stream.h
    ${APIAI_INCLUDE_DIR}/io/StreamReader.h
    ${APIAI_INCLUDE_DIR}/io/StreamWriter.h
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

#target_link_libraries(demo json_library)
#target_link_libraries(demo indent_stream_library)
#target_link_libraries(demo http_library)
#target_link_libraries(demo cJson)
#target_link_libraries(demo curl)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/io/tests/sounds/sound1.wav ${CMAKE_CURRENT_BINARY_DIR}/io/tests/sounds/sound1.wav COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/io/tests/sounds/sound2.wav ${CMAKE_CURRENT_BINARY_DIR}/io/tests/sounds/sound2.wav COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/io/tests/sounds/speech_d.wav ${CMAKE_CURRENT_BINARY_DIR}/io/tests/sounds/speech_d.wav COPYONLY)
#>>>>>>> a9fb4855a4f3d31ccc1084ed9b4a9b24e3ca69b9
