#include "../includes/minirt.h"

/**
 * assign_checks - Assigns validation functions based on object type.
 * @type: The type of the object being validated.
 * @checks: Array of function pointers for validation checks.
 *
 * This function assigns a **set of validation functions** (`is_double`, `is_vector`, etc.)
 * to an array of function pointers based on the object's type.
 *
 * - Each `checks[i]` function validates a specific **property** of the object.
 * - The list ends with `NULL`, marking the **end of the validation sequence**.
 *
 * Example:
 * - A **camera** requires three checks:
 *   - Position → `is_vector`
 *   - Orientation → `is_vector`
 *   - Field of View → `is_int`
 *   - Termination → `NULL`
 *
 * The function dynamically sets up the validation rules, ensuring **correct format checking**.
 */
void    assign_checks(t_type type, int (**checks)(char *))
{
    if (type == AMBIENT)
    {
        checks[0] = &is_double;
        checks[1] = &is_color;
        checks[2] = NULL;
    }
    else if (type == CAMERA)
    {
        checks[0] = &is_vector;
        checks[1] = &is_vector;
        checks[2] = &is_int;
        checks[3] = NULL;
    }
    else if (type == LIGHT)
    {
        checks[0] = &is_vector;
        checks[1] = &is_double;
        checks[2] = NULL;
    }
    else if (type == SPHERE)
    {
        checks[0] = &is_vector;
        checks[1] = &is_double;
        checks[2] = &is_color;
        checks[3] = NULL;
    }
    else if (type == PLANE)
    {
        checks[0] = &is_vector;
        checks[1] = &is_vector;
        checks[2] = &is_color;
        checks[3] = NULL;
    }
    else
    {
        checks[0] = &is_vector;
        checks[1] = &is_vector;
        checks[2] = &is_double;
        checks[3] = &is_double;
        checks[4] = &is_color;
        checks[5] = NULL;
    }
}

/**
 * next_value - Moves the pointer to the next value in the string.
 * @ptr: Current position in the string.
 *
 * This function:
 * - Finds the next **whitespace-separated value** in the string.
 * - Returns a pointer to the start of the next value.
 * - Skips any additional spaces after the delimiter.
 *
 * If no next value is found, it returns `NULL`.
 *
 * Return:
 * - Pointer to the next value in the string.
 * - NULL if no next value exists.
 */
static char *next_value(char *ptr)
{
    ptr = ft_strchr(ptr, ' ');
    if (ptr == NULL)
        return (NULL);
    while (ft_isspace(*ptr))
        ptr++;
    return (ptr);
}

/**
 * validate - Validates a line from the scene file.
 * @line: The line containing object data.
 *
 * This function:
 * - **Identifies the object type** from the first token.
 * - **Assigns appropriate validation functions** based on object type.
 * - Iterates through all expected values and **validates them** using assigned functions.
 * - If any validation check fails, the function returns `NULL`.
 *
 * Example:
 * ```
 * L -40.0,50.0,0.0 0.6
 * ```
 * - `L` → Light object
 * - Checks:
 *   1. Position `(-40.0,50.0,0.0)` → `is_vector`
 *   2. Brightness `(0.6)` → `is_double`
 *
 * Return:
 * - The **original line** if it is valid.
 * - `NULL` if any value is **missing or invalid**.
 */
char    *validate(char *line)
{
    int  	(*checks[6])(char *);
    char 	*ptr;
    int  	i;
	t_type	type;

    type = get_type(line);
    if (line == NULL || ft_isspace(*line) || *line == '\0' || type == NONE)
        return (NULL);
assign_checks(type, checks);
    ptr = line;
	i = 0;
    while(checks[i] != NULL)
    {
        ptr = next_value(ptr);
		if (ptr == NULL || (checks[i])(ptr) == 0)
            return (NULL);
        i++;
    }
    return (line);
}
