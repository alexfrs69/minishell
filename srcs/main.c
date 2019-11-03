/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrancoi <afrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 04:28:19 by afrancoi          #+#    #+#             */
/*   Updated: 2019/11/03 02:58:11 by afrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

static void		ft_kickstart(char **env)
{
	char *tmp;

	if (!(g_env = ft_copy_env(env)))
		exit(0);
	if (!(ft_get_env("SHLVL")))
		ft_setenv("SHLVL", "1");
	else
	{
		tmp = ft_itoa(ft_atoi(ft_get_env("SHLVL")) + 1);
		ft_setenv("SHLVL", tmp);
		ft_strdel(&tmp);
	}
}

static void		ft_display_prompt(void)
{
	char *home;
	char *pwd;

	home = ft_get_env("HOME");
	pwd = ft_get_env("PWD");
	ft_putstr("[ ");
	if (ft_strequ(home, pwd))
		ft_putchar('~');
	else
		ft_putstr(pwd);
	ft_putstr(" ] ");
	ft_putstr("$>");
}

static void		ft_init(void)
{
	char buf[PATH_MAX + 1];

	if (!(ft_get_env("PWD")))
	{
		getcwd(buf, PATH_MAX);
		ft_setenv("PWD", buf);
	}
	ft_display_prompt();
}

static void		ft_run(void)
{
	char	*input;
	char	**cmds;
	int		ret;

	while (1)
	{
		ft_init();
		cmds = NULL;
		if (!(input = read_input()))
			break ;
		if (!ft_strlen(input))
		{
			ft_strdel(&input);
			continue ;
		}
		cmds = ft_strsplit(input, "	 ");
		ft_strdel(&input);
		if ((ret = ft_check_builtins(cmds)) == -1)
			break ;
		else if (ret == 0)
			ft_searchbin(cmds);
		ft_del_arrays(cmds);
	}
	ft_del_arrays(cmds);
	ft_del_arrays(g_env);
}

int				main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_kickstart(envp);
	ft_run();
	return (0);
}
