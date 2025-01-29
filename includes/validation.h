#ifndef VALIDATION_H
# define VALIDATION_H

/* TESTING MACROS BUT NOT WORKING
// Function pointer type for validation functions
typedef int (*t_validate)(char *);



// Define function pointer arrays with correct syntax
# define AMBIENT_VALID   ((t_validate[]){ is_double, is_color, NULL})
# define CAMERA_VALID    ((t_validate[]){ is_vector, is_vector, is_int, NULL })
# define LIGHT_VALID     ((t_validate[]){ is_vector, is_double, is_color, NULL })
# define SPHERE_VALID    ((t_validate[]){ is_vector, is_double, is_color, NULL })
# define PLANE_VALID     ((t_validate[]){ is_vector, is_vector, is_color, NULL })
# define CYLINDER_VALID  ((t_validate[]){ is_vector, is_vector, is_double, is_double, is_color, NULL })

*/

// delete this
typedef enum e_type
{
	CAMERA,
	LIGHT,
	AMBIENT,
	SPHERE,
	PLANE,
	CYLINDER,
	NONE
}	t_type;

int is_double(char *ptr);
int is_color(char *ptr);
int is_vector(char *ptr);
int is_int(char *ptr);

char    *validate(char *line);

#endif