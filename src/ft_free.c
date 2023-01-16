/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:20:58 by pealexan          #+#    #+#             */
/*   Updated: 2023/01/16 09:00:29 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	ft_freemain(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
	if (pipex->heredoc)
		unlink(".heredoc");
	while (pipex->paths[i])
	{
		free(pipex->paths[i]);
		i++;
	}
	free(pipex->paths);
	free(pipex->pipe_fd);
}

void	ft_freechild(char **args, char *command)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	free(command);
}

void	ft_freepipe(t_pipex *pipex)
{
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
	if (pipex->heredoc)
		unlink(".heredoc");
	free(pipex->pipe_fd);
	perror(strerror(errno));
	exit(1);
}
