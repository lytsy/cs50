#include "helpers.h"
#include <stdio.h>
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pixel;
    int average;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            pixel = image[j][i];
            average = round((pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed) / 3);
            pixel.rgbtBlue = average;
            pixel.rgbtGreen = average;
            pixel.rgbtRed = average;
            image[j][i] = pixel;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pixel, tmp;
    int middle = round(width / 2);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < middle; j++)
        {
            pixel = image[i][j];
            tmp = image[i][width - j];
            image[i][width - j] = pixel;
            image[i][j] = tmp;
        }
    }
    return;
}

RGBTRIPLE blur_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int r = 0;
    int g = 0;
    int b = 0;
    int pixels = 0;
    RGBTRIPLE point;
    for (int y = i - 1; y <= i + 1; y++)
    {
        for (int x = j - 1; x <= j + 1; x++)
        {
            if (y >= 0 && y < height && x >= 0 && x < width)
            {
                point = image[y][x];
                r += point.rgbtRed;
                g += point.rgbtGreen;
                b += point.rgbtBlue;
                pixels++;
            }
        }
    }
    point.rgbtRed = round(r / pixels);
    point.rgbtGreen = round(g / pixels);
    point.rgbtBlue = round(b / pixels);
    return point;
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pixel, tmp;
    //so that blurry pixels do not affect the rest, save them first in a temporary image
    RGBTRIPLE tmp_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp_image[i][j] = blur_pixel(i, j, height, width, image);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp_image[i][j];
        }
    }
    return;
}

int sobel(int gx, int gy)
{
    int color = round(sqrt(pow(gx, 2) + pow(gy, 2)));
    if (color > 255)
    {
        return 255;
    }
    return color;
}

RGBTRIPLE edge_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int rate_x[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int rate_y[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    int rate_index = 0;
    int gx_r = 0;
    int gx_g = 0;
    int gx_b = 0;
    int gy_r = 0;
    int gy_g = 0;
    int gy_b = 0;
    RGBTRIPLE point;
    for (int y = i - 1; y <= i + 1; y++)
    {
        for (int x = j - 1; x <= j + 1; x++)
        {
            if (y >= 0 && y < height && x >= 0 && x < width)
            {
                point = image[y][x];
                gx_r += point.rgbtRed * rate_x[rate_index];
                gx_g += point.rgbtGreen * rate_x[rate_index];
                gx_b += point.rgbtBlue * rate_x[rate_index];
                gy_r += point.rgbtRed * rate_y[rate_index];
                gy_g += point.rgbtGreen * rate_y[rate_index];
                gy_b += point.rgbtBlue * rate_y[rate_index];
            }
            rate_index++;
        }
    }
    point.rgbtRed = sobel(gx_r, gy_r);
    point.rgbtGreen = sobel(gx_g, gy_g);
    point.rgbtBlue = sobel(gx_b, gy_b);
    return point;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pixel, tmp;
    //so that modified pixels do not affect the rest, save them first in a temporary image
    RGBTRIPLE tmp_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp_image[i][j] = edge_pixel(i, j, height, width, image);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp_image[i][j];
        }
    }
    return;
}
