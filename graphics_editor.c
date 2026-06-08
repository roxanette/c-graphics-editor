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

void drawRectangle()
{
    int x, y, w, h, i;

    printf("Enter x y width height: ");
    scanf("%d%d%d%d", &x, &y, &w, &h);

    for(i = x; i < x + w; i++)
    {
        canvas[y][i] = '*';
        canvas[y + h - 1][i] = '*';
    }

    for(i = y; i < y + h; i++)
    {
        canvas[i][x] = '*';
        canvas[i][x + w - 1] = '*';
    }
}

int main()
{
    int choice;

    clearCanvas();

    while(1)
    {
        printf("\n===== GRAPHICS EDITOR =====\n");
        printf("1. Display Picture\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                displayCanvas();
                break;

            case 0:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}

