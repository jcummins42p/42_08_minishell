/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:40:47 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/06 17:02:35 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	linked list functions relating to the t_tokenlist struct

void	token_clear(t_tokenlist **tokens)
{
	t_tokenlist	*curr;
	t_tokenlist	*swap;

	if (tokens == NULL || *tokens == NULL)
		return ;
	curr = *tokens;
	while (curr)
	{
		swap = curr;
		curr = curr->next;
		free(swap->token);
		if (swap->expand)
			free(swap->expand);
		free(swap);
	}
	*tokens = NULL;
}

t_tokenlist	*token_at_index(t_tokenlist **tokens, int search)
{
	t_tokenlist	*curr;

	if (tokens == NULL || *tokens == NULL)
		return (NULL);
	curr = *tokens;
	while (curr)
	{
		if (curr->index == search)
			return (curr);
		else
			curr = curr->next;
	}
	return (NULL);
}

t_tokenlist	*token_last(t_tokenlist **tokens)
{
	t_tokenlist	*curr;

	curr = *tokens;
	if (curr == NULL)
		return (NULL);
	while (curr->next)
		curr = curr->next;
	return (curr);
}
