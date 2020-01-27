/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 10:46:08 by yviavant          #+#    #+#             */
/*   Updated: 2020/01/27 21:22:37 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_write_c(char c, t_params *params, int *size)
{
	if (!params->min)
		ft_write_width(params, 1, size);
	ft_putchar_fd(c, 1);
	if (params->min)
		ft_write_width(params, 1, size);
}

void	ft_write_s(char *str, t_params *params, int *size)
{
	int	len;

	if (!str)
		str = ft_strdup("(null)");
	len = ft_strlen(str);
	params->precision = params->precision < 0 ? -params->precision : params->precision;
	len = (!params->dot || params->precision >= len) ? len : params->precision;
	str = ft_substr(str, 0, len);
	params->precision = 0;
	params->dot = 0;
	if (!params->min)
		ft_write_width(params, len, size);
	ft_putstr_fd(str, 1);
	if (params->min)
		ft_write_width(params, len, size);
	free(str);
}

void	ft_write_d(long n, t_params *params, int *size)
{
	char	*str;
	int		len;
	int		c;
	int		neg;
	
	len = 0;
	neg = 0;
	if (n < 0 && ++len && ++neg && ++params->precision)
		n = -n;
	str = ft_itoa(n);
	c = (params->dot && !params->precision && !n);
	len += c ? 0 : ft_strlen(str);
	if (neg && !params->dot && (params->width < len || params->zero || params->min))
		ft_putchar_fd('-', 1);
	if (!(params->min))
		ft_write_width(params, len, size);
	if (neg && (params->dot || (params->width >= len && !params->min && !params->zero)))
		ft_putchar_fd('-', 1);
	ft_write_precision(params, len, size);
	if (!c)	
		ft_putstr_fd(str, 1);
	if (params->min)
		ft_write_width(params, len, size);
	free(str);
}

void	ft_write_x(long n, t_params *params, int *size, int maj)
{
	char	*str;
	int		len;
	int		c;
	
	str = ft_itoa_base(n, 16, maj);
	c = (params->dot && !params->precision && !n);
	len = c ? 0 : ft_strlen(str);
	if (!(params->min))
		ft_write_width(params, len, size);
	ft_write_precision(params, len, size);
	if (!c)
		ft_putstr_fd(str, 1);
	if (params->min)
		ft_write_width(params, len, size);
	free(str);
}

void	ft_write_p(t_params *params, va_list args, int *size)
{
	char	*str;
	int		len;
	long 	n;	

	n = va_arg(args, long);
	len = 0;
	str = ft_itoa_base(n, 16, 0);
	if (*str == '\0')
		str = ft_strdup("0");
	len = ft_strlen(str) + 2;
	if (!(params->min))
		ft_write_width(params, len, size);
	ft_putstr_fd("0x", 1);
	ft_putstr_fd(str, 1);
	if (params->min)
		ft_write_width(params, len, size);
	free(str);
}
