#include <stdio.h>

#define HEIGHT 30
#define WIDTH 60

char canvas[HEIGHT][WIDTH];

void clearCanvas()
{
    int i, j;
    for(i = 0; i < HEIGHT; i++)
    {
        for(j = 0; j < WIDTH; j++)
        {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas()
{
    int i, j;
    for(i = 0; i < HEIGHT; i++)
    {
        for(j = 0; j < WIDTH; j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    clearCanvas();
    displayCanvas();
    return 0;
}
