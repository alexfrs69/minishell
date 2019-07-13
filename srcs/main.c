/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrancoi <afrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 04:28:19 by afrancoi          #+#    #+#             */
/*   Updated: 2019/07/10 09:34:15 by afrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

static void ft_init(void)
{
	char buf[PATH_MAX + 1];

	if(!(ft_get_env("PWD")))
	{
		getcwd(buf, PATH_MAX);
		ft_setenv("PWD", buf);
	}
}

static	void ft_display_prompt(void)
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

int		main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**cmds;
	int		ret;

	input = NULL;
	if (!(g_env = ft_copy_env(envp)))
		exit(0);
	while (1)
	{
		ft_init();
		cmds = NULL;
		ft_display_prompt();
		if(!(input = read_input()))
			break ;
		cmds = ft_strsplit(input, ' ');
		ft_strdel(&input);
		if ((ret = ft_check_builtins(cmds)) == -1)
			break ;
		else if (ret == 0)
			ft_searchbin(cmds);
		ft_del_arrays(cmds);
	}
	ft_del_arrays(cmds);
	ft_del_arrays(g_env);
	return (0);
}
