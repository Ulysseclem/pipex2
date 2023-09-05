/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:53:48 by uclement          #+#    #+#             */
/*   Updated: 2023/09/05 16:40:33 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	p_process(t_arg *pipex, int f2, int *fd)
{
	int		status;

	waitpid(-1, &status, 0);
	dup2(f2, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	close(f2);
	execve(pipex->cmd[1], pipex->args[1], pipex->ev);
}

void	c_process(t_arg *pipex, int f1, int *fd)
{
	dup2(f1, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(f1);
	execve(pipex->cmd[0], pipex->args[0], pipex->ev);
}

void	process(t_arg pipex, int f1, int f2)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		perror("Error pipe");
	pid = fork();
	if (pid == 0 )
	{
		close(f2);
		c_process(&pipex, f1, fd);
	}
	if (pid != 0 )
	{
		close(f1);
		p_process(&pipex, f2, fd);
	}
	close(fd[0]);
	close(fd[1]);
	close(f1);
	close(f2);
	free_lst(pipex.path);
}
int	main(int argc, char **argv, char **envp)
{
	int		f1;
	int		f2;
	t_arg	pipex;

	if (argc != 5)
		return (0);
	init_pipex(&pipex, argv, envp);
	parse_cmds(&pipex);
	parse_args(&pipex);
	if ((f1 = open(argv[1], O_RDONLY)) == -1)
		msg_perror(argv[1]);
	if ((f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644)) == -1)
		msg_perror("error open");
	process(pipex, f1, f2);
}
