/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:29:14 by meudier           #+#    #+#             */
/*   Updated: 2022/08/30 11:18:29 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft.h"

static int	ft_get_size(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

static char	*ft_get_word(int *index, char *s, char c)
{
	char	*word;
	int		len;
	int		i;

	len = 0;
	while (s[*index] == c && s[*index])
		(*index)++;
	while (s[*index + len] != c && s[*index + len])
		len ++;
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[*index];
		(*index)++;
		i++;
	}
	word[i] = 0;
	return (word);
}

static char	**clear_tab(char ***tab)
{
	int		i;

	i = 0;
	while ((*tab)[i])
		free((*tab)[i++]);
	free (*tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		size;
	char	**tab;

	if (!s)
		return (NULL);
	size = ft_get_size(s, c);
	tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		tab[i] = ft_get_word(&j, (char *)s, c);
		if (!tab[i])
			return (clear_tab(&tab));
		i++;
	}
	tab[i] = 0;
	return (tab);
}
