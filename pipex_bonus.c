/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:30:19 by mnazar            #+#    #+#             */
/*   Updated: 2024/12/15 21:27:53 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **argv, char *envp[])
{
	pid_t	pid2;
	int		status;
	int		pipefd[2];
	int		i;

	i = 3;
	if (ac < 5)
	{
		ft_putstr_fd("./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(1);
	}
	if (pipe(pipefd) == -1)
		(perror("Error opening the pipe"), exit(1));
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		here_doc(argv[2], pipefd);
	else
		first_process(pipefd, argv, envp);
	while (i < ac - 2)
		mid_process(pipefd, argv[i++], envp);
	pid2 = second_process_bonus(pipefd, argv, envp, ac);
	(close(pipefd[0]), close(pipefd[1]));
	waitpid(pid2, &status, 0);
	while (wait(NULL) == -1)
		;
	return (WEXITSTATUS(status));
}
