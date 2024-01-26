// solutions.c
#include "solutions.h"
#include <stdlib.h>

int running_total(int n)
{
    static int total = 0;
    total += n;
    return total;
}

int *reverse(int *arr, int len)
{
    int *reversed = (int *)calloc(len, sizeof(int));
    for (int i = 0; i < len; i++)
    {
        reversed[i] = arr[len - i - 1];
    }
    return reversed;
}

int *reverse_in_place(int *arr, int len)
{
    for (int i = 0; i < len / 2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[len - i - 1];
        arr[len - i - 1] = temp;
    }
    return arr;
}

int num_occurences(int *arr, int len, int t)
{
    int count = 0;
    for (int i = 0; i < len; i++)
    {
        if (arr[i] == t)
        {
            count++;
        }
    }
    return count;
}