/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 10:42:07 by yviavant          #+#    #+#             */
/*   Updated: 2020/01/28 21:13:58 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** Includes
*/

# include <stdlib.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

/*
** Structures
*/

typedef struct	s_params
{
	int	min;
	int	dot;
	int	zero;
	int	width;
	int	precision;
}				t_params;

/*
** Conversions
*/

void			ft_write_c(char c, t_params *p, int *size);
void			ft_write_s(char *str, t_params *p, int *size);
void			ft_write_d(long n, t_params *p, int *size);
void			ft_write_p(t_params *p, va_list args, int *size);
void			ft_write_x(long n, t_params *p, int *size, int maj);

/*
** Utils
*/

void			ft_clean_params(t_params **p);
void			ft_write_width(t_params *p, int len, int *size);
void			ft_write_precision(t_params *p, int len, int *size);

/*
**	Core
*/

int				ft_printf(char *format, ...);
void			ft_parse(char *format, va_list args, int *size);

#endif
