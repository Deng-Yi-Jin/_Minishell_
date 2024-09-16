/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:28:31 by geibo             #+#    #+#             */
/*   Updated: 2024/09/16 11:26:40 by kytan            ###   ########.fr       */
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
	dup2(origstdout, STDOUT_FILENO);
}
