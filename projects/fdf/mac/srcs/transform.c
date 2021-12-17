/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaatar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 01:18:43 by bbaatar           #+#    #+#             */
/*   Updated: 2021/12/17 01:42:00 by bbaatar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_coord	transform_iso(t_coord coord)
{
	t_coord	result;

	result.x = (coord.x - coord.z) / sqrt(2);
	result.y = (coord.x + 2 * coord.y + coord.z) / sqrt(6);
	return (result);
}

t_coord	transform(t_camera camera, t_coord coord)
{
	t_coord	result;

	coord.z *= (camera.zoom * camera.depth) / 2;
	coord.x *= camera.zoom;
	coord.y *= camera.zoom;
	coord.x += 256;
	coord.y += 144;
	coord.x += camera.move_x;
	coord.y += camera.move_y;
	xaxis_rot(&coord.y, &coord.z, camera.thetaX);
	yaxis_rot(&coord.x, &coord.z, camera.thetaY);
	zaxis_rot(&coord.x, &coord.y, camera.thetaZ);
	result = transform_iso(coord);
	return (result);
}

void	calc_points_x(t_image *data, t_data img)
{
	int		x;
	int		y;
	int		percentage;
	t_coord	a;
	t_coord	b;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width - 1)
		{
			a.x = x;
			a.y = y;
			a.z = data->points[y][x];
			percentage = percent(data->min, data->max, a.z); //z point iin huvid, jishee ni 4->40% bolno.
			b.x = x + 1;
			b.y = y;
			b.z = data->points[y][x + 1];
			plot_line(transform(*data->camera, a),
				transform(*data->camera, b), &img);
			x++;
		}
		y++;
	}
}

void	calc_points_y(t_image *data, t_data img)
{
	int		x;
	int		y;
	t_coord	a;
	t_coord	b;

	x = 0;
	while (x < data->width)
	{
		y = 0;
		while (y < data->height - 1)
		{
			a.x = x;
			a.y = y;
			a.z = data->points[y][x];
			a.color = a.z;
			b.x = x;
			b.y = y + 1;
			b.z = data->points[y + 1][x];
			b.color = b.z;
			plot_line(transform(*data->camera, a),
				transform(*data->camera, b), &img);
			y++;
		}
		x++;
	}
}
