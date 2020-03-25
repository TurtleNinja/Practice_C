#ifndef encrypt_h
#define encrypt_h

#define     NUM_LETTERS             26
#define     SIMPLE_SUBSTITUTION     0
#define     VIGENERE_CIPHER       1
#define     dprint(expr)    printf(#expr " = %d\n", expr)   //debugging print


void encrypt(char* file_name, int method);
void sscipher(FILE *plain_text_file, FILE* cipher_text_file);
void vigenere_cipher(FILE *plain_text, FILE *cipher_text);

#endif /* encrypt_h */
