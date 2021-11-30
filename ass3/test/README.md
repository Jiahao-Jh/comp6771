I decided to separate my test into 5 file.

In graph_test_constructor.cpp, I tested different constructor and rule of 5.
In graph_test_other.cpp, I tested Extractor and Comparisons.
Other files' contents is consistent to their name.

In graph_test_constructor.cpp, I used is_node, empty and is_connected to test the correctness of the content most of the time.
In iterator tests, I used * oprator most of the time to verify the content.
In all other tests, I used weight and vector to check the content.
These methods are the easiest way to get access to the inner data so that i can verify if the result is correct. Therefore there are less chance that they have bug.