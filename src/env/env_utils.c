/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:53:14 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/01 14:13:21 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	specify scope as SHLVAR to print all variables including local shell vars
//	or scope as ENVVAR to only print ENV variables (default for env command)
void	env_print(t_envlist **envlist, t_vscope scope)
{
	t_envlist	*curr;

	curr = *envlist;
	while (curr)
	{
		if (curr->value && curr->scope >= scope)
			printf("%s=%s\n", curr->param, curr->value);
		curr = curr->next;
	}
}

int	env_list_size(t_envlist **envlist)
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
	while (env && env[i])
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
	if ((*envlist)->value)
		free((*envlist)->value);
	if ((*envlist)->param)
		free((*envlist)->param);
	next = (*envlist)->next;
	prev = (*envlist)->prev;
	if (next)
		next->prev = prev;
	if (prev)
		prev->next = next;
	free (*envlist);
	*envlist = NULL;
}
