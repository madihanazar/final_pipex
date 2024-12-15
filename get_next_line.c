/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:50:00 by mnazar            #+#    #+#             */
/*   Updated: 2024/12/07 22:08:19 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_str(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

static char	*gnl_read(int fd, char *buf, char *str)
{
	int			i;
	char		*tmp;

	i = 1;
	if (str)
		str = ft_strdup_gnl(str);
	while (i > 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1)
			return (free(str), NULL);
		else if (i == 0)
			break ;
		buf[i] = '\0';
		if (!str)
			str = ft_strdup_gnl("");
		tmp = str;
		str = ft_strjoin_gnl(tmp, buf);
		free(tmp);
		tmp = NULL;
		if (ft_strchr_gnl(buf, '\n'))
			break ;
	}
	return (str);
}

static char	*gnl_process(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0' || (str[i] == '\n' && str[i + 1] == '\0'))
		return (NULL);
	ret = ft_substr_gnl(str, i + 1, ft_strlen_gnl(str) - i);
	if (!ret)
	{
		free(ret);
		ret = NULL;
	}
	str[i + 1] = '\0';
	return (ret);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*res;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (free_str(&str));
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free_str(&str));
	res = gnl_read(fd, buf, str);
	free(buf);
	buf = NULL;
	if (!res)
		return (free_str(&str));
	free(str);
	str = NULL;
	str = gnl_process(res);
	buf = ft_strdup_gnl(res);
	free(res);
	res = NULL;
	if (!buf)
		return (free_str(&str));
	return (buf);
}
