#include "helpers.h"
#include <math.h>

// Convert image to grayscale //
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;
            float red = image[i][j].rgbtRed;

            int med = round( (blue + green + red)/ 3.0);

            image[i][j].rgbtBlue= image[i][j].rgbtGreen = image[i][j].rgbtRed = med;
        }

    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
   for(int i=0 ; i < height; i++)
   {
       for(int j=0; j < width; j++)
       {
           float originalBlue = image[i][j].rgbtBlue;
           float originalGreen = image[i][j].rgbtGreen;
           float originalRed = image[i][j].rgbtRed;

           int blueSepia = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

           int greenSepia = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);

           int redSepia = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);

           int sepia = blueSepia + greenSepia + redSepia;

           if(blueSepia > 255)
           {
              blueSepia = 255;
           }
           if (redSepia > 255)
           {
               redSepia = 255;
           }

           if (greenSepia > 255)
           {
               greenSepia = 255;
           }
           image[i][j].rgbtBlue = blueSepia;
           image[i][j].rgbtRed = redSepia;
           image[i][j].rgbtGreen = greenSepia;
       }
   }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j+1)];
            image[i][width - (j+1)] = temp;
        }
    }


    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
   
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            
            float blur_red;
            float blur_blue;
            float blur_green;
            int contador;
            blur_red = blur_blue= blur_green = contador= 0;
   for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check if pixel is outside rows
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    //
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    
                    blur_red += temp[i + k][j + l].rgbtRed;
                    blur_blue+= temp[i + k][j + l].rgbtBlue;
                    blur_green += temp[i + k][j + l].rgbtGreen;
                    contador++;
                }
            }
            // 
            image[i][j].rgbtRed = round(blur_red / contador);
            image[i][j].rgbtGreen = round(blur_green / contador);
            image[i][j].rgbtBlue = round(blur_blue/ contador);
        }
    }
    return;
}