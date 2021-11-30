cxx_test(TARGET euclidean_vector_test1 FILENAME "euclidean_vector_test1.cpp" LINK euclidean_vector)

   cxx_test(TARGET euclidean_vector_test_constructor_and_member_function FILENAME
            "euclidean_vector_test_constructor_and_member_function.cpp" LINK euclidean_vector)

      cxx_test(TARGET euclidean_vector_test_operations FILENAME "euclidean_vector_test_operations."
                                                                "cpp" LINK euclidean_vector)

         cxx_test(TARGET euclidean_vector_test_frineds FILENAME "euclidean_vector_test_frineds."
                                                                "cpp" LINK euclidean_vector)

            cxx_test(TARGET euclidean_vector_test_utility FILENAME "euclidean_vector_test_utility."
                                                                   "cpp" LINK euclidean_vector)
