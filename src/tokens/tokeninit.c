/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeninit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:40:26 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/26 17:42:13 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_getenv(t_tokenlist *token, t_envlist **envlist)
{
	t_envlist	*find;

	if (token->var == NULL || envlist == NULL)
		return ;
	find = env_search(envlist, token->var);
	token->envvar = find;
}

int	token_addvar(t_tokenlist *token, char *str)
{
	char		*out;
	int			i;
	int			len;

	i = 0;
	while (str[i] && !is_whitespace(str[i]) && !is_metachar(&str[i]))
		i++;
	len = i;
	out = malloc(sizeof(char) * len + 1);
	out[len] = '\0';
	while (--i >= 0)
		out[i] = str[i];
	token->var = out;
	return (len + 1);
}

int	token_add_dquote(t_tokenlist *token, char *str)
{
	char		*out;
	int			i;
	int			len;

	i = 0;
	while (str[i] != '\"')
		i++;
	len = i;
	out = malloc(sizeof(char) * len + 1);
	out[len] = '\0';
	while (--i >= 0)
		out[i] = str[i];
	token->var = out;
	return (len + 1);
}

int	token_add_squote(t_tokenlist *token, char *str)
{
	char		*out;
	int			i;
	int			len;

	i = 0;
	while (str[i] != '\'')
		i++;
	len = i;
	out = malloc(sizeof(char) * len + 1);
	out[len] = '\0';
	while (--i >= 0)
		out[i] = str[i];
	token->var = out;
	return (len + 1);
}

void	token_init(t_tokenlist *new, char *newtoken, int pos, t_tokentype ttyp)
{
	new->next = NULL;
	new->var = NULL;
	new->pos = pos;
	new->token = ft_strdup(newtoken);
	new->width = ft_strlen(newtoken);
	new->envvar = NULL;
	new->tokentype = ttyp;
}

//	creates new node in tokenlist based on token (metachar or command) and the
//	variable following that token, such as $VARIABLE
int	token_new(t_mshell *msh, char *newtoken, int pos, t_tokentype ttyp)
{
	t_tokenlist	*curr;
	t_tokenlist	*new;

	new = malloc(sizeof(t_tokenlist));
	if (new == NULL)
		return (0);
	token_init(new, newtoken, pos, ttyp);
	if (*newtoken == '$')
	{
		new->width += token_addvar(new, &msh->lineread[pos + 1]);
		token_getenv(new, &msh->envlist);
	}
	else if (*newtoken == '\"')
	{
		new->width += token_add_dquote(new, &msh->lineread[pos + 1]);
	}
	else if (*newtoken == '\'')
	{
		new->width += token_add_squote(new, &msh->lineread[pos + 1]);
	}
	curr = msh->tokens;
	if (curr == NULL)
	{
		msh->tokens = new;
		new->prev = NULL;
	}
	else
	{
		curr = token_last(&msh->tokens);
		curr->next = new;
		new->prev = curr;
	}
	return (new->width);
}
