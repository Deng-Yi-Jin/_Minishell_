/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:28:31 by geibo             #+#    #+#             */
/*   Updated: 2024/05/29 10:29:30 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_fd(int savedfd[2])
{
	savedfd[0] = dup(STDIN_FILENO);
	savedfd[1] = dup(STDOUT_FILENO);
}

void	restore_fd(int savedfd[2])
{
	dup2(savedfd[0], STDIN_FILENO);
	close(savedfd[0]);
	dup2(savedfd[1], STDOUT_FILENO);
	close(savedfd[1]);
}
