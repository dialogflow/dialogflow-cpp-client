file(GLOB_RECURSE SOURCES *.hpp *.cpp *.h *.c)

set(SOURCES ${SOURCES} PARENT_SCOPE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
