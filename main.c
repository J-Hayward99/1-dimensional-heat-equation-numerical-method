#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define FRAME_TIME_MILISECONDS 50                                                 // The time in miliseconds, used for the delay between frames
#define TIME_STEP 0.01f
#define THERMAL_CONDUCTIVITY 10
#define ARRAY_SIZE_X 10

/*
    Notes:
    du/dx = u(x)/ 1

    // TODO
    - Fix energy lose issue

*/

void printArray(float field[]);
void updateArray(float copyField[], float pasteField[]);
void sumArray(float field[]);

int main()
{
    // INIT SECTION
    printf("Hello world!\n");                                                       // Sanity test
    int frameCount = 1;

    float a_currentField[ARRAY_SIZE_X] = 
    {
        0.0f
    };
    a_currentField[0] = 10.0f;

    float a_workingField[ARRAY_SIZE_X] =
    {
        0.0f
    };
    a_workingField[0] = 10.0f;

    float ddu_dxx;
    float average_t;

    
    // LOOP SECTION
    while(1)                                                                        // This is the while loop
    {
        for (int i = 0; i < ARRAY_SIZE_X; i++)
        {
            if (i == 0)
            {
                ddu_dxx     = a_workingField[1] - a_workingField[0];
            }

            else if (i == 9)
            {
                ddu_dxx     = a_workingField[9] - a_workingField[8];
            }

            else
            {
                average_t   = a_workingField[i-1] + a_workingField[i+1];
                ddu_dxx     = average_t - (2 * a_workingField[i]);
            }

            float dudt = THERMAL_CONDUCTIVITY * ddu_dxx;
            float du = dudt * TIME_STEP;

             a_currentField[i] = du + a_workingField[i];

        }



        printf("Iteration: %d\n", frameCount);                                          // Makes sure that the loop is working

        printf("Current Field:\n");
        printArray(a_currentField);

        // printf("Working Field:\n");
        // printArray(a_workingField); 

        sumArray(a_currentField);
        updateArray(a_currentField, a_workingField);
        frameCount++;                                                               // Increments the counter
        Sleep(FRAME_TIME_MILISECONDS);                                              // Delay between refreshes
        system("cls");                                                              // Clears screen
    }

    return 0;                                                                       // Required
}



void printArray(float field[])
{
    for (int i = 0; i < ARRAY_SIZE_X; i++)
    {
        float previewValue  = field[i];

        if (field[i] < 0)
        {
            previewValue    = 0.0f;
        }

        if (i == 0)
        {
            printf("[ %5.2f, ", previewValue);
        }
        else if (i == (ARRAY_SIZE_X - 1))
        {
            printf("%5.2f ]\n", previewValue);
        }
        else
        {
            printf("%5.2f, ", previewValue);
        }
    }
}



void updateArray(float copyField[], float pasteField[])
{
    for (int i = 0; i < ARRAY_SIZE_X; i++)
    {
        pasteField[i] = copyField[i];
    }
}



void sumArray(float field[])
{
    float sum = 0;

    for (int i = 0; i < ARRAY_SIZE_X; i++)
    {
        sum += field[i];
    }

    printf("\nEnergy: %5.4f", sum);
}