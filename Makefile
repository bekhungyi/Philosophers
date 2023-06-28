# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 13:23:41 by bhung-yi          #+#    #+#              #
#    Updated: 2023/06/28 17:28:14 by bhung-yi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
CC			= gcc
FLAGS		= -Wall -Werror -Wextra
RM			= /bin/rm -f

SRCS	= 	./srcs/utils.c \
			./srcs/actions.c \
			./srcs/init.c \
			./srcs/threads.c \

%.o: %.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) philo.c $(SRCS) -o $(NAME) -fsanitize=address

re: fclean all

clean:
	$(RM) -r *.o

fclean: clean
	$(RM) $(NAME)
