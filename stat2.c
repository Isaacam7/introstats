#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include "isaac.h"

double correlation(double xmean, double xstandev, double ymean, double ystandev, double xvals[], double yvals[], double length);
double findmean(double arr[], int length);
double findstandarddev(double arr[], int length, double mean);
void lsrl(double xarr[], double yarr[], double length);

int main(void)

{
    int LENGTH;
    printf("How many variables: ");
    scanf("%i", &LENGTH);

    double x[LENGTH];
    double y[LENGTH];
    
    for(int i = 0; i < LENGTH; i++)
    {
        printf("xval%i: ", i + 1);
        scanf("%lf", &x[i]);
    }
    
    for(int i = 0; i < LENGTH; i++)
    {
        printf("yval%i: ", i + 1);
        scanf("%lf", &y[i]);
    }

    double xmean = findmean(x, LENGTH);
    double ymean = findmean(y, LENGTH);
    
    double xstandev = findstandarddev(x, LENGTH, xmean);
    double ystandev = findstandarddev(y, LENGTH, ymean);
    
    printf("\n");
    printf("r = %g\n", correlation(xmean, xstandev, ymean, ystandev, x, y, LENGTH));
    lsrl(x, y, LENGTH);
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

double findstandarddev(double arr[], int length, double mean)
{
    double sum = 0;
    double sum2 = 0;
    for(int i = 0; i < length; i++)
    {
        sum += pow((arr[i] - mean), 2);
    }
    
    sum2 = sqrt(sum/(length - 1));
    
    return sum2;
}


double correlation(double xmean, double xstandev, double ymean, double ystandev, double xvals[], double yvals[], double length)
{
    double sum = 0;
    
    for(int i = 0; i < length; i++)
    {
     
      sum += ((xvals[i] - xmean) / xstandev) * ((yvals[i] - ymean) / ystandev);
        
    }
    
    return ((1 / (length - 1)) * sum);
}



void lsrl(double xarr[], double yarr[], double length)
{
    double xsum = sum(xarr, length);
    double ysum = sum(yarr, length);
    double powxsum = 0;
    double sumxy = 0;
    for(int i=0; i<length; i++)
    {
        powxsum += pow(xarr[i], 2);
    }

    for(int i=0; i<length; i++)
    {
        sumxy += (xarr[i] * yarr[i]);
    }

    double m0 = (length * sumxy) - (xsum * ysum);
    double m1 = (length * powxsum) - pow(xsum, 2);

    double m = m0 / m1;

    double b = (ysum - (m * xsum)) / length;

    printf("LSRL: ŷ = %gx + %g\n", m, b);

    char ans[3];
    printf("Do you want a residual?\n");
    scanf("%s", ans);
    lowercase(ans, 3);
    if(strcmp(ans, "yes")==0) 
    {
        int answer = 0;
        printf("How many residuals?\n");
        scanf("%i", &answer);
        double values[answer];
        double predy[answer];
        double ytemp[answer];
        for(int i = 0; i < answer; i++)
        {
           printf("x-value:");
           scanf("%lf", &values[i]);
        }

        for(int i = 0; i < answer; i++)
        {
            for(int j = 0; j < length; j++)
            {
                if (values[i] == xarr[j])
                {
                    predy[i] = (m * values[i]) + b;
                    ytemp[i] = yarr[j];
                }  
            }
        }

        for(int i = 0; i < answer; i++)
        {
            printf("Residual for %g is %g\n", values[i], ytemp[i] - predy[i]);
        }
    }
    printf("\n");
    printf("The predicted y values in order of correspondace\n");
    printf("\n");
        for(int i = 0; i < length; i++)
        {
            printf("%g, ", ((m * xarr[i]) + b));
        }
    printf("\n");

    double RSS = 0;
    for(int i=0; i<length;i++)
    {
        RSS += pow(yarr[i] - ((m * xarr[i]) + b), 2);
    }

    double TSS = 0;
    double mean = 0;
    mean = (sum(yarr, length) / length);
    for(int i=0; i<length;i++)
    {
        TSS += pow((yarr[i] - mean),2);
    }

    double rsquared = 0;
    rsquared = (1 - (RSS/TSS));

    printf("R-squared = %g\n", rsquared);
}



