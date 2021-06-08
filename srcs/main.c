/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 16:10:56 by nle-biha          #+#    #+#             */
/*   Updated: 2021/06/08 15:32:16 by nle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	runcmd2(int filfd, int *pipfd, char **cmd, char **paths)
{
	int	pid;
	int	i;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		dup2(filfd, 1);
		close(pipfd[1]);
		dup2(pipfd[0], 0);
		execvp_mutiple_path(cmd, paths);
		perror(cmd[0]);
	}
	else if (pid == -1)
		perror("fork cmd2");
	return ;
}

void	runcmd1(int filfd, int *pipfd, char **cmd, char **paths)
{
	int	pid;
	int	i;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		close(pipfd[0]);
		dup2(filfd, 0);
		dup2(pipfd[1], 1);
		execvp_mutiple_path(cmd, paths);
		perror(cmd[0]);
	}
	else if (pid == -1)
		perror("fork cmd1");
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	char	**paths;
	int		pipfd[2];
	int		filfd[2];
	char	**cmd;

	if (argc != 5)
		return (0);
	pipe(pipfd);
	paths = ft_split(get_env_value("PATH", envp), ':');
	filfd[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 644);
	filfd[0] = open(argv[1], O_RDONLY);
	cmd = ft_split(argv[2], ' ');
	runcmd1(filfd[0], pipfd, cmd, paths);
	free_nulltermchartab(cmd);
	cmd = ft_split(argv[3], ' ');
	runcmd2(filfd[1], pipfd, cmd, paths);
	close(pipfd[1]);
	close(pipfd[0]);
	close(filfd[0]);
	close(filfd[1]);
	free_nulltermchartab(cmd);
	free_nulltermchartab(paths);
	return (0);
}
