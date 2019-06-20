/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrancoi <afrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 04:28:19 by afrancoi          #+#    #+#             */
/*   Updated: 2019/06/20 16:01:03 by afrancoi         ###   ########.fr       */
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

	cmds = NULL;
	input = NULL;
	if(!(g_env = ft_copy_env(envp)))
		exit(0);
	while (1)
	{
		ft_putstr("$>");
		input = read_input();
		cmds = ft_strsplit(input, ' ');
		ft_check_builtins(cmds);
	}
	return (0);
}
