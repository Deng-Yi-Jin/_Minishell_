/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:56:56 by sinlee            #+#    #+#             */
/*   Updated: 2024/04/30 08:30:19 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool execute_echo(char **args, char **flags)
{
    int i = 0;
    bool trailing = false;
    
    while (flags[i] != NULL)
    {
        if (ft_strcmp(flags[i], "-n") == 0)
            trailing = true;
        else if (ft_strcmp(flags[i], "--help") == 0)
            printf("Usage: echo [SHORT-OPTION]... [STRING]...\n  or:  echo LONG-OPTION\n\nEcho the STRING(s) to standard output.\n\n  -n             do not output the trailing newline\n  -e             enable interpretation of backslash escapes\n  -E             disable interpretation of backslash escapes (default)\n      --help     display this help and exit\n      --version  output version information and exit\n\nIf -e is in effect, the following sequences are recognized:\n\n  \\\\      backslash\n  \\a      alert (BEL)\n  \\b      backspace\n  \\c      produce no further output\n  \\e      escape\n  \\f      form feed\n  \\n      new line\n  \\r      carriage return\n  \\t      horizontal tab\n  \\v      vertical tab\n");
        else {
            printf("echo: invalid option -- '%s'\n", flags[i]);
            printf("Try 'echo --help' for more information.\n");
            return false;
        }
        i++;
    }
    i = 0;
    while (args[i] != NULL) {
        printf("%s ", args[i]);
        i++;
    }
    if (trailing == true)
        printf("\n");
    return true;
}