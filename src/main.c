/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:37:08 by maroy             #+#    #+#             */
/*   Updated: 2023/10/09 03:06:02 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	print_error(char *filename, char *error_msg)
{
	ft_putstr_fd (ANSI_COLOR_BRIGHT_RED ERR_PROMPT, STDERR_FILENO);
	if (filename)
	{
		ft_putchar_fd ('\"', STDERR_FILENO);
		ft_putstr_fd (filename, STDERR_FILENO);
		ft_putstr_fd ("\": ", STDERR_FILENO);
	}
	ft_putstr_fd (error_msg, STDERR_FILENO);
	ft_putendl_fd(ANSI_COLOR_RESET, STDERR_FILENO);
}

void	print_error_then_exit(char *filename, char *error_msg)
{
	print_error(filename, error_msg);
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	t_cub_file	cub_file;
	t_game		game;
	char 		*error;
	
	debug_print_msg("DEBUG mode enabled 🐛");
	first_arg_checks(argc, argv);
	launch_parser(argv[1], &cub_file);
	error = init_game(&cub_file, &game);
	free_cub_data(&cub_file);
	if (error)
		print_error_then_exit(argv[1], error);
		
	return	(EXIT_SUCCESS);
}
