/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:24:21 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/08 20:28:22 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strldup(const char *s, size_t size)
{
	char			*dup;
	unsigned int	len;
	unsigned int	i;

	len = 0;
	while (s[len] && len < size)
		len++;
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/*int	main(void)*/
/*{*/
	/*const char	*src = "Original String to be duplicated";*/

	/*printf("%s\n", ft_strdup(src));*/
	/*return (0);*/
/*}*/
