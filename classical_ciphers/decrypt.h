
#ifndef polyalphabetic_analysis_h
#define polyalphabetic_analysis_h

#include <stdio.h>

#define NUM_LETTERS             26
#define SIMPLE_SUBSTITUTION_IOC 0.066
#define HOMOPHONIC_CIPHER_IOC   0.038
#define dprint(expr)    printf(#expr " = %d\n", expr)   //debugging print macro

void decrypt(char *cipher_file_name);
double get_key_length(double ioc, int chars_count);
double calc_ioc(int chars_count, int* freq_table);
void get_freq(FILE* file, int *frequencies, int *len);

#endif /* polyalphabetic_analysis_h */
