cxx_library(
	TARGET test_main
	FILENAME test_main.cpp
	LINK Catch2::Catch2
)

add_subdirectory(graph)
