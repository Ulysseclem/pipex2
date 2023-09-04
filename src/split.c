/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:47:43 by uclement          #+#    #+#             */
/*   Updated: 2023/09/04 16:49:44 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_size(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			i++;
			while (s[i] != '\'' && s[i] != '\"')
				i++;
		}
		i++;
	}
	return (i);
}

static int	ft_count(char const *s, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			j++;
		while (s[i] != '\0' && s[i] != c)
		{
			if (s[i] == '\'' || s[i] == '\"')
			{
				i++;
				while (s[i] != '\'' && s[i] != '\"')
					i++;
			}
			i++;
		}
	}
	return (j);
}

static char	*ft_cut(char const *s, int i, char c)
{
	char	*str;
	int		k;

	k = 0;
	str = malloc(ft_size(&s[i], c) * sizeof(char) + 1);
	if (!str)
		return (NULL);
	while (s[i] != c && s[i])
	{
		if (s[i] == '\''  || s[i] == '\"')
			{
				i++;
				while (s[i] != '\'' && s[i] != '\"')
					str[k++] = s[i++];
				str[k] = ' ';
				k++;
				break ;
			}
		str[k++] = s[i++];
	}
	str[k] = '\0';
	return (str);
}

void	*ft_free2(char **str, int n)
{
	while (n >= 0)
	{
		free(str[n]);
		n--;
	}
	free(str);
	return (NULL);
}

char	**ft_split_pipex(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	str = malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while ((size_t)i < ft_strlen(s))
	{
		if (s[i] != c && s[i])
		{
			str[j] = ft_cut(s, i, c);
			if (!str[j])
				return (ft_free2(str, j));
			i = i + ft_strlen(str[j]);
			j++;
		}
		i++;
	}
	str[j] = NULL;
	return (str);
}