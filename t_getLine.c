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
signal(SIGINT, t_sigintHandler);

#if USE_GETLINE

r = getline(buf, &len_p, stdin);

#else

r = t_getline(info, buf, &len_p);

#endif

if (r > 0)
{
if ((*buf)[r - 1] == '\n')
{
(*buf)[r - 1] = '\0'; /* remove trailing newline */
r--;
}
info->linecount_flag = 1;
t_remove_comments(*buf);
t_build_history_list(info, *buf, info->histcount++);
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
t_putchar(BUF_FLUSH);
r = t_input_buf(info, &buf, &len);
if (r == -1) /* EOF */
return (-1);
if (len) /* we have commands left in the chain buffer */
{
j = i; /* init new iterator to current buf position */
p = buf + i; /* get pointer for return */
t_check_chain(info, buf, &j, i, len);
while (j < len) /* iterate to semicolon or end */
{
if (t_is_chain(info, buf, &j))
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
return (t_strlen(p)); /* return length of current command */
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
c = t_strchr(buf + i, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = t_realloc(p, s, s ? s + k : k + 1);
if (!new_p) /* MALLOC FAILURE! */
return (p ? free(p), -1 : -1);
if (s)
t_strncat(new_p, buf + i, k - i);
else
t_strncpy(new_p, buf + i, k - i + 1);
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
t_puts("\n");
t_puts("$ ");
t_putchar(BUF_FLUSH);
}

