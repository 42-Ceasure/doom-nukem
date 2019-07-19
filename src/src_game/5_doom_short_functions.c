/*BIG42HEADER*/

#include "doom.h"

double vmin(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
double vmax(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

double vabs(double a)
{
	if (a < 0)
		return (-a);
	else
		return (a);
}

double vmid(double a, double min, double max)
{
	return (vmin(vmax(a, min), max));
}

double sign(double a)
{
	return (((a) > 0) - ((a) < 0));
}

double v_c_p(double x0, double y0, double x1, double y1)
{
	return (x0 * y1 - x1 * y0);
}

double isoverlap(double a0, double a1, double b0, double b1)
{
	if ((vmin(a0,a1) <= vmax(b0,b1) && vmin(b0,b1) <= vmax(a0,a1)))
		return (1);
	else
		return (0);
}

double intersectbox(t_intersect i)
{

	if (isoverlap(i.x1, i.x2, i.x3, i.x4) && isoverlap(i.y1, i.y2, i.y3, i.y4))
		return (1);
	else
		return (0);
}

double pointside(t_coor p, double x0, double y0, double x1, double y1)
{
	return(sign(v_c_p(x1 - x0, y1 - y0, p.x - x0, p.y - y0)));
}

t_coor intersect(t_intersect i) 
{
	t_coor coor;
	double tmp1;
	double tmp2;
	double tmp3;
	double tmp4;

	tmp1 = v_c_p(i.x1, i.y1, i.x2, i.y2);
	tmp2 = i.x1 - i.x2;
	tmp3 = v_c_p(i.x3, i.y3, i.x4, i.y4);
	tmp4 = i.x3 - i.x4;
	coor.z = v_c_p(tmp1, tmp2, tmp3, tmp4);
	coor.x = (coor.z / v_c_p(i.x1 - i.x2, i.y1 - i.y2, i.x3 - i.x4, i.y3 - i.y4));
	tmp1 = v_c_p(i.x1, i.y1, i.x2, i.y2);
	tmp2 = i.y1 - i.y2;
	tmp3 = v_c_p(i.x3, i.y3, i.x4, i.y4);
	tmp4 = i.y3 - i.y4;
	coor.z = v_c_p(tmp1, tmp2, tmp3, tmp4);
	coor.y = (coor.z / v_c_p(i.x1 - i.x2, i.y1 - i.y2, i.x3 - i.x4, i.y3 - i.y4));
	coor.z = 0;
	return (coor);
}

double yaw(double y, double z, t_map *m)
{
	return (y + z * m->player.yaw);
}

double	pythagore(double a, double b)
{
	return (sqrt(a * a + b * b));
}
