set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c99")

include_directories(
	${CMAKE_SOURCE_DIR}/src
	)

add_executable(test_tables
	test_tables.c
	)

target_link_libraries(test_tables
	solinterp
	)

add_executable(test_symmetries
	test_symmetries.c
	)

target_link_libraries(test_symmetries
	solinterp
	)

add_subdirectory(resources)
