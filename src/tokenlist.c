/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:40:47 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/18 21:03:07 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokenlist *last_node(t_tokenlist **tokens)
{
	t_tokenlist	*curr;

	curr = *tokens;
	if (curr == NULL)
		return (NULL);
	while (curr->next)
		curr = curr->next;
	return (curr);
}

int	new_token(t_tokenlist **tokens, char *newtoken, int pos)
{
	t_tokenlist	*curr;
	t_tokenlist	*new;

	new = malloc(sizeof(t_tokenlist));
	if (new == NULL || new == NULL)
		return (0);
	new->next = NULL;
	new->pos = pos;
	new->token = ft_strdup(newtoken);
	new->width = ft_strlen(newtoken);
	curr = *tokens;
	if (curr == NULL)
	{
		*tokens = new;
		new->prev = NULL;
	}
	else
	{
		curr = last_node(tokens);
		curr->next = new;
		new->prev = curr;
	}
	return (new->width);
}

void	list_clear(t_tokenlist **tokens)
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
		free(swap);
	}
	*tokens = NULL;
}
