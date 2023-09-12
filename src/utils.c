/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:06:25 by uclement          #+#    #+#             */
/*   Updated: 2023/09/12 18:42:39 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*pathfinder(char **ev)
{
	int	i;

	i = 0;
	while (ev[i] != NULL)
	{
		if (ft_strncmp(ev[i], "PATH", 4) == 0)
		{
			return (&ev[i][5]);
			break ;
		}
		i++;
	}
	return (NULL);
}

char	*cmd_maker(char **ev, char **args)
{
	int		i;
	char	**path;
	char	*tmp;
	char	*cmd;

	path = ft_split(pathfinder(ev), ':');
	i = 0;
	if (access(args[0], X_OK) == 0)
		return (args[0]);
	else
	{
		while (path[i])
		{
			tmp = ft_strjoin(path[i], "/");
			cmd = ft_strjoin(tmp, args[0]);
			free (tmp);
			if (access(cmd, X_OK) == 0)
				return (cmd);
			free (cmd);
			i++;
		}
	}
	free_lst(path);
	return (NULL);
}

void	free_lst(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	msg_error(char *err1, char *err, int nb)
{
	if (err1 != NULL)
	{
		write(2, err1, ft_strlen(err1));
		write(2, ": ", 2);
	}
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
	if (nb < 0)
		exit(nb);
}
