# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhung-yi <bhung-yi@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 16:32:57 by bhung-yi          #+#    #+#              #
#    Updated: 2023/09/01 19:28:01 by bhung-yi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

AR_NAME		= philo.a

SRCS		= philo.c \
				src/actions.c \
				src/init_input.c \
				src/init_p_f.c \
				src/init_threads.c \
				src/utils.c \
				src/process.c \

OBJS		= $(SRCS:%.c=%.o)

CC			= gcc

AR			= ar rc

FLAGS		= -Wall -Werror -Wextra 
LFLAGS		= -fsanitize=thread -lpthread -g3 -pthread


$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(LFLAGS) $(OBJS) -o $(NAME)
 
all: $(NAME)

clean:
	rm -f $(AR_NAME)
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
	touch $(NAME)

.PHONY: all clean fclean re
