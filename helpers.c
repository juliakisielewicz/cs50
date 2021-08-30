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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width];

    int GxKernel[3][3] = {
        {-1, 0, 1}, 
        {-2, 0, 2}, 
        {-1, 0, 1}
        
    };
    
    int GyKernel[3][3] = {
        {-1, -2, -1}, 
        {0, 0, 0}, 
        {1, 2, 1}
        
    };
    
    float redGx, greenGx, blueGx, redGy, greenGy, blueGy;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            redGx = 0.0;
            greenGx = 0.0;
            blueGx = 0.0;
            redGy = 0.0;
            greenGy = 0.0;
            blueGy = 0.0;
            
            for (int p = -1; p < 2; p++)
            {
                for (int q = -1; q < 2; q++)
                {
                    if ((i + p) >= 0 && (i + p) < height && (j + q) >= 0 && (j + q) < width)
                    {
                        redGx = redGx + image[i + p][j + q].rgbtRed * GxKernel[p + 1][q + 1];
                        greenGx = greenGx + image[i + p][j + q].rgbtGreen * GxKernel[p + 1][q + 1];
                        blueGx = blueGx + image[i + p][j + q].rgbtBlue * GxKernel[p + 1][q + 1];
                        
                        redGy = redGy + image[i + p][j + q].rgbtRed * GyKernel[p + 1][q + 1];
                        greenGy = greenGy + image[i + p][j + q].rgbtGreen * GyKernel[p + 1][q + 1];
                        blueGy = blueGy + image[i + p][j + q].rgbtBlue * GyKernel[p + 1][q + 1];
                    }
                }
            }
            
            
            int finalRed = round(hypot(redGx, redGy));
            int finalGreen = round(hypot(greenGx, greenGy));
            int finalBlue = round(hypot(blueGx, blueGy));

            
            if(finalRed > 255)
            {
                tmp_image[i][j].rgbtRed = 255;
            }
            else
            {
                tmp_image[i][j].rgbtRed = finalRed;
            }
            
            if(finalGreen > 255)
            {
                tmp_image[i][j].rgbtGreen = 255;
            }
            else
            {
                tmp_image[i][j].rgbtGreen = finalGreen;
            }
            
            if(finalBlue > 255)
            {
                tmp_image[i][j].rgbtBlue = 255;
            }
            else
            {
                tmp_image[i][j].rgbtBlue = finalBlue;

            }
        
        }
    }
    
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tmp_image[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp_image[i][j].rgbtBlue;
           
           image[i][j] = tmp_image[i][j];
        }
    }
    
    return;
}
