/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaatar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:05:55 by bbaatar           #+#    #+#             */
/*   Updated: 2021/06/16 11:06:16 by bbaatar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//[min width][precision][length modifier][conversion specifier]

#include "../include/ft_printf.h"

int ft_length_nbr(int nbr)
{
	int i = 0;
	if(nbr < 0)
	{
		nbr = -nbr;
		i++;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

int ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_putnbr(int nbr)
{
	unsigned int nbr_ui;

	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = nbr * (-1);
	}
	nbr_ui = (unsigned int)nbr;
	if (nbr_ui > 9)
	{
		ft_putnbr(nbr_ui / 10);
	}
	ft_putchar(nbr_ui % 10 + '0');
}

void ft_putnbr_short(short nbr)
{
	unsigned short nbr_us;

	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = nbr * (-1);
	}
	nbr_us = (unsigned short)nbr;
	if (nbr_us > 9)
	{
		ft_putnbr(nbr_us / 10);
	}
	ft_putchar(nbr_us % 10 + '0');
}

void ft_putnbr_char(signed char nbr)
{
	signed char nbr_ch;

	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = nbr * (-1);
	}
	nbr_ch = (unsigned char)nbr;
	if (nbr_ch > 9)
	{
		ft_putnbr(nbr_ch / 10);
	}
	ft_putchar(nbr_ch % 10 + '0');
}

void	ft_putnbr_oct(long long nbr)
{
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr = -nbr;
	}
	if (nbr >= 8)
		ft_putnbr_oct(nbr / 8);
	ft_putchar("01234567"[nbr % 8]);
}

void ft_putstr(char *s)
{
	int i;

	i = 0;
	if (!s)
		return;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
}

void print_val_di(struct s_format *format, va_list a_list)
{
	char buff[100];
	int nbr;
	int i;
	int max;
	int len;

	if (format->precision == -1)
		format->precision = 0;
	char temp_p[format->precision];
	memset(buff, ' ', 100 * sizeof(char));
	memset(buff + (100 - 1 - format->precision), '0', format->precision * sizeof(char));
	buff[99] = 0;
	i = 98;
	nbr = va_arg(a_list, int);
	len = ft_length_nbr(nbr);
	while(nbr > 0)
	{
		buff[i] = nbr % 10 + '0';
		nbr /= 10;
		i--;
	}
	max = ft_max(ft_max(format->width, sizeof(temp_p)), len);
	ft_putstr(&buff[100 - 1 - max]);
}

void print_val_hhdi(struct s_format *format, va_list a_list)
{
	int precision;
	char buff[100];
	signed char nbr;
	int i;
	int max;
	int len;
	int negative;

	negative = 0;
	if (format->precision == -1)
		precision = 0;
	else 
		precision = format->precision;
	char temp_p[precision];
	memset(buff, ' ', 100 * sizeof(char));
	memset(buff + (100 - 1 - precision), '0', precision * sizeof(char));
	buff[99] = 0;
	i = 98;
	nbr = va_arg(a_list, int);
	len = ft_length_nbr(nbr);
	if (nbr < 0)
	{
		nbr = -nbr;
		negative = 1;
	}
	while(nbr > 0)
	{
		buff[i] = nbr % 10 + '0';
		nbr /= 10;
		i--;
	}
	max = ft_max(ft_max(format->width, sizeof(temp_p)), len);
	if(negative)
		memset(buff + (100 - 1 - len), '-', sizeof(char));
	ft_putstr(&buff[100 - 1 - max]);

}

void print_val_hdi(struct s_format *format, va_list a_list)
{
	int precision;
	char buff[100];
	short nbr;
	int i;
	int max;
	int len;

	if (format->precision == -1)
		precision = 0;
	else 
		precision = format->precision;
	char temp_p[precision];
	memset(buff, ' ', 100 * sizeof(char));
	memset(buff + (100 - 1 - precision), '0', precision * sizeof(char));
	buff[99] = 0;
	i = 98;
	nbr = va_arg(a_list, int);
	len = ft_length_nbr(nbr);
	while(nbr > 0)
	{
		buff[i] = nbr % 10 + '0';
		nbr /= 10;
		i--;
	}
	max = ft_max(ft_max(format->width, sizeof(temp_p)), len);
	ft_putstr(&buff[100 - 1 - max]);
}

void initialize_format(struct s_format *format)
{
	format->minus = 0;
	format->plus = 0;
	format->space = 0;
	format->zero = 0;
	format->apostrophe = 0;
	format->hash = 0;
	format->width = 0;
	format->width_digit = 0;
	format->precision = -1;
	format->precision_digit = 0;
	format->length = 0;
	format->length_digit = 0;
	format->specifier = 0;
}

int detect_width(char *str, struct s_format *format)
{
	int i;
	int nbr;

	i = 0;
	nbr = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	format->width = nbr;
	format->width_digit = i;
	return (format->width);
}

int detect_precision(char *str, struct s_format *format)
{
	int i;
	int nbr;

	i = 0;
	nbr = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	format->precision = nbr;
	format->precision_digit = i;
	return (format->precision);
}

int detect_length(char *str, struct s_format *format)
{
	int i;

	i = 0;
	if (str[i] == 'h')
	{
		i++;
		if (str[i] == 'h')
		{
			format->length = 2;
			format->length_digit = 2;
		}
		else
		{
			format->length = 1;
			format->length_digit = 1;
		}
	}
	else if (str[i] == 'l')
	{
		if (str[i++] == 'l')
			format->length = 4;
		format->length = 3;
	}	
	else if (str[i] == 'j')
		format->length = 5;
	else if (str[i] == 't')
		format->length = 6;
	else if (str[i] == 'z')
		format->length = 7;
	else if (str[i] == 'q')
		format->length = 8;
	else
		return (0);
	return (1);
}

int detect_specifier(char *str, struct s_format *format)
{
	int i;

	i = 0;
	if (str[i] == 'd' || str[i] == 'i')
	{
		format->specifier = 1;
	}
	else if (str[i] == 'o')
		format->specifier = 2;
	else if (str[i] == 'u')
		format->specifier = 3;
	else if (str[i] == 'x')
		format->specifier = 4;
	else if (str[i] == 'X')
		format->specifier = 5;
	else if (str[i] == 'D' || str[i] == 'O' || str[i] == 'U')
		format->specifier = 6;
	else if (str[i] == 'e' || str[i] == 'E')
		format->specifier = 7;
	else if (str[i] == 'f' || str[i] == 'F')
		format->specifier = 8;
	else if (str[i] == 'g' || str[i] == 'G')
		format->specifier = 9;
	else if (str[i] == 'a' || str[i] == 'A')
		format->specifier = 10;
	else if (str[i] == 'C')
		format->specifier = 11;
	else if (str[i] == 'c')
		format->specifier = 12;
	else if (str[i] == 'S')
		format->specifier = 13;
	else if (str[i] == 's')
		format->specifier = 14;
	else if (str[i] == 'p')
		format->specifier = 15;
	else if (str[i] == 'n')
		format->specifier = 16;
	else if (str[i] == '%')
		format->specifier = 17;
	else
		return (0);
	return (1);
}

void print_val(struct s_format *format, va_list a_list)
{
	if (format->length == 0)
	{
		if (format->specifier == 1)
		{
			print_val_di(format, a_list);
		}
		else if (format->specifier == 2 || format->specifier == 3 || \
		format->specifier == 4 || format->specifier == 5)
		{
			// print_val_ouxX(&format, a_list);
		}
		else if (format->specifier == 16)
		{
			// print_val_n(&format, a_list);
		}
	}
	if (format->length == 1)
	{
		if (format->specifier == 1)
		{
			// printf("here");
			print_val_hdi(format, a_list);
		}
		else if (format->specifier == 2 || format->specifier == 3 || \
		format->specifier == 4 || format->specifier == 5)
		{
			// print_val_hhouxX(&format, a_list);
		}
		else if (format->specifier == 16)
		{
			// print_val_hhn(&format, a_list);
		}
	}
	if (format->length == 2)
	{
		if (format->specifier == 1)
		{
			// printf("here");
			print_val_hhdi(format, a_list);
		}
		else if (format->specifier == 2 || format->specifier == 3 || \
		format->specifier == 4 || format->specifier == 5)
		{
			// print_val_hhouxX(&format, a_list);
		}
		else if (format->specifier == 16)
		{
			// print_val_hhn(&format, a_list);
		}
	}
}

int ft_printf(const char *input, ...)
{
	int i;
	int k;
	char *flag_res;
	va_list a_list;
	struct s_format format;

	initialize_format(&format);
	flag_res = (char *)malloc(100);
	if (!flag_res)
		return (-1);
	va_start(a_list, input);
	i = 0;
	k = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '%')
		{
			i++;
			if (detect_width((char *)&input[i], &format) != 0)
			{
				i += format.width_digit;
			}
			if(input[i] == '.')
			{
				i++;
				detect_precision((char *)&input[i], &format);
				i += format.precision_digit;
			}
			if (detect_length((char *)&input[i], &format) != 0)
			{
				i += format.length_digit;
			}
			if (detect_specifier((char *)&input[i], &format) != 0)
			{
				// i++;
			}
			print_val(&format, a_list);
		}
		else
		{
			write(1, (const void *)&input[i], 1);
			k++;
		}
		i++;
	}
	va_end(a_list);
	return (0);
}

int main()
{
	// printf("Standard output : |%1.2hhd|\n", (signed char)100);
	// ft_printf("   My function  : |%1.2hhd|\n", (signed char)100);

	// ft_printf("--------------------%%hhd-et-%%hhi--------------------\n");	//perfect
	// printf("01) Vrai PRINTF : |%hhd|\n", (char)42);
	// ft_printf("01) Mon PRINTF  : |%hhd|\n", (char)42);
	// printf("02) Vrai PRINTF : |%hhi|\n", (char)42);
	// ft_printf("02) Mon PRINTF  : |%hhi|\n", (char)42);
	printf("03) Vrai PRINTF : |%+hhd|\n", (char)42);
	ft_printf("03) Mon PRINTF  : |%+hhd|\n", (char)42);
	// printf("04) Vrai PRINTF : |%-hhd|\n", (char)42);
	// ft_printf("04) Mon PRINTF  : |%-hhd|\n", (char)42);
	// printf("05) Vrai PRINTF : |%10hhd|\n", (char)100);
	// ft_printf("05) Mon PRINTF  : |%10hhd|\n", (char)100);
	// printf("06) Vrai PRINTF : |%-10hhd|\n", (char)64);
	// ft_printf("06) Mon PRINTF  : |%-10hhd|\n", (char)64);
	// printf("07) Vrai PRINTF : |%.10hhd|\n", (char)100);
	// ft_printf("07) Mon PRINTF  : |%.10hhd|\n", (char)100);
	// printf("08) Vrai PRINTF : |%10.5hhd|\n", (char)100);
	// ft_printf("08) Mon PRINTF  : |%10.5hhd|\n", (char)100);
	// printf("09) Vrai PRINTF : |%5.10hhd|\n", (char)64);
	// ft_printf("09) Mon PRINTF  : |%5.10hhd|\n", (char)64);
	// printf("10) Vrai PRINTF : |%1.1hhd|\n", (char)16);
	// ft_printf("10) Mon PRINTF  : |%1.1hhd|\n", (char)16);
	// printf("11) Vrai PRINTF : |%+10hhd|\n", (char)50);
	// ft_printf("11) Mon PRINTF  : |%+10hhd|\n", (char)50);
	// printf("12) Vrai PRINTF : |%+2hhd|\n", (char)50);
	// ft_printf("12) Mon PRINTF  : |%+2hhd|\n", (char)50);
	// printf("13) Vrai PRINTF : |%+.10hhd|\n", (char)50);
	// ft_printf("13) Mon PRINTF  : |%+.10hhd|\n", (char)50);
	// printf("14) Vrai PRINTF : |%+.2hhd|\n", (char)50);
	// ft_printf("14) Mon PRINTF  : |%+.2hhd|\n", (char)50);
	// printf("15) Vrai PRINTF : |%          hhd|\n", (char)1);
	// ft_printf("15) Mon PRINTF  : |%          hhd|\n", (char)1);
	// printf("16) Vrai PRINTF : |% -hhd|\n", (char)1);
	// ft_printf("16) Mon PRINTF  : |% -hhd|\n", (char)1);
	// printf("17) Vrai PRINTF : |%-+hhd|\n", (char)32);
	// ft_printf("17) Mon PRINTF  : |%-+hhd|\n", (char)32);
	// printf("18) Vrai PRINTF : |%+-hhd|\n", (char)32);
	// ft_printf("18) Mon PRINTF  : |%+-hhd|\n", (char)32);
	// printf("19) Vrai PRINTF : |%-+10hhd|\n", (char)42);
	// ft_printf("19) Mon PRINTF  : |%-+10hhd|\n", (char)42);
	// printf("20) Vrai PRINTF : |%-+.10hhd|\n", (char)42);
	// ft_printf("20) Mon PRINTF  : |%-+.10hhd|\n", (char)42);
	// printf("21) Vrai PRINTF : |%hhd|\n", (char)-42);
	// ft_printf("21) Mon PRINTF  : |%hhd|\n", (char)-42);
	// printf("22) Vrai PRINTF : |%10hhd|\n", (char)-42);
	// ft_printf("22) Mon PRINTF  : |%10hhd|\n", (char)-42);
	// printf("23) Vrai PRINTF : |%.10hhd|\n", (char)-42);
	// ft_printf("23) Mon PRINTF  : |%.10hhd|\n", (char)-42);
	// printf("24) Vrai PRINTF : |%+hhd|\n", (char)-10);
	// ft_printf("24) Mon PRINTF  : |%+hhd|\n", (char)-10);
	// printf("25) Vrai PRINTF : |%10.5hhd|\n", (char)-16);
	// ft_printf("25) Mon PRINTF  : |%10.5hhd|\n", (char)-16);
	// printf("26) Vrai PRINTF : |%5.10hhd|\n", (char)-16);
	// ft_printf("26) Mon PRINTF  : |%5.10hhd|\n", (char)-16);
	// printf("27) Vrai PRINTF : |%1.1hhd|\n", (char)-20);
	// ft_printf("27) Mon PRINTF  : |%1.1hhd|\n", (char)-20);
	// printf("28) Vrai PRINTF : |%-10hhd|\n", (char)-50);
	// ft_printf("29) Mon PRINTF  : |%-10hhd|\n", (char)-50);
	// printf("30) Vrai PRINTF : |%++++++++++hhd|\n", (char)69);
	// ft_printf("30) Mon PRINTF  : |%++++++++++hhd|\n", (char)69);
	// printf("31) Vrai PRINTF : |%+10hhd|\n", (char)-64);
	// ft_printf("31) Mon PRINTF  : |%+10hhd|\n", (char)-64);
	// printf("32) Vrai PRINTF : |%+.10hhd|\n", (char)-64);
	// ft_printf("32) Mon PRINTF  : |%+.10hhd|\n", (char)-64);
	// printf("33) Vrai PRINTF : |%2hhd|\n", (char)-20);
	// ft_printf("33) Mon PRINTF  : |%2hhd|\n", (char)-20);
	// printf("34) Vrai PRINTF : |%.2hhd|\n", (char)-20);
	// ft_printf("34) Mon PRINTF  : |%.2hhd|\n", (char)-20);
	// printf("35) Vrai PRINTF : |%2hhd|\n", (char)-1);
	// ft_printf("35) Mon PRINTF  : |%2hhd|\n", (char)-1);
	// printf("36) Vrai PRINTF : |%.2hhd|\n", (char)-1);
	// ft_printf("36) Mon PRINTF  : |%.2hhd|\n", (char)-1);
	// printf("37) Vrai PRINTF : |%-10hhd|\n", (char)-80);
	// ft_printf("37) Mon PRINTF  : |%-10hhd|\n", (char)-80);
	// printf("38) Vrai PRINTF : |%-.10hhd|\n", (char)-80);
	// ft_printf("38) Mon PRINTF  : |%-.10hhd|\n", (char)-80);
	// printf("39) Vrai PRINTF : |%06hhd|\n", (char)35);
	// ft_printf("39) Mon PRINTF  : |%06hhd|\n", (char)35);
	// printf("40) Vrai PRINTF : |%06hhd|\n", (char)-35);
	// ft_printf("40) Mon PRINTF  : |%06hhd|\n", (char)-35);
	// printf("41) Vrai PRINTF : |%-+10hhd|\n", (char)-40);
	// ft_printf("41) Mon PRINTF  : |%-+10hhd|\n", (char)-40);
	// printf("42) Vrai PRINTF : |%+-10hhd|\n", (char)-40);
	// ft_printf("42) Mon PRINTF  : |%+-10hhd|\n", (char)-40);
	// printf("43) Vrai PRINTF : |%05.3hhd|\n", (char)5);
	// ft_printf("43) Mon PRINTF  : |%05.3hhd|\n", (char)5);
	// printf("44) Vrai PRINTF : |%03.5hhd|\n", (char)5);
	// ft_printf("44) Vrai PRINTF : |%03.5hhd|\n", (char)5);
	// printf("45) Vrai PRINTF : |%05.3hhd|\n", (char)-5);
	// ft_printf("45) Mon PRINTF  : |%05.3hhd|\n", (char)-5);
	// printf("46) Vrai PRINTF : |%03.5hhd|\n", (char)-5);
	// ft_printf("46) Mon PRINTF  : |%03.5hhd|\n", (char)-5);
	// printf("47) Vrai PRINTF : |%hhd| |%hhd|\n", (char)127, (char)-128);
	// ft_printf("47) Mon PRINTF  : |%hhd| |%hhd|\n", (char)127, (char)-128);
	// printf("48) Vrai PRINTF : |%hhd| |%hhd|\n", (char)128, (char)-129);
	// ft_printf("48) Mon PRINTF  : |%hhd| |%hhd|\n", (char)128, (char)-129);
	// printf("49) Vrai PRINTF : |%.hhd|\n", (char)0);
	// ft_printf("49) Mon PRINTF  : |%.hhd|\n", (char)0);
	// printf("50) Vrai PRINTF : |%.hhd|\n", (char)100);
	// ft_printf("50) Mon PRINTF  : |%.hhd|\n", (char)100);
	
	return 0;
}