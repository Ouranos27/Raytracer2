/*
** torus.c for raytracer2 in /home/ouranos27/my_desktop/C_Graphical_Prog/raytracer2/src
** 
** Made by philippe kam
** Login   <philippe.kam@epitech.eu>
** 
** Started on  Tue May 23 14:27:40 2017 philippe kam
** Last update Tue May 23 14:27:40 2017 philippe kam
*/

#include "raytracer2.h"

float		quartic_resolution(float *value)
{
  static double	pt1 = 0.5;
  static int	i = 0;
  double	x;
  sfVector2f	fx;
  double	p;

  if (++i < SCREEN_WIDTH)
    {
      fx.x = (value[0] * pow(pt1, 4)) + (value[1] * pow(pt1, 3))
	+ (value[2] * pow(pt1, 2)) + (value[3] * pt1) + value[4];
      p = (4 * (value[0] * pow(pt1, 3))) + (3 * (value[1] * pow(pt1, 2)))
	+ (2 * value[2] * pt1) + value[3];
      if (p == 0)
	exit(84);
      x = pt1 - (fx.x / p);
      if (round(pt1 * pow(10, 2)) == round(x * pow(10, 2)))
	return (EXIT_SUCCESS);
      fx.y = (value[0] * pow(x, 4)) + (value[1] * pow(x, 3))
	+ (value[2] * pow(x, 2)) + (value[3] * x) + value[4];
      pt1 = x;
      return (quartic_resolution(value));
    }
  return (pt1);
}

float		biggest_value(sfVector3f eye_pos, sfVector3f dir_vector,
			     float major_radius, float tube_radius)
{
  float		value;

  value = 2 * (2 * (eye_pos.x * dir_vector.x + eye_pos.y * dir_vector.y
		       + eye_pos.z * dir_vector.z)) * (powf(eye_pos.x, 2)
						       + powf(eye_pos.y, 2)
						       + powf(eye_pos.z, 2)
						       + powf(major_radius, 2)
						       + powf(tube_radius, 2))
    - 8 * powf(major_radius, 2) * (eye_pos.x * dir_vector.x
				   + eye_pos.y * dir_vector.y);
  return (value);
}

float		intersect_torus(sfVector3f eye_pos, sfVector3f dir_vector,
				float major_radius, float tube_radius)
{
  float		*value;

  if (!(value = malloc(sizeof(float) * 5)))
    return (-1);
  value[0] = powf(powf(dir_vector.x, 2) + powf(dir_vector.y, 2) +
		  powf(dir_vector.z , 2), 2);
  value[1] = 2 * sqrtf(value[0]) * 2 * (eye_pos.x * dir_vector.x + eye_pos.y *
				 dir_vector.y + eye_pos.z * dir_vector.z);
  value[2] = (2 * sqrtf(value[0]) * (powf(eye_pos.x, 2) + powf(eye_pos.y, 2)
			      + powf(eye_pos.z, 2) + powf(major_radius, 2)
			      - powf(tube_radius, 2)))
    + powf(2 * (eye_pos.x * dir_vector.x + eye_pos.y * dir_vector.y
		+ eye_pos.z * dir_vector.z), 2) - 4 * powf(major_radius, 2)
    * (powf(dir_vector.x, 2) + powf(dir_vector.y, 2));
  value[3] = biggest_value(eye_pos, dir_vector, major_radius, tube_radius);
  value[4] = powf(powf(eye_pos.x, 2) + powf(eye_pos.y, 2) + powf(eye_pos.z, 2)
		  + powf(major_radius, 2) - powf(tube_radius, 2), 2)
    - 4 * powf(major_radius, 2) * (powf(dir_vector.x, 2)
				   + powf(dir_vector.y, 2));
  return (quartic_resolution(value));
}
