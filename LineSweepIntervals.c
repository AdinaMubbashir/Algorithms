#include <stdio.h>
#include <sys/timeb.h>
#include <stdlib.h>
#define MAXPAIRS 100000

int compareFunc(const void *a, const void *b)
{
    int num1 = *((int *)a);
    int num2 = *((int *)b);

    if (num1 > num2)
    {
        return 1;
    }
    else if (num1 == num2)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

void preSort(int arr1[MAXPAIRS], int arr2[MAXPAIRS], int count)
{
    int countInv = 0;
    int countPoint = 0;

    // Sort Arrays using qsort
    qsort(arr1, count, sizeof(int), compareFunc);
    qsort(arr2, count, sizeof(int), compareFunc);

    int i = 0;
    int j = 0;
    int curCount = 0;

    // Loop throught arrays
    while (i < count && j < count)
    {
        if (arr1[i] < arr2[j - 1])
        {
            curCount++;
            // Get new max for intervals
            if (curCount > countInv)
            {
                countInv = curCount;
                countPoint = arr1[i];
                countPoint++;
            }
            // Increment arr1
            i++;
        }
        else
        {
            curCount--;
            // Increment arr2
            j++;
        }
    }

    printf("The maximum number of intervals: %d\n", countInv);
    printf("The intervals include point: %d\n", countPoint);
}

int main(int argc, char const *argv[])
{
    struct timeb startTime, endTime;
    char filename[100];
    int arr1[MAXPAIRS];
    int arr2[MAXPAIRS];
    int count = 0;

    printf("Enter the file name\n");
    scanf("%s", filename);
    getchar();

    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        fprintf(stderr, "File could not be opened \n");
        return 0;
    }

    // Get file content
    while (fscanf(fp, "%d %d", &arr1[count], &arr2[count]) == 2)
    {
        count++;
    }

    fclose(fp);

    printf("Presorting Technique:\n");

    ftime(&startTime);
    preSort(arr1, arr2, count);
    ftime(&endTime);

    // Get time in milliseconds
    float totalTime = (endTime.time - startTime.time) * 1000 + (endTime.millitm - startTime.millitm);

    printf("Execution time: %.2fms\n", totalTime);

    return 0;
}
