#include <stdio.h>      //printf
#include <string.h>     //memset
#include <stdlib.h>     //malloc


void aprint(int arr[], int length);
void merge(int nums[], int mlow, int mmid, int mhigh);
void sort(int arr[], int low, int high);

#define NNUMS 10

int main(void)
{
    // local variables
    int nums[] = {9, 1, 3, 5, 8, 2, 6, 4, 0, 7};
    
    printf("Original:\n\t");
    aprint(nums, NNUMS);
    
    //start sorting
    sort(nums, 0, NNUMS);
    
    printf("Result:\n\t");
    aprint(nums, NNUMS);
}


void sort(int arr[], int low, int high)
{
    // size of the array
    unsigned int n = high - low;
    
    if (n == 0 || n == 1)
        return;
    
    // divide the array into two parts
    int mid = low + (high - low) / 2;
    
    // sort each part
    sort(arr, low, mid);
    sort(arr, mid, high);
    
    
    //merged the two sorted parts
    merge(arr, low, mid, high);
}

void merge(int nums[], int mlow, int mmid, int mhigh)
{
    int n = mhigh - mlow;

    // create a temporary duplicate
    int *tmp = malloc(n * sizeof(int));
    memset(tmp, 0, n);
    for (int i = 0; i < n; i++)
        tmp[i] = nums[i + mlow];
    
    // index of mid, low in the temporary array
    int tlow = 0;
    int tmid = mmid - mlow;
    
    int j = tlow;
    int k = tmid;
    for (int i = mlow; i < mhigh; i++)
    {
        if (k == n)
            nums[i] = tmp[j++];
        else if (j == tmid)
            nums[i] = tmp[k++];
        else if (tmp[j] < tmp[k])
            nums[i] = tmp[j++];
        else
            nums[i] = tmp[k++];
    }
    
    free(tmp);
    
}


// print an integer array
void aprint(int arr[], int length)
{
    int i;
    
    printf("{");
    for (i = 0; i < length-1; i++)
        printf("%d, ", arr[i]);
    printf("%d}\n", arr[i]);
}
