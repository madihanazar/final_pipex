/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:34:30 by mnazar            #+#    #+#             */
/*   Updated: 2024/12/15 21:19:05 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "get_next_line/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h> // for wait

char	**ft_split(const char *s, char c);
int		ft_strncmp(const char *str1, const char *str2, int n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putstr_fd(char *s, int fd);
pid_t	first_process(int *pipefd, char **argv, char *envp[]);
char	*extract_path(char *envp[], char *args);
void	execute(char *arg, char *envp[]);
pid_t	second_process_bonus(int *pipefd, char **argv, char *envp[], int ac);
pid_t	second_process(int *pipefd, char **argv, char *envp[]);
void	free_split(char **path);
void	error(int *pipefd);
void	close_dup(int file1, int i, int *pipefd, int j);
char	*join_path(char *path, char *args);
char	*ft_strdup(const char *s);
void	display_cmd(char **args);
char	*ft_strchr(const char *str, int c);
void	error_exit(void);
int		ft_strlen(const char *c);
void	mid_process(int *pipefd, char *argv, char *envp[]);
void	here_doc(char *arg, int *pipefd);
void	run_here_doc(char *arg);

#endif