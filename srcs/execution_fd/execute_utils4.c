/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:26:10 by geibo             #+#    #+#             */
/*   Updated: 2024/09/16 13:56:42 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_infilefd(char **redir_list)
{
	char	*file_name;
	int		infilefd;
	int		i;

	infilefd = 0;
	i = 0;
	if (redir_list == NULL)
		return (infilefd);
	while (redir_list[i])
	{
		if (is_redir_in(redir_list[i]) || ft_strcmp(redir_list[i], "<<") == 0)
		{
			if (infilefd != 0)
				close(infilefd);
			file_name = redir_list[i + 1];
			infilefd = open(file_name, O_RDONLY, 0644);
			if (infilefd == -1)
			{
				printf("%s: No such file or directory\n", file_name);
				break ;
			}
		}
		i++;
	}
	return (infilefd);
}

int	get_outfilefd(char **redir_list)
{
	char	*file_name;
	int		out_fd;
	int		i;

	out_fd = 0;
	i = -1;
	if (redir_list == NULL)
		return (out_fd);
	while (redir_list[++i])
	{
		if (is_redir_out(redir_list[i]) || is_redir_append(redir_list[i]))
		{
			file_name = redir_list[i + 1];
			if (is_redir_out(redir_list[i]))
				out_fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (is_redir_append(redir_list[i]))
				out_fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		}
		if (out_fd == -1)
		{
			printf("%s: No such file or directory\n", file_name);
			break ;
		}
	}
	return (out_fd);
}
