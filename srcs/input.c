/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrancoi <afrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 10:44:48 by afrancoi          #+#    #+#             */
/*   Updated: 2019/07/10 09:22:59 by afrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <unistd.h>
#include <limits.h>

char	*parse_tilt(char *input, int i)
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
	if (input[i + 1] && input[i + 1] != '/'
		&& (i != 0 && input[i - 1] == ' ')
		&& ft_isalnum(input[i + 1]))
	{
		ft_strncpy(ret, input, i);
		ft_strncpy(ret + i, home, ft_strrchr(home, '/') - home);
		ft_strcat(ret, "/");
		ft_strcat(ret, input + i + 1);
	}
	else if (i != 0 && input[i - 1] == ' ')
	{
		ft_strncpy(ret, input, i);
		ft_strcpy(ret + i, home);
		ft_strcpy(ret + i + ft_strlen(home), input + i + 1);
	}
	else
		return (input);
	ft_strdel(&input);
	printf("ret = %s\n", ret);
	return (ret);
}


char	*parse_env(char *input, int i)
{
	char	*env;
	char	*ret;
	char	*name;
	int		sp;

	if(input[i + 1])
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
	printf("ret = %s\n", ret);
	ft_strdel(&input);
	return (ret);
}

char	*parse_input(char *input)
{
	int		i;
	char	*tmp;

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
	if (ft_strchr(input, '~') || ft_strchr(input, '$'))
		input = parse_input(input);

	return (input);
}
