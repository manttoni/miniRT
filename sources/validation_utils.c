#include "../includes/minirt.h"

/**
 * is_double - Checks if a string is a valid floating-point number.
 * @ptr: The input string.
 *
 * This function:
 * - Allows an optional `-` sign at the start.
 * - Counts digits (`0-9`) and at most **one** `.` (decimal point).
 * - Ensures there is at least **one digit**.
 * - Stops validation at a **whitespace** or the **end of the string**.
 *
 * Return:
 * - `1` if `ptr` is a **valid double**.
 * - `0` if `ptr` contains **invalid characters**.
 */
int is_double(char *ptr)
{
    int periods;
    int digits;

    periods = 0;
    digits = 0;
    if (*ptr == '-')
        ptr++;
    while (!ft_isspace(*ptr) && *ptr != '\0')
    {
        if (ft_isdigit(*ptr))
            digits++;
        else if (*ptr == '.')
            periods++;
        else
            return (0);
        ptr++;
    }
    return (periods <= 1 && digits >= 1);
}

/**
 * is_cs_double - Checks if a string is a valid comma-separated floating-point number.
 * @ptr: The input string.
 *
 * This function:
 * - Works like `is_double()`, but **stops validation at `,`**.
 * - Ensures that only one `.` and at least one digit are present.
 *
 * Return:
 * - `1` if `ptr` is a **valid floating-point number** before a comma.
 * - `0` if `ptr` contains **invalid characters**.
 */
int is_cs_double(char *ptr)
{
    int periods;
    int digits;

    periods = 0;
    digits = 0;
    if (*ptr == '-')
        ptr++;
    while (!ft_isspace(*ptr) && *ptr != '\0' && *ptr != ',')
    {
        if (ft_isdigit(*ptr))
            digits++;
        else if (*ptr == '.')
            periods++;
        else
            return (0);
        ptr++;
    }
    return (periods <= 1 && digits >= 1);
}

/**
 * is_color - Checks if a string represents a valid RGB color.
 * @ptr: The input string (expected format: "R,G,B").
 *
 * This function:
 * - Ensures there are exactly **3 integer values** between `0-255`.
 * - Ensures exactly **2 commas** are present.
 * - Stops processing at a **whitespace** or **null-terminator**.
 *
 * Return:
 * - `1` if `ptr` is a **valid RGB color**.
 * - `0` if `ptr` contains **invalid values or incorrect format**.
 */
int is_color(char *ptr)
{
    int commas;
    int values;

    commas = 0;
    values = 0;
    while (!ft_isspace(*ptr) && *ptr != '\0')
    {
        if (ft_isdigit(*ptr) && ft_atoi(ptr) / 256 == 0)
            values++;
        while (ft_isdigit(*ptr))
            ptr++;
        if (*ptr != ',')
            break;
        commas++;
        ptr++;
    }
    return (values == 3 && commas == 2);
}

/**
 * is_vector - Checks if a string is a valid 3D vector.
 * @ptr: The input string (expected format: "X,Y,Z").
 *
 * This function:
 * - Uses `is_cs_double()` to validate each component.
 * - Ensures **exactly 3 floating-point values** separated by `,`.
 * - Stops processing at a **whitespace** or **null-terminator**.
 *
 * Return:
 * - `1` if `ptr` is a **valid 3D vector**.
 * - `0` if `ptr` contains **invalid values**.
 */
int is_vector(char *ptr)
{
    int commas;
    int doubles;

    commas = 0;
    doubles = 0;
    while (!ft_isspace(*ptr) && *ptr != '.')
    {
        if (is_cs_double(ptr))
            doubles++;
        while (ft_isdigit(*ptr) || *ptr == '.' || *ptr == '-')
            ptr++;
        if (*ptr != ',')
            break;
        commas++;
        ptr++;
    }
    return (doubles == 3 && commas == 2);
}

/**
 * is_int - Checks if a string represents a valid integer.
 * @ptr: The input string.
 *
 * This function:
 * - Ensures **only digits (`0-9`)** are present.
 * - Stops processing at a **whitespace** or **null-terminator**.
 *
 * Return:
 * - `1` if `ptr` is a **valid integer**.
 * - `0` if `ptr` contains **non-numeric characters**.
 */
int is_int(char *ptr)
{
    while (!ft_isspace(*ptr) && *ptr != '\0')
    {
        if (!ft_isdigit(*ptr))
            return (0);
        ptr++;
    }
    return (1);
}

