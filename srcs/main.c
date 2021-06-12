/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 16:10:56 by nle-biha          #+#    #+#             */
/*   Updated: 2021/06/12 16:06:42 by nle-biha         ###   ########.fr       */
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
		return_error(dup2(filfd, 1), cmd, paths);
		close(pipfd[1]);
		return_error(dup2(pipfd[0], 0), cmd, paths);
		execvp_mutiple_path(cmd, paths);
		return_error(-1, cmd, paths);
	}
	else if (pid == -1)
	{
		perror("fork cmd1");
		exit (1);
	}
}

void	runcmd1(int filfd, int *pipfd, char **cmd, char **paths)
{
	int	pid;
	int	i;
	int	status;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		close(pipfd[0]);
		return_error(dup2(filfd, 0), cmd, paths);
		return_error(dup2(pipfd[1], 1), cmd, paths);
		execvp_mutiple_path(cmd, paths);
		return_error(-1, cmd, paths);
	}
	else if (pid == -1)
	{
		perror("fork cmd1");
		exit (1);
	}
	else
	{
		pid = wait(&status);
		while (pid != -1)
			pid = wait(&status);
	}
}

void	close_all(int *pipfd, int *filfd, char **cmd, char **paths)
{
	close(pipfd[1]);
	close(pipfd[0]);
	close(filfd[0]);
	close(filfd[1]);
	free_nulltermchartab(cmd);
	free_nulltermchartab(paths);
}

int	main(int argc, char **argv, char **envp)
{
	char	**paths;
	int		pipfd[2];
	int		filfd[2];
	char	**cmd;

	if (argc != 5)
		return (1);
	filfd[0] = open(argv[1], O_RDONLY);
	paths = ft_split(get_env_value("PATH", envp), ':');
	cmd = ft_split(argv[2], ' ');
	filfd[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return_error(filfd[1], cmd, paths);
	return_error(filfd[0], cmd, paths);
	return_error(pipe(pipfd), cmd, paths);
	if (paths && cmd)
	{
		runcmd1(filfd[0], pipfd, cmd, paths);
		free_nulltermchartab(cmd);
		cmd = ft_split(argv[3], ' ');
		if (cmd)
			runcmd2(filfd[1], pipfd, cmd, paths);
	}
	close_all(filfd, pipfd, paths, cmd);
	return (0);
}
