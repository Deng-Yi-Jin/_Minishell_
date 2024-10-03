/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:08:05 by codespace         #+#    #+#             */
/*   Updated: 2024/10/03 23:32:22 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	execution(t_exec *exec, char **envp, char *command_path)
{
	int	i;
	int	infilefd;
	int	outfilefd;
	int	origstdin;
	int	origstdout;

	i = 0;
	if (get_redirfd(exec, &infilefd, &outfilefd, envp) == false)
		return (false);
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
	if (exec->outfile != 0)
		close(exec->outfile);
	restore_fd(origstdin, origstdout);
	return (true);
}

static void	fork_and_execute(t_exec *exec, char **envp, char *command_path,
		int infile)
{
	int	i;

	i = 0;
	if (create_fork() == 0)
	{
		handle_lastcmd_child(exec, infile);
		run_cmd(envp, exec, command_path, &i);
		exit(126);
	}
	handle_lastcmd_parent(exec);
}

bool	execute_last_cmd(t_exec *exec, char **envp, char *command_path)
{
	int	i;
	int	origio[2];
	int	infile;
	int	outfile;

	i = 0;
	if (get_redirfd(exec, &infile, &outfile, envp) == false)
		return (false);
	init_origio(origio);
	manage_lastcmdredir(exec, infile, outfile);
	if (!exec->cmd_list)
	{
		restore_fd(origio[0], origio[1]);
		return (true);
	}
	if (check_command(exec->cmd_list[i], exec->cmd_list, envp)
		&& exec->prev == NULL)
		g_main->nuclear_status = execute_builtin(exec->cmd_list[i],
				exec->cmd_list, envp);
	else
		fork_and_execute(exec, envp, command_path, infile);
	restore_fd(origio[0], origio[1]);
	return (true);
}

static void	wait_for_children(void)
{
	int	status;

	while (wait(&status) > 0)
	{
		if (WEXITSTATUS(status))
			g_main->nuclear_status = WEXITSTATUS(status);
	}
}

void	start_command_exec(char *command_path, char **envp, t_exec *exec,
		int saved_stdin)
{
	t_exec	*current_node;

	current_node = exec;
	while (current_node)
	{
		if (!last_cmd(current_node))
		{
			if (pipe(current_node->fd) == -1)
				exit(-1);
			if (execution(current_node, envp, command_path) == false)
				break ;
		}
		else
		{
			if (execute_last_cmd(current_node, envp, command_path) == false)
				break ;
		}
		current_node = current_node->next;
	}
	wait_for_children();
}
