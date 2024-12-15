/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:14:29 by mnazar            #+#    #+#             */
/*   Updated: 2024/12/15 21:17:45 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *str1, const char *str2, int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		return (0);
	while (str1[i] != '\0' && str1[i] == str2[i] && i < n - 1)
		i++;
	return (str1[i] - str2[i]);
}

void	free_split(char **path)
{
	int	i;

	i = 0;
	if (!path)
		return ;
	while (path[i] != NULL)
	{
		free(path[i]);
		i++;
	}
	free(path);
}

char	*join_path(char *path, char *args)
{
	char	*full_cmd;
	char	*temp;

	temp = ft_strjoin(path, "/");
	if (temp == NULL)
		return (NULL);
	full_cmd = ft_strjoin(temp, args);
	free(temp);
	return (full_cmd);
}

char	*extract_path(char *envp[], char *args)
{
	int		i;
	char	**paths;
	char	*full_cmd;

	i = 0;
	while (envp[i] != NULL && (ft_strncmp(envp[i], "PATH=", 5) != 0))
		i++;
	if (envp[i] == NULL)
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_cmd = join_path(paths[i], args);
		if (full_cmd == NULL)
			return (free_split(paths), NULL);
		if (access(full_cmd, X_OK) == 0)
			return (free_split(paths), full_cmd);
		free(full_cmd);
		i++;
	}
	return (free_split(paths), NULL);
}

void	run_here_doc(char *arg)
{
	char	*str;

	if (!arg)
		exit(1);
	while (1)
	{
		str = get_next_line(0);
		if (str == NULL)
			exit(0);
		if (ft_strncmp(str, arg, ft_strlen(arg) + 1) == 0)
			(free(str), free(arg), exit(0));
		ft_putstr_fd(str, 1);
		free(str);
	}
}
