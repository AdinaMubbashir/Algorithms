#include <stdio.h>
#include <sys/timeb.h>
#include <stdlib.h>

#define MAX_SIZE 50000

// Brute force algorithm to find inversion count
int bruteforce(long unsigned int intArray[MAX_SIZE])
{
    // keep track of inversion counter
    int count = 0;
    for (int i = 0; i < MAX_SIZE - 1; i++)
    {
        for (int j = i + 1; j < MAX_SIZE; j++)
        {
            if (intArray[i] > intArray[j])
            {
                count++;
            }
        }
    }
    return count;
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
    invCount = bruteforce(intArray);
    ftime(&endTime);

    // Get time in milliseconds
    float totalTime = (endTime.time - startTime.time) * 1000 + (endTime.millitm - startTime.millitm);

    printf("Brute Force:\n");
    printf("Inversion Count: %d\nExecution time: %.2fms\n", invCount, totalTime);

    free(temp);

    return 0;
}
