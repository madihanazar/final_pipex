/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:52:18 by mnazar            #+#    #+#             */
/*   Updated: 2024/12/05 16:40:05 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	perror("Error");
	exit(1);
}

void	close_dup(int file1, int i, int *pipefd, int j)
{
	close(pipefd[i]);
	if (dup2(file1, i) == -1 || dup2(pipefd[j], j) == -1)
		error(pipefd);
	close(file1);
	close(pipefd[j]);
}

void	display_cmd(char **args)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_split(args);
}

void	error_exit(void)
{
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	exit(127);
}
