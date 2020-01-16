##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

CC		=       gcc

RM		=	rm -f

INCDIRS		=	$(addprefix -I, $(shell find ./include -type d -print))

CFLAGS		=       -Wall -Wextra -Wmissing-prototypes

CPPFLAGS	+=      $(INCDIRS)

NAME		=	myftp

SRCS		=	./src/connection.c	\
			./src/multi_clients.c	\
			./src/communication.c	\
			./src/my_ftp.c		\
			./src/basic_cmd.c	\
			./src/normal_cmd.c	\
			./src/call_cmd.c	\
			./src/close_window.c	\
			./src/parsing.c		\
			main.c

OBJS            =       $(addsuffix .o, $(basename $(SRCS)))

all             :       $(NAME)

$(NAME)         :       $(OBJS)
		@$(CC) -o $(NAME) $(OBJS)
		@printf "[\033[1;33mBuilt\033[0m] % 32s\n" $(NAME) | tr ' ' '.'
		@echo -e "\033[34m\n==== \033[35mCOMPLETED\033[34m ====\033[0m"

clean           :
		@$(RM) $(OBJS)
		@printf "[\033[1;31mDeleted_Obj\033[0m] % 30s\n" $(OBJS) | tr ' ' '.'

fclean          :       clean
		@$(RM) $(NAME)
		@printf "[\033[1;31mDeleted_Binary\033[0m] % 30s\n" $(NAME) | tr ' ' '.'

re              :       fclean all

%.o		:	%.c
		@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
		@echo -e "[\e[32mCompiled\033[0m]" "---->" $< || echo -e "REALLY NIGGA ??!!" $<

.PHONY		:	all clean fclean re %.o
