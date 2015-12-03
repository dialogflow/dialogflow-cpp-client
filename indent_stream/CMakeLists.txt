file(GLOB INDENT_STREAM_SOURCES
    "*.cpp"
)

file(GLOB INDENT_STREAM_HEADERS
    "*.h"
)

add_library(indent_stream_library STATIC ${INDENT_STREAM_SOURCES} ${INDENT_STREAM_HEADERS})
