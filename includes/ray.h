#ifndef RAY_H
# define RAY_H

# include "./data.h"
# include "./vector.h"


typedef struct s_ray
{
    t_vector    start;
    t_vector    direction;
    double      distance;
    uint32_t         color;
}   t_ray;

void		raycast(t_data *data);

#endif
