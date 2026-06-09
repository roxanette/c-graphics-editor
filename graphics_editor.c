#include <stdio.h>
#include <math.h>

#define HEIGHT 30
#define WIDTH 60
#define MAX_OBJECTS 100

char canvas[HEIGHT][WIDTH];

typedef struct
{
    int id;
    int type;      // 1=Rectangle 2=Line 3=Triangle 4=Circle
    int active;

    int x1, y1;
    int x2, y2;

    int width;
    int height;

    int radius;
} Shape;

Shape objects[MAX_OBJECTS];

int objectCount = 0;
int nextID = 1;

/* ---------- Utility ---------- */

void clearCanvas()
{
    int i,j;

    for(i=0;i<HEIGHT;i++)
    {
        for(j=0;j<WIDTH;j++)
        {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas()
{
    int i,j;

    for(i=0;i<HEIGHT;i++)
    {
        for(j=0;j<WIDTH;j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

/* ---------- Drawing Helpers ---------- */

void renderRectangle(Shape s)
{
    int i;

    for(i=s.x1;i<s.x1+s.width;i++)
    {
        if(i>=0 && i<WIDTH)
        {
            canvas[s.y1][i]='*';
            canvas[s.y1+s.height-1][i]='*';
        }
    }

    for(i=s.y1;i<s.y1+s.height;i++)
    {
        if(i>=0 && i<HEIGHT)
        {
            canvas[i][s.x1]='*';
            canvas[i][s.x1+s.width-1]='*';
        }
    }
}

void renderLine(Shape s)
{
    int i;

    if(s.y1 == s.y2)
    {
        int start=s.x1;
        int end=s.x2;

        if(start>end)
        {
            int t=start;
            start=end;
            end=t;
        }

        for(i=start;i<=end;i++)
            canvas[s.y1][i]='*';
    }
    else if(s.x1 == s.x2)
    {
        int start=s.y1;
        int end=s.y2;

        if(start>end)
        {
            int t=start;
            start=end;
            end=t;
        }

        for(i=start;i<=end;i++)
            canvas[i][s.x1]='*';
    }
}

void renderTriangle(Shape s)
{
    int i,j;

    for(i=0;i<s.height;i++)
    {
        canvas[s.y1+i][s.x1-i]='*';
        canvas[s.y1+i][s.x1+i]='*';
    }

    for(j=s.x1-s.height+1;
        j<=s.x1+s.height-1;
        j++)
    {
        canvas[s.y1+s.height-1][j]='*';
    }
}

void renderCircle(Shape s)
{
    int x,y;

    for(y=0;y<HEIGHT;y++)
    {
        for(x=0;x<WIDTH;x++)
        {
            double d=sqrt(
                (x-s.x1)*(x-s.x1)+
                (y-s.y1)*(y-s.y1)
            );

            if(d>=s.radius-0.5 &&
               d<=s.radius+0.5)
            {
                canvas[y][x]='*';
            }
        }
    }
}

/* ---------- Redraw ---------- */

void redrawCanvas()
{
    int i;

    clearCanvas();

    for(i=0;i<objectCount;i++)
    {
        if(objects[i].active==0)
            continue;

        switch(objects[i].type)
        {
            case 1:
                renderRectangle(objects[i]);
                break;

            case 2:
                renderLine(objects[i]);
                break;

            case 3:
                renderTriangle(objects[i]);
                break;

            case 4:
                renderCircle(objects[i]);
                break;
        }
    }
}

/* ---------- Add Objects ---------- */

void addRectangle()
{
    Shape s;

    s.id=nextID++;
    s.type=1;
    s.active=1;

    printf("Enter x y width height: ");
    scanf("%d%d%d%d",
          &s.x1,
          &s.y1,
          &s.width,
          &s.height);

    objects[objectCount++]=s;

    redrawCanvas();

    printf("Rectangle ID = %d\n", s.id);
}

void addLine()
{
    Shape s;

    s.id=nextID++;
    s.type=2;
    s.active=1;

    printf("Enter x1 y1 x2 y2: ");
    scanf("%d%d%d%d",
          &s.x1,
          &s.y1,
          &s.x2,
          &s.y2);

    objects[objectCount++]=s;

    redrawCanvas();

    printf("Line ID = %d\n", s.id);
}

void addTriangle()
{
    Shape s;

    s.id=nextID++;
    s.type=3;
    s.active=1;

    printf("Enter top_x top_y height: ");
    scanf("%d%d%d",
          &s.x1,
          &s.y1,
          &s.height);

    objects[objectCount++]=s;

    redrawCanvas();

    printf("Triangle ID = %d\n", s.id);
}

void addCircle()
{
    Shape s;

    s.id=nextID++;
    s.type=4;
    s.active=1;

    printf("Enter center_x center_y radius: ");
    scanf("%d%d%d",
          &s.x1,
          &s.y1,
          &s.radius);

    objects[objectCount++]=s;

    redrawCanvas();

    printf("Circle ID = %d\n", s.id);
}

/* ---------- Object Management ---------- */

void listObjects()
{
    int i;

    printf("\nOBJECT LIST\n");

    for(i=0;i<objectCount;i++)
    {
        if(objects[i].active)
        {
            printf("ID=%d  Type=%d\n",
                   objects[i].id,
                   objects[i].type);
        }
    }
}

void deleteObject()
{
    int id;
    int i;

    printf("Enter Object ID: ");
    scanf("%d",&id);

    for(i=0;i<objectCount;i++)
    {
        if(objects[i].id==id &&
           objects[i].active)
        {
            objects[i].active=0;

            redrawCanvas();

            printf("Object deleted.\n");
            return;
        }
    }

    printf("Object not found.\n");
}

/* ---------- Main ---------- */

int main()
{
    int choice;

    clearCanvas();

    while(1)
    {
        printf("\n===== 2D_GRAPHICS_EDITOR =====\n");
        printf("1. Add Rectangle\n");
        printf("2. Add Line\n");
        printf("3. Add Triangle\n");
        printf("4. Add Circle\n");
        printf("5. Delete Object\n");
        printf("6. List Objects\n");
        printf("7. Display Picture\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                addRectangle();
                break;

            case 2:
                addLine();
                break;

            case 3:
                addTriangle();
                break;

            case 4:
                addCircle();
                break;

            case 5:
                deleteObject();
                break;

            case 6:
                listObjects();
                break;

            case 7:
                displayCanvas();
                break;

            case 0:
                return 0;

            default:
                printf("Invalid Choice\n");
        }
    }
}
