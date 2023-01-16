/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filesandpipes_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:26:55 by pealexan          #+#    #+#             */
/*   Updated: 2023/01/16 09:10:13 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	ft_open_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nb - 1)
	{
		if (pipe(pipex->pipe_fd + (2 * i)) < 0)
			ft_freemain(pipex);
		i++;
	}
}

void	ft_close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->pipe_nb)
	{
		close(pipex->pipe_fd[i]);
		i++;
	}
}

void	ft_getinfile_fd(char **argv, t_pipex *pipex)
{
	if (!ft_strncmp("here_doc", argv[1], 9))
	{
		pipex->heredoc = 1;
		ft_heredoc(argv[2], pipex);
	}
	else
	{
		pipex->infile_fd = open(argv[1], O_RDONLY);
		if (!pipex->infile_fd)
		{
			perror(strerror(errno));
			exit(1);
		}
	}
}

void	ft_getoutfile_fd(char *argv, t_pipex *pipex)
{
	if (!pipex->heredoc)
		pipex->outfile_fd = open(argv, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	else
		pipex->outfile_fd = open(argv, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
	if (!pipex->outfile_fd)
	{
		perror(strerror(errno));
		exit(1);
	}
}
