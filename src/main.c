/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:37:08 by maroy             #+#    #+#             */
/*   Updated: 2024/02/12 15:09:38 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *filename, char *error_msg)
{
	ft_putstr_err(ANSI_COLOR_BRIGHT_RED ERR_PROMPT);
	if (filename)
	{
		ft_putchar_err('\"');
		ft_putstr_err(filename);
		ft_putstr_err("\": ");
	}
	ft_putstr_err(error_msg);
	ft_putstr_errnl(ANSI_COLOR_RESET);
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
	char		*error_msg;

	first_arg_checks(argc, argv);
	launch_parser(argv[1], &cub_file);
	error_msg = init_game(&cub_file, &game);
	free_cub_data(&cub_file);
	if (error_msg)
	{
		destroy_game(&game, false);
		print_error_then_exit(argv[1], error_msg);
	}
	return (EXIT_SUCCESS);
}
