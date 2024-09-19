//
// Created by sh on 19/8/23.
//

#ifndef FILTER2_HELPERS_H
#define FILTER2_HELPERS_H

#endif //FILTER2_HELPERS_H
#include "bmp.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]);

