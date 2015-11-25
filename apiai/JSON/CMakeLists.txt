file(GLOB JSON_SOURCES
    "*.cpp"
)

file(GLOB JSON_HEADERS
    "*.h"
)

add_library(json_library ${JSON_SOURCES} ${JSON_HEADERS})
target_link_libraries(json_library cJson)
