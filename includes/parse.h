/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:33:03 by djin              #+#    #+#             */
/*   Updated: 2024/03/08 22:17:53 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# define N_ARGS 2560

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

typedef struct	count
{
	int		i;
	int		j;
	int		count_words;
	int		strlen;
}	t_count;


void	parse(t_token **tokens, char **envp);
t_ast	*create_ast_node(char *cmd, int type);
t_ast	*create_parent_node(char *cmd);
void	print_ast(t_ast *ast);
void	print_ast_all(t_ast **ast);
bool	traverse(t_ast **ast, void (*f)(void *), int depth, bool print);

//dollar deal
void	dollar_deal(t_ast *ast, bool create_sibling);
char	*init_dollar(t_ast *ast);
void	build_dollar(char *strtrim, t_ast *ast, bool create_sibling);

//ast contruct
void	start_parse(t_ast **ast, t_token **tokens);
void	construct_child_after_pipe(t_ast **ast, char *tmp, bool *is_child);
void	construct_child_before_pipe(t_ast **ast, char *tmp, bool *is_child);
void	eldest_child(t_ast **ast, t_token **tokens, bool *create_sibling);
void	sibling(t_ast **ast, t_token **tokens, bool *create_sibling);
void	construct_sibling(t_ast **ast, t_token **tokens, bool *create_sibling);
void	form_ast(t_ast **ast, t_token **tokens);

#endif