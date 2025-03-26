/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:53:33 by doferet           #+#    #+#             */
/*   Updated: 2025/03/26 17:41:01 by doferet          ###   ########.fr       */
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

//double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
//double rayDirX = dirX + planeX * cameraX;
//double rayDirY = dirY + planeY * cameraX

//deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
//deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
//* OU
//deltaDistX = abs(1 / rayDirX)
//deltaDistY = abs(1 / rayDirY)

  //calculate step and initial sideDist
/*  if (rayDirX < 0)
  {
    stepX = -1;
    sideDistX = (posX - mapX) * deltaDistX;
  }
  else
  {
    stepX = 1;
    sideDistX = (mapX + 1.0 - posX) * deltaDistX;
  }
  if (rayDirY < 0)
  {
    stepY = -1;
    sideDistY = (posY - mapY) * deltaDistY;
  }
  else
  {
    stepY = 1;
    sideDistY = (mapY + 1.0 - posY) * deltaDistY;
  }*/

  //! MURS
  /*
        perform DDA
      while (hit == 0)
      {
        jump to next map square, either in x-direction, or in y-direction
        if (sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        Check if ray has hit a wall
        if (worldMap[mapX][mapY] > 0) hit = 1;
      } 
  */


//   if(side == 0) perpWallDist = (sideDistX - deltaDistX);
//       else          perpWallDist = (sideDistY - deltaDistY);

