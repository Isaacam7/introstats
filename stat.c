#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct
{
    double value;
    int occurance;
    
}
number;

typedef struct
{
    double digit;
    int instance;
    bool ismode;
}
num;

void insertionsort(double numberset[], int length);
int occur(double arr[], int length, double value);
double findmode(double arr[], int length);
double findmean(double arr[], int length);
double findmedian(double arr[], int length);
double findstandarddev(double arr[], int length, double mean);
double samplesd(double arr[], int length, double mean);
double range(double arr[], int length);
double q1(double arr[], int length);
double q3(double arr[], int length);
double iqr(double quar1, double quar3);
void otherval(double arr[], int length);
void zscore(double mean, double standev);
void lowercase(char arr[], int length);

int main(void)
{
    int LENGTH = 0;
    printf("How many values?\n");
    scanf("%i", &LENGTH);
    //declares the array the size of the amount of numbers
    double protonumberset[LENGTH];
    
    //populate the array with values
    for(int i = 0; i < LENGTH; i++)
    {
        printf("Value%i: ", i + 1);
        scanf("%lf", &protonumberset[i]);
    }
    
    //sort the numberset using an insertion sort
    insertionsort(protonumberset, LENGTH);
    //declare new sorted numberset
    double numberset[LENGTH];
    //store the sorted array into a new array
    for(int d = 0; d < LENGTH; d++)
    {
         numberset[d] = protonumberset[d];
    }
    printf("\n");
    //Get the statistics
    double mode = findmode(numberset, LENGTH);
    double mean = findmean(numberset, LENGTH);
    double median = findmedian(numberset, LENGTH);
    double standdev = findstandarddev(numberset, LENGTH, mean);
    double sample =  samplesd(numberset, LENGTH, mean);
    double regrange = range(numberset, LENGTH);
    double Q1 = q1(numberset, LENGTH);
    double Q3 = q3(numberset, LENGTH);
    double IQR = iqr(Q1, Q3);

    printf("Ordered list: ");
    for(int d = 0; d < LENGTH; d++)
    {
        printf("%g, ", numberset[d]);
    }
    
    printf("\n");
    printf("range: %g\n", regrange);
    printf("mode: %g\n", mode);
    printf("mean: %g\n", mean);
    printf("median: %g\n", median);
    printf("standard deviation: %g\n", standdev);
    printf("sample standard deviation: %g\n", sample);
    printf("IQR: %g\n", IQR);
    printf("\n");
    printf("five number summary: \n");
    printf("min: %g\n", numberset[0]);
    printf("Q1: %g\n", Q1);
    printf("median: %g\n", median);
    printf("Q3: %g\n", Q3);
    printf("max: %g\n", numberset[LENGTH - 1]);
    printf("\n");
    printf("Other possible values: \n");
    otherval(numberset, LENGTH);
    printf("\n");
    
    char ans[3];
    printf("Do you want a zscore?\n");
    scanf("%s", ans);
    lowercase(ans, 3);
    if(strcmp(ans, "yes")==0)
    {
        int answer = 0;
        printf("How many zscores?\n");
        scanf("%i", &answer);
        
        for(int i = 0; i < answer; i++)
        {
           zscore(mean, standdev); 
        }
    }
    
    printf("\n");
    printf("This program may not be accurate be sure to check\n");
  
}

void insertionsort(double numberset[], int length)
{
    for(int j = 0; j < length; j++)
    {
        double key = numberset[j];
        int i = j - 1;
        
        /*insert the number to the correct position
        if it is greater than the next number*/
        while(i >= 0 && numberset[i] > key)
        {
            numberset[i + 1] = numberset[i];
            i = i - 1;
        }
        numberset[i + 1] = key;
    }
}

int occur(double arr[], int length, double value)
{
    //count how many times each number occurs
    int count = 0;
    for(int i = 0; i < length; i++)
    {
        if(arr[i] == value)
        {
            count++;
        }
    }
    
    return count;
}

double findmode(double arr[], int length)
{
    number arr2[length];
    int MAX = 0;
    double themode = 0;
    
    for(int i = 0; i < length; i++)
    {
        arr2[i].value = arr[i];
        arr2[i].occurance = 0;
    }
    
    //store the occurances for each number in each of their occurances node
    for(int i = 0; i < length; i++)
    {
        arr2[i].occurance = occur(arr, length, arr[i]);
    }
    
    //find the most occurances
    for(int j = 0; j < length; j++)
    {
        if(arr2[j].occurance > MAX)
        {
            MAX = arr2[j].occurance;
        }
    }
    
    //find the mode
    for(int j = 0; j < length; j++)
    {
        if(arr2[j].occurance == MAX)
        {
            themode = arr2[j].value;
        }
    }
    
    return themode;
}

double findmean(double arr[], int length)
{
    double sum = 0;
    for(int i = 0; i < length; i++)
    {
        sum += arr[i];
    }
    double sum2 = sum/length;
    
    return sum2;
}

