/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:06:25 by uclement          #+#    #+#             */
/*   Updated: 2023/09/05 16:38:06 by uclement         ###   ########.fr       */
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
	pipex->args[0] = ft_split_pipex(pipex->av[2], ' ');
	pipex->args[1] = ft_split_pipex(pipex->av[3], ' ');
	pipex->cmd[0] = NULL;
	pipex->cmd[1] = NULL;
}

void	parse_cmds(t_arg *pipex)
{
	int	i;

	i = 0;
	while (pipex->ev[i] != NULL)
	{
		if (ft_strncmp(pipex->ev[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	if (pipex->ev[i] == NULL)
	{
		msg_error(NULL, "No env, please retry");
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
void	parse_args(t_arg *pipex)
{
	int		i;
	int		j;
	char	*cmd;

	j = 0;
	while (j < 2)
	{
		i = 0;
		if (access(pipex->args[j][0], X_OK) == 0)
			pipex->cmd[j] = pipex->args[j][0];
		else
		{
			while (pipex->path[i])
			{
				cmd = (ft_strjoin(pipex->path[i++], *pipex->args[j]));
				pipex->cmd[j] = cmd;
				if (access(pipex->cmd[j], X_OK) == 0)
					break ;
				free(pipex->cmd[j]);
			}
		}
		if (pipex->path[i] == NULL)
			msg_error(pipex->av[j + 2], "invalid command");
		j++;
	}
}
void free_lst(char **str)
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

void	msg_error(char *err1, char *err)
{
	if (err1 != NULL)
	{
		write(2, err1, ft_strlen(err1));
		write(2, " : ", 3);
	}
	write(2, err, ft_strlen(err));
	exit(1);
}

void	msg_perror(char *err)
{
	perror(err);
	exit(1);
}
