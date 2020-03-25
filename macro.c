//
//  macro.c
//  
//
//  Examples of the uses of macros in C program
//  Section 4.11

#include <stdio.h>

// MACRO SUBSTITUION have the form:
//      #define   name  replacement_text

#define     forever         for(;;) //infinite loop
#define     max(a, b)       (a) > (b) ? (a) : (b)
#define     square(x)       (x) * (x)
#define     dprint(expr)    printf(#expr " = %d\n", expr)   //debugging print macro
/*  dprint(x/y)    =    printf("x/y" " = %g\n", x/y)  */

#define paste(front, back)  front ## back   //creating a token by concatenating strings
/*  paste(Turtle, Ninja) --> TurtleNinja  */

//spread macro definitions into multiple lines, and use block structure
#define     swap(t, x, y)   {  (t) = *(x);  \
                               *(x) = *(y); \
                               *(y) = (t);  }



// CONDITIONAL INCLUSION
#if !defined(HDR)
    #if SYSTEM == SYSV
        #define HDR "sysv.h"
    #elif SYSTEM == BDS
        #define HDR "bds.h"
    #elif SYSTEM == MSDOS
        #define HDR "msdos.h"
    #else
        #define HDR "default.h"
    #endif
#endif
#include HDR


// demo some macro definitions
int main(void)
{
    int x, y, t;
    x = 100;
    y = 91;
    
    dprint( max(x,y) );
    
    dprint(x);
    dprint(y);
    swap(t, &x, &y);
    dprint(x);
    dprint(y);
    
    // generate a user ID token
    // --> how to use it efficiently?
    int paste(user, ID) = 7;    // int userID = 7
    dprint( userID );
    dprint( paste(user, ID) );
    
    

}


/*
 NOTE:

    // There is no text replacement in side a quoted string
    // Example: YES is a macro definition of "I agree",
    // and printf(YES) will be equivalent to printf("I agree")
    // however, printf("YES") will not be replace with "I agree"
 
    // Place parenthesis around replacement text to ensure correct operations
    // #define  square(x)  x * x    --> error when invoke square(z+1)
 
 */
