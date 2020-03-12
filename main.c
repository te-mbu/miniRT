/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tembu <tembu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:42:34 by tembu             #+#    #+#             */
/*   Updated: 2020/03/12 11:57:10 by tembu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
t_vector		add_vector(t_vector vector, t_vector vector2)
{
	t_vector final;
	final.x =  vector.x + vector2.x;
	final.y =  vector.y + vector2.y;
	final.z =  vector.z + vector2.z;
	return (final);
}

t_vector		minus_vector(t_vector vector, t_vector vector2)
{
	t_vector final;
	final.x =  vector.x - vector2.x;
	final.y =  vector.y - vector2.y;
	final.z =  vector.z - vector2.z;
	return (final);
}

t_vector		mult_vector(t_vector vector, double a)
{
	t_vector final;
	final.x =  vector.x * a;
	final.y =  vector.y * a;
	final.z =  vector.z * a;
	return (final);
}

t_vector		div_vector(t_vector vector, double a)
{
	t_vector final;
	final.x =  vector.x / a;
	final.y =  vector.y / a;
	final.z =  vector.z / a;
	return (final);
}

double		dot_vector(t_vector vector, t_vector vector2)
{
	return ((double)(vector.x * vector2.x + vector.y * vector2.y + vector.z * vector2.z));
}

double		get_norm2(t_vector vector)
{
	return ((double)(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z));
}

t_vector	ft_simplified(t_vector vector)
{
	double new;
	new = sqrt(get_norm2(vector));
	vector.x /= new;
	vector.y /= new;
	vector.z /= new;
	return (vector);
}	

t_vector		create_vect(double x, double y, double z)
{
	t_vector my_vect;

	my_vect.x = x;
	my_vect.y = y;
	my_vect.z = z;
	return (my_vect);
}

double			std_min(double a, double b)
{
	return (b < a) ? b : a;
}

double			std_max(double a, double b)
{
	return (b > a) ? b : a;
}

double			final_color()
{
	double color;

	color = 0xff0000 * 256 * 256 + 0x00ff00 * 256 + 0x0000ff;
	return (color);
}

int			intersection(t_ray ray, t_sphere sphere, t_vector *P, t_vector *N)
{
	double t;
	double a = 1;
	double b = 2 * dot_vector(ray.dir, minus_vector(ray.origin, sphere.origin));
	double c = get_norm2(minus_vector(ray.origin, sphere.origin)) - (sphere.rayon * sphere.rayon);

	double delta = b * b - 4 * a * c;
	if (delta < 0)
		return (0);
	double t1 = (-b - sqrt(delta)) / (2 * a);
	double t2 = (-b + sqrt(delta)) / (2 * a);
	if (t2 < 0)
		return (0);
	if (t1 > 0)
		t = t1;
	else
		t = t2;
	
	*P = add_vector(ray.origin, (mult_vector(ray.dir, t)));
	*N = ft_simplified(minus_vector(*P, sphere.origin));
	
	return (1);
}

int			main(void)
{
    void    *mlx_ptr;
    void    *mlx_window;
	t_ray ray;
	t_sphere sphere;
	t_light light;
	t_vector P;
	t_vector N;
	double fov = 60 * (M_PI / 180);
	int width = 1024;
	int height = 1024;
    mlx_ptr = mlx_init();
    mlx_window = mlx_new_window(mlx_ptr, width, height, "titreee");
	int i = 0;
	int j = 0;
	int has_inter;
	int red;
	int green;
	int blue;
	unsigned int color;


	sphere.origin = create_vect(0, 0, -55);			//centre de la sphere
	sphere.rayon = 20;								//rayon de la sphere

	light.position = create_vect(15, 60, -40);
	light.intensity = 1000000;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			ray.origin = create_vect(0, 0, 0);
			ray.dir = create_vect(j - (width / 2), i - (height / 2), -width / (2 * tan(fov / 2)));
			ray.dir = ft_simplified(ray.dir);
			has_inter = intersection(ray, sphere, &P, &N);
			
			double intensity_pixel = 0;
			if (has_inter == 1)
				intensity_pixel = (light.intensity * std_max(0, dot_vector(ft_simplified(minus_vector(light.position, P)), N)))  / get_norm2(minus_vector(light.position, P));
			red = std_min(255, std_max(0, intensity_pixel));
			green = std_min(255, std_max(0, intensity_pixel));
			blue = std_min(255, std_max(0, intensity_pixel));
			color = red * 256 * 256 + green * 256 + blue;
			mlx_pixel_put(mlx_ptr, mlx_window, j, i, color);		
			j++;
		}
		i++;
	}
    mlx_loop(mlx_ptr);
    return (0);
}