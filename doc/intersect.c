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

	if (ac != 8)
		write(1, "use ./a.out x1 y1 x2 y2 px py ang\n", 35);
	else
	{
		x1 = atof(av[1]);
		x2 = atof(av[3]);
		y1 = atof(av[2]);
		y2 = atof(av[4]);
		px = atof(av[5]);
		py = atof(av[6]);
		ang = atof(av[7]);
		m1 = (y2 - y1) / (x2 - x1);
		m2 = tan(ang);
		b1 = (px - x1) * m1 + (py - y1);
		//b1 = -x1 * m1 + y1;
		x = b1 / (m2 - m1);
		y = y1 + (x - x1) * m1;
		x_diff = (px - x);
		y_diff = (py - y);
		printf("m1 = %f\nm2 = %f\nb1 = %f\n x = %f\n y = %f\n x_diff = %f\n y_diff = %f\n", m1, m2, b1, x, y, x_diff, y_diff);
	}
	return (0);
}