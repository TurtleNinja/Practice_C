#include <stdio.h>


#define dprint(expr)    printf("#expr: %d", (expr))

// function prototype
void aprint(int arr[], int size);
void insert(int* arr, int from, int to);


int main(void)
{
    int a[] = {6, 3, 5, 4, 8, 9, 0, 7, 2, 1};
    int length = 10;
    
    // starting insertion sort
    for (int i = 1; i < length; i++)    // i marks the first unsorted element
    {
        // find the right position
        int j = i-1;
        while( (j >= 0) && (a[i] < a[j]) )
            --j;
        
        // insert to the prosition
        insert(a, i, j+1);
        
        // display result
        aprint(a, length);
    }
}


// print a formatted array
void aprint(int arr[], int size)
{
    
    for (int i = 0; i < (size-1); i++)
    {
        printf("%d, ", arr[i]);
    }
    
    printf("%d\n", arr[size-1]);
}



void insert(int* arr, int from, int to)
{
    int temp = arr[from];
    
    // make place for a[i]
    for (int i = from; i > to; i--)
    {
        arr[i] = arr[i-1];
    }
    
    // insert to the position
    arr[to] = temp;
}
