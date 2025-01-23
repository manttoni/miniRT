#include "../includes/minirt.h"

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	free_array(char **ar)
{
	char	**ptr;

	if (ar == NULL)
		return ;
	ptr = ar;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(ar);
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
	printf("trimmed len: %ld\n", end - start);
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
	printf("trimmed: %s\n", trimmed);
	return (trimmed);
}
