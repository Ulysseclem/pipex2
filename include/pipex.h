/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:56:00 by uclement          #+#    #+#             */
/*   Updated: 2023/09/05 16:35:23 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <inttypes.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include "libft.h"

# define ERR_CMD "Command not found\n"

typedef struct s_arg
{
	char	**av;
	char	**ev;
	char	**path;
	char	**argparent;
	char	**argchild;
	char	**args[2];
	char	*cmd[2];
}	t_arg;

char	**ft_split_pipex(char const *s, char c);

void init_pipex(t_arg *pipex, char** argv, char **envp);
void parse_cmds(t_arg *pipex);
void parse_args(t_arg *pipex);
void free_lst(char **str);
void	msg_error(char *err1, char *err);
void	msg_perror(char *err);


#endif