# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgregory <cgregory@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 10:09:46 by cgregory          #+#    #+#              #
#    Updated: 2022/06/22 18:21:45 by cgregory         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo
SRCS_DIR		=	./src/
SRCS			=	main.c		ft_atoi_char.c	init.c	utils.c\
					errors.c	monitor.c		actions.c\
					philo_eats.c
PHILO_H			=	philo.h
HEADERS			=	./inc/
OBJ				=	$(addprefix $(SRCS_DIR), $(SRCS:%.c=%.o))
CC				=	cc
LFLAGS			=	-pthread
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -rf
.PHONY			:	all clean fclean re bonus
all				:	$(NAME)
$(NAME)			:	$(OBJ) $(HEADERS)$(PHILO_H)
					@$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -o $(NAME)
					@echo "$(BLUE)project $(NAME) created!$(DEFAULT)"
%.o:				%.c $(HEADERS)$(PHILO_H)
					@$(CC) $(CFLAGS) $(LFLAGS) -I$(HEADERS) -c $< -o $@
clean			:	
					@$(RM) $(OBJ)
					@echo "$(YELLOW)object files deleted!$(DEFAULT)"
fclean			:	clean
					@$(RM) $(NAME)
					@echo "$(RED)all files deleted!$(DEFAULT)"
re				:	fclean all

RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
DEFAULT = \033[0m
