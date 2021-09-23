project(long-alg)

set(HEADER_FILES
        big_integer.h
        )

set(SOURCE_FILES
        big_integer.cpp
        )

add_library(long-alg_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})