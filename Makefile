# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/05 14:14:37 by kshim             #+#    #+#              #
#    Updated: 2022/07/11 14:42:51 by kshim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Werror -Wextra
DEBUG = -g
RM = rm
RMFLAGS = -f

HEADERS = -I$(INCLUDE)

LIBDIR = ./libft

LIBFLAG = -lft

INCLUDE = ./include

SRCSDIR = ./srcs/

BONUS_SRCSDIR = ./srcs_bonus/

SRCS_FILES = pipex.c ft_px_util.c ft_px_data_structs.c ft_px_parse_argv.c

BONUS_SRCS_FILES = 

SRCS = $(addprefix $(SRCSDIR), $(SRCS_FILES))

BONUS_SRCS = $(addprefix $(BONUS_SRCSDIR), $(BONUS_SRCS_FILES))

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

ifdef DO_BONUS
	OBJECTS = $(OBJS) $(BONUS_OBJS)
else
	OBJECTS = $(OBJS)
endif

$(NAME): $(LIBDIR) $(OBJECTS)
	make -C $(LIBDIR) bonus
	$(CC) $(CFLAGS) $(DEBUG) -I$(LIBDIR) $(HEADERS) $(OBJECTS) -L$(LIBDIR) $(LIBFLAG) -o $(NAME)

%.o	: %.c
	$(CC) $(CFLAGS) $(DEBUG) $(HEADERS) -I$(LIBDIR) -c $< -o $@

all : $(NAME)

bonus: 
	make DO_BONUS=1 all
	
clean:
	make -C $(LIBDIR) clean
	$(RM) $(RMFLAGS) $(OBJS) $(BONUS_OBJS)

fclean: clean
	make -C $(LIBDIR) fclean
	$(RM) $(RMFLAGS) $(NAME)

re: 
	make fclean 
	make all

.PHONY:all bonus clean fclean re
