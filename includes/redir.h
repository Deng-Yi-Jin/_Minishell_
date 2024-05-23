/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:24:01 by geibo             #+#    #+#             */
/*   Updated: 2024/05/23 13:12:26 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "minishell.h"
# include "execute.h"

bool	is_redir(char *cmd);
bool	open_outfile(t_exec *exec, char *file);
bool	open_infile(t_exec *exec, char *file);
bool	redirect(char *file, char *cmd, t_exec *exec);

#endif