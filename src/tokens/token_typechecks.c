/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_typechecks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:33:09 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/16 15:56:52 by jcummins         ###   ########.fr       */
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
	if (!ft_strncmp(str, "$", 1) && str[1])
		ismeta = DOLLAR;
	else if (!ft_strncmp(str, "'", 1))
		ismeta = SQUOTE;
	else if (!ft_strncmp(str, "\"", 1))
		ismeta = DQUOTE;
	else if (!ft_strncmp(str, "=", 1))
		ismeta = ASS;
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

	isbuiltin = C_NONE;
	if (!ft_strncmp(str, "echo\0", 5))
		isbuiltin = C_ECHO;
	else if (!ft_strncmp(str, "cd\0", 3))
		isbuiltin = C_CD;
	else if (!ft_strncmp(str, "pwd\0", 4))
		isbuiltin = C_PWD;
	else if (!ft_strncmp(str, "export\0", 7))
		isbuiltin = C_EXPORT;
	else if (!ft_strncmp(str, "unset\0", 6))
		isbuiltin = C_UNSET;
	else if (!ft_strncmp(str, "env\0", 4))
		isbuiltin = C_ENV;
	else if (!ft_strncmp(str, "exit\0", 5))
		isbuiltin = C_EXIT;
	else if (is_assign(str))
		isbuiltin = C_ASSIGN;
	return (isbuiltin);
}
