/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:40:26 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/02 16:15:21 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	token_getenv(t_tokenlist *token, t_envlist **envlist)*/
/*{*/
	/*t_envlist	*find;*/

	/*if (token->var == NULL || envlist == NULL)*/
		/*return ;*/
	/*find = env_search(envlist, token->var);*/
	/*token->envvar = find;*/
/*}*/

/*int	token_addvar(t_tokenlist *token, char *str)*/
/*{*/
	/*char		*out;*/
	/*int			i;*/
	/*int			len;*/

	/*i = 0;*/
	/*while (str[i] && !is_whitespace(str[i]) && str[i] != '$')*/
		/*i++;*/
	/*if (!str[i] || !is_whitespace(str[i]))*/
		/*token->trail_space = false;*/
	/*len = i;*/
	/*out = malloc(sizeof(char) * len + 1);*/
	/*out[len] = '\0';*/
	/*while (--i >= 0)*/
		/*out[i] = str[i];*/
	/*token->var = out;*/
	/*return (len);*/
/*}*/

/*int	token_add_dquote(t_tokenlist *token, char *str)*/
/*{*/
	/*char		*out;*/
	/*int			i;*/
	/*int			len;*/

	/*i = 0;*/
	/*while (str[i] != '\"')*/
		/*i++;*/
	/*len = i;*/
	/*out = malloc(sizeof(char) * len + 1);*/
	/*out[len] = '\0';*/
	/*while (--i >= 0)*/
		/*out[i] = str[i];*/
	/*token->var = out;*/
	/*return (len + 1);*/
/*}*/

/*int	token_add_squote(t_tokenlist *token, char *str)*/
/*{*/
	/*char		*out;*/
	/*int			i;*/
	/*int			len;*/

	/*i = 0;*/
	/*while (str[i] != '\'')*/
		/*i++;*/
	/*len = i;*/
	/*out = malloc(sizeof(char) * len + 1);*/
	/*out[len] = '\0';*/
	/*while (--i >= 0)*/
		/*out[i] = str[i];*/
	/*token->var = out;*/
	/*return (len + 1);*/
/*}*/

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
	/*if (new->mtctype == DOLLAR)*/
	/*{*/
		/*//	problem here with width*/
		/*new->width += token_addvar(new, &msh->lineread[pos + 1]);*/
		/*token_getenv(new, &msh->envlist);*/
	/*}*/
	/*else if (new->mtctype == DQUOTE)*/
		/*new->width += token_add_dquote(new, &msh->lineread[pos + 1]);*/
	/*else if (new->mtctype == SQUOTE)*/
		/*new->width += token_add_squote(new, &msh->lineread[pos + 1]);*/
	token_append(&msh->tokens, &new);
	return (new->width);
}
