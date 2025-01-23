#ifndef RAY_H
# define RAY_H

typedef struct s_ray
{
    t_vector    start;
    t_vector    direction;
    double      distance;
    int         color;
}   t_ray;

void		raycast(t_data *data);

#endif