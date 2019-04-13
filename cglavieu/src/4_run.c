/*BIG42HEADER*/

#include "doom.h"

void		get_height(t_map *m)
{
	int tmp;

	tmp = m->sector[m->player.sector].ceiling - m->sector[m->player.sector].floor;
	if (m->player.stance == 0)
	{
		if (tmp < STAND)
		{
			if (tmp > CROUCH)
			{
				if (m->player.height < CROUCH)
					m->player.height = m->player.height + 0.1;
				else
					m->player.height = CROUCH;
			}
			else
				m->player.height = CRAWL;
		}
		else if (m->player.height < CROUCH - 4)
			m->player.height = m->player.height + 0.1;
		else if (m->player.height < STAND - 0.2)
			m->player.height = m->player.height + 0.3;
		else
			m->player.height = STAND;
	}
	if (m->player.stance == 1)
	{
		if (tmp < CROUCH)
			m->player.height = CRAWL;
		else if (m->player.height < CROUCH - 4)
			m->player.height = m->player.height + 0.1;
		else if (m->player.height < CROUCH - 0.2)
			m->player.height = m->player.height + 0.3;
		else
			m->player.height = CROUCH;
	}
	if (m->player.stance == 2)
		m->player.height = CRAWL;
	m->player.ground = !m->player.fall;
}

void		is_falling(t_map *m)
{
	double	nxtz;

	if (m->player.fall == 1)
	{
		m->player.move_speed.z = m->player.move_speed.z - m->gravity;
		nxtz = m->player.coor.z + m->player.move_speed.z;
		if (m->player.move_speed.z < 0 && nxtz < m->sector[m->player.sector].floor + m->player.height)
		{
			m->player.coor.z = m->sector[m->player.sector].floor + m->player.height;
			m->player.move_speed.z = 0;
			m->player.fall = 0;
			m->player.ground = 1;
		}
		else if (m->player.move_speed.z > 0 && nxtz > m->sector[m->player.sector].ceiling)
		{
			m->player.move_speed.z = 0;
			m->player.fall = 1;
		}
		if (m->player.fall == 1)
		{
			m->player.coor.z = m->player.coor.z + m->player.move_speed.z;
			m->player.moving = 1;
		}
	}
}

void slow_down(t_env *w, t_map *m)
{
	if (w->inkeys[SDL_SCANCODE_W] || w->inkeys[SDL_SCANCODE_S]
	|| w->inkeys[SDL_SCANCODE_A] || w->inkeys[SDL_SCANCODE_Q])
		m->player.press = 1;
	else
		m->player.press = 0;
	if (m->player.press == 1)
		m->player.accel = 0.4;
	else
		m->player.accel = 0.2;
	m->player.move_speed.x = m->player.move_speed.x * (1 - m->player.accel) + m->player.move_speedless.x * m->player.accel;
	m->player.move_speed.y = m->player.move_speed.y * (1 - m->player.accel) + m->player.move_speedless.y * m->player.accel;
	if (m->player.press == 1)
		m->player.moving = 1;
	else
		m->player.moving = 0;
	m->player.move_speedless.x = 0.f;
	m->player.move_speedless.y = 0.f;
}

int			is_on_a_map_dot(t_map *m)
{
	t_intersect i;
	int		r1;
	int		r2;

	i.mem = 0;
	i.x1 = m->player.coor.x;
	i.y1 = m->player.coor.y;
	i.x2 = m->player.coor.x + m->player.move_speed.x;
	i.y2 = m->player.coor.y + m->player.move_speed.y;

	while (i.mem < m->dots_count)
	{
		i.x3 = m->dot[i.mem].x;
		i.y3 = m->dot[i.mem].y;
		r1 = (i.x3 - i.x1) * (i.y2 - i.y1);
		r2 = (i.y3 - i.y1) * (i.x2 - i.x1);
		if (r1 == r2)
		{
			if ((	i.x3 > vmin(i.x1, i.x2) && i.x3 < vmax(i.x1, i.x2))
				|| (i.y3 > vmin(i.y1, i.y2) && i.y3 < vmax(i.y1, i.y2)))
				return (-1);
		}
		i.mem++;
	}
	return (0);
}

