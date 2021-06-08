/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:16:25 by nle-biha          #+#    #+#             */
/*   Updated: 2021/06/08 20:05:06 by nle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	return_error(int err, char **cmd, char **paths)
{
	if (err == -1)
	{
		free_nulltermchartab(cmd);
		free_nulltermchartab(paths);
		perror("Error");
		exit(1);
	}
	return (0);
}

char	*get_env_value(char *env_var, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(env_var);
	while (envp[i])
	{
		if (ft_strncmp(env_var, envp[i], len) == 0)
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	execvp_mutiple_path(char **cmd, char **paths)
{
	int		i;
	char	*complete_cmd;

	i = 0;
	execvp(cmd[0], cmd);
	while (paths[i])
	{
		complete_cmd = ft_strjoin3(paths[i], "/", cmd[0]);
		if (complete_cmd == NULL)
			return_error(-1, cmd, paths);
		execvp(complete_cmd, cmd);
		free(complete_cmd);
		i++;
	}
	return (0);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	size_t	lens1;
	size_t	lens2;
	size_t	lens3;
	char	*ret;
	size_t	i;

	i = -1;
	if (!s1 || !s2 || !s3)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	lens3 = ft_strlen(s3);
	ret = malloc(lens1 + lens2 + lens3 + 1);
	if (ret != NULL)
	{
		while (++i < lens1)
			ret[i] = s1[i];
		while (++i <= lens2 + lens1)
			ret[i - 1] = s2[i - 1 - lens1];
		while (i++ <= lens3 + lens2 + lens1)
			ret[i - 2] = s3[i - 2 - lens1 - lens2];
		ret[i - 2] = '\0';
	}
	return (ret);
}

void	free_nulltermchartab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
