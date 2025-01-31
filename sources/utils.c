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

void	error_msg(t_data *data)
{
	if (!data)
	{
		printf("Data structure failed\n");
		return ;
	}
	if (!data->objects)
	{
		printf("Failed create data objects\n");
		return ;
	}
	if (!data->mlx)
		printf("MLX failed to initialize\n");
	if (!data->image)
		printf("No image\n");
	return ;
}
