/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrancoi <afrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 17:28:51 by afrancoi          #+#    #+#             */
/*   Updated: 2019/11/03 01:27:54 by afrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

char	*parse_input(char *input)
{
	int		i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '~')
		{
			if (!(input = parse_tilt(input, i)))
				break ;
		}
		else if (input[i] == '$')
		{
			if (!(input = parse_env(input, i)))
				break ;
		}
	}
	return (input);
}

char	*read_input(void)
{
	char	buf;
	char	*input;
	int		n;
	char	*tmp;

	tmp = NULL;
	input = ft_strnew(1);
	while ((n = read(0, &buf, 1)) && buf != '\n')
	{
		tmp = input;
		input = ft_strnew(ft_strlen(input) + 1);
		ft_strcpy(input, tmp);
		ft_strdel(&tmp);
		input[ft_strlen(input)] = buf;
	}
	if (ft_strlen(input))
	{
		tmp = input;
		input = ft_strtrim(input);
		ft_strdel(&tmp);
	}
	if (ft_strchr(input, '~') || ft_strchr(input, '$'))
		input = parse_input(input);
	return (input);
}
