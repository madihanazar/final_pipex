/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:30:19 by mnazar            #+#    #+#             */
/*   Updated: 2024/12/05 16:53:10 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **argv, char *envp[])
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;
	int		pipefd[2];

	if (ac != 5)
	{
		ft_putstr_fd("./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(1);
	}
	if (pipe(pipefd) == -1)
	{
		perror("Error opening the pipe");
		exit(1);
	}
	pid1 = first_process(pipefd, argv, envp);
	pid2 = second_process(pipefd, argv, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (WEXITSTATUS(status));
}
