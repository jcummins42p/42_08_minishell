/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:33:09 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/01 16:12:18 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_assign(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && !is_whitespace(str[i]))
	{
		if (str[i] == '=')
			return (i);
		else
			i++;
	}
	return (0);
}

int	is_metachar(char *str)
{
	t_mtctype	ismeta;

	ismeta = NO_MTC;
	if (!ft_strncmp(str, "$", 1))
		ismeta = DOLLAR;
	else if (!ft_strncmp(str, "'", 1))
		ismeta = SQUOTE;
	else if (!ft_strncmp(str, "\"", 1))
		ismeta = DQUOTE;
	else if (!ft_strncmp(str, "|", 1))
		ismeta = PIPE;
	else if (!ft_strncmp(str, ">>", 2))
		ismeta = RDAPP;
	else if (!ft_strncmp(str, "<<", 2))
		ismeta = DELIMIT;
	else if (!ft_strncmp(str, ">", 1))
		ismeta = RDOUT;
	else if (!ft_strncmp(str, "<", 1))
		ismeta = RDIN;
	return (ismeta);
}

int	is_builtin(char *str)
{
	t_comtype	isbuiltin;

	isbuiltin = NO_COM;
	if (!ft_strncmp(str, "echo", 4))
		isbuiltin = ECHO;
	else if (!ft_strncmp(str, "cd", 2))
		isbuiltin = CD;
	else if (!ft_strncmp(str, "pwd", 3))
		isbuiltin = PWD;
	else if (!ft_strncmp(str, "export", 6))
		isbuiltin = EXPORT;
	else if (!ft_strncmp(str, "unset", 5))
		isbuiltin = UNSET;
	else if (!ft_strncmp(str, "env", 3))
		isbuiltin = ENV;
	else if (!ft_strncmp(str, "exit", 4))
		isbuiltin = EXIT;
	else if (is_assign(str))
		isbuiltin = ASSIGN;
	return (isbuiltin);
}
