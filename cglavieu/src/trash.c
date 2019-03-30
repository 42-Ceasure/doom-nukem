typedef struct	s_item
{
	int sectorno;
	int sx1;
	int sx2;
}				t_item;

static void DrawScreen()
{
	enum { MaxQueue = 32 };  // maximum number of pending portal renders
	t_item queue[MaxQueue];
	t_item *head=queue;
	t_item *tail=queue;
	int ytop[WIDTH]={0};
	int ybottom[WIDTH];
	int renderedsectors[m->sector_count];
	unsigned int x=0;
	unsigned int n=0;

	while (x < WIDTH)
	{
		ybottom[x] = H-1;
		x++;
	}
	while (n<NumSectors)
	{
		renderedsectors[n] = 0;
		n++;
	}

	/* Begin whole-screen rendering from where the player is. */
	*head.sectorno = m->player.sector;
	*head.sx1 = 0;
	*head.sx2 = WIDTH-1;

	if(++head == queue+MaxQueue) head = queue;

	do {
	/* Pick a sector & slice from the queue to draw */
	const struct item now = *tail;
	if(++tail == queue+MaxQueue) tail = queue;

	if(renderedsectors[now.sectorno] & 0x21) continue; // Odd = still rendering, 0x20 = give up
	++renderedsectors[now.sectorno];
	const struct sector* const sect = &sectors[now.sectorno];
	/* Render each wall of this sector that is facing towards player. */
	for(unsigned s = 0; s < sect->npoints; ++s)
	{
		/* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
		float vx1 = sect->vertex[s+0].x - player.where.x, vy1 = sect->vertex[s+0].y - player.where.y;
		float vx2 = sect->vertex[s+1].x - player.where.x, vy2 = sect->vertex[s+1].y - player.where.y;
		/* Rotate them around the player's view */
		float pcos = player.anglecos, psin = player.anglesin;
		float tx1 = vx1 * psin - vy1 * pcos,  tz1 = vx1 * pcos + vy1 * psin;
		float tx2 = vx2 * psin - vy2 * pcos,  tz2 = vx2 * pcos + vy2 * psin;
		/* Is the wall at least partially in front of the player? */
		if(tz1 <= 0 && tz2 <= 0) continue;
		/* If it's partially behind the player, clip it against player's view frustrum */
		if(tz1 <= 0 || tz2 <= 0)
		{
			float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20.f;
			// Find an intersection between the wall and the approximate edges of player's view
			struct xy i1 = Intersect(tx1,tz1,tx2,tz2, -nearside,nearz, -farside,farz);
			struct xy i2 = Intersect(tx1,tz1,tx2,tz2,  nearside,nearz,  farside,farz);
			if(tz1 < nearz) { if(i1.y > 0) { tx1 = i1.x; tz1 = i1.y; } else { tx1 = i2.x; tz1 = i2.y; } }
			if(tz2 < nearz) { if(i1.y > 0) { tx2 = i1.x; tz2 = i1.y; } else { tx2 = i2.x; tz2 = i2.y; } }
		}
		/* Do perspective transformation */
		float xscale1 = hfov / tz1, yscale1 = vfov / tz1;    int x1 = W/2 - (int)(tx1 * xscale1);
		float xscale2 = hfov / tz2, yscale2 = vfov / tz2;    int x2 = W/2 - (int)(tx2 * xscale2);
		if(x1 >= x2 || x2 < now.sx1 || x1 > now.sx2) continue; // Only render if it's visible
		/* Acquire the floor and ceiling heights, relative to where the player's view is */
		float yceil  = sect->ceil  - player.where.z;
		float yfloor = sect->floor - player.where.z;
		/* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
		int neighbor = sect->neighbors[s];
		float nyceil=0, nyfloor=0;
		if(neighbor >= 0) // Is another sector showing through this portal?
		{
			nyceil  = sectors[neighbor].ceil  - player.where.z;
			nyfloor = sectors[neighbor].floor - player.where.z;
		}
		/* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
		#define Yaw(y,z) (y + z*player.yaw)
		int y1a  = H/2 - (int)(Yaw(yceil, tz1) * yscale1),  y1b = H/2 - (int)(Yaw(yfloor, tz1) * yscale1);
		int y2a  = H/2 - (int)(Yaw(yceil, tz2) * yscale2),  y2b = H/2 - (int)(Yaw(yfloor, tz2) * yscale2);
		/* The same for the neighboring sector */
		int ny1a = H/2 - (int)(Yaw(nyceil, tz1) * yscale1), ny1b = H/2 - (int)(Yaw(nyfloor, tz1) * yscale1);
		int ny2a = H/2 - (int)(Yaw(nyceil, tz2) * yscale2), ny2b = H/2 - (int)(Yaw(nyfloor, tz2) * yscale2);

		/* Render the wall. */
		int beginx = max(x1, now.sx1), endx = min(x2, now.sx2);
		for(int x = beginx; x <= endx; ++x)
		{
			/* Calculate the Z coordinate for this point. (Only used for lighting.) */
			int z = ((x - x1) * (tz2-tz1) / (x2-x1) + tz1) * 8;
			/* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
			int ya = (x - x1) * (y2a-y1a) / (x2-x1) + y1a, cya = clamp(ya, ytop[x],ybottom[x]); // top
			int yb = (x - x1) * (y2b-y1b) / (x2-x1) + y1b, cyb = clamp(yb, ytop[x],ybottom[x]); // bottom

			/* Render ceiling: everything above this sector's ceiling height. */
			vline(x, ytop[x], cya-1, 0x111111 ,0x222222,0x111111);
			/* Render floor: everything below this sector's floor height. */
			vline(x, cyb+1, ybottom[x], 0x0000FF,0x0000AA,0x0000FF);

			/* Is there another sector behind this edge? */
			if(neighbor >= 0)
			{
				/* Same for _their_ floor and ceiling */
				int nya = (x - x1) * (ny2a-ny1a) / (x2-x1) + ny1a, cnya = clamp(nya, ytop[x],ybottom[x]);
				int nyb = (x - x1) * (ny2b-ny1b) / (x2-x1) + ny1b, cnyb = clamp(nyb, ytop[x],ybottom[x]);
				/* If our ceiling is higher than their ceiling, render upper wall */
				unsigned r1 = 0x010101 * (255-z), r2 = 0x040007 * (31-z/8);
				vline(x, cya, cnya-1, 0, x==x1||x==x2 ? 0 : r1, 0); // Between our and their ceiling
				ytop[x] = clamp(max(cya, cnya), ytop[x], H-1);   // Shrink the remaining window below these ceilings
				/* If our floor is lower than their floor, render bottom wall */
				vline(x, cnyb+1, cyb, 0, x==x1||x==x2 ? 0 : r2, 0); // Between their and our floor
				ybottom[x] = clamp(min(cyb, cnyb), 0, ybottom[x]); // Shrink the remaining window above these floors
			}
			else
			{
				/* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
				unsigned r = 0x010101 * (255-z);
				vline(x, cya, cyb, 0, x==x1||x==x2 ? 0 : r, 0);
			}
		}
		/* Schedule the neighboring sector for rendering within the window formed by this wall. */
		if(neighbor >= 0 && endx >= beginx && (head+MaxQueue+1-tail)%MaxQueue)
		{
			*head = (struct item) { neighbor, beginx, endx };
			if(++head == queue+MaxQueue) head = queue;
		}
	} // for s in sector's edges
	++renderedsectors[now.sectorno];
	} while(head != tail); // render any other queued sectors
}