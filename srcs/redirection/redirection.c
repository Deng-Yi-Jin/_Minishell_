/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:17:49 by geibo             #+#    #+#             */
/*   Updated: 2024/05/29 08:45:07 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_in(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->cmd[i] != NULL)
	{
		if (is_redir_in(exec->cmd[i]))
		{
			i++;
			exec->fd[0] = open(exec->cmd[i], O_RDONLY);
			dup2(exec->fd[0], STDIN_FILENO);
			close(exec->fd[0]);
			i++;
		}
		else
			break;
	}
}

int	return_after_redir(t_exec *exec, int i)
{
	while (exec->cmd[i] != NULL)
	{
		if (is_redir_in(exec->cmd[i]))
			i += 2;
		else
			break;
	}
	return (i);
}
