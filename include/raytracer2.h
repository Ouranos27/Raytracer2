/*
** raytracer1.h for raytracer1 in /home/ouranos27/my_desktop/C_Graphical_Prog/raytracer1/include
** 
** Made by philippe kam
** Login   <philippe.kam@epitech.eu>
** 
** Started on  Tue Feb  7 18:25:27 2017 philippe kam
** Last update Fri Feb 24 13:50:23 2017 philippe kam
*/

#ifndef RAYTRACER2_H_
# define RAYTRACER2_H_

# define SCREEN_WIDTH	1080
# define SCREEN_HEIGHT	560

# include <SFML/Graphics.h>
# include <SFML/Config.h>

# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define NB_OBJ		4
# define NB_LIGHT	1
# define BRIGHTNESS	0.9
# define SEMIANGLE	9
# define S_RADIUS	70
# define C_RADIUS	35

# define ERROR		-1

typedef	struct		s_my_framebuffer
{
  sfUint8		*pixels;
  int			width;
  int			height;
}			t_my_framebuffer;

typedef struct		s_vec
{
  sfVector3f		*eye_pos;
  sfVector3f		dir_vector;
  sfVector3f		normal;
  sfVector3f		angles;
  sfVector3f		reflection;
  sfVector3f		*light;
  sfVector3f		**light_vector;
  sfVector3f		*point;
}			t_vec;

typedef struct		s_obj
{
  sfColor		*color;
  float			*k_obj;
  float			k;
  int			pos;
  float			**klight;
  float			**light_coef;
  float			spots_coef;
}			t_obj;

typedef struct		s_sfml
{
  sfRenderWindow	*window;
  sfEvent		event;
  sfSprite		*sprite;
  sfTexture		*texture;
}			t_sfml;


/*
**		intersections
*/
float			delta_k(float, float, float);
float			intersect_plane(sfVector3f eye_pos,
					sfVector3f dir_vector);
float			intersect_sphere(sfVector3f eye_pos,
					 sfVector3f dir_vector, float radius);
sfVector3f		calc_dir_vector(float dist_to_plane,
					sfVector2i screen_size,
					sfVector2f screen_pos);
void			my_put_pixel(t_my_framebuffer *framebuffer, int x,
				     int y, sfColor color);
float			intersect_cylinder(sfVector3f eye_pos,
					   sfVector3f dir_vector, float radius);
float			intersect_cone(sfVector3f eye_pos,
				       sfVector3f dir_vector, float semiangle);
float			intersect_moebius(sfVector3f eye_pos,
					  sfVector3f dir_vector);
float			intersect_torus(sfVector3f eye_pos,
					  sfVector3f dir_vector,
					  float major_radius,
					  float tube_radius);
float			handler(float a, float b, float delta);

/*
**		light
*/
float			get_light_coef(sfVector3f light_vector,
				       sfVector3f normal_vector);
sfVector3f		get_inters(float k, sfVector3f point,
				     sfVector3f vector);
sfVector3f		get_light_vector(sfVector3f light, sfVector3f point);
sfVector3f		get_reflection_vector(sfVector3f dir_vector,
					  sfVector3f normal_vector);

/*
**		rotation
*/
sfVector3f		rotation_x(sfVector3f to_rotate, sfVector3f angles);
sfVector3f		rotation_y(sfVector3f to_rotate, sfVector3f angles);
sfVector3f		rotation_z(sfVector3f to_rotate, sfVector3f angles);
sfVector3f		rotate_xyz(sfVector3f to_rotate, sfVector3f angles);
sfVector3f		rotate_zyx(sfVector3f to_rotate, sfVector3f angles);
sfVector3f		normalizer(sfVector3f vec);
sfVector3f		translate(sfVector3f to_translate,
				  sfVector3f translations);

/*
**		get_normals
*/
sfVector3f		get_normal_cone(sfVector3f intersection_point,
					float semiangle);
sfVector3f		get_normal_cylinder(sfVector3f intersection_point);
sfVector3f		get_normal_plane(int upward);
sfVector3f		get_normal_sphere(sfVector3f intersection_point);

/*
**		others
*/
sfVector3f		inv_translate(sfVector3f to_translate,
				      sfVector3f translations);
int			moves(t_vec *vec);
int			draw_all(t_my_framebuffer *framebuffer, t_vec *vec);
t_vec			*find_the_normal(t_vec *vec, t_obj *obj);
t_obj			*find_the_right_color(t_obj *obj);
t_obj			*find_the_right_k(t_obj *obj, t_vec *vec);
t_obj			*obj_between_light(t_obj *obj, t_vec *vec);
t_obj			*my_put_obj(t_vec *vec, t_obj *obj);
t_obj			*use_coef(t_obj *obj);
void			free_obj(t_obj *obj);
t_obj			*malloc_obj(t_obj *obj);
t_vec			*rotate_effect(t_vec *vec);

#endif /* !RAYTRACER2_H_ */
