#include <stdio.h>


//function prototypes
void quicksort(int arr[], int left, int right);
void aprint(int arr[], int size);
int partition(int arr[], int left, int right, int p);

#define dprint(expr)        printf(#expr": %d\n", expr)
#define swap(a, b)      {int t = *a; *a = *b; *b = t;}

int main(void)
{
    //local variables
    const int N = 6;
    int nums[] = {0, 0, 0, 3, 4, 3};
    
    aprint(nums, N);
    quicksort(nums, 0, N-1);
    aprint(nums, N);
    
}


void quicksort(int a[], int left, int right)
{
    if (left >= right)
        return;
    
    if (left == right-1)  {
        if (a[left] > a[right]) {
            swap(&a[left], &a[right]);
        }
        return;
    }
    
    // pick a pivot
    int pivot = a[left];
    
    // partition
    int index = partition(a, left, right, pivot);
    
    // put the pivot into the boundary
    //swap(&a[left], &a[index]);      --> cancel the swap in partition!

    
    //quicksort left part and right part
    quicksort(a, left, index-1);
    quicksort(a, index+1, right);
    
}

//return the cprrect position of the pivot p
int partition(int arr[], int pleft, int pright, int p)
{
    while (pleft < pright)
    {
        while (pleft < pright && arr[pleft] < p) pleft++;
        while (pright > pleft && arr[pright] >= p) pright--;
        swap(&arr[pleft], &arr[pright]);
    }
    
    return pleft;
}

void aprint(int arr[], int size)
{
    printf("{%d", arr[0]);
    for (int i = 1; i < size; i++)
        printf(", %d", arr[i]);
    printf("}\n");
}
