/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 10:41:27 by yviavant          #+#    #+#             */
/*   Updated: 2020/01/27 21:23:48 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_clean_params(t_params **params)
{
	*params = (t_params*)malloc(sizeof(t_params));
	(*params)->min = 0;
	(*params)->dot = 0;
	(*params)->zero = 0;
	(*params)->width = 0;
	(*params)->precision = 0;
}

void	ft_write_width(t_params *params, int len, int *size)
{
	char	sep;
	int		width;

	width = params->width;
	sep = (params->zero && !params->min && !params->dot) ? '0' : ' ';
	if (params->precision > len)
		width= width > params->precision ? (width - params->precision) : 0;
	else
		width = width > len ? width - len : 0;
	*size += (len + width);
	while (width-- > 0)
		ft_putchar_fd(sep, 1);
}

void	ft_write_precision(t_params *params, int len, int *size)
{
	int	precision;

	precision = params->precision > len ? params->precision - len : 0;
	*size += precision;
	while (precision-- > 0)
		ft_putchar_fd('0', 1);
}

int		ft_printf(char *format, ...)
{
	va_list	args;
	int		size;
	
	size = 0;
	va_start(args, format);
	ft_parse(format, args, &size);	
	va_end(args);
	return (size);
}
