/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinlee <sinlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:05:55 by sinlee            #+#    #+#             */
/*   Updated: 2024/04/01 18:05:56 by sinlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool execute_pwd()
{
	char *path;

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