/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:53:14 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/20 19:19:03 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_clear(t_envlist **envlist)
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
		free(swap->param);
		free(swap->value);
		swap->value = NULL;
		swap->param = NULL;
		free(swap);
	}
	*envlist = NULL;
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

int	env_new(t_envlist **envlist, char *newparam, char *newvalue)
{
	t_envlist	*curr;
	t_envlist	*new;

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
