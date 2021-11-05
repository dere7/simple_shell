#include <unistd.h>
#include <limits.h>
#include "main.h"

/**
 * _atoi - convert string to an integer
 * @s: string
 * Return: integer
 */
int _atoi(char *s)
{
	int i = 0, sign = 1, val = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '-')
			sign *= -1;
		else if (s[i] >= '0' && s[i] <= '9')
		{
			if (val > INT_MAX / 10 || (val == INT_MAX / 10))
			{
				return (sign == -1 ? INT_MIN : INT_MAX);
			}
			val = val * 10 + s[i] - '0';
		}
		else if (val != 0)
			break;
		i++;
	}

	return (sign * val);
}

/**
 * print_num - prints an int
 * @n: int to print
 *
 * Return: number of printed character
 */
int print_num(long n)
{
	unsigned int absolute, aux, countnum, count;

	count = 0;
	if (n < 0)
	{
		absolute = (n * -1);
		count += _putchar('-');
	}
	else
		absolute = n;

	aux = absolute;
	countnum = 1;
	while (aux > 9)
	{
		aux /= 10;
		countnum *= 10;
	}
	while (countnum >= 1)
	{
		count += _putchar(((absolute / countnum) % 10) + '0');
		countnum /= 10;
	}
	return (count);
}
/**
 * print - print str to stdout
 * @s: string to be printed
 */
void print(char *s)
{
	write(STDOUT_FILENO, s, _strlen(s));
}
/**
 * _strcpy - copies the string
 * @dest: destination string
 * @src: source string
 * Return: the pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
