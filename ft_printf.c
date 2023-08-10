#include <limits.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		count++;
		str++;
	}
	return (count);
}

int	ft_putstr(char *str)
{
	int	len;

	len = 0;
	if (!str)
		str = "(null)";
	while (*str)
	{
		write(1, str++, 1);
		len++;
	}
	return (len);
}

int	ft_atoi(char *str)
{
	int	num;
	int	sum;
	int	len;
	int	sign;

	sign = 1;
	len = ft_strlen(str);
	num = 10 * len;
	sum = num;
	if (*str && *str == '+')
		str++;
	else if (*str && *str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str)
	{
		num += sum * (*str - '0');
		sum /= 10;
		str++;
	}
	return (sign * num);
}

int	ft_putdigit(long number, int base_len, int len)
{
	char	*base;

	base = "0123456789abcdef";
	if (number < 0)
	{
		number *= -1;
		len += write(1, "-", 1);
	}
	if (number >= base_len)
		len = ft_putdigit((number / (long)base_len), base_len, len);
	len += write(1, &base[number % base_len], 1);
	return (len);
}

int	ft_printf(char *fmt, ...)
{
	va_list	ap;
	char	*s;
	int		len;
	long	d;

	len = 0;
	va_start(ap, fmt);
	while (*fmt)
	{
		if (*fmt && *fmt == '%' && fmt[1] && fmt[1] == 's')
		{
			fmt++;
			s = va_arg(ap, char *);
			len += ft_putstr(s);
		}
		else if (*fmt && *fmt == '%' && fmt[1] && fmt[1] == 'd')
		{
			fmt++;
			d = (long)va_arg(ap, int);
			len += ft_putdigit(d, 10, 0);
		}
		else if (*fmt && *fmt == '%' && fmt[1] && fmt[1] == 'x')
		{
			fmt++;
			d = (long)va_arg(ap, unsigned int);
			len += ft_putdigit(d, 16, 0);
		}
		else if (*fmt && *fmt == '%' && fmt[1] && fmt[1] == '%')
		{
			fmt++;
			len += write(1, fmt, 1);
		}
		else if (*fmt)
			len += write(1, fmt, 1);
		fmt++;
	}
	va_end(ap);
	return (len);
}

// int	main(void)
// {
// 	ft_printf("123%s789%d\n", "456", 123456789);
// 	ft_printf("123%s789%x\n", "456", 123456789);
// 	ft_printf("123%s789%d\n", "456", INT32_MAX);
// 	ft_printf("123%s789%d\n", "456", INT32_MIN);
// 	ft_printf("123%s789%x\n", "456", INT32_MAX);
// 	ft_printf("123%s789%x\n", "456", INT32_MIN);
// 	ft_printf("123%%789\n");
// 	ft_printf("123%%%s789\n", "456");
// 	ft_printf("123%%%%789%s\n", "456");
// 	ft_printf("123789%s", "456");
// 	ft_printf("\n");

// 	printf("123%s789%d\n", "456", 123456789);
// 	printf("123%s789%x\n", "456", 123456789);
// 	printf("123%s789%d\n", "456", INT32_MAX);
// 	printf("123%s789%d\n", "456", INT32_MIN);
// 	printf("123%s789%x\n", "456", INT32_MAX);
// 	printf("123%s789%x\n", "456", INT32_MIN);
// 	printf("123%%789\n");
// 	printf("123%%%s789\n", "456");
// 	printf("123%%%%789%s\n", "456");
// 	printf("123789%s", "456");
// 	printf("\n");
// 	return (1);
// }