int			is_next_to_a_dot(t_map *m)
{
	t_intersect	i;
	double		test;
	double		test2;
	double		testutx;
	double		testuty;
	double		slope;
	double		diffx;
	double		diffy;
	double		dist;
	double		dist_min;
	int			dot_mem;

	i.mem = 0;
	dist_min = 0;
	slope = 0;
	diffx = 0;
	diffy = 0;
	dist = 0;
	dot_mem = 0;
	i.x1 = m->player.coor.x;
	i.y1 = m->player.coor.y;
	while (i.mem < m->dots_count)
	{
		i.x2 = m->dot[i.mem].x;
		i.y2 = m->dot[i.mem].y;
		slope = (i.y2 - i.y1) / (i.x2 - i.x1);
		diffx = (i.x1 - i.x2);
		diffy = (i.y1 - i.y2);
		if (vabs(diffx) > vabs(diffy))
			dist = vabs(diffx / cos(slope));
		else
			dist = vabs(diffy / sin(slope));
		if (dist_min == 0)
		{
			dist_min = dist;
			dot_mem = i.mem;
		}
		else if (dist < dist_min)
		{
			dist_min = dist;
			dot_mem = i.mem;
		}
		i.mem++;
	}
	// m->player.move_speedless.x += m->player.anglecos / 3;
	// m->player.move_speedless.y += m->player.anglesin / 3;
	// slope = atan((i.y1 - m->dot[dot_mem].y) / (i.x1 - m->dot[dot_mem].x));
	slope = atan2((i.y1 - m->dot[dot_mem].y), (i.x1 - m->dot[dot_mem].x));
	testutx = m->player.coor.x + cos(PL_A);
	testuty = m->player.coor.y + sin(PL_A);
	test = atan((testuty - m->player.coor.y) / (testutx - m->player.coor.x));
	test2 = atan2((testuty - m->player.coor.y),(testutx - m->player.coor.x));
	// printf("slope:%f,cslope:%f,sslope:%f\n", slope, cos(slope), sin(slope));
	// printf("pslope:%f,corrected:%f,pa:%f,cpa:%f,spa:%f\n", test,test2, PL_A, cos(PL_A), sin(PL_A));
	// printf("ccorrected:%f,scorrected:%f\n", cos(test2), sin(test2));
	// printf("-----------------------------------------------------------\n");
	if (dist_min < 0.1)
	{
		// m->player.move_speed.x = 0;
		// m->player.move_speed.y = 0;
		// m->player.coor.x = m->dot[dot_mem].x + cos(slope)*dist_min;
		// m->player.coor.x = m->dot[dot_mem].y + sin(slope)*dist_min;
		m->player.move_speed.x = (cos(slope)*dist_min);
		m->player.move_speed.y = (sin(slope)*dist_min);
		return (-1);
	}
	// printf("point:%d,dist:%f\n", dot_mem, dist_min);
	return (0);
}

void move_player(double dx, double dy, t_map *m)
{
	int s;
	t_intersect i;
	t_coor coor;
	

	i.x1 = m->player.coor.x;
	i.y1 = m->player.coor.y;
	i.x2 = m->player.coor.x + dx;
	i.y2 = m->player.coor.y + dy;
	s = 0;
	while (s < m->sector[m->player.sector].wall_count)
	{
		i.x3 = m->sector[m->player.sector].dot[s].x;
		i.y3 = m->sector[m->player.sector].dot[s].y;
		i.x4 = m->sector[m->player.sector].dot[s + 1].x;
		i.y4 = m->sector[m->player.sector].dot[s + 1].y;
		coor.x = i.x2;
		coor.y = i.y2;
		if(m->sector[m->player.sector].network[s] >= 0  
		&& intersectbox(i) 
		&& pointside(coor, i.x3, i.y3, i.x4, i.y4) <= 0)
		{
			m->player.sector = m->sector[m->player.sector].network[s];
			if (is_on_a_map_dot(m) == -1)
			{
				dx = 0;
				dy = 0;
			}
			break;
		}
		s++;
	}
	m->player.coor.x = m->player.coor.x + dx;
	m->player.coor.y = m->player.coor.y + dy;
	m->player.anglesin = sin(m->player.angle);
	m->player.anglecos = cos(m->player.angle);
}

