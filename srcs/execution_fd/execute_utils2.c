/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:59:26 by geibo             #+#    #+#             */
/*   Updated: 2024/05/29 15:11:37 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_lastcmd_child(t_exec *exec, int infilefd)
{
	if (exec->prev && exec->prev->fd[0] != 0)
	{
		close(exec->prev->fd[1]);
		if (infilefd == 0)
			dup2(exec->prev->fd[0], STDIN_FILENO);
		close(exec->prev->fd[0]);
	}
}

void	handle_lastcmd_parent(t_exec *exec)
{
	if (exec->prev && exec->prev->fd[0] != 0)
	{
		close(exec->prev->fd[0]);
		close(exec->prev->fd[1]);
	}
}
