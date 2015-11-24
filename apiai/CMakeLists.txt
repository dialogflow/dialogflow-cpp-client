
set( CMAKE_C_FLAGS "-Wall" )
#set( CMAKE_CXX_FLAGS "-Wall -std=c++11" )

add_subdirectory(http)
add_subdirectory(query)

file (GLOB SRCS *.cpp *.h *.hpp *.c)

add_executable ( demo ${SRCS} ${QUERY_SOURCE})

target_link_libraries(demo query_library)
target_link_libraries(demo http_library)
target_link_libraries(demo json)
target_link_libraries(demo curl)
