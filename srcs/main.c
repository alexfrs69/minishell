/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrancoi <afrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 04:28:19 by afrancoi          #+#    #+#             */
/*   Updated: 2019/07/09 05:32:19 by afrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

int		main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**cmds;
	int		ret;

	cmds = NULL;
	input = NULL;
	if (!(g_env = ft_copy_env(envp)))
		exit(0);
	while (1)
	{
		ft_putstr("[ ");
		if (ft_strequ(ft_get_env("HOME"), ft_get_env("PWD")))
			ft_putchar('~');
		else
			ft_putstr(ft_get_env("PWD"));
		ft_putstr(" ] ");
		ft_putstr("$>");
		if(!(input = read_input()))
		{
			ft_putstr("PARSING FAILED\n");
			break ;
		}
		cmds = ft_strsplit(input, ' ');
		ft_strdel(&input);
		if ((ret = ft_check_builtins(cmds)) == -1)
			break ;
		/*else if (ret == 0)
			ft_searchpath();
		*/
		ft_del_arrays(cmds);
	}
	ft_del_arrays(cmds);
	ft_del_arrays(g_env);
	return (0);
}
