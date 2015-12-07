INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../apiai/src)

add_executable(text_request_example text_request.cpp)
add_executable(voice_file_request_example voice_file_request.cpp)

file(GLOB TEST_FILES *.txt)

install (FILES ${TEST_FILES} DESTINATION ${RUNTIME_INSTALL_DIR})

if(BUILD_SHARED_LIBS)
    target_link_libraries(text_request_example apiai)
    target_link_libraries(voice_file_request_example apiai)
else(BUILD_SHARED_LIBS)
    target_link_libraries(text_request_example apiai_static)
    target_link_libraries(voice_file_request_example apiai_static)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test.txt ${CMAKE_CURRENT_BINARY_DIR}/test.txt COPYONLY)
