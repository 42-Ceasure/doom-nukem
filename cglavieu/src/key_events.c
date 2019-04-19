/**/

#include "doom.h"

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
			Mix_PlayChannel(2, w->sound.jump, 0);
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