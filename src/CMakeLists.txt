set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c99")

add_library(solinterp SHARED
	tables.c
	symmetries.c
	)

target_link_libraries(solinterp
	m
	)

install(TARGETS solinterp
	LIBRARY DESTINATION lib
	)
