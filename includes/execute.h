/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:54:15 by codespace         #+#    #+#             */
/*   Updated: 2024/01/30 18:52:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

typedef struct s_exec
{
	char	**cmd;
	struct s_exec *next;
	struct s_exec *prev;
	pid_t	pid;
	int		fd[2];
	int		infile;
	int		outfile;
} t_exec;

t_exec	*create_exec_node(char **cmd);
t_exec *join_exec_nodes(t_exec *exec, char **cmd);
t_exec	*executing(t_ast **ast, t_exec *exec);
void	execute_single_cmd(t_exec *exec, char **envp);
void	free_exec(t_exec *exec);
void	print_exec(t_exec *exec);
void	execute(t_exec *exec, char **envp);
void	execute_cmd(char **cmd, char **envp);

#endif