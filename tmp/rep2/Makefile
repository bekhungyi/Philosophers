# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 16:32:57 by jchu              #+#    #+#              #
#    Updated: 2023/07/10 19:55:17 by bhung-yi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

AR_NAME		= philo.a

SRCS		= srcs/actions.c \
				srcs/init_input.c \
				srcs/init_threads.c \
				philo.c \
				srcs/utils.c \

OBJS		= $(SRCS:%.c=%.o)

CC			= gcc

AR			= ar rc

FLAGS		= -Wall -Werror -Wextra
LFLAGS		= -pthread


$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) -fsanitize=thread -lpthread -g3
	$(AR) $(AR_NAME) $(OBJS)
	rm -f $(OBJS)
 
all: $(NAME)

clean:
	rm -f $(AR_NAME)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PONY: all clean fclean re