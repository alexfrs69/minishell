/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrancoi <afrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 10:44:48 by afrancoi          #+#    #+#             */
/*   Updated: 2019/07/13 17:37:18 by afrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	ft_cpy_tilt(char *input, char *home, char *ret, int i)
{
	if (input[i + 1] && input[i + 1] != '/'
		&& (i != 0 && input[i - 1] == ' ')
		&& ft_isalnum(input[i + 1]))
	{
		ft_strncpy(ret, input, i);
		ft_strncpy(ret + i, home, ft_strrchr(home, '/') - home);
		ft_strcat(ret, "/");
		ft_strcat(ret, input + i + 1);
		return (1);
	}
	return (0);
}

char		*parse_tilt(char *input, int i)
{
	char	*ret;
	char	*home;
	int		sizeinput;

	if (!(home = ft_get_env("HOME")))
		return (input);
	sizeinput = ft_strlen(input);
	if (sizeinput == 1)
		return (ft_strdup(home));
	if (!(ret = ft_strnew(sizeinput + ft_strlen(home))))
		return (input);
	if (ft_cpy_tilt(input, home, ret, i))
		i = 0;
	else if (i != 0 && input[i - 1] == ' ')
	{
		ft_strncpy(ret, input, i);
		ft_strcpy(ret + i, home);
		ft_strcpy(ret + i + ft_strlen(home), input + i + 1);
	}
	else
		return (input);
	ft_strdel(&input);
	return (ret);
}

char		*parse_env(char *input, int i)
{
	char	*env;
	char	*ret;
	char	*name;
	int		sp;

	if (input[i + 1])
	{
		if ((sp = ft_strichr(input + i + 1, ' ')) == -1)
			if ((sp = ft_strichr(input + i + 1, '$')) == -1)
				sp = ft_strlen(input + i + 1);
		if (!(name = ft_strndup(input + i + 1, sp)))
			return (input);
		if (!(env = ft_get_env(name)))
			return (input);
		ft_strdel(&name);
		if (!(ret = ft_strnew(ft_strlen(input) + ft_strlen(env))))
			return (input);
		ft_strncpy(ret, input, i);
		ft_strcpy(ret + i, env);
		ft_strcpy(ret + i + ft_strlen(env), input + i + 1 + sp);
	}
	else
		return (input);
	ft_strdel(&input);
	return (ret);
}
