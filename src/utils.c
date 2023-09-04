/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:06:25 by uclement          #+#    #+#             */
/*   Updated: 2023/09/04 18:18:09 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void init_pipex(t_arg *pipex, char** argv, char **envp)
{
	pipex->av = argv;

	pipex->ev = envp;
	if (envp == NULL)
		write (1, "ping", 4); 
	pipex->path = NULL;
	pipex->argparent = NULL;
	pipex->argchild = NULL;

}

void parse_cmds(t_arg *pipex)
{
	int i;

	i = 0;

	while (pipex->ev[i] != NULL)
		{
			if (ft_strncmp(pipex->ev[i], "PATH", 4) == 0)
				break ;
			i++;
		}
	if (pipex->ev[i] == NULL)
	{
		perror("test");
		exit (0);
	}
	pipex->path = ft_split(&pipex->ev[i][5], ':');
	i = 0;
	while (pipex->path[i])
	{
		pipex->path[i] = ft_strjoin(pipex->path[i], "/");
		i++;
	}
}

void parse_args(t_arg *pipex)
{
	pipex->argchild = ft_split_pipex(pipex->av[2], ' ');
	pipex->argparent = ft_split_pipex(pipex->av[3], ' ');
}
void free_lst(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
