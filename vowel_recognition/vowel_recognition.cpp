//this program is to recognise the vowels using the reference files that are generated by reference_generation.cpp
#include "stdafx.h"
#include "utils.h"

const char* path = "../INPUT/";

char filepath[1000], file[1000], vowels[5] = {'a', 'e', 'i', 'o', 'u'}, filename[30];
double s[N], r[p+1], a[p+1], c[p+1], w[p] = {1.0, 3.0, 7.0, 13.0, 19.0, 22.0, 25.0, 33.0, 42.0, 50.0, 56.0, 61.0};
int size;

FILE *input, *input_n;


int _tmain(int argc, _TCHAR* argv[])
{
	//to iterate over all the files for all the vowels 
	for(int cnt=0; cnt<5; ++cnt){
		int Tcorrect = 0, Ecorrect = 0;
		char testfile[100];
		double C[11][5][p+1], avg_C[5][p+1] = {{0}};
		for(int filecnt=1; filecnt<=10; ++filecnt){
			double s[frame][N], r[frame][p+1] = {{0}}, a[frame][p+1] = {{0}}, c[frame][p+1] = {{0}};
			strcpy(filepath, path);
			sprintf(testfile, "%c/214101012_%c_%d.txt", vowels[cnt], vowels[cnt], filecnt + 10); // we are doing filecnt + 10 so as the take the next 10 files	
			strcat(filepath, testfile);
			fopen_s(&input, filepath, "r");
			fopen_s(&input_n, "normalized_input.txt", "w+");
			
			normalize_input(input, input_n); //normalizing and dc shifting the input
			rewind(input_n);
			skipFrames(input_n, s); // finding the stable 5 frames
			applyHamming(s); // applying hamming window

			calculateR(s, r); //calculating Ri's
			calculateA(r, a); //calculating Ai's using Ri's
			calculateC(r, a, c); //calculating Ci's

			fclose(input);
			fclose(input_n);


			//finding the distance (Tokhura's) from the reference and recognising the vowel
			double TDistance = DBL_MAX, EDistance = DBL_MAX;
			char Tvowel, Evowel;
			for(int i=0; i<5; ++i){
				strcpy(filepath, path);
				sprintf(filename, "reference/%c.txt", vowels[i]);
				strcat(filepath, filename);
				fopen_s(&input, filepath, "r");
				double distance = tokhuraDistance(c, w, input);
				if(TDistance > distance){
					TDistance = distance;
					Tvowel = vowels[i];
				}
			}

			fclose(input);


			//finding the distance (Euclidian) fromm all the vowels
			for(int i=0; i<5; ++i){
				strcpy(filepath, path);
				sprintf(filename, "reference/%c.txt", vowels[i]);
				strcat(filepath, filename);
				fopen_s(&input, filepath, "r");
				double distance = euclidianDistance(c, input);
				if(EDistance > distance){
					EDistance = distance;
					Evowel = vowels[i];
				}
			}

			//printing out the result obtaing
			printf("ACTUAL: %c | PREDICTED TOKURA: %c | TOKHURA: %lf | PREDICTED EUDLIDIAN: %c | EUCLIDIAN: %lf\n", vowels[cnt], Tvowel, TDistance, Evowel, EDistance);
			if(vowels[cnt] == Tvowel) Tcorrect++;
			if(vowels[cnt] == Evowel) Ecorrect++;
		}
		printf("---------------------------\n");
		printf("ACCURACY TOKURA: %lf\n", (Tcorrect/10.0)*100);
		printf("ACCURACY EUCLIDIAN: %lf\n", (Ecorrect/10.0)*100);
		printf("---------------------------\n");
	}
}
