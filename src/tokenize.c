/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:33:09 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/18 20:57:55 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize(t_tokenlist **tokens, char *str)
{
	int			i = 0;

	while (str[i])
	{
		if (!strncmp(&str[i], "$", 1))
			i += new_token(tokens, "$", i);
		else if (!strncmp(&str[i], "'", 1))
			i += new_token(tokens, "'", i);
		else if (!strncmp(&str[i], "\"", 1))
			i += new_token(tokens, "\"", i);
		else if (!strncmp(&str[i], "|", 1))
			i += new_token(tokens, "|", i);
		else if (!strncmp(&str[i], ">>", 2))
			i += new_token(tokens, ">>", i);
		else if (!strncmp(&str[i], "<<", 2))
			i += new_token(tokens, "<<", i);
		else if (!strncmp(&str[i], ">", 1))
			i += new_token(tokens, ">", i);
		else if (!strncmp(&str[i], "<", 1))
			i += new_token(tokens, "<", i);
		else
			i++;
	}
	if (*tokens)
		print_tokens(tokens);
}

void	print_tokens(t_tokenlist **head)
{
	t_tokenlist	*curr;
	int			i;

	if (head == NULL || *head == NULL)
		return ;
	curr = *head;
	i = 0;
	while (curr)
	{
		printf("Token %d: %s at position %d with width %d\n", i++, curr->token, curr->pos, curr->width);
		curr = curr->next;
	}
}
