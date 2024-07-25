/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:31:31 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/25 19:56:35 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	recreates the env in original format so that it can be passed to execve

void	env_unset_string(char **env[])
{
	int i;

	i = 0;
	while ((*env)[i])
		free ((*env)[i++]);
	free (*env);
}

void	env_set_string(t_envlist **envlist, char **env[])
{
	t_envlist	*curr;
	int			line;
	int			size;

	if (*env)
		env_unset_string(env);
	curr = *envlist;
	line = 0;
	size = env_list_size(envlist);
	*env = malloc(sizeof (char *) * (size + 1));
	while (curr)
	{
		(*env)[line++] = ft_strchrjoin(curr->param, curr->value, '=');
		curr = curr->next;
	}
	*env[line] = NULL;
}

void	env_unset(t_envlist **envlist, const char *search)
{
	t_envlist	*find;

	find = env_search(envlist, search);
	if (find)
		env_del(&find);
	else
		ft_printf("Error, no parameter of that name found in env\n");
}

void	env_set(t_envlist **envlist, const char *search, const char *newval)
{
	t_envlist	*find;

	find = env_search(envlist, search);
	if (find)
	{
		free (find->value);
		find->value = ft_strdup(newval);
	}
	else
	{
		ft_printf("Creating variable %s with value %s\n", search, newval);
		env_new(envlist, search, newval);
	}
}
