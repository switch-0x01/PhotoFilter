#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round(((float)image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

int border(int x)
{
    if (x < 0)
    {
        return 0;
    }
    else if (x > 255)
    {
        return 255;
    }
    else 
    {
        return x;
    }
}



// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float originalRed = image[i][j].rgbtRed;
            float originalBlue = image[i][j].rgbtBlue;
            float originalGreen = image[i][j].rgbtGreen;
            
            image[i][j].rgbtRed = border(round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue));
            image[i][j].rgbtGreen = border(round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue));
            image[i][j].rgbtBlue = border(round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue));
        }
    }
   return;
}

void swap(RGBTRIPLE *x, RGBTRIPLE *y)
{
     RGBTRIPLE tmp = *x;
     *x = *y;
     *y = tmp;
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j], &image[i][width-1-j]);
        }
    }
    return;
}



RGBTRIPLE blurred(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int averageRed = 0;
    int averageBlue = 0;
    int averageGreen = 0;
    int validpixels = 0;
    for (int k = -1; k < 2; k++)
    {
        for (int d = -1; d < 2; d++)
        {
            if ((k + i) >= 0 && (k + i) < height && (j + d) >= 0 && (j + d) < width)
            {
                validpixels += 1;
                averageRed += image[k + i][d + j].rgbtRed;
                averageGreen += image[k + i][d + j].rgbtGreen;
                averageBlue += image[k + i][d + j].rgbtBlue;
            }
        }
    }
    RGBTRIPLE blurred_pixel;
    blurred_pixel.rgbtRed = round((float)averageRed / validpixels);
    blurred_pixel.rgbtBlue = round((float)averageBlue / validpixels);
    blurred_pixel.rgbtGreen = round((float)averageGreen / validpixels);
    
    return blurred_pixel;
}



// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_image[i][j] = blurred(i, j, height, width, image);
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
    return;
}
