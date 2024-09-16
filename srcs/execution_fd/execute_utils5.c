/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:34:10 by geibo             #+#    #+#             */
/*   Updated: 2024/09/16 15:37:35 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_file_descriptor(int *fd, int (*get_fd_func)(char **),
		t_exec *exec)
{
	*fd = get_fd_func(exec->redir_list);
	if (*fd == -1)
	{
		free_redir_list(exec);
		return (false);
	}
	return (true);
}
