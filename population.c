#include <cs50.h>

#include <stdio.h>



int main(void)

{

    // TODO: Prompt for start size
    int start = 0;
    do
    {
        start = get_int("Enter starting size (min 9): ");
    }
    while (start < 9);
    


    // TODO: Prompt for end size
    int end = 0;
    do
    {
        end = get_int("Enter ending size: ");
    }
    while (end < start);



    // TODO: Calculate number of years until we reach threshold
    int population = start;
    int years = 0;
    while (population < end)
    {
        population = population + (population / 3) - (population / 4);
        years++;
    }


    // TODO: Print number of years
    printf("Start size: %i\n", start);
    printf("End size: %i\n", end);
    printf("Years: %i\n", years);
}

