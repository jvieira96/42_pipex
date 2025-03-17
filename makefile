# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpedro-f <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 17:11:13 by jpedro-f          #+#    #+#              #
#    Updated: 2025/03/17 17:11:20 by jpedro-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                NAMES & PATHS                                 #
#==============================================================================#
NAME = pipex
HEADER_PATH = pipex.h
SRCS = main.c \
		checks.c \
		errors.c \
		pipes.c \
		processes.c \
		utils.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ./libft/
LIBFT = ./Libft/libft.a

#==============================================================================#
#                            FLAGS & COMMANDS                                  #
#==============================================================================#
C_COMP = cc

FLAGS = -Wall -Werror -Wextra -g

RM = rm -f

AR = ar rcs

MAKE = make
#==============================================================================#
#                                  COLORS                                      #
#==============================================================================#
RED			= "\033[0;31m"
GREEN		= "\033[0;32m"  
YELLOW		= "\033[0;33m" 
RESET		= "\033[0m"
#==============================================================================#
#                               RULES & DEPS                                   #
#==============================================================================#
all: $(LIBFT) $(NAME)

%.o: %.c 
	@$(C_COMP) $(FLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@$(C_COMP) $(FLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo $(GREEN) "$(NAME) was created successfully!" $(RESET)
#==============================================================================#
#                                  CLEAN RULES                                 #
#==============================================================================#
clean:
	@$(RM) $(OBJS)
	@echo $(RED) "All .o files were deleted!" $(RESET)

cleanall: clean
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME)
	@echo $(RED) "$(NAME) was deleted!" $(RESET)

fcleanall: cleanall fclean
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re cleanall fcleanall
