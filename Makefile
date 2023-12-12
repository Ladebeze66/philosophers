# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgras-ca <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/23 16:10:39 by fgras-ca          #+#    #+#              #
#    Updated: 2023/10/23 16:10:46 by fgras-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LOGO = @echo " __,     ____, ____,  ____,  ____   ____,  ___,   ____,";\
	echo "(-|     (-/_| (-|  \ (-|_,  (-|__) (-|_,  (- /   (-|_,";\
        echo " _|__,  _/  |, _|__/  _|__,  _|__)  _|__,  _/__,  _|__,";\
        echo "(      (      (      (      (      (      (      ("

RST			= \033[0m
GRAY			= \033[0;90m
RED			= \033[0;91m
GREEN			= \033[0;92m
YELLOW			= \033[0;93m
BLUE			= \033[0;94m
MAGENTA			= \033[0;95m
CYAN			= \033[0;96m
WHITE			= \033[0;97m
ORANGE			= \033[38;5;214m

NAME = philo

SRCS = 	main.c \
	threads.c \
	initialize.c \
	time.c \
	philos.c \
	utils.c \
	memory.c \
	routine.c \
	forks.c \
	monitoring.c \

OBJS =	$(SRCS:.c=.o)

CC = gcc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -g 

all:	$(NAME)

$(NAME): $(OBJS)
	@echo "$(RED)Compilation philosopher... $(RST)"
	@$(CC)  $(CFLAGS) $(OBJS) -o $(NAME) -lpthread
	@echo "$(GREEN)Compilation complete. $(ORANGE)Type "./philo" for the menu!!$(RST)"
	$(LOGO)

t : $(NAME)
	@echo "$(RED)Compilation philosopher with fsanitize... $(RST)"
	@$(CC) $(CFLAGS) -fsanitize=thread $(OBJS) -o $(NAME) -lpthread
	@echo "$(GREEN)Compilation complete. $(ORANGE)Type "./philo" for the menu!!$(RST)"	
	$(LOGO)

clean:
	@echo "$(RED)Deleating files objects... $(RST)"
	@$(RM) $(OBJS)
	@echo "$(GREEN)files deleted!! $(RST)"
	$(LOGO)

fclean: clean
	@echo "$(RED)Deleting program... $(RST)"
	@$(RM) $(NAME)
	@echo "$(GREEN)files deleted!! $(RST)"
	$(LOGO)

re: fclean all

.PHONY: all t clean fclean re
