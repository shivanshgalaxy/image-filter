//
// Created by sh on 19/8/23.
//

#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average = 0;
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            average = (int)roundf((float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE holder;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            holder.rgbtRed = image[i][j].rgbtRed;
            holder.rgbtGreen = image[i][j].rgbtGreen;
            holder.rgbtBlue = image[i][j].rgbtBlue;
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j].rgbtRed = holder.rgbtRed;
            image[i][width - 1 - j].rgbtGreen = holder.rgbtGreen;
            image[i][width - 1 - j].rgbtBlue = holder.rgbtBlue;
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
            float totalR = 0, totalG = 0, totalB = 0;
            int count = 0;
            for (int heightShift = -1; heightShift <= 1; heightShift++)
            {
                for (int widthShift = -1; widthShift <= 1; widthShift++)
                {
                    int curRow = i + heightShift;
                    int curCol = j + widthShift;
                    if (curRow >= 0 && curRow < height && curCol >= 0 && curCol < width)
                    {
                        RGBTRIPLE pixel = image[curRow][curCol];
                        totalR += pixel.rgbtRed;
                        totalG += pixel.rgbtGreen;
                        totalB += pixel.rgbtBlue;
                        count++;
                    }
                }
            }
            temp[i][j].rgbtRed = roundf(totalR/count);
            temp[i][j].rgbtGreen = roundf(totalG/count);
            temp[i][j].rgbtBlue = roundf(totalB/count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int arrX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int arrY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float totalRX = 0, totalGX = 0, totalBX = 0;
            float totalRY = 0, totalGY = 0, totalBY = 0;
            int count = 0;
            int rowCoords[] = {i - 1, i , i + 1};
            int colCoords[] = {j - 1, j, j + 1};
            for (int row = 0; row < 3; row++)
            {
                for (int col = 0; col < 3; col++)
                {
                    int curRow = rowCoords[row];
                    int curCol = colCoords[col];
                    if (curRow < 0 || curRow >= height || curCol < 0 || curCol >= width)
                    {
                        continue;
                    }
                    RGBTRIPLE pixel = image[curRow][curCol];
                    totalRX += pixel.rgbtRed * arrX[row][col];
                    totalGX += pixel.rgbtGreen * arrX[row][col];
                    totalBX += pixel.rgbtBlue * arrX[row][col];

                    totalRY += pixel.rgbtRed * arrY[row][col];
                    totalGY += pixel.rgbtGreen * arrY[row][col];
                    totalBY += pixel.rgbtBlue * arrY[row][col];
                }
            }

            float totalR = roundf(sqrtf((totalRX * totalRX) + (totalRY * totalRY)));
            float totalG = roundf(sqrtf((totalGX * totalGX) + (totalGY * totalGY)));
            float totalB = roundf(sqrtf((totalBX * totalBX) + (totalBY * totalBY)));
            if (totalR > 255)
            {
                temp[i][j].rgbtRed = 255;
            }
            else
            {
                temp[i][j].rgbtRed = (int)totalR;
            }
            if (totalG > 255)
            {
                temp[i][j].rgbtGreen = 255;
            }
            else
            {
                temp[i][j].rgbtGreen = (int)totalG;
            }
            if (totalB > 255)
            {
                temp[i][j].rgbtBlue = 255;
            }
            else
            {
                temp[i][j].rgbtBlue = (int)totalB;
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}