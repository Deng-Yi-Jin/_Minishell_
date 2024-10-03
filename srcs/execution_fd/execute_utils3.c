/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:01:41 by kytan             #+#    #+#             */
/*   Updated: 2024/10/03 23:59:57 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	total_command(t_exec *exec, int count)
{
	t_exec	*temp;

	temp = exec;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->cmd[0], "") == 0)
			break ;
		count++;
		temp = temp->next;
	}
	return (count);
}

void	check_match_cmd(t_exec *exec, char **envp, int *i)
{
	exit(execute_builtin(exec->cmd_list[*i], exec->cmd_list, envp));
}

bool	check_command(char *inpt, char *args[N_ARGS], char **envp)
{
	if (!ft_strcmp(inpt, "exit"))
		return (true);
	else if (!ft_strcmp(inpt, "cd"))
		return (true);
	else if (!ft_strcmp(inpt, "fancy"))
		return (true);
	else if (!ft_strcmp(inpt, "quotes"))
		return (true);
	else if (ft_strcmp(inpt, "export") == 0)
		return (true);
	else if (ft_strcmp(inpt, "echo") == 0)
		return (true);
	else if (ft_strcmp(inpt, "pwd") == 0)
		return (true);
	else if (ft_strcmp(inpt, "env") == 0)
		return (true);
	else if (ft_strcmp(inpt, "unset") == 0)
		return (true);
	return (false);
}

void	free_redir_list(t_exec *exec)
{
	int	i;

	i = 0;
	if (exec->redir_list != NULL)
	{
		while (exec->redir_list[i] != NULL)
		{
			free(exec->redir_list[i]);
			i++;
		}
		free(exec->redir_list);
	}
}

bool	get_redirfd(t_exec *exec, int *infilefd, int *outfilefd, char **envp)
{
	redirect(exec, infilefd, outfilefd);
	*infilefd = get_infilefd(exec->redir_list);
	if (*infilefd == -1)
	{
		free_redir_list(exec);
		return (false);
	}
	*outfilefd = get_outfilefd(exec->redir_list);
	if (*outfilefd == -1)
	{
		free_redir_list(exec);
		return (false);
	}
	free_redir_list(exec);
	return (true);
}
