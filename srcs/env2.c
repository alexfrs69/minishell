/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrancoi <afrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:34:09 by afrancoi          #+#    #+#             */
/*   Updated: 2019/06/24 16:06:19 by afrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	ft_display_env(void)
{
	int i;

	i = -1;
	while (g_env[++i])
		ft_putendl(g_env[i]);
	printf("total %d\n", i);
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
	return (-1);
}

int		ft_get_size_env(void)
{
	int ret;

	ret = 0;
	while(g_env[ret])
		++ret;
	return(ret);
}

char	*ft_get_env(char *name)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = -1;
	while (g_env[++i])
	{
			if (ft_strnequ(g_env[i], name, ft_strlen(name))
				&& g_env[i][ft_strlen(name)] == '=')
				return (g_env[i] + ft_strlen(name) + 1);
	}
	return (NULL);
}
