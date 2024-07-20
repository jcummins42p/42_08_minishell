/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:40:47 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/19 18:37:20 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	linked list functions relating to the t_tokenlist struct

void	tokens_print(t_tokenlist **tokens)
{
	t_tokenlist	*curr;
	int			i;

	if (tokens == NULL || *tokens == NULL)
		return ;
	curr = *tokens;
	i = 0;
	while (curr)
	{
		printf("Token %d: %s at position %d with width %d\n", \
				i++, curr->token, curr->pos, curr->width);
		curr = curr->next;
	}
}

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
		free(swap);
	}
	*tokens = NULL;
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

int	token_new(t_tokenlist **tokens, char *newtoken, int pos)
{
	t_tokenlist	*curr;
	t_tokenlist	*new;

	new = malloc(sizeof(t_tokenlist));
	if (new == NULL)
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
		curr = token_last(tokens);
		curr->next = new;
		new->prev = curr;
	}
	return (new->width);
}
