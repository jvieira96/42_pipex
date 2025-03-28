# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 17:11:13 by jpedro-f          #+#    #+#              #
#    Updated: 2025/03/28 16:05:42 by jpedro-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                NAMES & PATHS                                 #
#==============================================================================#
NAME = pipex

BONUS_NAME = pipex_bonus

HEADER = pipex.h \
		pipex_bonus.h

SRCS = main.c \
       errors.c \
       pipes.c \
       processes.c \
       utils.c

BONUS = bonus/main_bonus.c \
        bonus/errors_bonus.c \
        bonus/pipes_bonus.c \
        bonus/processes_bonus.c \
        bonus/utils_bonus.c

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS:.c=.o)

LIBFT_DIR = libft/

LIBFT = $(LIBFT_DIR)/libft.a

#==============================================================================#
#                            FLAGS & COMMANDS                                  #
#==============================================================================#
C_COMP = cc
FLAGS = -Wall -Wextra -Werror -g
RM = rm -f
MAKE = make
AR = ar rcs

#==============================================================================#
#                                  COLORS                                      #
#==============================================================================#
RED = "\033[0;31m"
GREEN = "\033[0;32m"  
YELLOW = "\033[0;33m" 
RESET = "\033[0m"

#==============================================================================#
#                               RULES & DEPS                                   #
#==============================================================================#
all: $(NAME)

bonus: $(BONUS_NAME)

%.o: %.c $(HEADER)
	@$(C_COMP) $(FLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@$(C_COMP) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo $(GREEN) "$(NAME) was created successfully!" $(RESET)
	@touch $(NAME)  # Marks as up to date to prevent relinking

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT)
	@$(C_COMP) $(FLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)
	@echo $(GREEN) "Bonus $(BONUS_NAME) was created successfully!" $(RESET)
#==============================================================================#
#                                  CLEAN RULES                                 #
#==============================================================================#
clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo $(RED) "All .o files were deleted!" $(RESET)

fclean: clean
	@$(RM) $(NAME) $(BONUS_NAME) $(LIBFT)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo $(RED) "$(NAME) was deleted!" $(RESET)

re: fclean all

.PHONY: all clean fclean re bonus
