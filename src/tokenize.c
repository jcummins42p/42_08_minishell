/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:33:09 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/19 16:57:25 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize(t_tokenlist **tokens, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!strncmp(&str[i], "$", 1))
			i += token_new(tokens, "$", i);
		else if (!strncmp(&str[i], "'", 1))
			i += token_new(tokens, "'", i);
		else if (!strncmp(&str[i], "\"", 1))
			i += token_new(tokens, "\"", i);
		else if (!strncmp(&str[i], "|", 1))
			i += token_new(tokens, "|", i);
		else if (!strncmp(&str[i], ">>", 2))
			i += token_new(tokens, ">>", i);
		else if (!strncmp(&str[i], "<<", 2))
			i += token_new(tokens, "<<", i);
		else if (!strncmp(&str[i], ">", 1))
			i += token_new(tokens, ">", i);
		else if (!strncmp(&str[i], "<", 1))
			i += token_new(tokens, "<", i);
		else
			i++;
	}
}
