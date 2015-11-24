file(GLOB HTTP_SOURCES
    "*.cpp"
)

file(GLOB HTTP_HEADERS
    "*.h"
)

#set( CMAKE_CXX_FLAGS "-Wall -std=c++11" )

#add_library(http_library STATIC ${HTTP_SOURCES} ${HTTP_HEADERS})
add_library(http_library ${HTTP_SOURCES} ${HTTP_HEADERS})
