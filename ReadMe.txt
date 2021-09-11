===================================
INSTRUCTIONS TO RUN THE APPLICATION
===================================

Pre-requisites:
Make sure the following are present:
1. INPUT folder
2. vowel_recognition.cpp
3. reference_generation.cpp
4. utils.h

Follow the below steps to run the program:
1. Run the reference_generation.cpp to generate the references with which the next 10 files will be tested.
2. Find if the references are created in the INPUT/references directory.
3. Run the vowel_recognition.cpp file to test the files.

N.B.
When running the reference_generation.cpp file exclude the other file from the project, do the same for the other file also.
By default there will be some output reference files created. If you want to check if the recognition work you can use them
also instead of generating files again.

For verification there is a program verification.cpp which is to verify weather the logic for ri, ai and ci calculation is 
correct or not. Dump files are created in the same directory and the test dump files are present in INPUT/test_files directory.