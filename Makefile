# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vboivin <marvin42.fr>                     +#+   +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/17 14:50:04 by vboivin           #+#    #+#              #
#    Updated: 2017/09/13 21:50:12 by vboivin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
HPATH		= includes
INC			= -I$(HPATH) -Ilibft/includes
FLAGS		= -Wall -Werror -Wextra
COMP		= gcc
LIBFT		= -Llibft -lft

SRCS 		= main.c env.c
DIR_SRC		= $(addprefix $(SRCPATH)/, $(SRCS))
SRCPATH		= src

OBJ 		= $(SRCS:.c=.o)
DIR_OBJ		= $(addprefix $(OBJPATH)/, $(OBJ))
OBJPATH		= obj

all: $(NAME)

$(OBJPATH)/%.o: $(SRCPATH)/%.c
	@printf "Compiling $<                                            \r"
	@$(COMP) $(FLAGS) -c $< -o $@ $(INC)

$(NAME): $(DIR_OBJ)
	@printf "                                                        \r"
	@printf "main compilation:\tdone\n"
	@make -C libft
	@$(COMP) $(DIR_OBJ) -o $(NAME) $(INCMAC) $(LIBFT) $(FLAGS)

clean:
	@make clean -C libft
	@rm -rf $(OBJ)

fclean: rmtest
	@make fclean -C libft
	@rm -rf $(DIR_OBJ)
	@rm -rf $(NAME)
test:
	@mkdir test_dir
	@mkdir test_dir/test_rec
	@mkdir test_dir/test_rec2
	@touch test_dir/test_file
	@touch test_dir/test_file2
	@chmod 7000 test_dir/test_file
	@chmod 7777 test_dir/test_file2
	@ln -s test_dir/test_file test_dir/test_link

rmtest:
	@rm -rf test_dir

re: fclean all
