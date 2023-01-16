/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 08:51:58 by pealexan          #+#    #+#             */
/*   Updated: 2023/01/16 09:16:19 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

char	**ft_getpaths(char **env)
{
	while (ft_strncmp(*env, "PATH", 4))
		env++;
	return (ft_split(*env + 5, ':'));
}

int	ft_total_args(char *argv1, t_pipex *pipex)
{
	if (!ft_strncmp("here_doc", argv1, 9))
	{
		pipex->heredoc = 1;
		return (6);
	}
	else
		return (5);
}

void	ft_init_pipex(t_pipex *pipex)
{
	pipex->cmd_nb = 0;
	pipex->heredoc = 0;
	pipex->infile_fd = 0;
	pipex->ix = 0;
	pipex->outfile_fd = 0;
	pipex->paths = 0;
	pipex->pipe_fd = 0;
	pipex->pipe_nb = 0;
}

int	ft_errormsg(char *error)
{
	ft_printf("%s", error);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5 || argc < ft_total_args(argv[1], &pipex))
		return (ft_errormsg("Not enough arguments.\n"));
	ft_init_pipex(&pipex);
	ft_getinfile_fd(argv, &pipex);
	ft_getoutfile_fd(argv[argc - 1], &pipex);
	pipex.cmd_nb = (argc - 3 - pipex.heredoc);
	pipex.pipe_nb = (pipex.cmd_nb - 1) * 2;
	pipex.pipe_fd = (int *)malloc(sizeof(int) * pipex.pipe_nb);
	if (!pipex.pipe_fd)
		return (ft_errormsg(strerror(errno)));
	pipex.paths = ft_getpaths(envp);
	if (!pipex.paths)
		ft_freepipe(&pipex);
	ft_open_pipes(&pipex);
	pipex.ix = -1;
	while (++pipex.ix < pipex.cmd_nb)
		ft_processes(argv, envp, &pipex);
	ft_close_pipes(&pipex);
	wait(&pipex.status);
	ft_freemain(&pipex);
	return (0);
}
