# Main var
NAME = minishell

# GCC
CC = gcc
CFLAGS = -g3 -fsanitize=address -Wall -Wextra -I includes/ -I libft/includes

# Sources & Objects
SRCS =	srcs/main.c		\
		srcs/input.c	\
		srcs/env1.c		\
		srcs/env2.c		\

OBJS_PATH = objs/
OBJS = $(patsubst srcs/%.c,$(OBJS_PATH)%.o, $(SRCS))

# Includes
LIBFT = libft/
INCLUDES = -L libft/ -lft
# Utils
RM = rm -rf
SHELL = /bin/zsh

# Compiling & other stuff

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	@make -C $(LIBFT)
	@printf "\e[1;32m%-30s\e[0m" "Creating $@"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDES)
	@printf "\e[1;32m%08s\e[0m\n" "[ OK ]"

$(OBJS_PATH)%.o : srcs/%.c
	@mkdir -p $(OBJS_PATH)
	@printf "\e[1;36m%-30s\e[0m" "$<"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\e[1;32m%08s\e[0m\n" "[ OK ]"
clean :
	@make clean -C $(LIBFT)
	@$(RM) $(OBJS_PATH)
	@echo "\e[1;33m Cleaning objects. \e[0m"

fclean : clean
	@make fclean -C $(LIBFT)
	@$(RM) $(NAME)
	@echo "\e[1;33m Cleaning $(NAME). \e[0m"

re : fclean all

.PHONY : all clean fclean re
