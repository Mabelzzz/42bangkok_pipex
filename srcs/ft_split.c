
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <pnamwayk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:05:51 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/03/13 15:56:53 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

size_t	cnt_alphabet(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != 0 && s[i] != c)
		i++;
	return (i);
}

char	*keep_alphabet(char const *s, char c)
{
	size_t	i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (cnt_alphabet(s, c) + 2));
	if (!word)
		return (NULL);
	while (s[i] && s[i] != c && i <= cnt_alphabet(s, c))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

size_t	cnt_word(char const *s, char c)
{
	size_t	count;
	int		i;

	i = 0;
	count = 0;
	while (s[i] != 0)
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**word;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	word = (char **)malloc(sizeof(char *) * (cnt_word(s, c) + 1));
	if (!word)
		return (NULL);
	i = 0;
	j = 0;
	while (j < cnt_word(s, c))
	{
		while (s[i] != 0 && s[i] == c)
			i++;
		word[j] = keep_alphabet(&s[i], c);
		while (s[i] != 0 && s[i] != c)
			i++;
		j++;
	}
	word[j] = NULL;
	return (word);
}

