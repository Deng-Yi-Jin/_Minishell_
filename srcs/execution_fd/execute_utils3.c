/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:01:41 by kytan             #+#    #+#             */
/*   Updated: 2024/09/07 05:57:56 by kytan            ###   ########.fr       */
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
	exit(execute_builtin(exec->cmd[*i], exec->cmd, envp));
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