double findmedian(double arr[], int length)
{
    int location = 0;
    int leftbound = 0;
    int rightbound = 0;
    double bound = 0;
    
    if(length % 2 != 0)
    {
        //since location is an int it will round to the lower bound 
        location = (length / 2);
        return arr[location];
    }
    
    else
    {
         leftbound = length / 2;
         rightbound = leftbound + 1;
         bound = ((arr[leftbound - 1] + arr[rightbound - 1])/2);
         return bound;
    }
    
}

double findstandarddev(double arr[], int length, double mean)
{
    double sum = 0;
    double sum2 = 0;
    for(int i = 0; i < length; i++)
    {
        sum += pow((arr[i] - mean), 2);
    }
    
    sum2 = sqrt(sum/length);
    
    return sum2;
}

double samplesd(double arr[], int length, double mean)
{
    double sum = 0;
    double sum2 = 0;
    for(int i = 0; i < length; i++)
    {
        sum += pow((arr[i] - mean), 2);
    }
    
    //for sample standard deviation the denomitator is N - 1
    sum2 = sqrt(sum/(length - 1));
    
    return sum2;
}

double range(double arr[], int length)
{
    return (arr[length - 1] - arr[0]);
}

double q1(double arr[], int length)
{
    double answer = 0;
    int n = 0;
    if(length % 2 != 0)
    {
        double arr2[n];
        n = ((length - 1) / 2);
        answer = findmedian(arr, n);
    }
    
    else
    {
        n = length / 2;
        double arr2[n];
        answer = findmedian(arr, n);
    }
    
    return answer;
}

double q3(double arr[], int length)
{
    double answer = 0;
    int n = 0;
    //counter to populate the arrays correctly
    int u = 0;
    int i2 = 0;
    if(length % 2 != 0)
    {
        double med = 0;
        med = findmedian(arr, length);
        n = ((length - 1) / 2);
        double arr2[length];
        //length plus 1 then divided by 2 always returns the place of the median
        //but in code it is indexed by 0 so the place is actually minus 1
        i2 = ((length + 1)/2);
        //plus  1 cause dont want to start at the median
        for(int i = i2; i < length; i++, u++)
        {
            arr2[u] = arr[i];
            
        }
        answer = findmedian(arr2, n);
    }
    
    else
    {
        n = length / 2;
        double arr2[n];
        for(int i = n; i < length; i++, u++)
        {
            arr2[u] = arr[i];
        }
        
        answer = findmedian(arr2, n);
    }
    
    /*for both for loops the i values have been subtracted by 1
    this is because values in arrays begin at 0*/
    
    return answer;
}

double iqr(double quar1, double quar3)
{
    return quar3 - quar1;
}


void otherval(double arr[], int length)
{
    //TO FIND ALL MODES
    
    /*length must be + 1 for the bool check on the bottom of 
    the other mode section to work properly and not seg fault*/
    
    num arr1[length + 1];
    
    for(int i = 0; i < length; i++)
    {
        arr1[i].digit = arr[i];
        arr1[i].instance = 0;
        arr1[i].ismode = false;
    }
    
    for(int i = 0; i < length; i++)
    {
        arr1[i].instance = occur(arr, length, arr1[i].digit);
    }
    
    int MAX = 0;
    
    for(int i = 0; i < length; i++)
    {
        if(arr1[i].instance > MAX)
        {
            MAX = arr1[i].instance;
        }
    }
    
    for(int i = 0; i < length; i++)
    {
        if(arr1[i].instance == MAX)
        {
            arr1[i].ismode = true;
        }
    }
    printf("Other possible modes: ");
    for(int i = 0; i < length; i++)
    {
        if(arr1[i].ismode == true && arr1[i].digit != arr1[i + 1].digit)
        {
            printf("%g, ", arr1[i].digit);
        }
    }
    printf("\n");
    
    //TO FIND OUTLIERS
    printf("possible outliers: ");
    double Q1 = q1(arr, length);
    double Q3 = q3(arr, length);
    double IQR = iqr(Q1, Q3);
    
    double param = IQR * 1.5;
    double bound_upper = param + Q3;
    double bound_lower = Q1 - param;
    
    double arr3[length];
    for(int i = 0; i < length; i++)
    {
        arr3[i] = arr[i];
    }
    
    for(int i = 0; i < length; i++)
    {
        if(arr3[i] < bound_lower || arr3[i] > bound_upper)
        {
            printf("%g, ", arr3[i]);
        }
    }
    printf("\n");
}

void zscore(double mean, double standev)
{
    double value = 0;
    printf("What value?\n");
    scanf("%lf", &value);
    
    double Z = 0;
    Z = ((value - mean) / standev);
    
    printf("%g is %g standard deviations from the mean\n", value, Z);
}

void lowercase(char arr[], int length)
{
    for(int i = 0; i < length; i++)
    {
        arr[i] = tolower(arr[i]);
    }
}


    
    




