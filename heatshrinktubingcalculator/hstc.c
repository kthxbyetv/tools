/*
The MIT License (MIT)

Copyright (c) 2014 Jean THOMAS

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <stdio.h>
#include <math.h>
#include "hstc.h"

int main() {
    int choice = 0, i, values_found;
    char shrink_factor = 0;
    float object_perimeter, heatshrink_perimeter, shrinked_perimeter;
    
    printf("Heatshrink tubing calculator by Jean THOMAS\n\n");
    printf("1 : Circle profile\n");
    printf("2 : Rectangular profile \n");
    printf("Enter your choice : ");
    scanf("%1d",&choice);
    
    if (choice == 1 || choice == 2) {
        if (choice == 1) {
            // Circle
            float circle_diameter = 0;
            
            printf("\nEnter the diameter of the circle (in mm) : ");
            scanf("%f",&circle_diameter);
            
            if (circle_diameter == 0) {
                printf("Wrong value, exiting.\n");
                return 1; 
            } else {
                object_perimeter = calculate_circle_perimeter(circle_diameter);
            }
        } else if (choice == 2) {
            // Rectangle
            float rectangle_width = 0, rectangle_height = 0;
            
            printf("\nEnter the width of the rectangle (in mm) : ");
            scanf("%f",&rectangle_width);
            printf("Enter the height of the rectangle (in mm) : ");
            scanf("%f",&rectangle_height);
            
            if (rectangle_width == 0 || rectangle_height == 0) {
                printf("Wrong values, exiting.\n");
                return 1;
            }
            
            object_perimeter = calculate_rectangle_perimeter(rectangle_width, rectangle_height);
        }
        
        printf("\nShrinking factor (percentage) : ");
        scanf("%d",&shrink_factor);
        
        if (shrink_factor == 0 || shrink_factor > 100 || shrink_factor < 0) {
            printf("Wrong values, exiting.\n");
            return 1;
        }
        
        printf("\nObject perimeter : %.2f mm\n\n",object_perimeter);
        
        for (i = 0; i < num_heatshrink_diameters; ++i) {
            heatshrink_perimeter = calculate_circle_perimeter(heatshrink_diameters[i]);
            shrinked_perimeter = heatshrink_perimeter * ((float)shrink_factor / 100);
            
            if (object_perimeter < heatshrink_perimeter && object_perimeter > shrinked_perimeter) {
                printf("Found correct value : %.2f mm (unshrinked delta : %.1f %%, shrinked delta : %.1f %%)\n",
                       heatshrink_diameters[i],
                       100 - (object_perimeter/heatshrink_perimeter) * 100,
                       (shrinked_perimeter/object_perimeter) * 100);
                values_found++;
            } 
        }
        
        if (values_found == 0) {
            printf("No values found. Check your values, and or new heatshrink diameters.\n");
        }
        
    } else {
        printf("Wrong value, exiting.\n");
        return 1;
    }
    
    return 0;
}

float calculate_circle_perimeter(float circle_diameter) {
    return circle_diameter * M_PI;
}

float calculate_rectangle_perimeter(float rectangle_width, float rectangle_height) {
    return rectangle_width * 2 + rectangle_height * 2;
}