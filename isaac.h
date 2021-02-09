#include <math.h>
#include <stdio.h>
#include <ctype.h>

void lowercase(char arr[], int length)
{
    for(int i = 0; i < length; i++)
    {
        arr[i] = tolower(arr[i]);
    }
}

double sum(double arr[], double length)
{
    double sum0 = 0;
    for(int i = 0; i<length; i++)
    {
        sum0 += arr[i];
    }

    return sum0;
}

