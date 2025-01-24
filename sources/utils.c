#include "../includes/minirt.h"

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
/* Returns a char pointer with all c
 * removed from start and end */
char	*trim(char *str, char c)
{
	char	*start;
	char	*end;
	char	*trimmed;
	int		i;

	if (str == NULL)
		return (NULL);
	start = str;
	while (*start == c)
		start++;
	end = str + ft_strlen(str);
	while (*end == c)
		end--;
	trimmed = malloc(end - start);
	if (trimmed == NULL)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (i < (end - start) - 1)
	{
		trimmed[i] = start[i];
		i++;
	}
	free(str);
	trimmed[i] = '\0';
	return (trimmed);
}
