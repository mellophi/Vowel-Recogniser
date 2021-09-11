//this program is to generate the reference file for using which we have to test
#include "stdafx.h"
#include "utils.h"

const char* path = "../INPUT/";

char filepath[1000], file[1000], vowels[5] = {'a', 'e', 'i', 'o', 'u'}, filename[30];
double s[N], r[p+1], a[p+1], c[p+1];
int size;

FILE *input, *output_r, *output_a, *output_c, *input_n;


int _tmain(int argc, _TCHAR* argv[])
{
	//for reference generation
	for(int cnt=0; cnt<5; ++cnt){
		double C[11][5][p+1], avg_C[5][p+1] = {{0}};
		for(int filecnt=1; filecnt<=10; ++filecnt){

			double s[frame][N], r[frame][p+1] = {{0}}, a[frame][p+1] = {{0}}, c[frame][p+1] = {{0}};

			strcpy(filepath, path);
			sprintf(filename, "%c/214101012_%c_%d.txt", vowels[cnt], vowels[cnt], filecnt);	// starting from filecnt 1 for generation of reference file
			strcat(filepath, filename);
			fopen_s(&input, filepath, "r");
			fopen_s(&input_n, "normalized_input.txt", "w+");
			
			normalize_input(input, input_n); // normalizing and dc shifting the input
			rewind(input_n);
			skipFrames(input_n, s); // finding the stable frames
			applyHamming(s); // applying the hamming window on the stable frames

			calculateR(s, r); // calculating Ri's 
			calculateA(r, a); // calcualting Ai's
			calculateC(r, a, c); // calculating Ci's

			// saving the ci's for a perticular file in a bigger matrix to facilitate the average ci's calculation
			// and generation of reference file
			for(int i=0; i<frame; ++i){
				for(int j=0; j<=p; ++j){
					C[filecnt][i][j] = c[i][j];
				}
			}

			
			fclose(input);
			fclose(input_n);
		}
		 
		//finding the average ci's and saving it in another matrix named avg_c
		for(int i=0; i<frame; ++i){
			for(int j=0; j<=p; ++j){
				double sum = 0;
				for(int filecnt=1; filecnt<=10; ++filecnt){
					avg_C[i][j] += C[filecnt][i][j];
				}

				avg_C[i][j] /= 10.0;
				printf("Average C for frame %d is %lf\n", i, avg_C[i][j]);

			}
		}

		// saving the average ci's in a file in the path ../INPUT/reference
		strcpy(filepath, path);
		sprintf(filename, "reference/%c.txt", vowels[cnt]);
		strcat(filepath, filename);
		printf("%s\n", filepath);
		fopen_s(&output_c, filepath, "w+");
		for(int i=0; i<frame; ++i){
			for(int j=0; j<p; ++j){
				fprintf(output_c, "%lf,", avg_C[i][j]);
			}
			fprintf(output_c, "%lf\n", avg_C[i][p]);
		}
		fclose(output_c);
	}
}

