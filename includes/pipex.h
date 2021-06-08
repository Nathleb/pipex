/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 16:57:48 by nle-biha          #+#    #+#             */
/*   Updated: 2021/06/08 19:06:00 by nle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

char	*get_env_value(char *env_var, char **envp);
int		execvp_mutiple_path(char **cmd, char **paths);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
void	free_nulltermchartab(char **tab);
int		runcmd2(int filfd, int *pipfd, char **cmd, char **paths);
int		runcmd1(int filfd, int *pipfd, char **cmd, char **paths);
int		return_error(int err, char **cmd, char **paths);
#endif
