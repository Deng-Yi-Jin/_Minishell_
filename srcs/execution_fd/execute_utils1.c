/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:28:31 by geibo             #+#    #+#             */
/*   Updated: 2024/09/15 17:41:40 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_origio(int origio[])
{
	origio[0] = dup(STDIN_FILENO);
	origio[1] = dup(STDOUT_FILENO);
}

void	restore_fd(int origstdin, int origstdout)
{
	dup2(origstdin, STDIN_FILENO);
	// close(origstdin);
	dup2(origstdout, STDOUT_FILENO);
	// close(origstdout);
}
