
set( CMAKE_C_FLAGS "-Wall" )
#set( CMAKE_CXX_FLAGS "-Wall -std=c++11" )

add_subdirectory(http)
add_subdirectory(indent_stream)
add_subdirectory(JSON)

file (GLOB SRCS *.cpp *.h *.hpp *.c)

file (GLOB QUERY_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  query/*.cpp query/response/*.cpp query/request/*.cpp)

set(SRCS ${SRCS} ${QUERY_SOURCES})

include_directories(indent_stream)

add_executable ( demo ${SRCS})

target_link_libraries(demo json_library)
target_link_libraries(demo indent_stream_library)
target_link_libraries(demo http_library)
target_link_libraries(demo cJson)
target_link_libraries(demo curl)
