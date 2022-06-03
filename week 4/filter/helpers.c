#include "helpers.h"
#include "math.h"
#include "string.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get RGB values
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;

            // Calculate the average value and round it to the nearest integer
            int average = round((blue + green + red) / 3.0);

            // Set each RGB values to the average value
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary storage
    RGBTRIPLE pixel;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels on horizontally opposite sides
            pixel = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = pixel;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // Copying the image to keep an unaltered version to loop over
    memcpy(temp, image, sizeof(RGBTRIPLE) * height * width);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initiate RGB values to 0
            int blue = 0;
            int green = 0;
            int red = 0;

            // Initialize avarage to 0.0
            double average = 0.0;

            // Iterate from top to bottom of the current pixel
            for (int k = -1; k < 2; k++)
            {
                // Iterate from right to left of the current pixel
                for (int l = -1; l < 2; l++)
                {
                    // Check whether the current row and column are in the index of the image
                    if (i + k != -1 && j + l != -1 && i + k != height && j + l != width)
                    {
                        blue += temp[i + k][j + l].rgbtBlue;
                        green += temp[i + k][j + l].rgbtGreen;
                        red += temp[i + k][j + l].rgbtRed;

                        average++;
                    }
                }
            }

            // Calculate & Set each RGB values to the average value by rounding it to the nearest integer
            image[i][j].rgbtBlue = round(blue / average);
            image[i][j].rgbtGreen = round(green / average);
            image[i][j].rgbtRed = round(red / average);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // Copying the image to keep an unaltered version to loop over
    memcpy(temp, image, sizeof(RGBTRIPLE) * height * width);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize RGB Gx & Gy value to be 0
            int blueGx = 0, blueGy = 0;
            int greenGx = 0, greenGy = 0;
            int redGx = 0, redGy = 0;

            // Initialise convolution Gx, Gy matrix using Sobel formula
            int Gxy[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

            // Iterate from top to bottom of the current pixel
            for (int k = -1, m = 0; k < 2; k++, m++)
            {
                // Iterate from right to left of the current pixel
                for (int l = -1, n = 0; l < 2; l++, n++)
                {
                    // Check whether the current row and column are in the index of the image
                    if (i + k != -1 && j + l != -1 && i + k != height && j + l != width)
                    {
                        // Multiply and sum each pixel RGB value by each Gx matrix value
                        blueGx += Gxy[m][n] * temp[i + k][j + l].rgbtBlue;
                        greenGx += Gxy[m][n] * temp[i + k][j + l].rgbtGreen;
                        redGx += Gxy[m][n] * temp[i + k][j + l].rgbtRed;

                        // Multiply and sum each pixel RGB value by each Gy matrix value
                        blueGy += Gxy[n][m] * temp[i + k][j + l].rgbtBlue;
                        greenGy += Gxy[n][m] * temp[i + k][j + l].rgbtGreen;
                        redGy += Gxy[n][m] * temp[i + k][j + l].rgbtRed;

                    }
                }
            }

            // Compute and set each new RGB value as the square root of Gx2 + Gy2
            // If the RGB value exceeds the 255 limit, set the RGB value to 255
            image[i][j].rgbtBlue = fmin(255, round(sqrt(pow(blueGx, 2.0) + pow(blueGy, 2.0))));
            image[i][j].rgbtGreen = fmin(255, round(sqrt(pow(greenGx, 2) + pow(greenGy, 2.0))));
            image[i][j].rgbtRed = fmin(255, round(sqrt(pow(redGx, 2.0) + pow(redGy, 2.0))));
        }
    }
    return;
}