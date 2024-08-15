/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:08:05 by codespace         #+#    #+#             */
/*   Updated: 2024/08/14 19:04:04 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_exec *exec, char **envp, char *command_path)
{
	int	i;
	int	infilefd;
	int	outfilefd;
	int	origstdin;
	int	origstdout;

	i = 0;
	redirect_in(exec, &infilefd, &outfilefd);
	origstdin = dup(STDIN_FILENO);
	origstdout = dup(STDOUT_FILENO);
	i = return_after_redir(exec, i);
	if (create_fork() == 0)
	{
		manage_pipe_child(exec, infilefd, outfilefd);
		run_cmd(envp, exec, command_path, &i);
	}
	else
		manage_pipe_parent(exec);
	if (exec->infile != 0)
		close(exec->infile);
	restore_fd(origstdin, origstdout);
}

void	execute_last_cmd(t_exec *exec, char **envp, char *command_path)
{
	int	i;
	int	origio[2];
	int	infile;
	int	outfile;

	i = 0;
	redirect_in(exec, &infile, &outfile);
	init_origio(origio);
	manage_lastcmdredir(exec, infile, outfile);
	if (match_cmd(exec->cmd[i], exec->cmd, envp) && exec->prev == NULL)
		check_match_cmd(exec, envp, &i);
	else
	{
		if (create_fork() == 0)
		{
			handle_lastcmd_child(exec, infile);
			run_cmd(envp, exec, command_path, &i);
			exit(126);
		}
		handle_lastcmd_parent(exec);
	}
	restore_fd(origio[0], origio[1]);
}

void	start_command_exec(char *command_path, char **envp,
		t_exec *exec, int saved_stdin)
{
	t_exec	*current_node;

	current_node = exec;
	while (current_node)
	{
		if (!last_cmd(current_node))
		{
			if (pipe(current_node->fd) == -1)
				exit(-1);
			execution(current_node, envp, command_path);
		}
		else
		{
			if (current_node->type[0] == HERE_DOC)
				return ;
			execute_last_cmd(current_node, envp, command_path);
		}
		current_node = current_node->next;
	}
	while (wait(NULL) > 0)
		;
}

void	execute(t_exec *exec, char **envp)
{
	char	*command_path;
	int		saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	start_command_exec(command_path, envp, exec, saved_stdin);
}

/* KYLIE TINKERED WITH 6:53PM 8/14/2024

split execute_last_cmd(): added check_match_cmd()
created : total_command(), check_match_cmd()*/
/*
void	execute_last_cmd(t_exec *exec, char **envp, char *command_path)
{
	int	i;
	int	origio[2];
	int	infile;
	int	outfile;

	i = 0;
	redirect_in(exec, &infile, &outfile);
	init_origio(origio);
	manage_lastcmdredir(exec, infile, outfile);
	if (match_cmd(exec->cmd[i], exec->cmd, envp) && exec->prev == NULL)
	{
		if (!match_cmd(exec->cmd[i], exec->cmd, envp))
		{
			printf("minishell: %s: command not found\n", exec->cmd[i]);
			exit(127);
		}
	}
	else
	{
		if (create_fork() == 0)
		{
			handle_lastcmd_child(exec, infile);
			run_cmd(envp, exec, command_path, &i);
			exit(126);
		}
		handle_lastcmd_parent(exec);
	}
	restore_fd(origio[0], origio[1]);
}
*/