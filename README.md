# avtogen.cpp
generates c code of predefined substring searcher based on finite-state machine single-pass algo

Example of string (in abba_test.txt):

ABBA__ABBAAAABBBAAABBBABBABBABBABAAB
*///  *///            *//*//*///
1     2               3  4  5

here we have 5 entries of "ABBA" substring

Example of usage:

g++ avtogen.cpp -o avtogen
./avtogen ABBA abba_test.txt abba_finder.c
g++ abba_finder.c -o abba_finder
./abba_finder
