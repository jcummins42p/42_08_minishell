/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:53:14 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/24 13:12:44 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
