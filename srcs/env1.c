/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrancoi <afrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 11:40:56 by afrancoi          #+#    #+#             */
/*   Updated: 2019/06/20 16:18:31 by afrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

char **ft_realloc_env(size_t size)
{
	char	**new;
	int	i;

	if(!(new = ft_memalloc(sizeof(char*) * (size + 1))))
		return (NULL);
	i = -1;
	while(g_env[++i])
	{
		new[i] = ft_strdup(g_env[i]);
		ft_strdel(&g_env[i]);
	}
	free(g_env);
	return (new);
}

char **ft_copy_env(char **env)
{
	char	**ret;
	int		i;

	i = 0;
	while (env[i])
		i++;
	if (!(ret = ft_memalloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = -1;
	while (env[++i])
	{
		if (!(ret[i] = ft_strdup(env[i])))
			return (NULL);
	}
	ret[i] = 0;
	return (ret);
}

int		ft_get_i_env(char *name)
{
	int		i;

	i = -1;
	while (g_env[++i])
	{
		if (ft_strnequ(g_env[i], name, ft_strlen(name))
			&& g_env[i][ft_strlen(name)] == '=')
			return (i);
	}
	return (0);
}

int		ft_setenv(char *name, char *value)
{
	int		i;

	i = 0;
	if (!(i = ft_get_i_env(name)))
	{
		while(g_env[i])
			i++;
	}
	if(!(g_env = ft_realloc_env(i + 1)))
		return (0);
	g_env[i] = ft_strnew(ft_strlen(name) + ft_strlen(value) + 1);
	ft_strcpy(g_env[i], name);
	ft_strcat(g_env[i], "=");
	ft_strcat(g_env[i], value);
	return (1);
}

int		ft_unsetenv(char *name)
{
	int i;

	if(!(i = ft_get_i_env(name)))
		return (0);
	ft_strdel(&g_env[i]);
	while(g_env[i + 1])
	{
		g_env[i] = ft_strdup(g_env[i + 1]);
		ft_strdel(&g_env[i + 1]);
		i++;
	}
	g_env = ft_realloc_env(i);
	return (1);
}

