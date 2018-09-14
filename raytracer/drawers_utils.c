/*
** drawers_utils.c for raytracer2 in /home/ouranos27/my_desktop/C_Graphical_Prog/raytracer2
** 
** Made by philippe kam
** Login   <philippe.kam@epitech.eu>
** 
** Started on  Sun May 28 16:28:14 2017 philippe kam
** Last update Sun May 28 16:28:14 2017 philippe kam
*/

#include "raytracer2.h"

void		free_obj(t_obj *obj)
{
  free(obj->k_obj);
  free(obj->klight);
  free(obj->color);
  free(obj);
}

t_obj		*malloc_obj(t_obj *obj)
{
  if (!(obj = malloc(sizeof(t_obj)))
      || !(obj->k_obj = malloc(sizeof(float) * NB_OBJ))
      || !(obj->klight = malloc(sizeof(float *) * NB_LIGHT))
      || !(obj->color = malloc(sizeof(sfColor) * NB_OBJ)))
    return (NULL);
  return (obj);
}

t_vec		*rotate_effect(t_vec *vec)
{
  int		i;

  vec->angles.x = (vec->angles.x < 0) ? vec->angles.x * -1 : vec->angles.x;
  vec->dir_vector = rotate_zyx(vec->dir_vector, vec->angles);
  vec->angles.x *= -1;
  vec->dir_vector = rotate_xyz(vec->dir_vector, vec->angles);
  i = 0;
  while (i < NB_OBJ)
    {
      vec->angles.x = (vec->angles.x < 0) ? vec->angles.x * -1 : vec->angles.x;
      vec->eye_pos[i] = rotate_zyx(vec->eye_pos[i], vec->angles);
      vec->angles.x *= -1;
      vec->eye_pos[i] = rotate_xyz(vec->eye_pos[i], vec->angles);
      ++i;
    }
  return (vec);
}
