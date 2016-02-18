set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c99")

add_library(soli_tables SHARED
	tables.c
	)

install(TARGETS soli_tables
	LIBRARY DESTINATION lib)
