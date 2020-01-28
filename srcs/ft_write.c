/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 10:46:08 by yviavant          #+#    #+#             */
/*   Updated: 2020/01/28 20:42:24 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_write_c(char c, t_params *p, int *size)
{
	if (!p->min)
		ft_write_width(p, 1, size);
	ft_putchar_fd(c, 1);
	if (p->min)
		ft_write_width(p, 1, size);
}

void	ft_write_s(char *str, t_params *p, int *size)
{
	int	len;

	if (!str)
		if (!(str = ft_strdup("(null)")))
			return ;
	len = ft_strlen(str);
	p->precision = p->precision < 0 ? -p->precision : p->precision;
	len = (!p->dot || p->precision >= len) ? len : p->precision;
	if (!(str = ft_substr(str, 0, len)))
		return ;
	p->precision = 0;
	p->dot = 0;
	if (!p->min)
		ft_write_width(p, len, size);
	ft_putstr_fd(str, 1);
	if (p->min)
		ft_write_width(p, len, size);
	free(str);
}

void	ft_write_d(long n, t_params *p, int *size)
{
	char	*str;
	int		len;
	int		c;
	int		neg;

	len = 0;
	neg = 0;
	if (n < 0 && ++len && ++neg && ++p->precision)
		n = -n;
	if (!(str = ft_itoa(n)))
		return ;
	c = (p->dot && !p->precision && !n);
	len += c ? 0 : ft_strlen(str);
	if (neg && !p->dot && (p->width < len || p->zero || p->min))
		ft_putchar_fd('-', 1);
	if (!(p->min))
		ft_write_width(p, len, size);
	if (neg && (p->dot || (p->width >= len && !p->min && !p->zero)))
		ft_putchar_fd('-', 1);
	ft_write_precision(p, len, size);
	if (!c)
		ft_putstr_fd(str, 1);
	if (p->min)
		ft_write_width(p, len, size);
	free(str);
}

void	ft_write_x(long n, t_params *p, int *size, int maj)
{
	char	*str;
	int		len;
	int		c;

	if (!(str = ft_itoa_base(n, 16, maj)))
		return ;
	c = (p->dot && !p->precision && !n);
	len = c ? 0 : ft_strlen(str);
	if (!(p->min))
		ft_write_width(p, len, size);
	ft_write_precision(p, len, size);
	if (!c)
		ft_putstr_fd(str, 1);
	if (p->min)
		ft_write_width(p, len, size);
	free(str);
}

void	ft_write_p(t_params *p, va_list args, int *size)
{
	char	*str;
	int		len;
	long	n;

	n = va_arg(args, long);
	len = 0;
	if (!(str = ft_itoa_base(n, 16, 0)))
		return ;
	if (*str == '\0')
		if (!(str = ft_strdup("0")))
			return ;
	len = ft_strlen(str) + 2;
	if (!(p->min))
		ft_write_width(p, len, size);
	ft_putstr_fd("0x", 1);
	ft_putstr_fd(str, 1);
	if (p->min)
		ft_write_width(p, len, size);
	free(str);
}
