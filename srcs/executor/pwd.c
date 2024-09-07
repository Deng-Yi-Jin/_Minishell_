/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:05:55 by sinlee            #+#    #+#             */
/*   Updated: 2024/09/04 16:09:57 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	execute_pwd(void)
{
	char	*path;

	printf("Executing pwd...\n");
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror_color("pwd");
		return (false);
	}
	printf("%s\n", path);
	free(path);
	return (true);
}
