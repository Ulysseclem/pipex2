/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:56:00 by uclement          #+#    #+#             */
/*   Updated: 2023/09/12 18:41:28 by uclement         ###   ########.fr       */
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

char	**ft_split_pipex(char const *s, char c);
void	process(char **av, int f1, int f2, char **ev);
void	free_lst(char **str);
void	msg_error(char *err1, char *err, int nb);
char	*cmd_maker(char **ev, char **args);
char	*pathfinder(char **ev);

#endif