#include <stdio.h>
#include <string.h>
#include <sys/timeb.h>
#include <stdlib.h>

#define MAX_SIZE 50000

int merge(unsigned long int intArray[MAX_SIZE], int left, int middle, int right)
{

    int countInv = 0;
    unsigned long int temp[MAX_SIZE];
    int i = left;
    int j = middle;
    int k = left;

    // While loop checks the right and left side of array
    while ((j <= right) && (i < middle))
    {

        if (intArray[i] > intArray[j])
        {
            // if inversion is found
            countInv += (middle - i);
            temp[k] = intArray[j++];
        }
        else if (intArray[i] < intArray[j])
        {
            // if inversion is not found
            temp[k] = intArray[i++];
        }

        k++;
    }

    // Elements are copied from array
    while (j <= right)
    {
        temp[k] = intArray[j];
        j++;
        k++;
    }

    // Elements are copied from array
    while (i < middle)
    {
        temp[k] = intArray[i];
        i++;
        k++;
    }

    // Stores sorted long int
    for (i = left; i <= right; i++)
    {
        intArray[i] = temp[i];
    }

    return countInv;
}

int mergeSortInversionCount(unsigned long intArray[MAX_SIZE], int left, int right)
{
    int inversionCount = 0;

    if (left < right)
    {

        int middle = (right + left) / 2;
        // recursively call functions to get inversion count
        inversionCount += mergeSortInversionCount(intArray, left, middle);
        inversionCount += mergeSortInversionCount(intArray, middle + 1, right);
        inversionCount += merge(intArray, left, middle + 1, right);

        return inversionCount;
    }
    else
    {
        return 0;
    }
}

int main(int argc, char const *argv[])
{

    struct timeb startTime, endTime;
    int array = 0;
    int count = 0;
    char filename[100];
    char c;
    unsigned long int intArray[MAX_SIZE] = {0};
    char *temp = (char *)calloc(100, sizeof(char));
    int invCount = 0;
    float totalTime;

    // User enters file name
    printf("Enter the file name\n");
    scanf("%s", filename);
    getchar();

    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        fprintf(stderr, "File could not be opened \n");
        return 0;
    }

    while (!feof(fp))
    {
        c = fgetc(fp);
        if (c == ' ')
        {
            // store long int
            intArray[count] = atol(temp);
            count++;
            array = 0;
            free(temp);
            temp = (char *)calloc(100, sizeof(char));
        }
        else if (c == '\n')
        {
            continue;
        }
        else
        {
            temp[array] = c;
            array++;
        }
    }

    fclose(fp);

    ftime(&startTime);
    invCount = mergeSortInversionCount(intArray, 0, MAX_SIZE - 1);
    ftime(&endTime);

    totalTime = (endTime.time - startTime.time) * 1000 + (endTime.millitm - startTime.millitm);

    printf("Divide and Conquer:\n");
    printf("Inversion Count: %d\nExecution time: %.2fms\n", invCount, totalTime);

    free(temp);

    return 0;
}
