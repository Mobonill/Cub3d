/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morgane <morgane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:01:10 by morgane           #+#    #+#             */
/*   Updated: 2025/01/21 18:22:47 by morgane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void print_char_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return;
}
void	err(char *str)
{
	while (*str)
		write(2, str++, 1);
	exit(1);
}
int count_lines_fd(char *argv)
{
	char *line;
	int len;
	int fd;

	line = NULL;
	len = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		err(OPENFD);
	while ((line = get_next_line(fd)) != NULL)
	{
		len++;
		free(line);
	}
	close(fd);
	return (len);
}


