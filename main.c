
#include <stdio.h>                                                                  // Needed for printing
#include <windows.h>                                                                // Needed for sleep command on Windows
#include <conio.h>                                                                  // Needed for terminal commands on Windows

#define FRAME_TIME_MILISECONDS 50                                                   // The time in miliseconds, used for the delay between frames
#define TIME_STEP 0.01f                                                             // The time step
#define THERMAL_CONDUCTIVITY 10                                                     // The thermal conductivity K (or alpha)
#define ARRAY_SIZE_X 10                                                             // Manual array size

/*
    Notes:
    du/dx = u(x)/ 1

    // TODO
    - Fix energy lose issue
    - - Could make the equation work off ratios times the total input energy
*/

void printArray(float field[]);                                                     // This prints the array
void copyArray(float copyField[], float pasteField[]);                              // This copies the array from one to another
void sumArray(float field[]);                                                       // This totals the values of the field, used to calculate the total energy of the system (for error checking)


int main()                                                                          // Script start
{
    // INIT SECTION
    printf("Hello world!\n");                                                       //  // Sanity test
    int frameCount = 1;                                                             //  // Frame counter init

    float a_currentField[ARRAY_SIZE_X] = {0.0f};                                    //  // Inits the current field, the current field is the field presented
    a_currentField[0] = 10.0f;                                                      //  // Sets the initial conditions

    float a_workingField[ARRAY_SIZE_X] = {0.0f};                                    //  // Inits the working field, basically holds the values used for calculations, while the a_currentField gets updated
    a_workingField[0] = 10.0f;                                                      //  // Sets the initial conditions, currently written manually despite copyArray() function because it's not worth it atm

    float ddu_dxx;                                                                  //  // The d^2 u / d x^2 init
    float average_t;                                                                //  // Used to find the average value for inner values

    
    // LOOP SECTION
    while(1)                                                                        //  // This is the while loop
    {
        for (int i = 0; i < ARRAY_SIZE_X; i++)
        {
            if (i == 0)                                                             //  // If the value is at L = 0 (beginning)
            {
                ddu_dxx     = a_workingField[1] - a_workingField[0];                //  // Only take difference from i = 0 and i = 1
            }

            else if (i == 9)                                                        //  // If the value is at L = L (ending)
            {
                ddu_dxx     = a_workingField[9] - a_workingField[8];                //  // Only take difference from i = N and i = (N -1)
            }

            else                                                                    //  // Remaining elements
            {
                average_t   = a_workingField[i-1] + a_workingField[i+1];            //  // Gets the average value of the points left and right of the current point
                ddu_dxx     = average_t - (2 * a_workingField[i]);                  //  // differences of the average surrounding temperatures, omitting the 1 / d x^2 since it's literally just 1 / 1^2 (= 1)
            }

            float dudt = THERMAL_CONDUCTIVITY * ddu_dxx;                            //  // Difference in temperature over time
            float du = dudt * TIME_STEP;                                            //  // Difference in temperature given the time step

             a_currentField[i] = du + a_workingField[i];                            //  // u_NEW = du + u_OLD (Comes from du = u_NEW - u_OLD)

        }



        printf("Iteration: %d\n", frameCount);                                      //  // Makes sure that the loop is working

        // printf("Current Field:\n");                                              //  // Used for debugging
        printArray(a_currentField);

        // printf("Working Field:\n");                                              //  // Used for debugging
        // printArray(a_workingField);                                              //  // Used for debugging

        sumArray(a_currentField);                                                   //  // Prints the total energy of the system
        copyArray(a_currentField, a_workingField);                                  //  // Updates the working field
        frameCount++;                                                               //  // Increments the counter
        Sleep(FRAME_TIME_MILISECONDS);                                              //  // Delay between refreshes
        system("cls");                                                              //  // Clears screen
    }

    return 0;                                                                       //  // Required
}



void printArray(float field[])                                                      // To print array
{
    for (int i = 0; i < ARRAY_SIZE_X; i++)                                          //  // For loop for elements
    {
        float previewValue  = field[i];                                             //  // Disassociates the value from the field

        if (field[i] < 0) {previewValue    = 0.0f;}                                 //  // Avoids negative numbers due to small floating point errors

        if (i == 0) {printf("[ %5.2f, ", previewValue);}                            //  // If first element, include the left bracket
        else if (i == (ARRAY_SIZE_X - 1)) {printf("%5.2f ]\n", previewValue);}      //  // Else if the element is the last, include the right bracket
        else {printf("%5.2f, ", previewValue);}                                     //  // Otherwise do the normal format
    }
}



void copyArray(float copyField[], float pasteField[])                               // To copy arrays of the same dimension size
{
    for (int i = 0; i < ARRAY_SIZE_X; i++) {pasteField[i] = copyField[i];}          //  // Replaces each field
}



void sumArray(float field[])                                                        // Gets the total value of an array
{
    float sum = 0;                                                                  //  // Inits the sum variable

    for (int i = 0; i < ARRAY_SIZE_X; i++) {sum += field[i];}                       //  // Cumulative value

    printf("\nEnergy: %5.4f", sum);                                                 //  // Print the total
}