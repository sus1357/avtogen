#include <stdio.h>
#include <string.h>
#define MAX_LEN 256
int unique_symbols(char *key, char *symbols);
int str_comp(char *str1, char *str2, int ind1, int ind2, int n);

int main(int argc, char **argv) {
	FILE *fout=NULL;
	char key[MAX_LEN],
		 key4comp[MAX_LEN],
		 progname[32],
		 symbols[256];
	int i=0, j=0, k=0, n_uniq_symb, max_match, key_len, substr_len;
	if(argc != 3) {
		printf("Usage: avtogen string_to_search name_of_output_c_prog\n");
		return -1;
	}

	strcpy(key, argv[1]);		//String for search
	strcpy(progname, argv[2]);	//Name of output C file
	//
	fout = fopen(progname, "w");
	fprintf(fout, "%s%s%s%s%s%s%s%s%s",
			"// searches for string \'", key, "\'",
			"\n#include <stdio.h>",
			"\nint main(int argc, char **argv) {",
			"\n\tint state=0, count=0;\n\tchar ch;",
			"\n\tFILE *fp=NULL;\n\tfp=fopen(argv[1], \"r\");",
			"\n\tif(!fp) {printf(\"file not opened\\n\"); return 2;}",
			"\n\twhile(fscanf(fp, \"%c\", &ch)==1) {\n"
			);
	// main algo
	key_len  = strlen(key);
	n_uniq_symb = unique_symbols(key, symbols);

	for (i = 0; i < key_len; i++) {
		strcpy(key4comp, key);
		substr_len = i+1;
		for (j = 0; j < n_uniq_symb; j++) {
			key4comp[i] = symbols[j];

			max_match = 0;
			for (k = 1; k < substr_len; k++) {
				if (str_comp(key, key4comp, 0, substr_len-k, k))
					max_match = k;
			}

			if(symbols[j] != key[i]) {
				if (max_match != 0) { // 'aba' case
					fprintf(fout, "\t\t");
					if(i != 0) fprintf(fout, "else ");
					fprintf(fout, "%s%d%s%c%s%d%s", "if(state==", i,
													" && ch==\'", symbols[j],
													"\') state=", max_match,
													";\n"); 
				}
			}
			else {
				fprintf(fout, "\t\t");
				if(i != 0) fprintf(fout, "else ");
				if (i < key_len - 1) {
					fprintf(fout, "%s%d%s%c%s", "if(state==", i,
												" && ch==\'", key[i],
												"\') state++;\n");
				}
				else { // last symbol of key
					fprintf(fout, "%s%d%s%c%s%d%s", "if(state==", i,
													" && ch==\'", key[i],
													"\') {state=", max_match,
													"; count++;}\n");
				}
			}
		}
	}
	if (key_len > 1) fprintf(fout, "\t\telse state=0;\n\t}\n");
	//
	fprintf(fout, "%s%s%s", "\tprintf(\"found %d entries of string \\\"", key,
							"\\\" in %s\\n\", count, argv[1]);\n\treturn 0;\n}");
	fclose(fout);
	printf("created %s\n", progname);
	return 0;
}

int unique_symbols(char *key, char *symbols) {
	// example: key = "abacadacaba" --> symbols = "abcd" (unique symbols of key string only)
	int i, j, n_uniq_symb=0, flag;
	for (i = 0; key[i]; i++) {
		flag=1;
		for (j = 0; j < i; j++)
			if (key[j] == key[i]) {
				flag=0;
			}
		if (flag) {
			symbols[n_uniq_symb]=key[i];
			n_uniq_symb++;
		}
	}
	return n_uniq_symb;
}

int str_comp(char *str1, char *str2, int ind1, int ind2, int n) {
	// custom string comparing func
	for (int i = 0; i < n; i++)
	if (str1[ind1+i] != str2[ind2+i]) return 0;
	return 1;
}
