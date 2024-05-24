/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:36:08 by anqabbal          #+#    #+#             */
/*   Updated: 2024/03/08 15:50:15 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	to_check(const char *format, va_list ar, int i, int count)
{
	if (*(format + i) == '%' && (*(format + i + 1) == '%'))
		count += ft__putchar_fd('%', 1);
	else if (*(format + i) == '%' && (*(format + i + 1) == 'c'))
		count += ft__putchar_fd(va_arg(ar, int), 1);
	else if (*(format + i) == '%' && (*(format + i + 1) == 's'))
		count += ft__putstr_fd(va_arg(ar, char *), 1);
	else if (*(format + i) == '%'
		&& (*(format + i + 1) == 'd' || *(format + i + 1) == 'i'))
		count += ft__putnbr_fd(va_arg(ar, int), 1);
	else if (*(format + i) == '%' && *(format + i + 1) == 'x')
		count += ft__print_hexa(va_arg(ar, unsigned int), 0);
	else if (*(format + i) == '%' && *(format + i + 1) == 'X')
		count += ft__print_hexa(va_arg(ar, unsigned int), 1);
	else if (*(format + i) == '%' && *(format + i + 1) == 'u')
		count += ft__print_unsigned(va_arg(ar, int), 1);
	else if (*(format + i) == '%' && *(format + i + 1) == 'p')
		count += ft__print_address(va_arg(ar, void *));
	else if (*(format + i) == '%')
		count += ft__putchar_fd(*(format + i + 1), 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	int		i;
	va_list	ar;

	va_start(ar, format);
	i = 0;
	count = 0;
	while (*(format + i))
	{
		if (write(1, "", 0) == -1)
			return (-1);
		if (*(format + i) == '%' && *(format + i + 1) != '\0')
			count = to_check(format, ar, i++, count);
		else if (format[i] != '%')
			count += ft__putchar_fd(*(format + i), 1);
		i++;
	}
	va_end(ar);
	return (count);
}
