/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:25:45 by pealexan          #+#    #+#             */
/*   Updated: 2023/01/16 09:12:10 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	ft_error(char *error, int i)
{
	if (i == 1)
	{
		perror(error);
		exit(errno);
	}
	if (i == 2)
	{
		unlink(".heredoc");
		perror(error);
		exit(errno);
	}
}

void	ft_heredoc(char *limiter, t_pipex *pipex)
{
	int		tempfile;
	char	*buff;

	tempfile = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (tempfile < 0)
		ft_error(strerror(errno), 1);
	while (1)
	{
		write(1, "heredoc> ", 9);
		buff = get_next_line(0);
		buff[ft_strlen(buff) - 1] = '\0';
		if (!buff)
			exit(errno);
		if (!ft_strncmp(limiter, buff, ft_strlen(limiter) + 1))
			break ;
		write(tempfile, buff, ft_strlen(buff));
		write(tempfile, "\n", 1);
		free(buff);
	}
	free(buff);
	close(tempfile);
	pipex->infile_fd = open(".heredoc", O_RDONLY);
	if (pipex->infile_fd < 0)
		ft_error(strerror(errno), 2);
}
