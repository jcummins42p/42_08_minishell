/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envinit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:53:00 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/30 14:15:53 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	initialises and assigns value to a node in env linked list
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

//	initialises and assigns parameter to a node in env linked list. Returns
//	length of that string so that the init value function can start at the
//	correct place in that line to retreive the following value
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

//	creates new node of env linked list. Parameter and value have already been
//	created when this is called.
int	env_new(t_envlist **envlist, const char *newparam, const char *newvalue)
{
	t_envlist	*curr;
	t_envlist	*new;

	new = malloc(sizeof(t_envlist));
	if (new == NULL)
		return (0);
	new->next = NULL;
	new->param = ft_strdup(newparam);
	new->value = ft_strdup(newvalue);
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

//	takes *env[] input and creates env linked list
void	env_init(t_envlist **envlist, char *env[])
{
	int		i;
	int		len;
	char	*param;
	char	*value;
	t_envlist	*find;

	i = 0;
	param = NULL;
	value = NULL;
	while (env[i])
	{
		len = env_init_param(&param, env[i]);
		env_init_value(&value, env[i], len);
		find = env_search(envlist, param);
		if (find)
		{
			free (find->value);
			find->value = ft_strdup(value);
		}
		else
			env_new(envlist, param, value);
		i++;
	}
	env_set(envlist, "SHELL", "./minishell");
	env_set(envlist, "PS1", "$ ");
}
