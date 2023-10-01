/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checksymb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djin <djin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 14:03:36 by djin              #+#    #+#             */
/*   Updated: 2023/09/03 17:00:15 by djin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_checksymb(char c)
{
	if (c == '!')
		return (EXCLAMATION);
	if (c == '@')
		return (AT);
	if (c == '#')
		return (HASH);
	if (c == '%')
		return (PERCENT);
	if (c == '^')
		return (CIRCUMFLEX);
	if (c == '*')
		return (ASTERISK);
	if (c == '-')
		return (MINUS);
	if (c == '_')
		return (UNDERSCORE);
	if (c == '=')
		return (EQUAL);
	if (c == '+')
		return (PLUS);
	if (c == ':')
		return (COLON);
	if (c == '?')
		return (QUESTION);
	if (c == '.')
		return (DOT);
	if (c == ',')
		return (COMMA);
	if (c == '$')
		return (DOLLAR);
	if (c == '/')
		return (SLASH);
	if (c == '\"')
		return (DOMESTIC_EXPANSION);
	if (c == '\'')
		return (BOO_NO_EXPANSION);
	return (0);
}
