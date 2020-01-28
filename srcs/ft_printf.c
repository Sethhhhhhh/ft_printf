/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 10:41:27 by yviavant          #+#    #+#             */
/*   Updated: 2020/01/28 21:16:11 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_clean_params(t_params **p)
{
	*p = (t_params*)malloc(sizeof(t_params));
	(*p)->min = 0;
	(*p)->dot = 0;
	(*p)->zero = 0;
	(*p)->width = 0;
	(*p)->precision = 0;
}

void	ft_write_width(t_params *p, int len, int *size)
{
	char	sep;
	int		width;

	width = p->width;
	sep = (p->zero && !p->min && !p->dot) ? '0' : ' ';
	if (p->precision > len)
		width = width > p->precision ? (width - p->precision) : 0;
	else
		width = width > len ? width - len : 0;
	*size += (len + width);
	while (width-- > 0)
		ft_putchar_fd(sep, 1);
}

void	ft_write_precision(t_params *p, int len, int *size)
{
	int		precision;

	precision = p->precision > len ? p->precision - len : 0;
	*size += precision;
	while (precision-- > 0)
		ft_putchar_fd('0', 1);
}

int		ft_printf(char *format, ...)
{
	va_list	args;
	int		size;

	size = 0;
	if (!format)
		return (size);
	va_start(args, format);
	ft_parse(format, args, &size);
	va_end(args);
	return (size);
}
