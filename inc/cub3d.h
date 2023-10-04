/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:15:26 by maroy             #+#    #+#             */
/*   Updated: 2023/10/03 19:14:46 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "defines.h"
# include "parsing.h"
# include "../libs/libft/inc/libft.h"

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <fcntl.h>

typedef enum e_direction
{
	NO,
	SO,
	WE,
	EA,
	NONE
}	t_direction;

void	print_error(char *file_error);


#endif