#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Get height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    
    //Draw pyramid
    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= (height - i); j++)
        {
            printf(" ");
        }
        
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        
        printf("  ");
        
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        
        printf("\n");
        
    }
}