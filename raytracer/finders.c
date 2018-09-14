/*
** finders.c for raytracer1 in /home/ouranos27/my_desktop/C_Graphical_Prog/raytracer1
**
** Made by philippe kam
** Login   <philippe.kam@epitech.eu>
**
** Started on  Sun Mar 19 19:45:05 2017 philippe kam
** Last update Sun Mar 19 19:45:05 2017 philippe kam
*/

#include "raytracer2.h"

t_obj	*obj_between_light(t_obj *obj, t_vec *vec)
{
  int	i;

  i = 0;
  while (i < NB_LIGHT)
    {
      if ((obj->klight[i] = malloc(sizeof(float) * NB_OBJ)) == NULL)
	return (NULL);
      obj->klight[i][0] = intersect_plane(vec->point[obj->pos],
					     vec->light_vector[i][obj->pos]);
      obj->klight[i][1] = intersect_sphere(vec->point[obj->pos],
					   vec->light_vector[i][obj->pos], S_RADIUS);
      obj->klight[i][2] = intersect_cylinder(vec->point[obj->pos],
					     vec->light_vector[i][obj->pos], C_RADIUS);
      obj->klight[i][3] = intersect_cone(vec->point[3],
					 vec->light_vector[i][obj->pos], SEMIANGLE);
      ++i;
    }
  return (obj);
}

t_obj	*use_coef(t_obj *obj)
{
  int	i;
  int	j;

  i = 0;
  j = obj->pos;
  while (i < NB_LIGHT)
    {
      if ((obj->klight[i][0] >  1 && obj->klight[i][0] < 0)
    	  || (obj->klight[i][1] > 1 && obj->klight[i][1] < 0)
    	  || (obj->klight[i][2] > 1 && obj->klight[i][2] < 0)
    	  || (obj->klight[i][3] > 1 && obj->klight[i][3] < 0))
	{
	  obj->color[obj->pos].r *= obj->spots_coef;
	  obj->color[obj->pos].g *= obj->spots_coef;
	  obj->color[obj->pos].b *= obj->spots_coef;
	}
      ++i;
    }
  obj->spots_coef = powf(obj->spots_coef, BRIGHTNESS);
  obj->spots_coef += (obj->spots_coef < 0.9f) ? 0.1f : 1 - obj->spots_coef;
  obj->color[j].r = obj->color[j].r + obj->color[j].r * obj->spots_coef;
  obj->color[j].g = obj->color[j].g + obj->color[j].g * obj->spots_coef;
  obj->color[j].b = obj->color[j].b + obj->color[j].b * obj->spots_coef;
  return (obj);
}


t_vec	*find_the_normal(t_vec *vec, t_obj *obj)
{
  int	i;

  if (obj->pos == 0)
    {
      i = (vec->eye_pos[0].z > 0.0f) ? 1 : 0;
      vec->normal = get_normal_plane(i);
    }
  else if (obj->pos == 1)
    vec->normal = get_normal_sphere(vec->point[1]);
  else if (obj->pos == 2)
    vec->normal = get_normal_cylinder(vec->point[2]);
  else if (obj->pos == 3)
    vec->normal = get_normal_cone(vec->point[3], SEMIANGLE);
  vec->normal = normalizer(vec->normal);
  return (vec);
}

sfVector3f	*first_transparency(t_vec *vec, t_obj *obj)
{
  vec->point[0] = get_inters(obj->k_obj[0], vec->eye_pos[0],
			     vec->dir_vector);
  vec->point[1] = get_inters(obj->k_obj[1], vec->eye_pos[1],
			     vec->dir_vector);
  vec->point[2] = get_inters(obj->k_obj[2], vec->eye_pos[2],
			     vec->dir_vector);
  vec->point[3] = get_inters(obj->k_obj[3], vec->eye_pos[3],
			     vec->dir_vector);
  return (vec->point);
}

t_obj	*find_the_right_k(t_obj *obj, t_vec *vec)
{
  int   i;

  i = 0;
  obj->k = -0.99f;
  obj->pos = 0;
  if (!(vec->point = malloc(sizeof(sfVector3f) * NB_OBJ)))
    return (NULL);
  while (i < NB_OBJ)
    {
      if (obj->k_obj[i] > 0.1f)
	{
	  if (obj->k < 0.0f || obj->k > obj->k_obj[i])
	    {
	      obj->k = obj->k_obj[i];
	      //vec->point = first_transparency(vec, obj);
	      vec->point[i] = get_inters(obj->k, vec->eye_pos[i],
					 vec->dir_vector);
	      vec->point[i] = normalizer(vec->point[i]);
	      obj->pos = i;
	    }
	}
      ++i;
    }
  vec = find_the_normal(vec, obj);
  return (obj);
}
