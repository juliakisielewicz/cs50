#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            average = round(average / 3);
            
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float red;
    float green;
    float blue;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            green = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            blue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            
            
            if(red > 255)
            {
                red = 255;
            }
            
            if(green > 255)
            {
                green = 255;
            }
            
            if(blue > 255)
            {
                blue = 255;
            }
            
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
            
        }
    }
    
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    float red, green, blue;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width/2); j++)
        {
            red = image[i][j].rgbtRed;
            green = image[i][j].rgbtGreen;
            blue = image[i][j].rgbtBlue;
            
            image[i][j].rgbtRed = image[i][width-j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            
            image[i][width - j - 1].rgbtRed = red;
            image[i][width - j - 1].rgbtGreen = green;
            image[i][width - j - 1].rgbtBlue = blue;
            
        }
    }
    
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width];
    
    float red, green, blue, pixels;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = 0.0;
            green = 0.0;
            blue = 0.0;
            pixels = 0.0;
            
            for (int p = -1; p < 2; p++)
            {
                for (int q = -1; q < 2; q++)
                {
                    if ((i + p) >= 0 && (i + p) < height && (j + q) >= 0 && (j + q) < width)
                    {
                        pixels++;
                        red = red + image[i + p][j + q].rgbtRed;
                        green = green + image[i + p][j + q].rgbtGreen;
                        blue = blue + image[i + p][j + q].rgbtBlue;
                    }
                }
            }
            
            tmp_image[i][j].rgbtRed = round(red / pixels);
            tmp_image[i][j].rgbtGreen = round(green / pixels);
            tmp_image[i][j].rgbtBlue = round(blue / pixels);

        }
    }
    
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tmp_image[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp_image[i][j].rgbtBlue;
        }
    }
    
    return;
}


