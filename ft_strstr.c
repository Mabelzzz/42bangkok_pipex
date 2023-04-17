#include "pipex.h"

int	ft_strstr(char *str, char *find)
{
	int	i;
	int	j;
	int cp;

	i = 0;
	cp = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == find[0])
		{
			j = 0;
			while (find[j])
			{
				if (str[i] == find[j])
					cp++;
				j++;
				i++;
			}
			if (cp == j)
				return (0);
		}
		i++;
	}
	return (-1);
}

