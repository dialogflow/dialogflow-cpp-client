file(GLOB TESTS_SRCS *.cpp *.h **/*.cpp **/*.h)

add_executable(streams_test ${TESTS_SRCS})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/sounds/sound1.wav ${CMAKE_CURRENT_BINARY_DIR}/io/tests/sounds/sound1.wav COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/sounds/sound2.wav ${CMAKE_CURRENT_BINARY_DIR}/io/tests/sounds/sound2.wav COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/sounds/speech_d.wav ${CMAKE_CURRENT_BINARY_DIR}/io/tests/sounds/speech_d.wav COPYONLY)

if(BUILD_SHARED_LIBS)
    target_link_libraries(streams_test apiai)
else(BUILD_SHARED_LIBS)
    target_link_libraries(streams_test apiai_static)
endif()

add_test(streams_test streams_test)
