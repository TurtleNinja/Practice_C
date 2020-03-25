/*
    Phi test is used to determine if a cipher texted is encrypted
    by monoalphabetic encryption
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define NUM_LETTERS 26
#define SIMPLE_SUBSTITUTION_IOC 0.066
#define HOMOPHONIC_IOC 0.038

// get the frequency of each charater
int* get_freq(char* file)
{
    char *tmp = malloc(10 * sizeof(char));
    FILE *input_file = fopen(file, "r");
    int* freq = calloc(NUM_LETTERS, sizeof(int));
    char c;
    
    // get frequencies of each character
    while((c = fgetc(input_file)) != EOF)
    {
        if (isalpha(c))
        {
            freq[tolower(c) - 'a']++;
        }
    }
    
    free(tmp);
    
    return freq;
    
}

// calculate the index of coincidences (ioc) of a given string
double calc_ioc(char* file_name)
{
    int chars_count = 0;
    double ioc = 0;
    
    int* freq_table = get_freq(file_name);
    
    //calculate the total numbers of alphabetic characters
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        chars_count += freq_table[i];
        printf("Letter %c appeared %d times\n", 'a' + i, freq_table[i]);
    }
    
    //calculate the ioc
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        double numerator = (double) freq_table[i];
        double denominator = (double) chars_count;
        
        ioc += (numerator / denominator) * ((numerator-1) / (denominator-1));
    }
    
    return ioc;
}


/*
int main(void)
{
    
    char* file = malloc(100 * sizeof(char));
    double ioc;     //index of coincidences (ioc)
    double estimated_key_length;
    
    // calculate the ioc of the ciphered text from a file
    printf("Enter the file containing ciphered text: ");
    scanf("%s", file);
    ioc = calc_ioc(file);
    //estimated_key_length = estimate_key_length(file);
    
    // determine the kind of cipher
    if (fabs(ioc - SIMPLE_SUBSTITUTION_IOC) > fabs(ioc - HOMOPHONIC_IOC))
    {
        printf("%.3f - homophonic substitution\n", ioc);
    }
    else
    {
        printf("%.3f - monoalphabetic substitution\n", ioc);
    }
    
}
*/
