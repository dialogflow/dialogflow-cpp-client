add_executable(text_request_example text_request.cpp)

if(BUILD_SHARED_LIBS)
    target_link_libraries(text_request_example apiai)
else(BUILD_SHARED_LIBS)
    target_link_libraries(text_request_example apiai_static)
endif()
