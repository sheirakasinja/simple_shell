#ifndef _SHELL_H_
#define _SHELL_H_


#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>


/* for command chaining */
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for convert_number() */
#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function to
 * allow uniform prototype for function pointer struct
 * @arg: string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: string path for current command
 * @argc: argument count
 * @line_count: error count
 * @err_num: error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: history node
 * @alias: alias node
 * @env_changed: on if environ was changed
 * @status: return status of last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: fd from which to read line input
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
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: builtin command flag.
 * @func: function.
 */

typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void fork_cmd(info_t *);
void find_cmd(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);
char *dup_chars(char *, int, int);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
int _eputchar(char);
void _eputs(char *);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_copy_string.c */
char *_strchr(char *s, char c);
char *_strncat(char *dest, char *src, int n);
char *_strncpy(char *dest, char *src, int n);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);
void ffree(char **);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int interactive(info_t *);
int _atoi(char *);
int _isalpha(int);
int is_delim(char c, char *delim);

/* toem_errors1.c */
int _erratoi(char *);
int print_d(int, int);
void remove_comments(char *);
void print_error(info_t *, char *);
char *convert_number(long int, int, int);

/* toem_builtin.c */
int _myhelp(info_t *);
int _mycd(info_t *);
int _myexit(info_t *);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toem_getline.c */
void sigintHandler(__attribute__((unused))int sig_num);
int _getline(info_t *info, char **ptr, size_t *length);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
ssize_t get_input(info_t *info);
ssize_t input_buf(info_t *info, char **buf, size_t *len);
int is_chain(info_t *info, char *buf, size_t *j);


/* toem_getinfo.c */
void clear_info(info_t *);
void free_info(info_t *, int);
void set_info(info_t *, char **);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int populate_env_list(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int _myenv(info_t *);

/* toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int renumber_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
void free_list(list_t **);
int delete_node_at_index(list_t **, unsigned int);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
ssize_t get_node_index(list_t *, list_t *);
list_t *node_starts_with(list_t *, char *, char);

/* toem_variables.c */
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_vars(info_t *);
int replace_alias(info_t *);
int replace_string(char **, char *);

#endif
