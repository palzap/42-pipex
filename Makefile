# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 08:46:18 by pealexan          #+#    #+#              #
#    Updated: 2022/12/06 16:33:14 by pealexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
LIBFT		= libft.a

#----------DIRS----------#
SRCDIR = ./src/
LIBFTDIR = ./libft/
HEADERDIR = ./headers/

SRC = 	src/pipex.c \
	src/ft_filesandpipes.c \
	src/ft_free.c \
	src/ft_heredoc.c \
	src/ft_processes.c \

SRC_BONUS =	src/pipex_bonus.c \
	src/ft_filesandpipes_bonus.c \
	src/ft_free_bonus.c \
	src/ft_heredoc_bonus.c \
	src/ft_processes_bonus.c \

#--------COMMANDS--------#
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf

OBJ = ${SRC:.c=.o}
OBJ_BONUS = ${SRC_BONUS:.c=.o}

#---------RULES---------#
.c.o:
		$(CC) $(CFLAGS) -c -I$(HEADERDIR) $< -o ${<:.c=.o}

all: 		$(NAME)

$(LIBFT):
		cd $(LIBFTDIR) && $(MAKE)
	
$(NAME): 	$(OBJ) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFTDIR)$(LIBFT) -o $(NAME)
		
bonus: 	$(OBJ_BONUS) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFTDIR)$(LIBFT) -o $(NAME)	
clean:
		$(RM) $(OBJ) $(OBJ_BONUS)
		cd $(LIBFTDIR) && $(MAKE) clean

fclean: 	clean
		$(RM) $(NAME) $(LIBFT)
		cd $(LIBFTDIR) && $(MAKE) fclean
	
re: fclean all
