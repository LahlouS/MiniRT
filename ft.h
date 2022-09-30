/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:30:42 by meudier           #+#    #+#             */
/*   Updated: 2022/09/09 15:43:21 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <mlx_int.h>
# include <X11/keysym.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <float.h>
# define BUFFER_SIZE 100
# define WIDTH 1280
# define HEIGHT 690
# define PI 3.14159265359
# define BACK_GROUND 0x000000
# define WHITE 0xFFFFFF

enum e_type
{
	SP,
	PL,
	CL,
	OBJ_SIZE
};

enum e_algo
{
	RAY_DIR,
	HIT_POINT,
	NB_VEC
};

typedef struct s_image
{
	void	*mlx_img;
	char	*addr;
	int		bits_per_pix;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_equation
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	t1;
	float	t2;
	float	t;
}	t_equation;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_LumA
{
	float		ratio;
	t_vector	color;
}	t_LumA;

typedef struct s_Lum
{
	t_vector	pos;
	t_vector	color;
	float		ratio;
}	t_Lum;

typedef struct s_Cam
{
	t_vector	pos;
	t_vector	dir;
	int			fov;
}	t_Cam;

typedef struct s_Sphere
{
	t_vector	center;
	t_vector	color;
	float		radius;
}	t_Sphere;

typedef struct s_plan
{
	t_vector	origin;
	t_vector	normal_vec;
	t_vector	color;
}	t_plan;

typedef struct s_cylindre
{
	t_vector	base;
	t_vector	dir;
	float		heigth;
	float		radius;
	t_vector	color;
	int			inter_code;
}	t_cylindre;

typedef struct s_Objects
{
	int					id;
	void				*object;
	struct s_Objects	*next;
	struct s_Objects	*prev;
}	t_Objects;

typedef struct s_data
{
	t_LumA		*luma;
	t_Lum		*lum;
	t_Cam		*cam;
	t_Objects	*objects;
}	t_data;

typedef struct s_matrix
{
	t_vector	right;
	t_vector	up;
	t_vector	forward;
	t_vector	cam;
}	t_matrix;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_image	image;
	t_data	data;
	int		move;
	char	**av;
	int		ac;
}	t_vars;

/*src/window/loop_event*/
int			handle_event(t_vars *vars);
int			key_event(int keycode, t_vars *vars);
int			loop_end(t_vars *vars);

/*src/window/destroy*/
int			destroy(t_vars *vars);

/*src/tools/split*/
char		**ft_split(char const *s, char c);
char		**ft_split_charset(char *str, char *charset);

/*src/toolstools*/
int			ft_strcmp(const char *s1, const char *s2);
int			is_digit(char *str);
int			is_float(char *str);
int			ft_atoi(const char *nptr);
float		ft_atof(char *str);
float		max(float a, float b);
float		min(float a, float b);
int			into_radius(t_vector *rslt, t_vector base, float radius);
void		init_plan(t_plan *plan, t_cylindre *cl, float normal_dir);
int			ft_strlen(char *str);
char		*ft_itoa(int n);
char		*ftoa(float f);
char		*ft_strjoin(char *s1, char *s2);
void		rewind_list(t_Objects **obj);

/*GNL*/
char		*get_next_line(int fd);
char		*ft_cpy_buf(char *buf, int len);
char		*ft_cat_buf_to_str(char *str, char *buf, int str_len, int buf_len);

/*src/parser/free*/
int			free_data(t_data *data);
int			free_tab(char **tab);
int			free_void(void *a);

/*src/parser/parser*/
int			ft_parse_a(t_data *data, char **line_split);
int			ft_parse_c(t_data *data, char **line_split);
int			ft_parse_l(t_data *data, char **line_split);
void		init_ft_parse(int (*parse_line['s' + 1])(t_data *, char**));
int			parse(char *line, t_data *data);

/*src/parser/parser_obj*/
int			ft_parse_sp(t_data *data, char **line_split);
int			ft_parse_cl(t_data *data, char **line_split);
int			ft_parse_pl(t_data *data, char **line_split);
int			a_to_vec(char *str, t_vector *vector, int (*f)(char *));

/*src/parser/check*/
int			is_good_extension(char *str);
int			check_id(char *str);
int			check_range_vector(t_vector *vector, int min, int max);
int			check_acl(t_data *data);

/*src/parser/init*/
int			__add_node(t_Objects **data, void *current, int id);
void		initialize_data(t_data *data);
int			init_data(int ac, char **av, t_data *data);

/*src/calcul/calcul1*/
t_vector	float_x_vector(t_vector v1, float k);
t_vector	add_vector(t_vector v1, t_vector v2);
t_vector	cross_product(t_vector v1, t_vector v2);
t_vector	sub_vector(t_vector v1, t_vector v2);
t_vector	vector_x_vector(t_vector v1, t_vector v2);
t_vector	compute_nhit_sp(t_Sphere *sp, t_vector hit_point, t_vector cam_pos);
t_vector	compute_nhit_cy(t_cylindre *cy, t_vector hit_point, \
t_vector cam_pos);
t_vector	compute_nhit_pl(t_plan *pl, t_vector hit_point, t_vector cam_pos);

/*src/calcul/calcul2*/
t_vector	normalize(t_vector v1);
float		scalaire_product(t_vector v1, t_vector v2);
float		norme(t_vector v1);
void		eq_vector(t_vector *v1, t_vector v2);

/*src/calcul/calcul3*/
t_matrix	get_transfo_matrix(t_vector cam_orig, t_vector cam_dir);
t_vector	vector_x_matrix(t_vector v, t_matrix m, int i);
void		eq_matrix(t_matrix *m1, t_matrix m2);

/*src/calcul/intersection*/
float		inter_sphere(t_vector dir_pix, t_vector cam_o, void *sp, \
t_vector *rslt);
float		inter_plan(t_vector dir_pix, t_vector cam_o, void *plan, \
t_vector *rslt);
float		inter_cylindre(t_vector dir_pix, t_vector cam_o, \
void *cylindre, t_vector *rslt);
t_vector	get_nhit_cl(t_cylindre *cl, t_vector hit_point);

/*RT algo*/
void		set_img(t_image *image, t_vars *data, int w, int h);
int			img_pix_put(t_image *img, int x, int y, int color);
void		algo(t_vars *vars);
void		algo_shadow(t_vars *vars, t_vector hit_point, int i, int j);
int			shift_color(t_vector color);
void		rewind_list(t_Objects **obj);
t_vector	loop_object_hit(t_Objects **obj, t_vector ray_dir, \
t_vector cam_pos, float *t_min);
#endif
