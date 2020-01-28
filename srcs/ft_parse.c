/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 10:45:45 by yviavant          #+#    #+#             */
/*   Updated: 2020/01/28 20:40:34 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_is_pointer(va_list args, t_params *p, int *pt)
{
	int		n;

	n = va_arg(args, int);
	if (n < 0 && !p->dot)
	{
		n *= -1;
		p->min = 1;
	}
	else if (n < 0 && p->dot)
	{
		p->dot = 0;
		n = 0;
	}
	*pt = n;
}

static void	ft_is_dot(char **format, t_params *p, va_list args)
{
	p->dot = 1;
	(*format)++;
	while (**format && (ft_isdigit(**format) || **format == '*'))
	{
		if (ft_isdigit(**format))
			p->precision = (p->precision * 10) + (**format - 48);
		else
			ft_is_pointer(args, p, &(p->precision));
		(*format)++;
	}
	(*format)--;
}

static void	ft_check_flags(char **format, t_params *p, va_list args)
{
	(*format)++;
	while (**format && (ft_strchr("-0*.", **format) || ft_isdigit(**format)))
	{
		if (**format == '-')
			p->min = 1;
		else if (**format == '0')
			p->zero = 1;
		else if (**format == '*')
			ft_is_pointer(args, p, &p->width);
		else if (**format == '.')
			ft_is_dot(format, p, args);
		else if (**format >= '1' && **format <= '9')
		{
			p->width = 0;
			while (ft_isdigit(**format))
			{
				p->width = (p->width * 10) + (**format - 48);
				(*format)++;
			}
			(*format)--;
		}
		(*format)++;
	}
}

static void	ft_check_c(char **format, t_params *p, va_list args, int *size)
{
	if (**format == 'c')
		ft_write_c(va_arg(args, int), p, size);
	else if (**format == 's')
		ft_write_s(va_arg(args, char *), p, size);
	else if (**format == 'd' || **format == 'i')
		ft_write_d(va_arg(args, int), p, size);
	else if (**format == 'u')
		ft_write_d(va_arg(args, unsigned int), p, size);
	else if (**format == 'p')
		ft_write_p(p, args, size);
	else if (**format == 'x')
		ft_write_x(va_arg(args, unsigned int), p, size, 0);
	else if (**format == 'X')
		ft_write_x(va_arg(args, unsigned int), p, size, 1);
	else if (**format == '%')
	{
		p->dot = 0;
		p->precision = 0;
		ft_write_c('%', p, size);
	}
	(*format)++;
}

void		ft_parse(char *format, va_list args, int *size)
{
	t_params	*p;

	p = NULL;
	while (*format)
	{
		ft_clean_params(&p);
		if (*format == '%' && *(format + 1))
		{
			ft_check_flags(&format, p, args);
			ft_check_c(&format, p, args, size);
		}
		else
		{
			ft_putchar_fd(*format, 1);
			format++;
			(*size)++;
		}
		free(p);
	}
}
