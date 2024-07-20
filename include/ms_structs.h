/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:23:39 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/19 18:34:51 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRUCTS_H
# define MS_STRUCTS_H

typedef struct s_tokenlist
{
	char				*token;	// which token $ | >> etc
	int					pos;	// index of first char within string
	int					width;	// width of token in char
	struct s_tokenlist	*next;
	struct s_tokenlist	*prev;
}	t_tokenlist;

typedef struct s_envlist
{
	char				*param;	// environment variable
	char				*value; // variable value
	struct s_envlist	*next;
	struct s_envlist	*prev;
}	t_envlist;

typedef struct s_mshell
{
	t_tokenlist	*tokens;
	t_envlist	*envlist;
	char		*ptr;
	char		*prompt;
}	t_mshell;

#endif
