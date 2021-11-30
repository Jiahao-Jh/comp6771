configure_file("english.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("aaaaa.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

cxx_test(
   TARGET word_ladder_test_laddered
   FILENAME word_ladder_test_laddered.cpp
   LINK word_ladder lexicon Catch2::Catch2 test_main
)

cxx_test(
   TARGET word_ladder_test_sort
   FILENAME word_ladder_test_sort.cpp
   LINK word_ladder lexicon Catch2::Catch2 test_main
)

cxx_test(
   TARGET word_ladder_test_benchmark
   FILENAME word_ladder_test_benchmark.cpp
   LINK word_ladder lexicon Catch2::Catch2 test_main
)

cxx_test(
   TARGET word_ladder_test_different_lexcion
   FILENAME word_ladder_test_different_lexcion.cpp
   LINK word_ladder lexicon Catch2::Catch2 test_main
)

cxx_test(
   TARGET word_ladder_test_no_solution
   FILENAME word_ladder_test_no_solution.cpp
   LINK word_ladder lexicon Catch2::Catch2 test_main
)

cxx_test(
   TARGET word_ladder_test_size
   FILENAME word_ladder_test_size.cpp
   LINK word_ladder lexicon Catch2::Catch2 test_main
)
