/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:26:10 by geibo             #+#    #+#             */
/*   Updated: 2024/09/15 18:05:15 by geibo            ###   ########.fr       */
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
			// printf("file_name: %s\n", file_name);
			infilefd = open(file_name, O_RDONLY, 0644);
			if (infilefd == -1)
			{
				printf("%s: No such file or directory\n", file_name);
				break;
			}
		}
		i++;
	}
	return (infilefd);
}

int	get_outfilefd(char **redir_list)
{
	char	*file_name;
	int		outfilefd;
	int		i;

	outfilefd = 0;
	i = 0;
	if (redir_list == NULL)
		return (outfilefd);
	while (redir_list[i])
	{
		if (is_redir_out(redir_list[i]) || is_redir_append(redir_list[i]))
		{
			file_name = redir_list[i + 1];
			if (is_redir_out(redir_list[i]))
				outfilefd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (is_redir_append(redir_list[i]))
				outfilefd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		}
		if (outfilefd == -1)
		{
			printf("%s: No such file or directory\n", file_name);
			break;
		}
		i++;
	}
	return (outfilefd);
}

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	while (s1[i] && s2[i] && s1[i] == s2[i])
// 		i++;
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }
