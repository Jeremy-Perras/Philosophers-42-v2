# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jperras <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 08:32:21 by jperras           #+#    #+#              #
#    Updated: 2022/04/02 14:29:57 by jperras          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = Philosophers.c ft_philosophers_init.c ft_atoi.c ft_philosophers_utils.c ft_fork.c ft_new_thread.c

CC = gcc

CCDB = gcc -g

FLAGS = -Wall -Werror -Wextra 

OBJS = $(SRCS:.c=.o)

INCLUDES = -I./includes

.c.o:
		${CC} ${FLAGS} -I./includes  -c $< -o ${<:.c=.o}


$(NAME) : $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(INCLUDES) $(OBJS) 	

all : $(NAME)

test:
	$(CC) $(FLAGS) $(INCLUDES) $(SRCS) 	

debug:
	$(CCDB) $(FLAGS) -o $(NAME) $(INCLUDES) $(SRCS) 

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re
