#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int unique_symbols(char *key, char *symbols);
int str_comp(char *str1, char *str2, int left1, int left2, int n);

int main(int argc, char **argv)
{
	if(argc != 4) {
		cout << "Usage: avtogen string_to_search name_of_file_with_string name_of_resulting_c_prog" << endl;
		return -1;
	}
	
	char key[256],
		 key4comp[256],
		 filename[256],
		 progname[256],
		 symbols[256];

	int i=0, j=0, k=0, s, maxi, len, len1;

	strcpy(key, argv[1]); //Stroka dlya poiska
	strcpy(filename, argv[2]); //imya fayla s simvolami (XXX.txt)
	strcpy(progname, argv[3]); //imya fayla gotovoy programmi (XXX.c)
 
	ofstream fout;
	fout.open(progname);
	fout << "//"
		 << key
		 << "\n#include <stdio.h>\nint main()\n{\n\tchar ch;\n\tint sost=0;\n\tint count=0;\n\tFILE *fp=fopen(\""
		 << filename
		 << "\", \"r\");\n\tif(!fp) {printf(\"file not opened\\n\"); return 1;}\n\twhile(fscanf(fp, \"\%c\", &ch)==1)\n\t{\n";

/**********************************************************************/
	len  = strlen(key);
	s = unique_symbols(key, symbols);
	
	for (i = 0; i < len; i++)
	{
		strcpy(key4comp, key);
		len1 = i+1;
		for (j = 0; j < s; j++)
		{
			key4comp[i] = symbols[j];
			
			maxi = 0;
			for (k = 1; k < len1; k++)
			{
				if (str_comp(key, key4comp, 0, len1-k, k) == 1)
					maxi = k;
			}
			
			if(symbols[j] != key[i])
			{
				if (maxi != 0)
				{
					fout << "\t\t";
					if(i != 0) fout << "else ";
					fout << "if(sost==" << i << " && ch==\'" << symbols[j] << "\') sost=" << maxi << "; // *****\n";
				}
			}
			else
			{
				fout << "\t\t";
				if(i != 0) fout << "else ";
				if (i < len - 1) ///не самый последний символ
				{
					fout << "if(sost==" << i << " && ch==\'" << key[i] << "\') sost++;\n";
				}
				else ///самый последний символ
				{
					fout << "if(sost==" << i << " && ch==\'" << key[i] << "\') {sost=" << maxi << "; count++;}\n";
				}
			}
		}
	}
/***********************************************************************/

	if (len > 1) fout << "\t\telse sost=0;\n\t}\n";
	fout << "\tprintf(\""
			 << progname
			 << " found \%d entries of string \\\""
			 << key
			 << "\\\" in "
			 << filename
			 << " \\n\", count);\n\treturn 0;\n}";
	fout.close();
	cout << "created " << progname << endl;
	return 0;
}

int unique_symbols(char *key, char *symbols)
{
	int i, j, s=0, flag;
	for (i = 0; key[i]; i++)
	{
		flag=1;
		for (j = 0; j < i; j++)
			if (key[j] == key[i])
				flag=0;

		if (flag==1)
		{
			symbols[s]=key[i];
			s++; 
		}
	}
	return s;
}

int str_comp(char *str1, char *str2, int left1, int left2, int n)
{
	for (int i = 0; i < n; i++)
	if (str1[left1+i] != str2[left2+i]) return 0;
	return 1;
}
