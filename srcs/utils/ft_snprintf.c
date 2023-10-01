/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinlee <sinlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 03:41:35 by codespace         #+#    #+#             */
/*   Updated: 2023/08/19 22:39:01 by sinlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdarg.h>
#include <stddef.h>

static void	ft_snprintf_str(va_list *args, char *str, size_t attr[2])
{
	char	*value;
	char	*s;
	size_t	value_length;
	size_t	s_length;

	s = va_arg(*args, char *);
	s_length = ft_strlen(s);
	if (s_length > attr[1])
		s_length = attr[1];
	ft_strlcpy(str + attr[0], s, s_length + 1);
	attr[0] += s_length;
	attr[1] -= s_length;
}

static void	ft_snprintf_int(va_list *args, char *str, size_t attr[2])
{
	char	*value;
	size_t	value_length;
	char	value_str[12];

	value = ft_itoa(va_arg(*args, int));
	ft_strlcpy(value_str, value, sizeof(value_str));
	value_length = ft_strlen(value_str);
	if (value_length > attr[1])
		value_length = attr[1];
	ft_strlcat(str + attr[0], value_str, sizeof(str));
	attr[0] += value_length;
	attr[1] -= value_length;
	free(value);
}

// attr[0]: written, char attr[1]: remaining
static void	ft_snprintf_check(char format, va_list *args, char *str,
		size_t attr[2])
{
	if (format == 'd')
		ft_snprintf_int(args, str, attr);
	else if (format == 's')
		ft_snprintf_str(args, str, attr);
	else
	{
		if (attr[1] >= 2)
		{
			str[attr[0]++] = '%';
			str[attr[0]++] = format;
			attr[1] -= 2;
		}
	}
}

// attr[0]: written, char attr[1]: remaining
int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list	args;
	size_t	attr[2];
	char	value_str[12];

	va_start(args, format);
	attr[0] = 0;
	attr[1] = size - 1;
	while (*format != '\0' && attr[1] > 0)
	{
		if (*format == '%')
		{
			format++;
			ft_snprintf_check(*format, &args, str, attr);
		}
		else
		{
			str[attr[0]++] = *format;
			attr[1]--;
		}
		format++;
	}
	str[attr[0]] = '\0';
	va_end(args);
	return (attr[0]);
}
