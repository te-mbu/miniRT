/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tembu <tembu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:44:32 by tembu             #+#    #+#             */
/*   Updated: 2020/03/12 11:43:39 by tembu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
#include "mlx/mlx.h"
#include <math.h>

typedef struct 	s_vector
{
	double x;
	double y;
	double z;
}				t_vector;

typedef struct 	s_ray
{
	t_vector 	origin;
	t_vector 	dir;
}				t_ray;

typedef struct 	s_sphere
{
	t_vector 	origin;
	double 		rayon;
}				t_sphere;

typedef struct 	s_light
{
	t_vector	position;
	double		intensity;
}				t_light;



#endif