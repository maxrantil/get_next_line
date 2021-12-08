/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:00:51 by mrantil           #+#    #+#             */
/*   Updated: 2021/12/08 14:57:41 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFF_SIZE 10000

static int	ft_strlennl(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n')
		i++;
	return (i + 1);
}

int	get_next_line(const int fd, char **line)
{
	char			read_buf[BUFF_SIZE + 1];
	char			*temp;
	static char		*stat_buf;
	int				ret;

	ret = 1;
	if (!stat_buf)
		stat_buf = ft_strnew(BUFF_SIZE);
	if (ft_strchr(stat_buf, '\n') != NULL) //check if \n is in stat_buf
	{
		*line = ft_strsub(stat_buf, 0, ft_strlennl(stat_buf) - 1); //cpy str before \n into  *line
		if (ft_strchr(stat_buf, '\n')) //check if there is a string in stat_buf after \n
			temp = ft_strdup(ft_strchr(stat_buf, '\n') + 1); // put leftover str into temp
		ft_strdel(&stat_buf);
		stat_buf = ft_strdup(temp);
		ft_strdel(&temp);
		return (1);
	}
	while (ret)
	{
		ret = read(fd, read_buf, BUFF_SIZE);
		read_buf[ret] = '\0';
		if (ft_strchr(read_buf, '\n') == NULL && ft_strchr(stat_buf, '\0') != NULL) //check if buffer has newline - buffer no newline
		{
			stat_buf = ft_strjoin(stat_buf, ft_strdup(read_buf));
		}
		else if (ft_strchr(read_buf, '\n') != NULL) //check if buffer has newline - buffer has newline 
		{
			stat_buf = ft_strjoin(stat_buf, ft_strsub(read_buf, 0, ft_strlennl(read_buf) - 1)); //(static+buffer before \n) (VARNING! look if work)
			temp = ft_strdup(ft_strchr(read_buf, '\n') + 1); //leftover from static into temp
			*line = ft_strdup(stat_buf);
			ft_strdel(&stat_buf);
			stat_buf = ft_strdup(temp);
			ft_strdel(&temp);
			return (1);
		}
	}
	*line = ft_strdup(stat_buf);
	ft_strdel(&stat_buf);
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
//	if (get_next_line(fd, &line))
//		printf("%d	%s", get_next_line(fd, &line), line);
//	if (get_next_line(fd, &line))
//		printf("%s", line);
	while (get_next_line(fd, &line))
		printf("%s\n", line);
	printf("%s\n", line);
	return (0);
}
//first run returns one space too much and a nl?
