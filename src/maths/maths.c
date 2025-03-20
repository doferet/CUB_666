/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:53:33 by doferet           #+#    #+#             */
/*   Updated: 2025/03/20 11:48:10 by doferet          ###   ########.fr       */
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