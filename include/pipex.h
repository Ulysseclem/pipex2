/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:56:00 by uclement          #+#    #+#             */
/*   Updated: 2023/09/04 17:57:45 by uclement         ###   ########.fr       */
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

typedef struct s_arg
{
	char	**av;
	char	**ev;
	char	**path;
	char	**argparent;
	char	**argchild;
}	t_arg;

char	**ft_split_pipex(char const *s, char c);

void init_pipex(t_arg *pipex, char** argv, char **envp);
void parse_cmds(t_arg *pipex);
void parse_args(t_arg *pipex);
void free_lst(char **str);

#endif