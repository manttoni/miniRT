#ifndef RAY_H
# define RAY_H

# include "data.h"
# include "vector.h"
// # include "object.h"
# include <stdint.h>

typedef struct s_ray
{
    t_vector    direction;
    t_vector    coll_norm;
    double      distance;
    uint32_t    color;
    t_vector    location;
}   t_ray;

void    raycast(t_data *data);


#endif
