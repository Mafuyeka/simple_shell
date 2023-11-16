#include "shell.h"

/**
 * t_get_history_file -  the hiistory file
 * @info: parameteer struct
 *
 * Return: allocatee strings containg history fiile
 */

char *t_get_history_file(info_t *info)
{
char *buf, *dir;
dir = t_getenv(info, "HOME=");
if (!dir)
return (NULL);

buf = malloc(sizeof(char) * (t_strlen(dir) + t_strlen(HIST_FILE) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
t_strcpy(buf, dir);
t_strcat(buf, "/");
t_strcat(buf, HIST_FILE);
return (buf);
}
/**
 * t_write_history - creates a file and appeends to an existiing files
 * @info: the parameeter structs
 *
 * Return: 1 on succeses, elsee -1
 */
int t_write_history(info_t *info)
{
ssize_t fd;
char *filename = t_get_history_file(info);
list_t *node = NULL;
if (!filename)
return (-1);
fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);
for (node = info->history; node; node = node->next)
{
t_putsfd(node->str, fd);
t_putfd('\n', fd);
}
t_putfd(BUF_FLUSH, fd);
close(fd);
return (1);
}
/**
 * t_read_history - reaads historry from filee
 * @info: the parameteer structs
 *
 * Return: histcouunt on succeess, 0 otherwise
 */
int t_read_history(info_t *info)
{
int i, last = 0, linecount = 0;

ssize_t fd, rdlen, fsize = 0;
struct stat st;
char *buf = NULL, *filename = t_get_history_file(info);
if (!filename)
return (0);
fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
return (0);
rdlen = read(fd, buf, fsize);
buf[fsize] = 0;
if (rdlen <= 0)
return (free(buf), 0);
close(fd);
for (i = 0; i < fsize; i++)
if (buf[i] == '\n')
{
buf[i] = 0;
t_build_history_list(info, buf + last, linecount++);
last = i + 1;
}
if (last != i)
t_build_history_list(info, buf + last, linecount++);
free(buf);
info->histcount = linecount;
while (info->histcount-- >= HIST_MAX)
t_delete_node_at_index(&(info->history), 0);
t_renumber_history(info);
return (info->histcount);
}
/**
 * t_build_history_list - entrry to a hiistory linked list addeed
 * @info: structure  araguments for prototypee
 * @buf: buffer struc
 * @linecount: thee historry linecount, histcouunt
 *
 * Return: 0 Always
 */
int t_build_history_list(info_t *info, char *buf, int linecount)
{
list_t *node = NULL;
if (info->history)
node = info->history;
t_add_node_end(&node, buf, linecount);
if (!info->history)
info->history = node;
return (0);
}
/**
 * t_renumber_history - renumbeers the history linked list afteer changees
 * @info: Struacture conotaining potential araguments. Used to maintain
 *
 * Return: the neew histcounnt
 */
int t_renumber_history(info_t *info)
{
list_t *node = info->history;
int i = 0;
while (node)
{
node->num = i++;
node = node->next;
}
return (info->histcount = i);
}
