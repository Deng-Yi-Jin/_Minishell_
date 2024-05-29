# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: geibo <geibo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/15 06:55:38 by codespace         #+#    #+#              #
#    Updated: 2024/05/29 13:13:55 by geibo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC = gcc
CFLAGS = -ggdb -Wall -Werror -Wextra -fsanitize=address -w
INCLUDES = -Iincludes -Ilib/ft_printf/includes -Ilib/libft/includes

# Source files
SRCS_DIR = srcs
MAIN_DIR = main
# PARSING_DIR = parsing
GNL = gnl
EXEC_DIR = executor
DOLLAR = dollar_deal
UTILS_DIR = utils
ENV_DIR = env
LEXER_DIR = lexer
PARSE_DIR = parsing
EXPAND = expansion
TRAVERSE_DIR = traverse
REDIR_DIR = redirection
DQUOTE = dquote
EXECUTION_DIR = execution_fd
# SRCS_FILES = $(addprefix $(BUILTINS_DIR)/, cd.c echo.c env.c exit.c export.c pwd.c unset.c) \
#              $(addprefix $(MAIN_DIR)/, minishell.c redir.c signal.c) \
#              $(addprefix $(PARSING_DIR)/, line.c tokens.c expansions.c) \
#              $(addprefix $(TOOLS_DIR)/, fd.c free.c token.c type.c expansions.c parsing.c)
SRCS_FILES = $(addprefix $(MAIN_DIR)/, main.c initialize.c signals.c prompt.c) \
			 $(addprefix $(DQUOTE)/, dquote.c dquote_utils.c rm_quote.c) \
			 $(addprefix $(DOLLAR)/, dollar_sign.c dollar_utils.c dollar_execute_utils.c) \
			 $(addprefix $(UTILS_DIR)/, misc.c ft_snprintf.c ft_malloc.c) \
			 $(addprefix $(ENV_DIR)/, env.c env_utils.c) \
			 $(addprefix $(EXPAND)/, expand_dollar.c) \
			 $(addprefix $(GNL)/, get_next_line.c) \
			 $(addprefix $(EXEC_DIR)/, echo_checker.c commands.c cd.c welcome.c export.c execution_utils.c execution_utils2.c echo.c) \
			 $(addprefix $(LEXER_DIR)/, lexer.c lexer_linked_list.c lexer_linked_list_utils.c lexing_utils.c lexer_check_separator.c) \
			 $(addprefix $(PARSE_DIR)/, parse_linked_list.c parse.c ast_contruct.c parse_utils.c) \
			 $(addprefix $(TRAVERSE_DIR)/, traverse.c traversing.c exec_utils.c) \
			 $(addprefix $(REDIR_DIR)/, redirection.c redir_bool.c) \
			 $(addprefix $(EXECUTION_DIR)/, execute.c execute_utils.c execute_utils1.c fd_execution.c)

SRCS = $(addprefix $(SRCS_DIR)/,$(SRCS_FILES))

# Object files
OBJS_DIR = objs
# OBJS_DIRS = $(OBJS_DIR) $(OBJS_DIR)/$(BUILTINS_DIR) $(OBJS_DIR)/$(EXEC_DIR) $(OBJS_DIR)/$(MAIN_DIR) $(OBJS_DIR)/$(PARSING_DIR) $(OBJS_DIR)/$(TOOLS_DIR)
OBJS_DIRS = $(OBJS_DIR) $(OBJS_DIR)/$(MAIN_DIR) $(OBJS_DIR)/$(UTILS_DIR) $(OBJS_DIR)/$(EXEC_DIR) \
			 $(OBJS_DIR)/$(ENV_DIR) $(OBJS_DIR)/$(LEXER_DIR) $(OBJS_DIR)/$(PARSE_DIR) $(OBJS_DIR)/$(TRAVERSE_DIR) \
			 $(OBJS_DIR)/$(EXPAND) $(OBJS_DIR)/$(DOLLAR) $(OBJS_DIR)/$(GNL) $(OBJS_DIR)/$(DQUOTE) $(OBJS_DIR)/$(REDIR_DIR) \
			 $(OBJS_DIR)/$(EXECUTION_DIR)
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
