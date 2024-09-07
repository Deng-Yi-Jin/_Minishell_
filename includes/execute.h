/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:54:15 by codespace         #+#    #+#             */
/*   Updated: 2024/09/07 06:01:45 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

# include <stddef.h>
typedef struct s_exec
{
	char			**cmd;

	struct	s_exec	*next;
	struct	s_exec	*prev;
	pid_t			pid;
	int				*type;
	int				fd[2];
	int				infile;
	int				outfile;
}	t_exec;

t_exec	*create_exec_node(char **cmd, int *type);
bool	add_cmd_to_db_lst(t_ast **ast, t_exec *exec, int depth);
t_exec	*join_exec_nodes(t_exec *exec, char **cmd, int *type);
t_exec	*executing(t_ast **ast, t_exec *exec);
void	exec_pipe(t_exec *exec, char **envp, char *command_path);
void	execution(t_exec *exec, char **envp, char *command_path);
void	free_exec(t_exec *exec);
void	print_exec(t_exec *exec);

int		total_command(t_exec *exec, int count);
void	check_match_cmd(t_exec *exec, char **envp, int *i);

void	execute(t_exec *exec, char **envp);
bool	last_cmd(t_exec *exec);
void	manage_pipe_child(t_exec *exec, int infile_fd, int outfile_fd);
void	manage_pipe_parent(t_exec *exec);
char	**is_flags(char **str);
void	manage_lastcmdredir(t_exec *exec, int infile_fd, int outfile_fd);
void	restore_fd(int origstdin, int origstdout);
void	init_origio(int origio[]);
void	handle_lastcmd_child(t_exec *exec, int infilefd);
void	handle_lastcmd_parent(t_exec *exec);
void	run_cmd(char **envp, t_exec *exec, char *command_path, int *i);
pid_t	create_fork(void);
t_exec	*renamed_here_doc(t_exec *exec, char **envp);
int		ft_sstrlen(char **str);

void	set_exec_type(t_exec *exec, char **envp);
bool	check_command(char *inpt, char *args[N_ARGS], char **envp);

/* ENV_EXPANSION() */

char	*env_expansion(char **split, char q);
int		no_expansion_needed(char *s);

char	*dollar_q_expansion(char *s);

size_t	expanded_len(char *s, char q);
void	cp_to_output(char *dst, char *src, char q);
char	*extract_env(char *s);

char	ft_quote(char *s);
char	*ft_strldup(char *src, ptrdiff_t size);
bool	execute_pwd(void);

bool  execute_env(char **args);
bool	execute_unset(char **args);

#endif