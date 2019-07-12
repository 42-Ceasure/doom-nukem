
/*BIG42HEADER*/

#include "doom.h"

void		go_forward(t_map *m)
{
	m->player.movespeed = 1;
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

void		go_back(t_map *m)
{
	m->player.movespeed = 0;
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

void		go_left(t_map *m)
{
	m->player.movespeed = 1;
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

void		go_right(t_map *m)
{
	m->player.movespeed = 1;
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

void		look_left(t_map *m)
{
	PL_A = PL_A - 0.05;
	if (PL_A > 2 * M_PI)
		PL_A = PL_A - 2 * M_PI;
	if (PL_A < 0)
		PL_A = PL_A + 2 * M_PI;
	m->player.anglesin = sin(m->player.angle);
	m->player.anglecos = cos(m->player.angle);
}

void		look_right(t_map *m)
{
	PL_A = PL_A + 0.05;
	if (PL_A > 2 * M_PI)
		PL_A = PL_A - 2 * M_PI;
	if (PL_A < 0)
		PL_A = PL_A + 2 * M_PI;
	m->player.anglesin = sin(m->player.angle);
	m->player.anglecos = cos(m->player.angle);
}

void		jump(t_env *w, t_map *m)
{
	if (m->player.ground == 1 && m->player.stance == 0)
	{
		Mix_PlayChannel(2, w->sound.jump, 0);
		m->player.move_speed.z = m->player.move_speed.z + 0.8;
		m->player.fall = 1;
		m->player.jump = 1;
	}
}

void		jet_pack(t_map *m)
{
	m->player.move_speed.z = m->player.move_speed.z + 0.2;
}

void		sprint(t_map *m)
{
	m->player.movespeed = 1.5;
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

void		hud(t_map *m)
{
	if (m->player.hud != 1)
		m->player.hud = 1;
	else
		m->player.hud = 0;
}

void		minimap(t_map *m)
{
	if (m->player.display != 1)
		m->player.display = 1;
	else
		m->player.display = 0;
}

void		ramassage(t_map *m)
{
	int i;

	i = 0;
	while (i < m->sprite_map_count)
	{
		if (m->sprt[i].range >= 1 && ft_strcmp(m->sprite[m->sprt[i].index].type, "item") == 0)
		{
			m->player.take[m->sprt[i].index] = 1;
			m->sprt[i].taken = 1;
		}
		i++;
	}
}

void		pause_music(void)
{
	if (Mix_PausedMusic() == 1)
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();
}

void		volume_more(t_env *w)
{
	w->sound.volume += 5;
	w->sound.volume = (int)vmid(0, w->sound.volume, 128);
	Mix_VolumeMusic(w->sound.volume);
}

void		volume_less(t_env *w)
{
	w->sound.volume -= 5;
	w->sound.volume = (int)vmid(0, w->sound.volume, 128);
	Mix_VolumeMusic(w->sound.volume);
}

void		crouch(t_map *m)
{
	m->player.stance = 1;
	m->player.fall = 1;
}

void		crawl_lock(t_map *m)
{
	if (m->player.stance != 2)
		m->player.stance = 2;
	else
		m->player.stance = 0;
	m->player.fall = 1;
}

void		crouch_lock(t_map *m)
{
	if (m->player.stance != 1)
		m->player.stance = 1;
	else
		m->player.stance = 0;
	m->player.fall = 1;
}

void		switch_weapon(t_map *m, int i)
{
	m->player.handed = i;
	m->player.switching = 300;
}

void		look_around(t_env *w, t_map *m)
{
	PL_A = PL_A + (w->event.motion.xrel * 0.001) * m->player.mousesp;
	if (PL_A > 2 * M_PI)
		PL_A = PL_A - 2 * M_PI;
	if (PL_A < 0)
		PL_A = PL_A + 2 * M_PI;
	m->yaw = vmid(m->yaw + (w->event.motion.yrel * 0.002) * m->player.mousesp, -2, 2);
	m->player.yaw = m->yaw - m->player.move_speed.z * 0.02;
}

void		set_shoot(t_map *m, int i)
{
	if (i == 0)
		m->player.shooting = 0;
	else
		m->player.shooting = 1;
}

void		shoot(t_env *w, t_map *m)
{
	if (w->dtime.shootime > (Uint32)m->weap[PH].firerate)
	{
		w->dtime.shootime = 0;
		if (m->weap[PH].actu_ammo > 0 && Mix_Playing(1) == 0)
		{
			m->player.firing = 1;
			Mix_PlayChannel(3, m->weap[PH].shoot, 0);
			m->weap[PH].actu_ammo -= 1;
		}
		else if (m->weap[PH].actu_ammo == 0)
			Mix_PlayChannel(4, w->sound.clic, 0);
	}
}

void		stop_aim(t_env *w, t_map *m)
{
	m->player.field_of_vision_h = WIDTH / 2;
	m->player.field_of_vision_v = HEIGHT / 2;
	m->player.aiming = 0;
}

void		aim(t_env *w, t_map *m)
{
	m->player.field_of_vision_h = WIDTH;
	m->player.field_of_vision_v = HEIGHT;
	m->player.aiming = 1;
}

void		reload_weapon(t_env *w, t_map *m)
{
	if (Mix_Playing(3) == 0 && m->weap[PH].actu_ammo != m->weap[PH].magazine)
	{
		if (PH == 1 && m->player.bullet[1] > 0)
		{
			while (m->weap[PH].actu_ammo < m->weap[PH].magazine && m->player.bullet[1] > 0)
			{
				m->player.bullet[1]--;
				m->weap[PH].actu_ammo++;
			}
			Mix_PlayChannel(1, w->sound.reload, 0);
		}
		else if (PH != 1 && m->player.bullet[0] > 0)
		{
			while (m->weap[PH].actu_ammo < m->weap[PH].magazine && m->player.bullet[0] > 0)
			{
				m->player.bullet[0]--;
				m->weap[PH].actu_ammo++;
			}
			Mix_PlayChannel(1, w->sound.reload, 0);
		}
	}
}

void	get_that_time(t_env *w)
{
	Uint32		result;

	w->invert = -w->invert;
	w->random = 1.3 * (double)rand() / (double)RAND_MAX - 0.3;
	w->dtime.otime = w->dtime.ctime;
	w->dtime.ctime = SDL_GetTicks();
	result = w->dtime.ctime - w->dtime.otime;
	if (result != 0)
		w->dtime.fps = 1000 / result;
	w->dtime.etime = w->dtime.etime + result;
	w->dtime.shootime = w->dtime.shootime + result;
	w->dtime.stime = w->dtime.stime + result;
	w->dtime.walk += result;
	w->dtime.dead += result;
	if (w->dtime.stime > 1000)
		w->dtime.stime = 0;
	if (w->dtime.walk > 500)
		w->dtime.walk = 0;
	if (w->dtime.dead > 200)
		w->dtime.dead = 0;
}
