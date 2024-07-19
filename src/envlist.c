/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:53:14 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/19 18:18:02 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_alter(t_envlist **envlist, const char *search, const char *newval)
{
	t_envlist	*curr;
	int 		i;

	curr = *envlist;
	while (curr)
	{
		i = 0;
		while (curr->param[i] == search[i])
		{
			if (curr->param[i] == '\0' && search[i] == '\0')
			{
				free (curr->value);
				curr->value = ft_strdup(newval);
				return ;
			}
			i++;
		}
		curr = curr->next;
	}
	ft_printf("Error, no parameter of that name found in env\n");
}

char *env_get(t_envlist **envlist, const char *search)
{
	t_envlist	*curr;
	int			i;
	char		*out;

	out = NULL;
	curr = *envlist;
	while (curr)
	{
		i = 0;
		while (curr->param[i] == search[i])
		{
			if (curr->param[i] == '\0' && search[i] == '\0')
			{
				out = ft_strdup(curr->value);
				return (out);
			}
			i++;
		}
		curr = curr->next;
	}
	return (out);
}

void	env_print(t_envlist **envlist)
{
	t_envlist	*curr;

	curr = *envlist;
	while (curr)
	{
		printf("%s=%s\n", curr->param, curr->value);
		curr = curr->next;
	}
}

void	env_clear(t_envlist **envlist)
{
	t_envlist *curr;
	t_envlist *swap;
	int i = 0;

	if (envlist == NULL || *envlist == NULL)
		return ;
	curr = *envlist;
	while (curr)
	{
		swap = curr;
		curr = curr->next;
		free(swap->param);
		free(swap->value);
		free(swap);
		printf("Free %d in env", i++);
	}
	*envlist = NULL;
}

t_envlist	*env_last(t_envlist **envlist)
{
	t_envlist *curr;

	curr = *envlist;
	if (curr == NULL)
		return (NULL);
	while (curr->next)
	{
		curr = curr->next;
	}
	return (curr);
}

int	env_new(t_envlist **envlist, char *newparam, char *newvalue)
{
	t_envlist *curr;
	t_envlist *new;

	new = malloc(sizeof(t_envlist));
	if (new == NULL)
	   return (0);
	new->next = NULL;
	new->param = newparam;
	new->value = newvalue;
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

int env_init_param(char **param, char *envline)
{
	char *out;
	int i;
	int	len;

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

int	env_init_value(char **value, char *envline, int start)
{
	char *out;
	int len;
	int	i;

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
	int i;
	int	len;
	char *param;
	char *value;

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
	env_alter(envlist, "SHELL", "/bin/minishell");
}

