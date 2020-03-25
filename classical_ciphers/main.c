
#include <stdio.h>
#include <stdlib.h>

#include "encrypt.h"
#include "decrypt.h"

/*************************** MAIN ***************************/

int main(void)
{
    char cipher_text_file_name[50] = {0};
    char plain_text_file_name[50] = {0}; //calloc(100, sizeof(char));


    
    /****   START ENCRYPTING    ****/
    // prompt the file containing plain text
    printf("Enter name of the plain text file: ");
    scanf("%s", plain_text_file_name);

    // encrypt the plain text
    // output is a file, name is the plain text file name appended with encr in front
    encrypt(plain_text_file_name, VIGENERE_CIPHER);
    
    
    /****   START DECRYPTING    ****/
    // obtain the cipher text file name
    sprintf(cipher_text_file_name, "encr-%s", plain_text_file_name);
    
    printf("%s\n", cipher_text_file_name);
    
    decrypt(cipher_text_file_name);
    
    
    // end program
    return 0;
}


