#include <stdio.h>

/* Place your struct definitions for Circle, Triangle, and Rectangle here */
typedef struct
{
     double x, y, r;
} Circle;

typedef struct
{
     double x1, x2, minY, maxY;
} Triangle;

typedef struct
{
     double minX, maxX, minY, maxY;
} Rectangle;

/* Define these 9 functions */
void InitializeCircle(Circle *c, double radius, double originX, double originY)
{
     c->r = radius;
     c->x = originX;
     c->y = originY;
}

void InitializeRectangle(Rectangle *r, double minX, double maxX, double minY, double maxY)
{
     r->minX = minX;
     r->maxX = maxX;
     r->minY = minY;
     r->maxY = maxY;
}

void InitializeTriangle(Triangle *t, double pt1X, double pt2X, double minY, double maxY)
{
     t->x1 = pt1X;
     t->x2 = pt2X;
     t->minY = minY;
     t->maxY = maxY;
}

double GetCircleArea(Circle *c)
{
     /* 3.14159 * radius * radius */
     return (3.14159 * c->r * c->r); 
}

double GetRectangleArea(Rectangle *r)
{
     /* (maxX - minX) * (maxY - minY) */
     return (r->maxX - r->minX) * (r->maxY - r->minY);
}

double GetTriangleArea(Triangle *t)
{
     /* ((pt2X - pt1X) * (maxY - minY)) / 2 */
     return ((t->x2 - t->x1) * (t->maxY - t->minY)) / 2;
}

void GetCircleBoundingBox(Circle *c, double *bbox)
{
     bbox[0] = c->x - c->r;
     bbox[1] = c->x + c->r;
     bbox[2] = c->y - c->r;
     bbox[3] = c->y + c->r;
}

void GetRectangleBoundingBox(Rectangle *r, double *bbox)
{
     bbox[0] = r->minX;
     bbox[1] = r->maxX;
     bbox[2] = r->minY;
     bbox[3] = r->maxY;
}

void GetTriangleBoundingBox(Triangle *t, double *bbox)
{
     bbox[0] = t->x1;
     bbox[1] = t->x2;
     bbox[2] = t->minY;
     bbox[3] = t->maxY;
}

/* DO NOT MODIFY AFTER THIS POINT */


void PrintTriangle(Triangle *t)
{
    double bbox[4];
    double area;
    area = GetTriangleArea(t);
    GetTriangleBoundingBox(t, bbox);
    printf("Triangle has area %f and bounding box [%f->%f], [%f->%f]\n",
           area, bbox[0], bbox[1], bbox[2], bbox[3]);
}

void PrintRectangle(Rectangle *r)
{
    double bbox[4];
    double area;
    area = GetRectangleArea(r);
    GetRectangleBoundingBox(r, bbox);
    printf("Rectangle has area %f and bounding box [%f->%f], [%f->%f]\n",
           area, bbox[0], bbox[1], bbox[2], bbox[3]);
}

void PrintCircle(Circle *c)
{
    double bbox[4];
    double area;
    area = GetCircleArea(c);
    GetCircleBoundingBox(c, bbox);
    printf("Circle has area %f and bounding box [%f->%f], [%f->%f]\n",
           area, bbox[0], bbox[1], bbox[2], bbox[3]);
}

int main()
{
    Circle c;
    Triangle t;
    Rectangle r;

    InitializeCircle(&c, 1, 0, 0);
    PrintCircle(&c);
    InitializeCircle(&c, 1.5, 6, 8);
    PrintCircle(&c);
    InitializeCircle(&c, 0.5, -3, 4);
    PrintCircle(&c);

    InitializeRectangle(&r, 0, 1, 0, 1);
    PrintRectangle(&r);
    InitializeRectangle(&r, 1, 1.1, 10, 20);
    PrintRectangle(&r);
    InitializeRectangle(&r, 1.5, 3.5, 10, 12);
    PrintRectangle(&r);

    InitializeTriangle(&t, 0, 1, 0, 1);
    PrintTriangle(&t);
    InitializeTriangle(&t, 0, 1, 0, 0.1);
    PrintTriangle(&t);
    InitializeTriangle(&t, 0, 10, 0, 50);
    PrintTriangle(&t);
}