void		is_moving(t_map *m)
{
	int s;
	t_intersect i;
	t_coor		coor;

	s = 0;
	i.x1 = m->player.coor.x;
	i.y1 = m->player.coor.y;
	i.x2 = m->player.coor.x + m->player.move_speed.x;
	i.y2 = m->player.coor.y + m->player.move_speed.y;
	i.dx = m->player.move_speed.x;
	i.dy = m->player.move_speed.y;
	while (s < m->sector[m->player.sector].wall_count)
	{
		i.x3 = m->sector[m->player.sector].dot[s].x;
		i.y3 = m->sector[m->player.sector].dot[s].y;
		i.x4 = m->sector[m->player.sector].dot[s + 1].x;
		i.y4 = m->sector[m->player.sector].dot[s + 1].y;
		coor.x = i.x1 + i.dx;
		coor.y = i.y1 + i.dy;
		if(intersectbox(i) 
		&& pointside(coor, i.x3, i.y3, i.x4, i.y4) <= 0)
		{
			m->player.hole_low = 9e9;
			m->player.hole_high = -9e9;
			if (m->sector[m->player.sector].network[s] >= 0)
			{
				m->player.hole_low = vmax(m->sector[m->player.sector].floor, m->sector[m->sector[m->player.sector].network[s]].floor);
				m->player.hole_high = vmin(m->sector[m->player.sector].ceiling, m->sector[m->sector[m->player.sector].network[s]].ceiling);
			}
			if (m->player.hole_high < m->player.coor.z + HEADMARGIN
			|| m->player.hole_low > m->player.coor.z - m->player.height + KNEEH)
			{
				i.xd = m->sector[m->player.sector].dot[s + 1].x - m->sector[m->player.sector].dot[s].x;
				i.yd = m->sector[m->player.sector].dot[s + 1].y - m->sector[m->player.sector].dot[s].y;
				m->player.move_speed.x = i.xd * (i.dx * i.xd + i.dy * i.yd) / (i.xd * i.xd + i.yd * i.yd);
				m->player.move_speed.y = i.yd * (i.dx * i.xd + i.dy * i.yd) / (i.xd * i.xd + i.yd * i.yd);
				m->player.moving = 0;
				if (is_on_a_map_dot(m) == -1)
				{
					m->player.move_speed.x = 0;
					m->player.move_speed.y = 0;
					break;
				}
			}
		}
		s++;
	}
	// is_next_to_a_dot(m);
	move_player(m->player.move_speed.x, m->player.move_speed.y, m);
	m->player.fall = 1;

}

void		motion_events(t_env *w, t_map *m)
{
	PL_A = PL_A + w->event.motion.xrel * 0.001;
	if (PL_A > 2 * M_PI)
		PL_A = PL_A - 2 * M_PI;
	if (PL_A < 0)
		PL_A = PL_A + 2 * M_PI;
	m->yaw = vmid(m->yaw + w->event.motion.yrel * 0.002, -4, 4);
	m->player.yaw = m->yaw - m->player.move_speed.z * 0.02;
	if (m->player.display == 0)
	{
		w->event.motion.x = WIDTH / 2;
		w->event.motion.y = HEIGHT / 2;
	}
	move_player(0, 0, m);
}

void		key_events(t_env *w, t_map *m)
{
	if (w->inkeys[SDL_SCANCODE_W] && !w->inkeys[SDL_SCANCODE_LSHIFT])
	{
		m->player.move_speedless.x += m->player.anglecos / 3;
		m->player.move_speedless.y += m->player.anglesin / 3; 
		if (m->player.height <= 9.3)
		{
			m->player.move_speedless.x /= 2;
			m->player.move_speedless.y /= 2;
		}
		if (m->player.height <= 2)
		{
			m->player.move_speedless.x /= 2;
			m->player.move_speedless.y /= 2;
		}
	}
	if (w->inkeys[SDL_SCANCODE_S])
	{
		m->player.move_speedless.x -= m->player.anglecos / 5;
		m->player.move_speedless.y -= m->player.anglesin / 5;
		if (m->player.height <= 9.3)
		{
			m->player.move_speedless.x /= 2;
			m->player.move_speedless.y /= 2;
		}
		if (m->player.height <= 2)
		{
			m->player.move_speedless.x /= 2;
			m->player.move_speedless.y /= 2;
		}
	}
	if (w->inkeys[SDL_SCANCODE_A])
	{
		m->player.move_speedless.x += m->player.anglesin / 3;
		m->player.move_speedless.y -= m->player.anglecos / 3;
		if (m->player.height <= 9.3)
		{
			m->player.move_speedless.x /= 2;
			m->player.move_speedless.y /= 2;
		}
		if (m->player.height <= 2)
		{
			m->player.move_speedless.x /= 2;
			m->player.move_speedless.y /= 2;
		}
	}
	if (w->inkeys[SDL_SCANCODE_D])
	{
		m->player.move_speedless.x -= m->player.anglesin / 3;
		m->player.move_speedless.y += m->player.anglecos / 3;
		if (m->player.height <= 9.3)
		{
			m->player.move_speedless.x /= 2;
			m->player.move_speedless.y /= 2;
		}
		if (m->player.height <= 2)
		{
			m->player.move_speedless.x /= 2;
			m->player.move_speedless.y /= 2;
		}
	}
	if (w->inkeys[SDL_SCANCODE_Q])
	{
		PL_A = PL_A - 0.05;
		m->player.anglesin = sin(m->player.angle);
		m->player.anglecos = cos(m->player.angle);

	}
	if (w->inkeys[SDL_SCANCODE_E])
	{
		PL_A = PL_A + 0.05;
		m->player.anglesin = sin(m->player.angle);
		m->player.anglecos = cos(m->player.angle);
	}
	if (w->inkeys[SDL_SCANCODE_SPACE])
	{
		if (m->player.ground == 1 && m->player.stance == 0)
		{
			m->player.move_speed.z = m->player.move_speed.z + 0.8;
			m->player.fall = 1;
		}
	}
	if (w->inkeys[SDL_SCANCODE_LSHIFT] && w->inkeys[SDL_SCANCODE_W])
	{
		m->player.move_speedless.x += m->player.anglecos / 1.5;
		m->player.move_speedless.y += m->player.anglesin / 1.5; 
		if (m->player.height <= 9.3)
		{
			m->player.move_speedless.x /= 2;
			m->player.move_speedless.y /= 2;
		}
		if (m->player.height <= 2)
		{
			m->player.move_speedless.x /= 2;
			m->player.move_speedless.y /= 2;
		}
	}
}

