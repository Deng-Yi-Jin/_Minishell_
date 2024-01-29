/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:28:59 by root              #+#    #+#             */
/*   Updated: 2023/10/01 16:15:490 by root             ###   ########.fr       */
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

void	parse(t_token **tokens, char **envp);
t_ast	*create_ast_node(char *cmd, int type);
t_ast	*create_parent_node(char *cmd);
void	print_ast(t_ast *ast);
void 	print_ast_all(t_ast **ast);
void	dollar_deal(t_ast *ast, bool create_sibling);
bool 	traverse(t_ast **ast, void (*f)(void *), int depth, bool print);


#endif