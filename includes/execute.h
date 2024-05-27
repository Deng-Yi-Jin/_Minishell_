/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:54:15 by codespace         #+#    #+#             */
/*   Updated: 2024/05/27 16:38:05 by geibo            ###   ########.fr       */
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
bool	add_cmd_to_db_lst(t_ast **ast, t_exec *exec, int depth);
t_exec	*join_exec_nodes(t_exec *exec, char **cmd);
t_exec	*executing(t_ast **ast, t_exec *exec);
void	exec_pipe(t_exec *exec, char **envp, char *command_path);
void	execution(t_exec *exec, char **envp, char *command_path);
void	free_exec(t_exec *exec);
void	print_exec(t_exec *exec);
void	execute(t_exec *exec, char **envp);
pid_t	create_fork(void);
bool	last_cmd(t_exec *exec);
void	manage_pipe_child(t_exec *exec);
void	manage_pipe_parent(t_exec *exec);
char	**is_flags(char **str);

#endif