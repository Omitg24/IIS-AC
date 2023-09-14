#include <stdio.h>

//Include the header file
#include "1-1circle.h"

int main()
{
	double radius = 3.0;
	double area = circleArea(radius);
	printf("Circle area (radius=%f) is %f\n", radius, area);
	return 0;
}
