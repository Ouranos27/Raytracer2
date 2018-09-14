/*
** my_put_obj.c for raytracer1 in /home/ouranos27/my_desktop/C_Graphical_Prog/raytracer1
** 
** Made by philippe kam
** Login   <philippe.kam@epitech.eu>
** 
** Started on  Sun Mar 19 19:38:34 2017 philippe kam
** Last update Sun Mar 19 19:38:34 2017 philippe kam
*/

#include "raytracer2.h"

t_obj	*my_put_cone(t_vec *vec, t_obj *obj)
{
  obj->k_obj[3] = intersect_cone(vec->eye_pos[3], vec->dir_vector, SEMIANGLE);
  obj->color[3] = sfYellow;
  return (obj);
}

t_obj   *my_put_cylinder(t_vec *vec, t_obj *obj)
{
  obj->k_obj[2] = intersect_cylinder(vec->eye_pos[2], vec->dir_vector, C_RADIUS);
  obj->color[2] = sfGreen;
  return (obj);
}

t_obj	*my_put_sphere(t_vec *vec, t_obj *obj)
{
  obj->k_obj[1] = intersect_sphere(vec->eye_pos[1], vec->dir_vector, S_RADIUS);
  obj->color[1] = sfRed;
  return (obj);
}

t_obj	*my_put_plane(t_vec *vec, t_obj *obj)
{
  obj->k_obj[0] = intersect_plane(vec->eye_pos[0], vec->dir_vector);
  obj->color[0] = sfBlue;
  return (obj);
}

t_obj	*my_put_obj(t_vec *vec, t_obj *obj)
{
  obj = my_put_sphere(vec, obj);
  obj = my_put_plane(vec, obj);
  obj = my_put_cylinder(vec, obj);
  obj = my_put_cone(vec, obj);
  return (obj);
}
