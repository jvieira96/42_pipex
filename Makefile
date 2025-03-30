# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 17:11:13 by jpedro-f          #+#    #+#              #
#    Updated: 2025/03/30 19:39:37 by jpedro-f         ###   ########.fr        #
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
CFLAGS = -Wall -Wextra -Werror -g
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

bonus: $(LIBFT) $(BONUS_OBJS)
	@if [ -f $(NAME) ]; then $(RM) $(NAME); fi  # Delete pipex only if it exists
	$(C_COMP) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(NAME)
	@echo $(GREEN) "Bonus version of $(NAME) was created successfully!" $(RESET)
	@touch $(NAME)  # Marks it as up-to-date

%.o: %.c $(HEADER)
	$(C_COMP) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@if [ -f $(NAME) ]; then $(RM) $(NAME); fi  # Delete pipex if it was created by bonus
	$(C_COMP) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo $(GREEN) "$(NAME) was created successfully!" $(RESET)
	@touch $(NAME)  # Marks it as up-to-date

#==============================================================================#
#                                  CLEAN RULES                                 #
#==============================================================================#
clean:
	$(RM) $(OBJS) $(BONUS_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	@echo $(RED) "All .o files were deleted!" $(RESET)

fclean: clean
	$(RM) $(NAME) $(LIBFT)
	$(MAKE) -C $(LIBFT_DIR) fclean
	@echo $(RED) "$(NAME) was deleted!" $(RESET)

re: fclean all

.PHONY: all clean fclean re bonus
