set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

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

add_executable(test_interpolation
	test_interpolation.c
	)
target_link_libraries(test_interpolation
	solinterp
	)

file(COPY ./ DESTINATION . FILES_MATCHING PATTERN "*.py")

add_subdirectory(resources)
