/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenfuncs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:15:41 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/23 14:06:35 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokenlist *token_at_pos(t_tokenlist **tokens, int searchpos)
{
	t_tokenlist *curr;

	curr = NULL;
	if (!tokens)
		return (NULL);
	while (curr)
	{
		if (curr->pos == searchpos)
			return (curr);
		else
			curr = curr->next;
	}
	return (NULL);
}

int	token_count_type(t_tokenlist **tokens, char *metachar)
{
	t_tokenlist	*curr;
	int			count;
	int			len;

	count = 0;
	len = ft_strlen(metachar);
	curr = *tokens;
	if (!tokens)
		return (0);
	while (curr)
	{
		if (!strncmp(curr->token, metachar, len))
			count++;
		curr = curr->next;
	}
	return (count);
}

//	in tokenlist tokens, store the position (index) of each occurance of
//	specified metacharacter in pos[] array
void	token_pos_type(t_tokenlist **tokens, int **pos, char *metachar)
{
	t_tokenlist	*curr;
	int			len;
	int			i;

	i = 0;
	len = ft_strlen(metachar);
	curr = *tokens;
	if (!tokens)
		return ;
	while (curr)
	{
		if (!strncmp(curr->token, metachar, len))
			(*pos)[i++] = curr->pos;
		curr = curr->next;
	}
}
