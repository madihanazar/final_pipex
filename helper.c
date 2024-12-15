/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:36:05 by mnazar            #+#    #+#             */
/*   Updated: 2024/12/15 21:28:22 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *arg, char *envp[])
{
	char	*full_cmd;
	char	**args;

	args = ft_split(arg, ' ');
	if (!args || !args[0])
		(display_cmd(args), error_exit());
	if (ft_strchr(args[0], '/'))
		full_cmd = ft_strdup(args[0]);
	else
		full_cmd = extract_path(envp, args[0]);
	if (full_cmd == NULL)
	{
		display_cmd(args);
		error_exit();
	}
	if (execve(full_cmd, args, envp) == -1)
	{
		display_cmd(args);
		free(full_cmd);
		error_exit();
	}
}

pid_t	first_process(int *pipefd, char **argv, char *envp[])
{
	int		file1;
	pid_t	pid1;

	pid1 = fork();
	if (pid1 < 0)
		error(pipefd);
	if (pid1 == 0)
	{
		file1 = open(argv[1], O_RDONLY);
		if (file1 < 0)
			error(pipefd);
		close_dup(file1, 0, pipefd, 1);
		execute(argv[2], envp);
		close(file1);
	}
	return (pid1);
}

pid_t	second_process(int *pipefd, char **argv, char *envp[])
{
	int		file2;
	pid_t	pid2;

	pid2 = fork();
	if (pid2 < 0)
		error(pipefd);
	if (pid2 == 0)
	{
		file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file2 < 0)
			error(pipefd);
		close_dup(file2, 1, pipefd, 0);
		execute(argv[3], envp);
		close(file2);
	}
	return (pid2);
}
