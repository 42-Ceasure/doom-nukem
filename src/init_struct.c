/*BIG42HEADER*/

#include "doom.h"

t_texture		pre_init_texture(int w, int h)
{
	t_texture	texture;


	if (w > 0 && h > 0)
	{
		texture.w = w;
		texture.h = h;
		texture.len = w * h;
		texture.pix = (Uint32 *)malloc(sizeof(Uint32) * w * h);
	}
	else
	{
		texture.w = 0;
		texture.h = 0;
		texture.len = 0;
		texture.pix = NULL;
	}
	return (texture);
}
