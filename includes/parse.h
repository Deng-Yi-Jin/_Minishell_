/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:33:03 by djin              #+#    #+#             */
/*   Updated: 2024/09/10 13:36:34 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# define N_ARGS 2560
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include "minishell.h"

typedef struct s_ast
{
	char			*cmd;
	int				type;
	int				fd[2];
	struct s_ast	*child;
	struct s_ast	*prev;
	struct s_ast	*next;
	struct s_ast	*parent;
}	t_ast;

typedef struct s_execute
{
	int		fd[2];
	pid_t	pid;
}	t_execute;

typedef struct count
{
	size_t		i;
	int			j;
	int			count_words;
	int			strlen;
}	t_count;

void	parse(t_token **tokens, char **envp);
t_ast	*create_ast_node(char *cmd, int type);
t_ast	*create_parent_node(char *cmd);
void	print_ast(t_ast *ast);
void	print_ast_all(t_ast **ast);
bool	traverse(t_ast **ast, void (*f)(void *), int depth, bool print);
char	*executing_cmd(char **cmd, char **envp);
char	*execute_dollar_expansion(t_ast *ast, char **envp);
bool	execute_dollar(t_ast **ast, int depth, char **envp);
int		ast_len(t_ast *ast);
char	*add_cmd(t_ast *current_node, char **envp);

char	*execute_parent_process(t_execute *execute);
char	*handle_fork(t_execute *execute, char *command_path,
		char **cmd, char **envp);
void	dollar_deal(t_ast *ast, bool create_sibling, char **envp);
char	*init_dollar(t_ast *ast);
void	build_dollar(char *strtrim, t_ast *ast,
			bool create_sibling, char **envp);
char	*execute_dollar_expansion(t_ast *ast, char **envp);

//ast contruct
void	start_parse(t_ast **ast, t_token **tokens, char **envp);
void	construct_child_after_pipe(t_ast **ast, char *tmp, bool *is_child);
void	construct_child_before_pipe(t_ast **ast, char *tmp, bool *is_child);
void	eldest_child(t_ast **ast, t_token **tokens,
			bool *create_sibling, char **envp);
void	sibling(t_ast **ast, t_token **tokens,
			bool *create_sibling, char **envp);
void	construct_sibling(t_ast **ast, t_token **tokens,
			bool *create_sibling, char **envp);
void	form_ast(t_ast **ast, t_token **tokens, char **envp);

//rm quote
char	*unquote_str(char *str, char c);

char	*rm_quote(char *str);

#endif