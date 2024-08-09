/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:15:41 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/09 14:28:58 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokens_get_info(t_mshell *msh)
{
	t_token_inf	*info;

	info = msh->info;
	info->n_pipe = token_count_type(&msh->tokens, PIPE);
	info->n_ass = token_count_type(&msh->tokens, ASS);
	info->n_rdin = token_count_type(&msh->tokens, RDIN);
	info->n_rdout = token_count_type(&msh->tokens, RDOUT);
	info->n_rdapp = token_count_type(&msh->tokens, RDAPP);
	info->n_delimit = token_count_type(&msh->tokens, DELIMIT);
}

t_tokenlist	*token_after_pipeno(t_tokenlist **tokens, int pipe_no)
{
	t_tokenlist	*curr;
	int			curr_pipe;

	curr = *tokens;
	curr_pipe = 0;
	if (!tokens)
		return (NULL);
	while (curr)
	{
		if (curr_pipe == pipe_no)
			return (curr);
		else
			curr = curr->next;
		if (curr->mtctype == PIPE)
		{
			curr = curr->next;
			curr_pipe++;
		}
	}
	return (NULL);
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

int	token_count_type(t_tokenlist **tokens, t_mtctype search)
{
	t_tokenlist	*curr;
	int			count;

	count = 0;
	curr = *tokens;
	if (!tokens)
		return (0);
	while (curr)
	{
		if (curr->mtctype == search)
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
