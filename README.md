# avtogen.cpp
generates c code of predefined substring searcher based on finite-state machine single-pass algo

Example of string (in abba_test.txt):

ABBA__ABBAAAABBBAAABBBABBABBABBABAAB

here we have 5 entries of "ABBA" substring
Notice that "ABBABBABBA" = 3 concatenated "ABBA" substrings

Example of usage:

```
g++ avtogen.cpp -o avtogen
./avtogen ABBA abba_test.txt abba_finder.c
g++ abba_finder.c -o abba_finder
./abba_finder
```
