#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <string.h>

void shiftTables(char user[150], int shiftTable[500], int length)
{
    for (int i = 0; i < 500; i++)
    {
        shiftTable[i] = length - 1;
    }
    for (int i = 0; i < length - 1; i++)
    {
        shiftTable[(int)user[i]] = length - i - 1;
    }
}

// Horspool Algorithm from textbook
void Horspool(FILE *fp, char user[150])
{
    struct timeb startTime, endTime;

    ftime(&startTime);

    // Intialize shift table
    int shiftTable[500];
    int length = strlen(user);
    shiftTables(user, shiftTable, length);

    int patternCount = 0;
    int countShifts = 0;
    char lines[100000];

    // Loop through file line by line
    while (fgets(lines, 100000, fp) != NULL)
    {
        int length2 = strlen(lines);
        int var = length - 1;
        // Slide pattern until match is found or end has been reached
        while (var <= length2 - 1)
        {
            int i = 0;
            // Compare each character
            while (i <= length - 1 && user[length - 1 - i] == lines[var - i])
            {
                i++;
            }
            // Match is foubd
            if (i == length)
            {
                var = var + length - 1;
                patternCount++;
            }
            else
            {
                // Slide pattern
                var = var + shiftTable[(int)lines[var]];
                countShifts++;
            }
        }
    }

    ftime(&endTime);

    float totalTime = (endTime.time - startTime.time) * 1000 + (endTime.millitm - startTime.millitm);
    printf("Counts: %d\n", patternCount);
    printf("Shifts: %d\n", countShifts);
    printf("Execution time: %.2fms\n", totalTime);
}

int main(int argc, char const *argv[])
{
    char user[150];

    FILE *fp = fopen("data_A3_Q2.txt", "r");

    if (fp == NULL)
    {
        fprintf(stderr, "File could not be opened \n");
        return 0;
    }

    printf("Horspool's Algorithm:\n");
    // Prompt for pattern
    printf("Enter a pattern: ");
    scanf("%s", user);
    getchar();

    Horspool(fp, user);

    return 0;
}
