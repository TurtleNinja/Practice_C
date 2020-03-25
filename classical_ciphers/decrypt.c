#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#include "decrypt.h"

/***********************************************************/

// get the frequencies of alphabetical charaters from a file
// return the number of alphabetic characters read from file
void get_freq(FILE* input_file, int *frequencies, int *len)
{
    int count_char = 0;
    char c;
    
    // get frequencies of each character
    while((c = fgetc(input_file)) != EOF)
    {
        if (isalpha(c))
        {
            count_char++;
            frequencies[tolower(c) - 'a']++;
        }
    }
    
    *len = count_char;
    dprint(*len);
}


/***********************************************************/

// calculate the index of coincidences (ioc) of a frequency table
double calc_ioc(int chars_count, int* freq_table)
{
    double ioc = 0.0;
    
    // ioc is 0 when the text contains less than 2 characters
    if (chars_count < 2)
    {
        printf("Cipher text is insufficient to calculate ioc\n");
        return ioc;
    }
    
    //calculate the ioc
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        if (freq_table[i] <= 1)
        {
            continue;
        }
        
        double numerator = (double) freq_table[i];
        double denominator = (double) chars_count;
        
        ioc += (numerator / denominator) * ((numerator - 1) / (denominator - 1));
        
        //printf("(%.3f / %.3f) * (%.3f / %.3f)\n", numerator, denominator, numerator - 1, denominator - 1);
    }
    
    return ioc;
}


/***********************************************************/

// accept the length of the cipher text and the index of coincidence
// return the estimated length of the key
double get_key_length(double ioc, int n)
{
    
    /*
     Formula calculating index of coincidence:
        ioc = ((n/l - 1) * 0.066 + (n - n/l) * 0.038) / (n-1)
     */
    dprint(n);
    printf("get_key_length ioc: %f\n", ioc);
    
    return ( (0.028 * n) / (ioc * (n - 1) - 0.038 * n + 0.066) );
    
}


void decrypt(char* cipher_text_file_name)
{
    // open the cipher text file
    FILE *cipher_text_file = fopen(cipher_text_file_name, "r");
    if (!cipher_text_file)
    {
        printf("Cannot open cipher text file\n");
        exit(1);
    }
    
    int *freq_table = calloc(NUM_LETTERS, sizeof(int));
    int text_len = 0;   // number of alphabetic characters in the cipher text
    double ioc;     // index of coincidences (ioc)
    double estimated_key_length = 1;    //the default cipher is simple substitution
    
    
    // get frequencies of all alphabetic characters
    // store number of characters read
    get_freq(cipher_text_file, freq_table, &text_len);
    
    // calculate the index of coincidence
    ioc = calc_ioc(text_len, freq_table);
    
    // determine the kind of cipher
    if (fabs(ioc - SIMPLE_SUBSTITUTION_IOC) > fabs(ioc - HOMOPHONIC_CIPHER_IOC))
    {
        printf("%.3f - homophonic substitution\n", ioc);
        estimated_key_length = get_key_length(ioc, text_len);
        printf("estimated key length is %.1f\n", estimated_key_length);
    }
    else
    {
        printf("%.3f - simple substitution\n", ioc);
    }
    
    
    free(freq_table);
    fclose(cipher_text_file);
}
