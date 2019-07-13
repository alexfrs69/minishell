/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrancoi <afrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:49:23 by afrancoi          #+#    #+#             */
/*   Updated: 2019/07/10 08:51:22 by afrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void	ft_builtin_echo(char **args)
{
	int i;

	i = -1;
	if (!args[0])
		ft_putchar('\n');
	else
	{
		while (args[++i])
		{
			ft_putstr(args[i]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}

void	ft_builtin_env(char **args, int setenv)
{
	int		i;
	char	**kv;

	i = -1;
	if (!args[0] && !setenv)
		ft_display_env();
	else
	{
		while (args[++i])
		{
			if (!(ft_strchr(args[i], '=')))
				return ;
			if (!(kv = ft_strsplit(args[i], '=')))
				return ;
			ft_setenv(kv[0], kv[1]);
			ft_strdel(&kv[0]);
			ft_strdel(&kv[1]);
			free(kv);
		}
		if (!setenv)
			ft_display_env();
	}
}

void	ft_builtin_unsetenv(char **args)
{
	int i;

	i = -1;
	if (!args[0])
		ft_putendl("unsetenv: not enough arguments");
	else
	{
		while (args[++i])
			ft_unsetenv(args[i]);
	}
}

int		ft_check_builtins(char **cmds)
{
	if (cmds[0])
	{
		if (ft_strequ(cmds[0], "echo"))
			ft_builtin_echo(cmds + 1);
		else if (ft_strequ(cmds[0], "env"))
			ft_builtin_env(cmds + 1, 0);
		else if (ft_strequ(cmds[0], "setenv"))
			ft_builtin_env(cmds + 1, 1);
		else if (ft_strequ(cmds[0], "unsetenv"))
			ft_builtin_unsetenv(cmds + 1);
		else if (ft_strequ(cmds[0], "cd"))
			ft_builtin_cd(cmds + 1);
		else if (ft_strequ(cmds[0], "exit"))
			return (-1);
		else
			return (0);
		return (1);
	}
	return (0);
}
