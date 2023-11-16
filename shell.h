#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM  0
#define CMD_OR    1
#define CMD_AND   2
#define CMD_CHAIN 3

/* for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED  2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct liststr -  singly linked list
 * @num: the number field
 * @str: the string
 * @next: leads to the next node
 */
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;
/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int err_num;
int linecount_flag;
char *fname;
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;

char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
int cmd_buf_type; /* CMD_type ||, &&, ; */
int readfd;
int histcount;
}
info_t;
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
* struct builtin - implements built-in string operations and related functions
* @type: type of the built-in command flag
* @func: describe what the function does
*/
typedef struct builtin
{
char *type;
int (*func)(info_t *);
}

builtin_table;

/* t_shell_loop.c */
int t_hsh(info_t *, char **);
int t_find_builtin(info_t *);
void t_find_cmd(info_t *);
void t_fork_cmd(info_t *);

/* t_parser.c */
int t_is_cmd(info_t *, char *);
char *t_dup_chars(char *, int, int);
char *t_find_path(info_t *, char *, char *);

/* t_loophsh.c */
int t_loophsh(char **);

/* t_errors.c */
void t_eputs(char *);
int t_eputchar(char);
int t_putfd(char c, int fd);
int t_putsfd(char *str, int fd);

/* t_string.c */
int t_strlen(char *);
int t_strcmp(char *, char *);
char *t_starts_with(const char *, const char *);
char *t_strcat(char *, char *);

/* t_string1.c */
char *t_strcpy(char *, char *);
char *t_strdup(const char *);
void t_puts(char *);
int t_putchar(char);

/* t_exits.c */
char *t_strncpy(char *, char *, int);
char *t_strncat(char *, char *, int);
char *t_strchr(char *, char);

/* t_tokenizer.c */
char **t_strtow(char *, char *);
char **t_strtow2(char *, char);

/* t_realloc.c */
char *t_memset(char *, char, unsigned int);
void t_ffree(char **);
void *t_realloc(void *, unsigned int, unsigned int);

/* t_memory.c */
int t_bfree(void **);

/* t_atoi.c */
int t_interactive(info_t *info);
int t_is_delim(char c, char *delim);
int t_isalpha(int c);
int t_atoi(char *s);

/* t_errors1.c */
int t_erratoi(char *);
void t_print_error(info_t *, char *);
int t_print_d(int, int);
char *t_convert_number(long int, int, int);
void t_remove_comments(char *);

/* t_builtin.c */
int t_myexit(info_t *info);
int t_mycd(info_t *info);
int t_myhelp(info_t *info);

/* t_builtin1.c */
int t_myhistory(info_t *info);
int t_unset_alias(info_t *info, char *str);
int t_print_alias(list_t *node);
int t_myalias(info_t *);

/*t_getline.c */
ssize_t t_get_input(info_t *);
int t_getline(info_t *, char **, size_t *);
void t_sigintHandler(int);

/* t_getinfo.c */
void t_clear_info(info_t *);
void t_set_info(info_t *, char **);
void t_free_info(info_t *, int);

/* t_environ.c */
char *t_getenv(info_t *, const char *);
int t_myenv(info_t *);
int t_mysetenv(info_t *);
int t_myunsetenv(info_t *);
int t_populate_env_list(info_t *);

/* t_getenv.c */
char **t_get_environ(info_t *);
int t_unsetenv(info_t *, char *);
int t_setenv(info_t *, char *, char *);

/* t_history.c */
char *t_get_history_file(info_t *info);
int t_write_history(info_t *info);
int t_read_history(info_t *info);
int t_build_history_list(info_t *info, char *buf, int linecount);
int t_renumber_history(info_t *info);

/* t_lists.c */
list_t *t_add_node(list_t **, const char *, int);
list_t *t_add_node_end(list_t **, const char *, int);
size_t t_print_list_str(const list_t *);
int t_delete_node_at_index(list_t **, unsigned int);
void t_free_list(list_t **);

/* t_lists1.c */
size_t t_list_len(const list_t *);
char **t_list_to_strings(list_t *);
size_t t_print_list(const list_t *);
list_t *t_node_starts_with(list_t *, char *, char);
ssize_t t_get_node_index(list_t *, list_t *);

/* t_vars.c */
int t_is_chain(info_t *, char *, size_t *);
void t_check_chain(info_t *, char *, size_t *, size_t, size_t);
int t_replace_alias(info_t *);
int t_replace_vars(info_t *);
int t_replace_string(char **, char *);

#endif
