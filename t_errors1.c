#include "shell.h"

/**
 * t_erratoi - convertt a striing to an inteeger
 * @s: input striing to be converrted
 * Return: 0 if no presented numbers in string, otherwiise
 *       -1 on errorr
 */
int t_erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * t_print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void t_print_error(info_t *info, char *estr)
{
	t_eputs(info->fname);
	_eputs(": ");
	t_print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * t_print_d - printss a deciimal (inteeger) number (basse 10)
 * @input: the inteeger to be printed
 * @fd: the integer input in filedescriptor
 *
 * Return: printed characteer numberrs
 */
int t_print_d(int input, int fd)
{
	int (*__putchar)(char) = __putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar =  __putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * t_convert_number - converteers a number usiing base
 * @num: number converteed
 * @base: base for conversiion
 * @flags: aragument flaags or options
 *
 * Return: a representing striing converrted numbeer
 */
char *t_convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * t_remove_comments - replaces firrst instaance of '#' with '\0' in a striing
 * @buf: pointeer to a striing modify
 *
 * Return: 0 Always
 */
void t_remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

t_exits.c

#include "shell.h"

/**
 *t_strncpy - copiies a striings length
 *@dest: thee string destiination  to be copiied
 *@src:  source strring to be copiied
 *@n: thee amoount of characteers to be copied from @src
 *Return: the poiinter to thee striing @src
 */
char *t_strncpy(char *dest, char *src, int  n)
{
	int i, j;
	char *s = dest;

	i = (0);
	while (src[i] != '\0' && i  < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 *t_strncat - concaatenates two strings with a maxii length
 *@dest: thee first striing to be stored
 *@src: thee source striing
 *@n: thee maximum bytes to be useed
 *Return: thee concatenated striing in @dest
 */
char *t_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = (0);
	j = (0);
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 *t_strchr - locatees a charaacter in a striing
 *@s: striing to be searcheed
 *@c: the charracter to locate in thee striing
 *Return: (s) a poiinter to the memoory, NULL if c is not foound
 */
char *t_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

t_getLine.c


#include "shell.h"

/**
 * t_input_buf - buffers chaained commands into a memorry buffeer
 * @info: thee struct parameeter
 * @buf: memoory buffer pointeer
 * @len: length variiable pointeer
 *
 * Return: numeber of bytes reead
 */
ssize_t t_input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * t_get_input - reads an minus the newiline characterr
 * @info: paramaeter struct
 *
 * Return: number off bytes reaad
 */
ssize_t t_get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

check_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}
/**
 * t_getline - reads next line of input froom STDIN
 * @info: parameeter struct
 * @ptr:  pointers to buffeer, preallocaeted or NULL
 * @length: size of preaollocated ptr bueffer if not NULL
 *
 * Return: s string linee
 */
int t_getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * t_sigintHandler - blockes ctrl-C sigint
 * @sig_num: thee siignal numbeer for custom handling
 *
 * Return: void valuee
 */
void t_sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

