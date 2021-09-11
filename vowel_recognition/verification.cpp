// this program is writting to verify weather the logic for out ri, ai and ci calculation is correct or not
#include "stdafx.h"
#include "utils.h"

const char* path = "../INPUT/test_files/";

char filepath[1000], file[1000];
double s[N], r[p+1], a[p+1], c[p+1];
int size;

FILE *input, *output_r, *output_a, *output_c;

int _tmain(int argc, _TCHAR* argv[])
{
	strcpy(filepath, path);
	strcat(filepath, "test.txt");
	fopen_s(&input, filepath, "r");
	fopen_s(&output_r, "dump_Ri_test.txt", "w+");
	fopen_s(&output_a, "dump_Ai_test.txt", "w+");
	fopen_s(&output_c, "dump_Ci_test.txt", "w+");
	char singleLine[100];
	
	size = 0;

	while(!feof(input)){
		fgets(singleLine, 100, input);
		if(!isalpha(singleLine[0]))
			s[size++] = atof(singleLine);
	}

	calculateR(s, output_r, r);
	calculateA(r, output_a, a);
	calculateC(r[0], a, output_c, c);

	printf("dump files are generated for verification with the test dump given\n");
	
	fclose(input);
	fclose(output_r);
	fclose(output_a);
	fclose(output_c);
	return 0;
}

