/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:06:17 by pealexan          #+#    #+#             */
/*   Updated: 2023/01/16 11:19:19 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	int		heredoc;
	int		cmd_nb;
	int		pipe_nb;
	int		*pipe_fd;
	int		ix;
	char	**paths;
	int		status;
}	t_pipex;

void	ft_freepipe(t_pipex *pipex);
void	ft_freechild(char **args, char *command);
void	ft_freemain(t_pipex *pipex);
void	ft_processes(char **argv, char **envp, t_pipex *p);
char	*ft_getcommand(char *arg, t_pipex *pipex);
void	ft_redirect(int a, int b);
void	ft_heredoc(char *limiter, t_pipex *pipex);
void	ft_getoutfile_fd(char *argv, t_pipex *pipex);
void	ft_getinfile_fd(char **argv, t_pipex *pipex);
void	ft_close_pipes(t_pipex *pipex);
void	ft_open_pipes(t_pipex *pipex);
int		ft_errormsg(char *error);
void	ft_error(char *error, int i);
char	**ft_args(char **argv, t_pipex *p);
char	*ft_multiarg(char **args, int i, int j);

#endif
