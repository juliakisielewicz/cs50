#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int countLetters(string txt);
int countWords(string txt);
int countSentences(string txt);

int calculateIndex(string txt);

int main(void)
{
    
    //Get input
    string text = get_string("Text: ");
    
    //int letters = countLetters(text);
    //int words = countWords(text);
    //int sentences = countSentences(text);
    
    // Calculate result
    int grade;
    //grade = round(0.0588 * (letters * 100 / words) - 0.296 * (sentences * 100 / words) - 15.8);


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

//Functions

int countLetters(string txt)
{
    int sum = 0;
    
    for (int i = 0; i < strlen(txt); i++)
    {
        if (isalpha(txt[i]))
        {
            sum++;
        }
    }
    
    return sum;
}

int countWords(string txt)
{
    int sum = 0;
    
    for (int i = 0; i < strlen(txt); i++)
    {
        if (isspace(txt[i]) || txt[i] == '\'')
        {
            sum++;
        }
    }
    
    return sum + 1;  
}

int countSentences(string txt)
{
    int sum = 0;
    
    for (int i = 0; i < strlen(txt); i++)
    {
        if (txt[i] == '.' || txt[i] == '!' || txt[i] == '?')
        {
            sum++;
        }
    }
    
    return sum;
}


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
            if (i == strlen(txt) - 1)
            {
                words++;
            }
            sentences++;
        }
    }
    
    index = round(0.0588 * (letters * 100 / words) - 0.296 * (sentences * 100 / words) - 15.8);
    
    return index;
}
