/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrancoi <afrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 04:28:19 by afrancoi          #+#    #+#             */
/*   Updated: 2019/06/17 04:33:01 by afrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		main(int argc, char **argv, char **env)
{
	if(argc != 2)
		return (0);
	ft_putendl(argv[1]);
	ft_putendl(env[0]);
	return (0);
}
