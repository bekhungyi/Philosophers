# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 13:23:41 by bhung-yi          #+#    #+#              #
#    Updated: 2023/06/10 13:25:28 by bhung-yi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
CC			= gcc
FLAGS		= -Wall -Werror -Wextra
RM			= /bin/rm -f

SRCS	= 	./srcs/ft_utils.c \
			./srcs/ft_utils.c \

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
