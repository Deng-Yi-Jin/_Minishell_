/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:24:01 by geibo             #+#    #+#             */
/*   Updated: 2024/09/16 09:31:41 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "minishell.h"
# include "execute.h"

bool	is_redir(char *cmd);
bool	is_redir_in(char *cmd);
bool	is_redir_out(char *cmd);
bool	is_redir_append(char *cmd);
void	redirect(t_exec *exec, int *infilefd, int *outfilefd);
int		return_after_redir(t_exec *exec, int i);

#endif