int		run(t_env *w, t_map *m)
{
	while (1)
	{
		while (SDL_PollEvent(&w->event))
		{
			if (w->event.type == SDL_KEYDOWN)
			{
				if (KEY == 27)
					exit_game(w, m);
				if (KEY == SDLK_t)
				{
					if (m->trippymod == 1)
						m->trippymod = 0;
					else
						m->trippymod = 1;
				}
				if (KEY == SDLK_LCTRL)
				{
					m->player.stance = 1;
					m->player.fall = 1;
				}
				if (KEY == SDLK_z)
				{
					if (m->player.stance != 2)
						m->player.stance = 2;
					else
						m->player.stance = 0;
					m->player.fall = 1;
				}
				if (KEY == SDLK_x)
				{
					if (m->player.stance != 1)
						m->player.stance = 1;
					else
						m->player.stance = 0;
					m->player.fall = 1;
				}
				if (KEY == SDLK_KP_PLUS)
					m->maxrenderedsector += 1;
				if (KEY == SDLK_KP_MINUS)
					if (m->maxrenderedsector > 0)
						m->maxrenderedsector -= 1;
				if (KEY == SDLK_UP)
					m->player.field_of_vision_v += 5;
				if (KEY == SDLK_DOWN)
					m->player.field_of_vision_v -= 5;
				if (KEY == SDLK_RIGHT)
					m->player.field_of_vision_h += 5;
				if (KEY == SDLK_LEFT)
					m->player.field_of_vision_h -= 5;
				if (KEY == SDLK_PAGEUP)
					m->sector[m->player.sector].floor += 1;
				if (KEY == SDLK_PAGEDOWN)
					m->sector[m->player.sector].floor -= 1;
				if (KEY == SDLK_HOME)
					m->sector[m->player.sector].ceiling += 1;
				if (KEY == SDLK_END)
					m->sector[m->player.sector].ceiling -= 1;
				if (KEY == SDLK_TAB)
					m->player.display = 1;
				if (KEY == SDLK_KP_9)
					printf("hfov:%f,vfov:%f\n", m->player.field_of_vision_h, m->player.field_of_vision_v);
			}
			if (w->event.type == SDL_KEYUP)
			{
				if (KEY == SDLK_LCTRL)
					m->player.stance = 0;
				if (KEY == SDLK_TAB)
					m->player.display = 0;
			}
			if (w->event.type == SDL_MOUSEMOTION)
				motion_events(w, m);
		}
		if (m->player.display == 0)
			draw(w, m);
		else if (m->player.display == 1)
			draw_mini_map(w, m);
		img_update(w);
		get_height(m);
		is_falling(m);
		is_moving(m);
		w->inkeys = SDL_GetKeyboardState(NULL);
		key_events(w, m);
		slow_down(w, m);
		if (w->sequential_draw == 1)
			exit_game(w, m);
	}
	return (0);
}
