/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrancoi <afrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 10:44:48 by afrancoi          #+#    #+#             */
/*   Updated: 2019/06/18 11:11:22 by afrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

char *read_input(void)
{
	char	buf;
	char	*input;
	int		n;
	char	*tmp;

	tmp = NULL;
	input = ft_strnew(1);
	while((n = read(0, &buf, 1)) && buf != '\n')
	{
		tmp = input;
		input = ft_strnew(ft_strlen(input) + 1);
		ft_strcpy(input, tmp);
		input[ft_strlen(input)] = buf;
	}
	return (input);
}
