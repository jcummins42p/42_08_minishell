/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envinit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:53:00 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/20 17:53:16 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_init_param(char **param, char *envline)
{
	char	*out;
	int		i;
	int		len;

	i = 0;
	while (envline[i] && envline[i] != '=')
		i++;
	len = i;
	out = malloc(sizeof(char) * (len + 1));
	out[i--] = '\0';
	while (i >= 0)
	{
		out[i] = envline[i];
		i--;
	}
	*param = out;
	return (len);
}

static int	env_init_value(char **value, char *envline, int start)
{
	char	*out;
	int		len;
	int		i;

	len = 0;
	start++;
	i = start;
	while (envline[i++])
		len++;
	out = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
		out[i++] = envline[start++];
	out[i] = '\0';
	*value = out;
	return (len);
}

void	env_init(t_envlist **envlist, char *env[])
{
	int		i;
	int		len;
	char	*param;
	char	*value;

	i = 0;
	param = NULL;
	value = NULL;
	while (env[i])
	{
		len = env_init_param(&param, env[i]);
		env_init_value(&value, env[i], len);
		env_new(envlist, param, value);
		i++;
	}
	env_set(envlist, "SHELL", "/bin/minishell");
}
