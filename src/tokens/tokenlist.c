/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:40:47 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/23 16:02:30 by jcummins         ###   ########.fr       */
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

void	token_getenv(t_tokenlist *token)
{
	if (token->var == NULL)
		return ;
}

int	token_addvar(t_tokenlist *token, char *str)
{
	char		*out;
	int			i;
	int			len;

	i = 0;
	while (str[i] && !is_whitespace(str[i]))
		i++;
	len = i;
	out = malloc(sizeof(char) * len + 1);
	out[len] = '\0';
	while (--i >= 0)
		out[i] = str[i];
	token->var = out;
	return (len);
}

int	token_new(t_tokenlist **tokens, char *newtoken, char *str, int pos)
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
	if (*newtoken == '$')
		new->width += token_addvar(new, &str[pos + 1]);
	else
		new->envvar = NULL;
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
