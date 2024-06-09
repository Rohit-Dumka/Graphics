#include <stdio.h>
#include <math.h>

// Function to plot the points
void plot(int x, int y) {
    printf("(%d, %d)\n", x, y);
}

// Function to draw the upper half of a circle using Midpoint Circle Algorithm
void drawHalfCircle(int radius) {
    int x = 0;
    int y = radius;
    int p = 1 - radius; // Initial decision parameter

    // Plot the initial point on the circle
    plot(x, y);

    // Loop to generate the remaining points in the upper half of the circle
    while (x < y) {
        x++;

        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }

        // Plot the points for the upper half of the circle
        plot(x, y);
        plot(-x, y);
        plot(y, x);
        plot(-y, x);
    }
}

int main() {
    int radius;

    printf("Enter the radius of the circle: ");
    scanf("%d", &radius);

    printf("Points on the upper half of the circle:\n");
    drawHalfCircle(radius);

    return 0;
}
