/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:53:48 by uclement          #+#    #+#             */
/*   Updated: 2023/09/12 18:43:06 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	p_process(char **av, int f2, int *fd, char **ev)
{
	char	*cmd;
	char	**path;

	path = ft_split_pipex(av[3], ' ');
	if (pathfinder(ev) == NULL)
	{
		if (execve(path[0], path, ev) == -1)
			msg_error(av[3], "command not found", 127);
	}
	else
	{
		cmd = cmd_maker(ev, path);
		dup2(f2, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		if (cmd != NULL)
			execve(cmd, path, ev);
		else
		{
			msg_error(av[3], "command not found", 127);
			free(cmd);
			free_lst(path);
		}
	}
}

void	c_process(char **av, int f1, int *fd, char **ev)
{
	char	*cmd;
	char	**path;

	path = ft_split_pipex(av[2], ' ');
	if (pathfinder(ev) == NULL)
	{
		if (execve(path[0], path, ev) == -1)
			msg_error(av[2], "command not found", 0);
	}
	else
	{
		cmd = cmd_maker(ev, path);
		dup2(f1, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		if (cmd != NULL)
			execve(cmd, path, ev);
		else
		{
			msg_error(av[2], "command not found", 0);
			free(cmd);
			free_lst(path);
		}
	}
}

void	process(char **av, int f1, int f2, char **ev)
{
	int	fd[2];
	int	pid;
	int	status;

	if (pipe(fd) == -1)
		perror("Error pipe");
	pid = fork();
	if (!pid && (f1 != -1))
	{
		close(f2);
		c_process(av, f1, fd, ev);
	}
	if (pid && (f2 != -1))
	{
		close(f1);
		p_process(av, f2, fd, ev);
	}
	waitpid(pid, &status, 0);
	close(fd[0]);
	close(fd[1]);
}

int	main(int argc, char **argv, char **envp)
{
	int		f1;
	int		f2;

	if (argc != 5)
		msg_error(NULL, "issue with nbr of args", 1);
	f1 = open(argv[1], O_RDONLY);
	if (f1 == -1)
		msg_error(argv[1], "No such file or directory", 0);
	f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f2 == -1)
		perror(argv[4]);
	process(argv, f1, f2, envp);
}
