/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:40:26 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/05 13:56:35 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_init(t_tokenlist *new, char *newtoken, int pos)
{
	new->token = ft_strdup(newtoken);
	new->comtype = is_builtin(newtoken);
	new->mtctype = is_metachar(newtoken);
	if (new->comtype)
		new->tokentype = COMMAND;
	else if (new->mtctype)
		new->tokentype = METACHAR;
	else
		new->tokentype = GENERIC;
	new->pos = pos;
	new->width = ft_strlen(newtoken);
	new->var = NULL;
	new->trail_space = true;
	new->envvar = NULL;
	new->next = NULL;
	new->envvar = NULL;
}

void	token_append(t_tokenlist **tokens, t_tokenlist **new)
{
	t_tokenlist *curr;

	curr = *tokens;
	if (curr == NULL)
	{
		*tokens = *new;
		(*new)->prev = NULL;
	}
	else
	{
		curr = token_last(tokens);
		curr->next = *new;
		(*new)->prev = curr;
	}
}

//	creates new node in tokenlist based on token (metachar or command) and the
//	variable following that token, such as $VARIABLE
int	token_new(t_mshell *msh, char *newtoken, int pos)
{
	t_tokenlist	*new;

	new = malloc(sizeof(t_tokenlist));
	if (new == NULL)
		return (0);
	token_init(new, newtoken, pos);
	if (new->mtctype == DOLLAR || new->mtctype == DQUOTE)
		new->expand = expand_string_dq(msh, newtoken);
	else if (new->mtctype == SQUOTE)
		new->expand = expand_string_sq(newtoken);
	else
		new->expand = ft_strdup(new->token);
	printf("Expanded %s\t->\t%s\n", new->token, new->expand);
	token_append(&msh->tokens, &new);
	return (new->width);
}
