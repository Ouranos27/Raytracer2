/*
** drawers.c for raytracer1 in /home/ouranos27/my_desktop/C_Graphical_Prog/raytracer1
** 
** Made by philippe kam
** Login   <philippe.kam@epitech.eu>
** 
** Started on  Mon May 22 13:36:58 2017 philippe kam
** Last update Mon May 22 13:36:58 2017 philippe kam
*/

#include "raytracer2.h"

sfVector3f	**all_light_vectors(t_vec *vec)
{
  int		i;
  int		j;

  i = 0;
  while (i < NB_LIGHT)
    {
      j = 0;
      if (!(vec->light_vector[i] = malloc(sizeof(sfVector3f) * NB_OBJ)))
	return (NULL);
      while (j < NB_OBJ)
	{
	  vec->angles.x = (vec->angles.x < 0) ?
	    vec->angles.x * -1 : vec->angles.x;
	  vec->light_vector[i][j] = get_light_vector(vec->light[i]
						     , vec->point[j]);
	  vec->light_vector[i][j] = rotate_zyx(vec->light_vector[i][j]
					       , vec->angles);
	  vec->angles.x *= -1;
	  vec->light_vector[i][j] = rotate_xyz(vec->light_vector[i][j]
					       , vec->angles);
	  ++j;
	}
      ++i;
    }
  return (vec->light_vector);
}

float		**all_light_coefs(t_obj *obj, t_vec *vec)
{
  int		i;
  int		j;

  i = 0;
  if  (!(obj->light_coef = malloc(sizeof(float *) * (NB_LIGHT))))
    return (NULL);
  while (i < NB_LIGHT)
    {
      j = 0;
      if (!(obj->light_coef[i] = malloc(sizeof(float) * (NB_OBJ))))
	return (NULL);
      while (j < NB_OBJ)
	{
	  obj->light_coef[i][j] = get_light_coef(vec->light_vector[i][j]
						 , vec->normal);
	  ++j;
	}
      ++i;
    }
  return (obj->light_coef);
}

float		spots_coef(t_obj *obj)
{
  float		coef;
  int		i;
  int		j;

  i = 0;
  coef = 0;
  while (i < NB_LIGHT)
    {
      j = 0;
      while (j < NB_OBJ)
	{
	  coef += obj->light_coef[i][j];
	  ++j;
	}
      free(obj->light_coef[i]);
      ++i;
    }
  free(obj->light_coef);
  coef /= NB_OBJ * NB_LIGHT;
  return (coef);
}

void		draw_scene(t_my_framebuffer *framebuffer, t_obj *obj,
		   t_vec *vec, sfVector2f screen_pos)
{
  obj = find_the_right_k(obj, vec);
  if (obj->k > 0.00001f)
    {
      vec->light_vector = all_light_vectors(vec);
      vec->reflection = get_reflection_vector(vec->dir_vector, vec->normal);
      obj->light_coef = all_light_coefs(obj, vec);
      obj->spots_coef = spots_coef(obj);
      obj = obj_between_light(obj, vec);
      obj = use_coef(obj);
    }
  else
    obj->color[obj->pos] = sfBlack;
  my_put_pixel(framebuffer, (int)(screen_pos.x),
	       (int)(screen_pos.y), obj->color[obj->pos]);
}

int		draw_all(t_my_framebuffer *framebuffer, t_vec *vec)
{
  t_obj		*obj;
  sfVector2i	screen_size;
  sfVector2f	screen_pos;

  obj = NULL;
  if (!(obj = malloc_obj(obj)))
    return (ERROR);
  screen_pos.y = 0;
  screen_size.x = SCREEN_WIDTH;
  screen_size.y = SCREEN_HEIGHT;
  while (screen_pos.y++ < SCREEN_HEIGHT)
    {
      screen_pos.x = 0;
      while (screen_pos.x++ < SCREEN_WIDTH)
	{
	  vec->dir_vector = calc_dir_vector((float)375,
					    screen_size, screen_pos);
	  vec = rotate_effect(vec);
	  obj = my_put_obj(vec, obj);
	  draw_scene(framebuffer, obj, vec, screen_pos);
	}
    }
  free(obj);
  return (0);
}
