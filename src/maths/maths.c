/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:53:33 by doferet           #+#    #+#             */
/*   Updated: 2025/04/02 17:33:28 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// hauteur des murs = 64
// hauteur du joueur = 32

//Fonctions trigonométriques
// sin = calcule le sinus
// cos = calcule le cosinus
// tan = calcule la tangente
// asin = calcule l'arc sinus
// acos = calcule l'arc cosinus
// atan = calcule l'arc tangente
// => fonction a utiliser pour les calculs

// le jouer a un fov de 60
// il est comme au centre d'un cercle trigonométrique
// utiliser des doubles

// centre Projection plan = 960, 540
// distance projection plan = 1662
// Angle between subsequent rays = 60 / 1920


/*======Finding horizontal intersection ======
1. Finding the coordinate of A.  
   If the ray is facing up      
     A.y = rounded_down(Py/64) * (64) - 1;
   If the ray is facing down
     A.y = rounded_down(Py/64) * (64) + 64;

   (In the picture, the ray is facing up, so we use
   the first formula.  
   A.y=rounded_down(224/64) * (64) - 1 = 191;
   Now at this point, we can find out the grid 
   coordinate of y.
   However, we must decide whether A is part of 
   the block above the line,
   or the block below the line.  
   Here, we chose to make A part of the block
   above the line, that is why we subtract 1 from A.y.
   So the grid coordinate of A.y is 191/64 = 2;

   A.x = Px + (Py-A.y)/tan(ALPHA);
   In the picture, (assume ALPHA is 60 degrees), 
   A.x=96 + (224-191)/tan(60) = about 115;
   The grid coordinate of A.x is 115/64 = 1;

   So A is at grid (1,2) and we can check 
   whether there is a wall on that grid.
   There is no wall on (1,2) so the ray will be 
   extended to C.

2. Finding Ya
   If the ray is facing up      
     Ya=-64;
   If the ray is facing down
     Ya=64;

3. Finding Xa
   Xa = 64/tan(60) = 36;

4. We can get the coordinate of C as follows:
   C.x=A.x+Xa = 115+36 = 151;
   C.y=A.y+Ya = 191-64 = 127;
   Convert this into grid coordinate by 
   dividing each component with 64.  
   The result is 
   C.x = 151/64 = 2 (grid coordinate), 
   C.y = 127/64 = 1 (grid coordinate) 
   So the grid coordinate of C is (2, 1).  
   (C programmer's note: Remember we always round down, 
   this is especially true since
   you can use right shift by 8 to divide by 64).

5. Grid (2,1) is checked.  
   Again, there is no wall, so the ray is extended 
   to D.  
   
6. We can get the coordinate of D as follows:
   D.x=C.x+Xa = 151+36 = 187;
   D.y=C.y+Ya = 127-64 = 63;
   Convert this into grid coordinate by 
   dividing each component with 64.  
   The result is 
   D.x = 187/64 = 2 (grid coordinate), 
   D.y = 63/64 = 0 (grid coordinate) 
   So the grid coordinate of D is (2, 0).  

7. Grid (2,0) is checked.  
   There is a wall there, so the process stop.

*/


//TODO: CALCULS
//horizontalVelocity = speed * Math.cos(Math.toRadians(facingAngle));
//verticalVelocity = speed * Math.sin(Math.toRadians(facingAngle));

void  calcul(int x, t_cub *cub)
{
  cub->player_pos.cam_orientation = 2 * x / (double)WIDTH - 1;
  
  cub->player_pos.dirx = cub->player_pos.dirx + cub->player_pos.planx * cub->player_pos.cam_orientation;
  cub->player_pos.diry = cub->player_pos.diry + cub->player_pos.plany * cub->player_pos.cam_orientation;

  cub->player_pos.deltax = fabs(1 / cub->player_pos.raydirx);
  cub->player_pos.deltay = fabs(1 / cub->player_pos.raydirx);
}
 
void  calcul_2(t_cub *cub)
{
  if (cub->player_pos.dirx < 0)
  {
    cub->player_pos.stepx = -1;
    cub->player_pos.sidex = (cub->player_pos.posx - cub->player_pos.mapx) * cub->player_pos.deltax;
  }
  else
  {
    cub->player_pos.stepx = 1;
   cub->player_pos.sidex = (cub->player_pos.mapx + 1.0 - cub->player_pos.posx) * cub->player_pos.deltax;
  }
  if (cub->player_pos.diry < 0)
  {
    cub->player_pos.stepy = -1;
    cub->player_pos.sidey = (cub->player_pos.posy - cub->player_pos.mapy) * cub->player_pos.deltay;
  }
  else
  {
    cub->player_pos.stepy = 1;
    cub->player_pos.sidey = (cub->player_pos.mapy + 1.0 - cub->player_pos.posy) * cub->player_pos.deltay;
  }
}

void  dda_algo(t_cub *cub)
{
  int hit;
  int side;

  hit = 0;
  side = 0;
  while (hit == 0)
  {
    if (cub->player_pos.sidex < cub->player_pos.sidey)
    {
      cub->player_pos.sidex += cub->player_pos.deltax;
      cub->player_pos.mapx += cub->player_pos.stepx;
      side = 0;
    }
    else
    {
      cub->player_pos.sidey += cub->player_pos.deltay;
      cub->player_pos.mapy += cub->player_pos.stepy;
      side = 1;
    }
    if (cub->map.map[cub->player_pos.mapy][cub->player_pos.mapx] > 0)
      hit = 1;
    }
  }


//   if(side == 0) perpWallDist = (sideDistX - deltaDistX);
//       else          perpWallDist = (sideDistY - deltaDistY);
