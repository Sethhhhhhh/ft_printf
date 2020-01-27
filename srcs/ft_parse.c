/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 10:45:45 by yviavant          #+#    #+#             */
/*   Updated: 2020/01/27 21:23:45 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_is_pointer(va_list args, t_params *params, int *pt)
{
	int	n;

	n = va_arg(args, int);
	if (n < 0 && !params->dot)
	{
		n *= -1;
		params->min = 1;
	} 
	else if (n < 0 && params->dot)
	{
		params->dot = 0;
		n = 0;
	}
	*pt = n;
}

static void	ft_is_dot(char **format, t_params *params, va_list args)
{
	params->dot = 1;
	(*format)++;
	while (**format && (ft_isdigit(**format) || **format == '*' ))
	{
		if (ft_isdigit(**format))
			params->precision = (params->precision * 10) + (**format - 48);
		else
			ft_is_pointer(args, params, &(params->precision));
		(*format)++;
	}
	(*format)--;
}

static void	ft_check_flags(char **format, t_params *params, va_list args) 
{
	(*format)++;
	while (**format && (ft_strchr("-0*.", **format) || ft_isdigit(**format)))
	{
		if (**format == '-')
			params->min = 1;
		else if (**format == '0')
			params->zero = 1;
		else if (**format == '*')
			ft_is_pointer(args, params, &params->width);
		else if (**format == '.')
			ft_is_dot(format, params, args);
		else if (**format >= '1' && **format <= '9')
		{
			params->width = 0;
			while (ft_isdigit(**format))
			{
				params->width = (params->width * 10) + (**format - 48);
				(*format)++;
			}
			(*format)--;
		}
		(*format)++;
	}
}

static void	ft_check_conversions(char **format, t_params *params, va_list args, int *size)
{
	if (**format == 'c')
		ft_write_c(va_arg(args, int), params, size);
	else if (**format == 's')
		ft_write_s(va_arg(args, char *), params, size);
	else if (**format == 'd' || **format == 'i')
		ft_write_d(va_arg(args, int), params, size);
	else if (**format == 'u')
		ft_write_d(va_arg(args, unsigned int), params, size);
	else if (**format == 'p')
		ft_write_p(params, args, size);	
	else if (**format == 'x')
		ft_write_x(va_arg(args, unsigned int), params, size, 0);
	else if (**format == 'X')
		ft_write_x(va_arg(args, unsigned int), params, size, 1);
	else if (**format == '%')
	{
		params->dot = 0;
		params->precision = 0;
		ft_write_c('%', params, size);
	}
	(*format)++;
}

void	ft_parse(char *format, va_list args, int *size)
{
	t_params	*params;

	params = NULL;
	while (*format)
	{
		ft_clean_params(&params);
		if (*format == '%' && *(format + 1))
		{
			ft_check_flags(&format, params, args);
			ft_check_conversions(&format, params, args, size);
		}
		else
		{
			ft_putchar_fd(*format, 1);
			format++;
			(*size)++;
		}
		free(params);
	}
}
