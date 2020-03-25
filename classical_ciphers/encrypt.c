#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>


#include "encrypt.h"

/***********************************************************/

// encrypt all alphabetic characters
// write the cipher text to a file; return the file name
void encrypt(char *plain_text_file_name, int code)
{
    
    // open the plain text file
    FILE *plain_text_file = fopen(plain_text_file_name, "r");
    if (!plain_text_file)
    {
        printf("Abort. Cannot open plain text file.\n");
        exit(1);
    }
    
    // get cipher file's name
    char *cipher_file_name = malloc(100 * sizeof(char));
    memset(cipher_file_name, 0, 100 * sizeof(char));
    sprintf(cipher_file_name, "encr-%s", plain_text_file_name);
    
    // open file to write cipher text
    FILE *cipher_text_file = fopen(cipher_file_name, "w");
    if (!cipher_text_file)
    {
        printf("Cannot open file to write cipher text\n");
        exit(1);
    }
    
    
    // choose the suitable encryption method
    switch(code)
    {
        case SIMPLE_SUBSTITUTION: sscipher(plain_text_file, cipher_text_file);
            break;
        
        case VIGENERE_CIPHER:
            vigenere_cipher(plain_text_file, cipher_text_file);
            break;
            
        default: printf("Invalid encryption method\n");
    }
    
    
    // close file before exiting
    fclose(plain_text_file);
    fclose(cipher_text_file);
}

/***********************************************************/

// encrypt a plain text using simple substitution with random generated key
void sscipher(FILE *plain_text_file, FILE *cipher_text_file)
{
    int key = rand(); // generate a random key for the substitution
    
    char c, new_c;
    // substitute alphabetical characters
    while ((c = fgetc(plain_text_file)) != EOF)
    {
        if (isalpha(c))
        {
            new_c = 'a' + ((tolower(c) - 'a' + key) % NUM_LETTERS);
            fputc(new_c, cipher_text_file);
        }
        else
        {
            fputc(c, cipher_text_file);
        }
    }
}


/***********************************************************/
// encrypt a plain text using simple substitution with key user provided
void vigenere_cipher(FILE *plain_text, FILE *cipher_text)
{
    // obtain the key
    char *key = calloc(100, sizeof(char));
    printf("Please input the key phrase: ");
    scanf("%s", key);   //--> buffer overflow
    int key_len = strlen(key);
    
    
    // substitute alphabetical characters
    int i = 0;
    char c, new_c;
    while ((c = fgetc(plain_text)) != EOF)
    {
        if (isalpha(c))
        {
            new_c = 'A' + ((tolower(c) - 'a' + tolower(key[i]) - 'a' +1) % NUM_LETTERS);
            i = (i + 1) % key_len;
            fputc(new_c, cipher_text);
        }
        else
        {
            fputc(c, cipher_text);
        }
    }
}
