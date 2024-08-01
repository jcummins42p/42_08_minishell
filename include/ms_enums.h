/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_enums.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:32:26 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/01 13:50:53 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ENUMS_H
# define MS_ENUMS_H

typedef enum e_tokentype
{
	GENERIC,
	METACHAR,
	COMMAND
}	t_tokentype;

typedef enum e_comtype
{
	NO_COM,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	ASSIGN,
	EXIT
}	t_comtype;

typedef enum e_mtctype
{
	NO_MTC,
	DOLLAR,		// $ - environment variable
	SQUOTE,		// '
	DQUOTE,		// "
	PIPE,		// |
	RDIN,		// < - redirect input
	RDOUT,		// > - redirect output (overwrite)
	RDAPP,		// >> - redirect output (append)
	DELIMIT
}	t_mtctype;

typedef enum e_vscope
{
	SHLVAR,
	ENVVAR
}	t_vscope;

#endif
