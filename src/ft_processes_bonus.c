/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_processes_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:22:57 by pealexan          #+#    #+#             */
/*   Updated: 2023/01/16 11:19:15 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	ft_redirect(int a, int b)
{
	dup2(a, STDIN_FILENO);
	dup2(b, STDOUT_FILENO);
}

char	*ft_getcommand(char *arg, t_pipex *pipex)
{
	char	*temp;
	char	*command;

	if (arg[0] == '.')
		return (arg);
	while (*pipex->paths)
	{
		temp = ft_strjoin(*pipex->paths, "/");
		command = ft_strjoin(temp, arg);
		if (access(command, X_OK) == 0)
			return (command);
		pipex->paths++;
	}
	return (0);
}

char	*ft_multiarg(char **args, int i, int j)
{
	char	*temp;
	char	*multiarg;

	multiarg = ft_strdup(args[i]);
	while (args[j])
	{
		if (ft_isquote(args[j][ft_strlen(args[j]) - 1]))
		{
			multiarg[ft_strlen(multiarg) - 1] = '\0';
			break ;
		}
		temp = ft_strjoin(multiarg, " ");
		multiarg = ft_strjoin(temp, args[j + 1]);
		j++;
	}
	return (multiarg);
}

char	**ft_args(char **argv, t_pipex *p)
{
	char	**args;
	char	*multiarg;
	int		i;
	int		j;

	i = 0;
	j = 0;
	args = ft_split(argv[2 + p->heredoc + p->ix], ' ');
	while (args[i])
	{
		if (ft_isquote(args[i][0]))
		{
			j = i;
			args[i]++;
			multiarg = ft_multiarg(args, i, j);
			args[i] = ft_strdup(multiarg);
			args[i + 1] = 0;
		}
		i++;
	}
	return (args);
}

void	ft_processes(char **argv, char **envp, t_pipex *p)
{
	int		pid;
	char	**args;
	char	*command;

	pid = fork();
	if (pid == 0)
	{
		if (p->ix == 0)
			ft_redirect(p->infile_fd, p->pipe_fd[1]);
		else if (p->ix == p->cmd_nb - 1)
			ft_redirect(p->pipe_fd[2 * p->ix - 2], p->outfile_fd);
		else
			ft_redirect(p->pipe_fd[2 * p->ix - 2], p->pipe_fd[2 * p->ix + 1]);
		ft_close_pipes(p);
		args = ft_args(argv, p);
		command = ft_getcommand(args[0], p);
		if (!command)
		{
			perror(strerror(errno));
			ft_freechild(args, command);
			exit(errno);
		}
		execve(command, args, envp);
	}
}
