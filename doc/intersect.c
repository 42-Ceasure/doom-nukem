#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int ac, char **av)
{
	double x1;
	double x2;
	double y1;
	double y2;
	double px;
	double py;
	double ang;
	double m1;
	double m2;
	double b1;
	double x;
	double y;
	double x_diff;
	double y_diff;

	if (ac != 6)
		write(1, "./a.out x1 y1 x2 y2 ang", 24);
	x1 = atof(av[1]);
	x2 = atof(av[3]);
	y1 = atof(av[2]);
	y2 = atof(av[4]);
	px = 0;
	py = 0;
	ang = atof(av[5]);
	m1 = (y2 - y1) / (x2 - x1);
	m2 = tan(ang);
	b1 = -x1 * m1 + y1;
	x = b1 / (m2 - m1);
	y = y1 + (x - x1) * m1;
	x_diff = (px - x);
	y_diff = (py - y);
	printf("m1 = %f\nm2 = %f\nb1 = %f\n x = %f\n y = %f\n x_diff = %f\n y_diff = %f\n", m1, m2, b1, x, y, x_diff, y_diff);

	return (0);
}