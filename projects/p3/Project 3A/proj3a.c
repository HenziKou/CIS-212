#include <stdio.h>
#include <stdlib.h>

/* Place struct definitions for Circle, Triangle, and Rectangle here */
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

/* PART 2: Make an abstract type called Shape */
typedef struct
{
    void *self;    
    double (*GetArea)(void *);
    void (*GetBoundingBox)(void *, double *);
} Shape;

/* PART 5: NEW FUNCTIONS */
double GetArea(Shape *s)
{
    return s->GetArea(s->self);
}

void GetBoundingBox(Shape *s, double *bbox)
{
    s->GetBoundingBox(s->self, bbox);
}

/* PART 3: Modify the 9 functions below */
double GetCircleArea(void *a)
{
    Circle *c = (Circle *) a;    
    return (3.14159 * c->r * c->r); 
}

double GetRectangleArea(void *a)
{
    Rectangle *r = (Rectangle *) a;
    return (r->maxX - r->minX) * (r->maxY - r->minY);
}

double GetTriangleArea(void *a)
{
    Triangle *t = (Triangle *) a;
    return ((t->x2 - t->x1) * (t->maxY - t->minY)) / 2;
}

void GetCircleBoundingBox(void *a, double *bbox)
{
    Circle *c = (Circle *) a;

    bbox[0] = c->x - c->r;
    bbox[1] = c->x + c->r;
    bbox[2] = c->y - c->r;
    bbox[3] = c->y + c->r;
}

void GetRectangleBoundingBox(void *a, double *bbox)
{
    Rectangle *r = (Rectangle *) a;

    bbox[0] = r->minX;
    bbox[1] = r->maxX;
    bbox[2] = r->minY;
    bbox[3] = r->maxY;
}

void GetTriangleBoundingBox(void *a, double *bbox)
{
    Triangle *t = (Triangle *) a;

    bbox[0] = t->x1;
    bbox[1] = t->x2;
    bbox[2] = t->minY;
    bbox[3] = t->maxY;
}

/* PART 4: Reimplement the Create functions */
Shape *CreateCircle(double radius, double originX, double originY)
{
    Circle *c = malloc(sizeof(Circle));
    Shape *s = malloc(sizeof(Shape));
    s->self = c;
    s->GetArea = GetCircleArea;
    s->GetBoundingBox = GetCircleBoundingBox;

    c->r = radius;
    c->x = originX;
    c->y = originY;

    return s;
}

Shape *CreateRectangle(double minX, double maxX, double minY, double maxY)
{
    Rectangle *r = malloc(sizeof(Rectangle));
    Shape *s = malloc(sizeof(Shape));
    s->self = r;
    s->GetArea = GetRectangleArea;
    s->GetBoundingBox = GetRectangleBoundingBox;

    r->minX = minX;
    r->maxX = maxX;
    r->minY = minY;
    r->maxY = maxY;

    return s;
}

Shape *CreateTriangle(double pt1X, double pt2X, double minY, double maxY)
{
    Triangle *t = malloc(sizeof(Triangle));
    Shape *s = malloc(sizeof(Shape));
    s->self = t;
    s->GetArea = GetTriangleArea;
    s->GetBoundingBox = GetTriangleBoundingBox;

    t->x1 = pt1X;
    t->x2 = pt2X;
    t->minY = minY;
    t->maxY = maxY;

    return s;
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
    Shape *shapes[9];
    int    i;
    shapes[0] = CreateCircle(1, 0, 0);
    shapes[1] = CreateCircle(1.5, 6, 8);
    shapes[2] = CreateCircle(0.5, -3, 4);

    shapes[3] = CreateRectangle(0, 1, 0, 1);
    shapes[4] = CreateRectangle(1, 1.1, 10, 20);
    shapes[5] = CreateRectangle(1.5, 3.5, 10, 12);

    shapes[6] = CreateTriangle(0, 1, 0, 1);
    shapes[7] = CreateTriangle(0, 1, 0, 0.1);
    shapes[8] = CreateTriangle(0, 10, 0, 50);

    for (i = 0 ; i < 9 ; i++)
    {
        double bbox[4];
        printf("Shape %d\n", i);
        printf("\tArea: %f\n", GetArea(shapes[i]));
        GetBoundingBox(shapes[i], bbox);
        printf("\tBbox: %f-%f, %f-%f\n", bbox[0], bbox[1], bbox[2], bbox[3]);
    }
}
