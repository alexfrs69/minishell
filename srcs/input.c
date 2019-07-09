/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrancoi <afrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 10:44:48 by afrancoi          #+#    #+#             */
/*   Updated: 2019/07/09 05:26:43 by afrancoi         ###   ########.fr       */
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
		return (NULL);
	sizeinput = ft_strlen(input);
	if (sizeinput == 1)
		return (ft_strdup(home));
	if (!(ret = ft_strnew(sizeinput + ft_strlen(home))))
		return (NULL);
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
		return (ft_strdup(input));
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
			return (NULL);
		if (!(env = ft_get_env(name)))
			return (ft_strdup(input));
		ft_strdel(&name);
		if (!(ret = ft_strnew(ft_strlen(input) + ft_strlen(env))))
			return (NULL);
		ft_strncpy(ret, input, i);
		ft_strcpy(ret + i, env);
		ft_strcpy(ret + i + ft_strlen(env), input + i + 1 + sp);
	}
	else
		return (ft_strdup(input));
	printf("ret = %s\n", ret);
	return (ret);
}

char	*parse_input(char *input)
{
	int		i;
	char	*tmp;

	i = -1;
	while (input[++i])
	{
		tmp = input;
		if (input[i] == '~')
		{
			if (!(input = parse_tilt(input, i)))
				break ;
			ft_strdel(&tmp);
		}
		else if (input[i] == '$')
		{
			if (!(input = parse_env(input, i)))
				break ;
			ft_strdel(&tmp);
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
