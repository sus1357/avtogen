# avtogen.c
Generates C code of predefined substring searcher based on finite-state machine single-pass algo

Description: Imagine that you have to find how many times ```str1 = 'aba'``` substring entries in ``` str2 = 'aabababb' ```.
<br>
Simple algorithm comparing every substring of the ```str2``` with ```str1``` will find two entries (on 2nd and 4th positions, notice that they are interlocked), but in ```O(length_of_str1 * length_of_str2)```.

One more example of string (in test.txt):
```
abacabacababacaba
*   *     *
```
- Here we have 3 entries of ```'abacaba'``` substring (* to find them)

- Notice that this string can be interlocked with itself in two ways:
```
abacab-a-bacaba
```
or
```
abac-aba-caba
```

To create a single-pass algorithm which works with interlocking substrings you can use the ideology of finite-state machine: while moving through string you store how many symbols of the substring do already match (=state of the machine), and with each new symbol you recalculate that value.


Example of usage:
1) Create C file (abba_finder.c) for finding ```'ABBA'``` string

```
g++ avtogen.c -o avtogen
./avtogen ABBA abba_finder.c
```
2) Run abba_finder with text file including some kind of string, and it will output the amount of ```'ABBA'``` entries 
```
g++ abba_finder.c -o abba_finder
./abba_finder abba_test.txt
```

Example of an output C file for ```'aba'```:
```C
// searches for string 'aba'
#include <stdio.h>
int main(int argc, char **argv) {
	int state=0, count=0;
	char ch;
	FILE *fp=NULL;
	fp=fopen(argv[1], "r");
	if(!fp) {printf("file not opened\n"); return 2;}
	while(fscanf(fp, "%c", &ch)) {
		if(state==0 && ch=='a') state++;
		else if(state==1 && ch=='a') state=1;
		else if(state==1 && ch=='b') state++;
		else if(state==2 && ch=='a') {state=1; count++;}
		else state=0;
	}
	printf("found %d entries of string \"aba\" in %s\n", count, argv[1]);
	return 0;
}
```
