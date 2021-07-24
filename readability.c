#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int calculateIndex(string txt);

int main(void)
{
    //Get input
    string text = get_string("Text: ");
    
    // Calculate result
    int grade;
    grade = calculateIndex(text);
    
    //Display result
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
    
}

//Function

int calculateIndex(string txt)
{
    int letters = 0, words = 0, sentences = 0, index = 0;
    
    for (int i = 0; i < strlen(txt); i++)
    {
        if (isalpha(txt[i]))
        {
            letters++;
        }
        else if (isspace(txt[i]))
        {
            words++;
        }
        else if (txt[i] == '.' || txt[i] == '!' || txt[i] == '?')
        {
            sentences++;
        }
    }
    
    words++;
    
    index = round(0.0588 * ((float)letters * 100 / (float) words) - 0.296 * ((float) sentences * 100 / (float) words) - 15.8);
    
    return index;
}
