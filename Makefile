# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: geibo <geibo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/15 06:55:38 by codespace         #+#    #+#              #
#    Updated: 2024/03/06 14:29:33 by geibo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC = gcc
CFLAGS = -ggdb -fsanitize=address
INCLUDES = -Iincludes -Ilib/ft_printf/includes -Ilib/libft/includes

# Source files
SRCS_DIR = srcs
MAIN_DIR = main
# PARSING_DIR = parsing
EXEC_DIR = executor
UTILS_DIR = utils
ENV_DIR = env
LEXER_DIR = lexer
PARSE_DIR = parsing
EXPAND = expansion
TRAVERSE_DIR = traverse
# SRCS_FILES = $(addprefix $(BUILTINS_DIR)/, cd.c echo.c env.c exit.c export.c pwd.c unset.c) \
#              $(addprefix $(MAIN_DIR)/, minishell.c redir.c signal.c) \
#              $(addprefix $(PARSING_DIR)/, line.c tokens.c expansions.c) \
#              $(addprefix $(TOOLS_DIR)/, fd.c free.c token.c type.c expansions.c parsing.c)
SRCS_FILES = $(addprefix $(MAIN_DIR)/, main.c initialize.c signals.c prompt.c) \
			 $(addprefix $(UTILS_DIR)/, misc.c ft_snprintf.c ft_malloc.c) \
			 $(addprefix $(ENV_DIR)/, env.c env_utils.c) \
			 $(addprefix $(EXPAND)/, expand_dollar.c) \
			 $(addprefix $(EXEC_DIR)/, commands.c cd.c welcome.c export.c execute.c execution_utils.c execution_utils2.c) \
			 $(addprefix $(LEXER_DIR)/, lexer.c lexer_linked_list.c lexer_linked_list_utils.c lexing_utils.c lexer_check_separator.c) \
			 $(addprefix $(PARSE_DIR)/, parse_linked_list.c parse.c dollar_sign.c ast_contruct.c parse_utils.c) \
			 $(addprefix $(TRAVERSE_DIR)/, traverse.c traversing.c exec_utils.c) \

SRCS = $(addprefix $(SRCS_DIR)/,$(SRCS_FILES))

# Object files
OBJS_DIR = objs
# OBJS_DIRS = $(OBJS_DIR) $(OBJS_DIR)/$(BUILTINS_DIR) $(OBJS_DIR)/$(EXEC_DIR) $(OBJS_DIR)/$(MAIN_DIR) $(OBJS_DIR)/$(PARSING_DIR) $(OBJS_DIR)/$(TOOLS_DIR)
OBJS_DIRS = $(OBJS_DIR) $(OBJS_DIR)/$(MAIN_DIR) $(OBJS_DIR)/$(UTILS_DIR) $(OBJS_DIR)/$(EXEC_DIR) $(OBJS_DIR)/$(ENV_DIR) $(OBJS_DIR)/$(LEXER_DIR) $(OBJS_DIR)/$(PARSE_DIR) $(OBJS_DIR)/$(TRAVERSE_DIR) $(OBJS_DIR)/$(EXPAND)
OBJS_FILES = $(patsubst %.c,%.o,$(SRCS_FILES))
OBJS = $(addprefix $(OBJS_DIR)/,$(OBJS_FILES))

# Libraries
LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

PRINTF_DIR = lib/ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

LIBS = -L$(LIBFT_DIR) -L$(PRINTF_DIR) -lft -lftprintf -lreadline

# Binary
NAME = minishell

# Colors and text formatting
RESET = \033[0m
BOLD = \033[1m
DIM = \033[2m
UNDERLINE = \033[4m
BLINK = \033[5m
INVERT = \033[7m
LIGHT_BLUE = \033[94m
YELLOW = \033[93m

# Makefile rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	@echo "$(BOLD)$(LIGHT_BLUE)Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(BOLD)$(LIGHT_BLUE)$(NAME) created successfully!$(RESET)"
	@echo "$(BOLD)Copyright Reserved. Lee Sin Liang."

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIRS)
	@echo "$(BOLD)$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(BOLD)$(LIGHT_BLUE)Building libft...$(RESET)"
	@make -C $(LIBFT_DIR) -s

$(PRINTF):
	@echo "$(BOLD)$(LIGHT_BLUE)Building ft_printf...$(RESET)"
	@make -C $(PRINTF_DIR) -s

clean:
	@echo "$(BOLD)$(LIGHT_BLUE)Cleaning objects...$(RESET)"
	@rm -rf $(OBJS_DIR)
	@rm -f a.out
	@make -C $(LIBFT_DIR) clean -s
	@make -C $(PRINTF_DIR) clean -s

fclean: clean
	@echo "$(BOLD)$(LIGHT_BLUE)Cleaning $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean -s
	@make -C $(PRINTF_DIR) fclean -s

re: fclean all

.PHONY: all clean fclean re
