#include "shell.h"

/**
 * t_is_cmd - an execuatable commaned files determinese
 * @info: the info struct informationes
 * @path: pathe to the filee to be checkied
 *
 * Return: 1 if true otherwise 0
 */
int t_is_cmd(info_t *info, char *path)
{
struct stat st;
(void)info;
if (!path || stat(path, &st))
return (0);
if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}
/**
 * dup_chars - duplicatees characters in a string rangee
 * @pathstr: thee PATH string sourcee
 * @start: starting indexe duplicatee
 * @stop: stoppiing index of duplicate
 *
 * Return: new buffer pointerr
 */
char *dup_chars(char *pathstr, int start, int stop)
{
static char buf[1024];
int i = 0, k = 0;
for (k = 0, i = start; i < stop; i++)
if (pathstr[i] != ':')
buf[k++] = pathstr[i];
buf[k] = 0;
return (buf);
}
/**
 * t_find_path - finde this cmd in the PATH stringes
 * @info: the info structes
 * @pathstr: the PATH stringe
 * @cmd: the cmd to be finde
 *
 * Return: pathe of cmd if founde or NULL
 */
char *t_find_path(info_t *info, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;
if (!pathstr)
return (NULL);
if ((t_strlen(cmd) > 2) && t_starts_with(cmd, "./"))
{
if (t_is_cmd(info, cmd))
return (cmd);

}
while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = dup_chars(pathstr, curr_pos, i);
if (!*path)
t_strcat(path, cmd);

else
{
t_strcat(path, "/");
_strcat(path, cmd);
}
if (t_is_cmd(info, path))
return (path);
if (!pathstr[i])
break;
curr_pos = i;
}
i++;
}
return (NULL);
}
