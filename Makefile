# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/15 15:48:03 by kdouveno          #+#    #+#              #
#    Updated: 2017/12/18 15:00:05 by kdouveno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

SRCS =	check.c\
		display.c\
		main.c\
		parse.c\

LIBS = libft/libft.a libs/libmlx.a

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	@gcc $(FLAGS) $(LIBS) $(OBJS)
	@ranlib $@
%.o: %.c
	@gcc $(FLAGS) -I includes -c $^

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
