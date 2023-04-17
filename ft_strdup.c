#include "pipex.h"

char	*ft_strdup(const char *str)
{
	char	*new;
	int		index;

	new = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!new)
		return (NULL);
	index = 0;
	while (str[index] != 0)
	{
		new[index] = str[index];
		index++;
	}
	new[index] = 0;
	return (new);
}