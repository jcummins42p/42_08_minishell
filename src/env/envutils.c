/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:53:14 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/29 15:52:53 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_print(t_envlist **envlist)
{
	t_envlist	*curr;

	curr = *envlist;
	while (curr)
	{
		if (curr->value)
			printf("%s=%s\n", curr->param, curr->value);
		curr = curr->next;
	}
}

int		env_list_size(t_envlist **envlist)
{
	t_envlist	*curr;
	int			size;

	size = 0;
	curr = *envlist;
	while (curr)
	{
		curr = curr->next;
		size++;
	}
	return (size);
}

void	env_string_clear(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free (env[i++]);
	free (env);
}

void	env_list_clear(t_envlist **envlist)
{
	t_envlist	*curr;
	t_envlist	*swap;

	if (envlist == NULL || *envlist == NULL)
		return ;
	curr = *envlist;
	while (curr)
	{
		swap = curr;
		curr = curr->next;
		if (swap->param)
			free(swap->param);
		if (swap->value)
			free(swap->value);
		swap->value = NULL;
		swap->param = NULL;
		free(swap);
	}
}

void	env_del(t_envlist **envlist)
{
	t_envlist	*next;
	t_envlist	*prev;

	if (envlist == NULL || *envlist == NULL)
		return ;
	next = (*envlist)->next;
	prev = (*envlist)->prev;
	if (next)
		next->prev = prev;
	if (prev)
		prev->next = next;
	free (*envlist);
	*envlist = NULL;
}
