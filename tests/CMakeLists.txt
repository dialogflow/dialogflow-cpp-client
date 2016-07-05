find_package (Boost COMPONENTS unit_test_framework)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../apiai/src)

find_package (Threads)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    file(GLOB TESTS_SRCS *.cpp *.h **/*.cpp **/*.h)

    add_executable(streams_test ${TESTS_SRCS})

    target_link_libraries (streams_test ${Boost_LIBRARIES})

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/sounds/sound1.wav ${CMAKE_CURRENT_BINARY_DIR}/io/sounds/sound1.wav COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/sounds/sound2.wav ${CMAKE_CURRENT_BINARY_DIR}/io/sounds/sound2.wav COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/sounds/speech_d.wav ${CMAKE_CURRENT_BINARY_DIR}/io/sounds/speech_d.wav COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/sounds/count-hammer.raw ${CMAKE_CURRENT_BINARY_DIR}/vad/sounds/count-hammer.raw COPYONLY)

    if(BUILD_SHARED_LIBS)
        target_link_libraries(streams_test apiai)
    else(BUILD_SHARED_LIBS)
        target_link_libraries(streams_test apiai_static)
    endif()

    add_test(streams_test streams_test)

    target_link_libraries (streams_test ${CMAKE_THREAD_LIBS_INIT})
elseif(Boost_FOUND)
    message(WARNING "Not found BOOST with components `unit_test_framework`. Test could not be compiled. It will be passed.")
endif(Boost_FOUND)
