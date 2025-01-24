#ifndef RAY_H
# define RAY_H

# include "./data.h"
# include "./vector.h"


typedef struct s_ray
{
    t_vector    start;
    t_vector    direction;
    t_vector    coll_norm;
    double      distance;
<<<<<<< HEAD
    uint32_t    color;
=======
    uint32_t         color;
>>>>>>> master
}   t_ray;

void		raycast(t_data *data);

#endif
