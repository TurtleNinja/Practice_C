#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define     dprint(expr)          printf(#expr " = %d\n", expr)
#define     append_digit(n, d)    (n) * 10 + (d)

int main(void)
{
    char divident[7] = {0};
    char b[7] = {0};    // divisor
    
    // get input
    printf("Please enter the divisor: ");
    scanf("%s", b);
    printf("Please enter the divident: ");
    scanf("%s", divident);
    
    // perform the division
    int a = atoi(divident);
    int len = strlen(b);
    
    // the starting quotient and remainder are 0
    int r = 0;
    int q = 0;
    
    
    for (int i = 0; i < len; i++)
    {
        // update the remainder
        r = append_digit(r, b[i] - '0');
        
        // calculate result of the current division
        int mediate_q = r / a;
        
        // update the quotient and remainder
        q = append_digit(q, mediate_q);
        r -= mediate_q * a;
        
    }
    
    dprint(q);
    dprint(r);
}
