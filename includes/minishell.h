/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:06:06 by sinlee            #+#    #+#             */
/*   Updated: 2024/08/28 12:26:33 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "color.h"
# include "tokens.h"
# include "libft.h"
# include "parse.h"
# include "redir.h"
# include "execute.h"
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>

// int         g_num_env_vars;
// extern char **  environ;
# define PATH_MAX 4096
# define LOGIN_NAME_MAX 256
# define N_ARGS 2560
# define MAX_ENV_VARS 10240

// Structure to hold environment variables
typedef struct env_var_s
{
	char	*key;
	char	*value;
}	t_env_var;

typedef struct s_main
{
	int			nuclear_status; // exit status
	char		**envp;
	t_env_var	**env_vars;
}	t_main;

// extern t_env_var **g_env_vars;
extern t_main	*g_main;

char	*new_line(char *input, char c);
bool	is_bracket(char c);
char	*error_bracket(char	**split, int word);

char		*dquote(char *input);

void		perror_color(char *str);
void		error_exit(char *str, bool is_perror);
void		exit_success(void);

char		*prompt_msg(char prompt[LOGIN_NAME_MAX + PATH_MAX + 20]);

void		init(char **envp);
void		init_signals(void);

int			execute_builtin(char *inpt, char *args[N_ARGS], char **envp);
void		ft_free_path_env(char **path_env);
char		*get_path(char *cmd, char **envp);
char		*find_command_path(char *command, char **envp);
int			is_command(char *cmd, char **envp);
void		parse_input(char *input, char **envp);

void		init_new_env_var(t_env_var **new_env_vars, int num_env_vars, char *key,
			char *value);

void		add_env_vars(char *key, char *value);
void		modify_env_vars(char *key, char *value);
void		delete_env_vars(char *key);
t_env_var	*find_env_vars(char *key);
int			find_env(char *key, char **envp);
char		*ft_getenv(char *key);
void		free_env_vars(void);
bool		flip_bool_env_vars(char *key);
// bool    print_env_vars();

bool		execute_echo(char **args, char **flags);

t_env_var	**dup_darr(char **arr);
void		free_darr(t_env_var **arr);
void		free_jutsu(bool darr, char *key, char *value);

bool		execute_cd(char *args[N_ARGS], char **envp);
bool		echo(char **args, char **flags);
bool		execute_export(char **args);
bool		welcome_msg(void);

int			ft_snprintf(char *str, size_t size, const char *format, ...);
char		*ft_strtok(char *str, const char *delim);
void		*ft_malloc(size_t size);

/* NEW UTILS ADDED FOR EXPANSION */

char	*ft_strfjoin(char *s1, char *s2);

// Token linked listfunctions
t_token		*lst_first_last(t_token *tokens, bool is_last);
void		token_lstadd_back(t_token **lst, t_token *new);
t_token		*add_tokens(t_token *tokens, char *cmd, int type);
t_token		*create_token(char *cmd, int type);
void		free_stack(t_token **tokens,
				void (*del)(void *), bool loop, char *input);
// void		del(void *content);
void		print_stack(t_token *tokens);
void		free_split(char **str);
t_token		*lst_go_back(t_token *tokens);
t_token		*add_null_token(t_token *tokens);

//GetNextLine
char		*get_next_line(int fd);

// expand dollar
char		*expand_dollar(char *input);

// Lexer utils
void		lexing(char *input, t_token **tokens, int *i, int *count_words);
bool		ft_bracket(char input);
void		start_lex(char *input, t_token **tokens);
bool		ft_symbol(char input);
int			ft_return_op(char input);
void		ft_redir(char *input, int *i, t_token **tokens);
void		ft_pipe(char *input, int *i, t_token **tokens);
void		quoting(char *str, int *i, int *count_words, char c);
void		quotation(char *input, int *i, int *count_words, char c);
void		dollar(char *input, int *i, int *count_words);

void		print_token(t_token *tokens, bool to_first, char *str);

void		test_traverse(void);


#endif