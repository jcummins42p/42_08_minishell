/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:53:00 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/01 13:10:31 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	initialises and assigns value to a node in env linked list
static int	env_init_value(char **value, char *envline, int start)
{
	int		len;
	int		i;

	len = 0;
	start++;
	i = start;
	while (envline[i++])
		len++;
	*value = malloc(sizeof(char) * (len + 1));
	if (*value == NULL)
		return (-1);
	i = 0;
	while (i < len)
		(*value)[i++] = envline[start++];
	(*value)[i] = '\0';
	return (len);
}

//	initialises and assigns parameter to a node in env linked list. Returns
//	length of that string so that the init value function can start at the
//	correct place in that line to retreive the following value
static int	env_init_param(char **param, char *envline)
{
	int		i;
	int		len;

	i = 0;
	while (envline[i] && envline[i] != '=')
		i++;
	len = i;
	*param = malloc(sizeof(char) * (len + 1));
	(*param)[i--] = '\0';
	while (i >= 0)
	{
		(*param)[i] = envline[i];
		i--;
	}
	return (len);
}

//	creates new node of env linked list. Parameter and value have already been
//	created when this is called.
int	env_new(t_envlist **envlist, const char *newparam, const char *newval)
{
	t_envlist	*curr;
	t_envlist	*new;

	if (*newparam == '\0' || *newval == '\0')
		return (0);
	new = malloc(sizeof(t_envlist));
	if (new == NULL)
		return (0);
	new->next = NULL;
	new->param = ft_strdup(newparam);
	new->value = ft_strdup(newval);
	curr = *envlist;
	if (curr == NULL)
	{
		*envlist = new;
		new->prev = NULL;
	}
	else
	{
		curr = env_last(envlist);
		curr->next = new;
		new->prev = curr;
	}
	return (1);
}

//	makes new env node from a single string assignation that includes a '='
//	checks for validity done within the env_set function
void	env_from_str(t_envlist **envlist, char *str)
{
	char		*param;
	char		*value;
	int			len;

	param = NULL;
	value = NULL;
	len = env_init_param(&param, str);
	env_init_value(&value, str, len);
	env_set(envlist, param, value);
	free(param);
	free(value);
}

//	takes *env[] input and creates env linked list
void	env_init(t_envlist **envlist, char *env[])
{
	int		i;

	i = 0;
	while (env[i])
		env_from_str(envlist, env[i++]);
	env_set(envlist, "SHELL", "./minishell");
	env_set(envlist, "PS1", "$ ");
}
