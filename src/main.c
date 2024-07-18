/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:30:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/18 14:48:03 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc == 3)
	{
		printf("argc is 3, macro in structs file is %d\n", STRUCTMACRO);
		printf("supplied argument is %s\n", argv[1]);
	}
	else
		return (1);
	return (0);
}
