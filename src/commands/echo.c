/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:07:17 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/29 13:45:32 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wordlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && !is_whitespace(str[i]) && str[i] != '$')
	   i++;
	return (i);
}

char *echo_get_var(char *str)
{
	char	*out;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	len = ft_wordlen(str);
	out = malloc(sizeof(char) * (len + 1));
	i = -1;
	while (++i < len)
		out[i] = str[i];
	out[i] = '\0';
	return (out);
}

//	needs to print the value stored at $VAR but return the length of the param
int	expand_var(t_mshell *msh, char *str, int fd)
{
	char		*param;
	char		**value;
	int			len;
	int			i;

	i = 0;
	param = echo_get_var(str);
	len = ft_strlen(param);
	value = env_get_value(&msh->envlist, param);
	free(param);
	if (value)
	{
		while ((*value)[i])
			write(fd, &(*value)[i++], 1);
	}
	return (len + 1);
}

void	echo_expand_str(t_mshell *msh, char *str, int fd)
{
	int	i;
	int	var;

	i = 0;
	var = 0;
	(void)msh;
	while (str[i])
	{
		while (str[i] && is_whitespace(str[i]))
				i++;
		if (str[i] == '$')
			i += expand_var(msh, &str[i + 1], fd);
		else
		{
			if (str[i] && is_whitespace(str[i]))
				write(fd, " ", 1);
			else
				if (str[i])
					write(fd, &str[i++], 1);
		}
	}
	write(fd, "\n", 1);
}
