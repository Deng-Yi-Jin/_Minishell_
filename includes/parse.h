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

# include "minishell.h"

typedef struct s_ast
{
	char			*cmd;
	char			*value;
	struct s_ast	*next_sibling;
	struct s_ast	*prev_sibling;
	t_token			**token;
	int				type;
	struct s_ast	*right;
	struct s_ast	*prev;
	struct s_ast	*next;
	struct s_ast	*parent;
}	t_ast;

void	parse(t_token **tokens);
char	*ast_strjoin(t_token **tokens, char *str);
t_ast	*add_ast(t_ast	*ast, char *cmd);
t_ast	*create_ast_node(char *cmd);
t_ast	*ast_first_last(t_ast *ast, bool is_last);
void	free_ast(t_ast **ast);
void	print_ast(t_ast *ast);
void print_ast_all(t_ast **ast);

#endif