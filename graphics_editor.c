#include <stdio.h>

#define HEIGHT 30
#define WIDTH 60

char canvas[HEIGHT][WIDTH];

/* Function Prototypes */
void clearCanvas();
void displayCanvas();
void drawRectangle();
void drawLine();

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
    scanf("%d %d %d %d", &x, &y, &w, &h);

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

void drawLine()
{
    int x1, y1, x2, y2, i;

    printf("Enter x1 y1 x2 y2: ");
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    if(y1 == y2)
    {
        for(i = x1; i <= x2; i++)
        {
            canvas[y1][i] = '*';
        }
    }
    else if(x1 == x2)
    {
        for(i = y1; i <= y2; i++)
        {
            canvas[i][x1] = '*';
        }
    }
    else
    {
        printf("Only horizontal and vertical lines supported.\n");
    }
}

int main()
{
    int choice;

    clearCanvas();

    while(1)
    {
        printf("\n===== GRAPHICS EDITOR =====\n");
        printf("1. Draw Rectangle\n");
        printf("2. Draw Line\n");
        printf("3. Display Picture\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice){
        case 1:
        drawRectangle();
        break;

        case 2:
        drawLine();
        break;

        case 3:
        displayCanvas();
        break;

        case 0:
        return 0;

        default:
        printf("Invalid choice!\n");
        }
    }

    return 0;
}

