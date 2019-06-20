/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrancoi <afrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:34:09 by afrancoi          #+#    #+#             */
/*   Updated: 2019/06/20 15:47:30 by afrancoi         ###   ########.fr       */
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
				return (g_env[i]);
	}
	return (NULL);
}
