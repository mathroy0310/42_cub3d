/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:37:08 by maroy             #+#    #+#             */
/*   Updated: 2023/10/03 18:38:41 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	print_error(char *file_error)
{
	ft_putstr_fd (ANSI_COLOR_BRIGHT_RED ERR_PROMPT, STDERR_FILENO);
	ft_putstr_fd (file_error, STDERR_FILENO);
	ft_putendl_fd(ANSI_COLOR_RESET, STDERR_FILENO);
}

int	main(int argc, char *argv[])
{
	char *error;
	if (!is_valid_arg(argc, argv))
		return (EXIT_FAILURE);
	error = parse_cub_file(argv[1]);
	if (error)
	{
		return (EXIT_FAILURE);
	}
	
		
	return	(EXIT_SUCCESS);
}
