# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 17:11:13 by jpedro-f          #+#    #+#              #
#    Updated: 2025/03/31 17:29:15 by jpedro-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                NAMES & PATHS                                 #
#==============================================================================#
NAME = pipex

HEADER = pipex.h \
		pipex_bonus.h

SRCS = main.c \
       errors.c \
       pipes.c \
       processes.c \
       utils.c

BONUS_SRCS = bonus/main_bonus.c \
             bonus/errors_bonus.c \
             bonus/pipes_bonus.c \
             bonus/processes_bonus.c \
             bonus/utils_bonus.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)/libft.a

#==============================================================================#
#                            FLAGS & COMMANDS                                  #
#==============================================================================#
C_COMP = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f
MAKE = make

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

all:
	@if [ ! -f "$(NAME)" ]; then \
		$(MAKE) normal_build; \
	else \
		echo $(YELLOW) "$(NAME) already exists!" $(RESET); \
	fi

bonus:
	@if [ ! -f "$(NAME)" ]; then \
		$(MAKE) bonus_build; \
	else \
		echo $(YELLOW) "$(NAME) already exists!" $(RESET); \
	fi

normal_build: $(OBJS) $(LIBFT)
	@$(C_COMP) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo $(GREEN) "$(NAME) (normal version) was created successfully!" $(RESET)

bonus_build: $(BONUS_OBJS) $(LIBFT)
	@$(C_COMP) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(NAME)
	@echo $(GREEN) "$(NAME) (bonus version) was created successfully!" $(RESET)

%.o: %.c $(HEADER)
	@$(C_COMP) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(LIBFT_DIR)

#==============================================================================#
#                                  CLEAN RULES                                 #
#==============================================================================#
clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo $(RED) "All object files were deleted!" $(RESET)

fclean: clean
	@$(RM) $(NAME) $(LIBFT)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo $(RED) "$(NAME) was deleted!" $(RESET)

re: fclean all

.PHONY: all clean fclean re bonus normal_build bonus_build
