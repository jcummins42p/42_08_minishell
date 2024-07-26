/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenfuncs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:15:41 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/26 17:58:08 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_get_info(t_mshell *msh)
{
	t_token_inf	*info;

	info = msh->info;
	info->n_dollar = token_count_type(&msh->tokens, "$");
	info->n_pipe = token_count_type(&msh->tokens, "|");
	info->n_squote = token_count_type(&msh->tokens, "\'");
	info->n_dquote = token_count_type(&msh->tokens, "\"");
	info->n_rdin = token_count_type(&msh->tokens, "<");
	info->n_rdout = token_count_type(&msh->tokens, ">");
	info->n_rdapp = token_count_type(&msh->tokens, ">>");
	info->n_delimit = token_count_type(&msh->tokens, "<<");
	printf("$\t-\t%d\n|\t-\t%d\n'\t-\t%d\n\"\t-\t%d\n", \
			info->n_dollar, info->n_pipe, info->n_squote, info->n_dquote);
	printf("<\t-\t%d\n>\t-\t%d\n>>\t-\t%d\n<<\t-\t%d\n", \
			info->n_rdin, info->n_rdout, info->n_rdapp, info->n_delimit);
}

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
		printf("Token %d: %s at position %d with width %d", \
				i++, curr->token, curr->pos, curr->width);
		if (curr->envvar)
			printf(" and variable %s expanding to %s", \
					curr->envvar->param, curr->envvar->value);
		else if (curr->var)
			printf(" containing string:%s", curr->var);
		printf("\n");
		curr = curr->next;
	}
}

t_tokenlist	*token_at_pos(t_tokenlist **tokens, int searchpos)
{
	t_tokenlist	*curr;

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
