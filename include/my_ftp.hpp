/*
** EPITECH PROJECT, 2019
** ftp server
** File description:
** hpp ftp server
*/

#ifndef _MY_FTP_H_
#define _MY_FTP_H_

#include <netdb.h>
#include <stdbool.h>

static const bool SUCCESS = true;
static const bool FAILURE = false;
static const int WRONG_ORDER = -1;
static const int CLIENT_SOCKET_SIZE = 50;
static const int BUFF_SIZE = 1024;
static const int CMD_NB = 7;
static const char NEW_CLIENT[] = "220 Service ready for new user.\r\n";
static const char CLIENT_QUIT[] = "221 Service closing control.\r\n";
static const char USR_NAME_OK[] = "331 User name okay, need password.\r\n";
static const char USR_NAME_KO[] = "530 username incorrect.\r\n";
static const char USR_PASSWD_OK[] = "230 User logged in, proceed.\r\n";
static const char BAD_INPUT_LOGIN[] = "530 Not logged in.\r\n";
static const char BAD_INPUT[] = "500 Syntax error, command unrecognized.\r\n";
static const char BAD_SEQUENCES[] = "503 Bad sequence of commands.\r\n";
static const char CMD_NOOP[] = "200 Command okay.\r\n";
static const char CMD_HELP[] = "214 Help message.\r\n";
static const char CMD_CWD_KO[] = "550 Requested action not taken.\r\n";
static const char CMD_CWD_OK[] = "250 Requested file action \
okay, completed.\r\n";
static const char SOCKET_FAILED[] = "Socket creation failed\n";
static const char BIND_FAILED[] = "Socket bind failed\n";
static const char LISTEN_FAILED[] = "Listen failed\n";
static const char ACCEPT_FAILED[] = "Server accept failed\n";
static const char SELECT_FAILED[] = "Select users or server failed\n";

typedef struct connect_s {
    int sock_fd;
    struct sockaddr_in addr;
    int conn_fd;
    int max_fd;
} connect_t;

typedef struct enter_s {
    bool authent[50];
    bool username[50];
    char anonymous[60];
    int login_exec;
} enter_t;

typedef struct cmd_s {
    char path[1024];
    char path_user[1024];
    fd_set fset;
} cmd_t;

typedef struct communicate_s {
    int client_socket[50];
    char cmd_param[2][1024];
    enter_t enter;
    cmd_t cmd;
} communicate_t;

extern int create_socket(void);
extern bool set_socket_opt(connect_t *connect);
extern bool bind_socket(connect_t *connect, char **av);
extern bool server_listening(connect_t *connect);
extern int accept_client(connect_t *connect);
extern bool handle_multi_clients(connect_t *connect,
    communicate_t *communicate);
extern void server_client_communication(connect_t *connect,
    communicate_t *communicate);
extern bool my_ftp(char **av);
extern void get_second_elem_array(char buff[], char new_buff[]);
extern void get_first_elem_array(char buff[], char new_buff[]);
extern bool user_cmd(communicate_t *communicate, int sock_cli_fd, int i);
extern bool pass_cmd(communicate_t *communicate, int sock_cli_fd, int i);
extern bool quit_cmd(communicate_t *communicate, int *sock_cli_fd, int i);
extern bool help_cmd(communicate_t *communicate, int *sock_cli_fd, int i);
extern bool noop_cmd(communicate_t *communicate, int *sock_cli_fd, int i);
extern bool cwd_cmd(communicate_t *communicate, int *sock_cli_fd, int i);
extern bool pwd_cmd(communicate_t *communicate, int *sock_cli_fd, int i);
extern bool cdup_cmd(communicate_t *communicate, int *sock_cli_fd, int i);
extern bool dele_cmd(communicate_t *communicate, int *sock_cli_fd, int i);
extern void bad_cmd(communicate_t *communicate,
    char client_msg[], int *sock_cli_fd);
extern void call_user_commands(communicate_t *communicate,
    char client_msg[], int *sock_cli_fd);
extern int check_back_slash_n_r(char buff[]);
extern void check_close_window(connect_t *connect,
    communicate_t *communicate,
    int *sock_cli_fd, int i);

#endif /* _MY_FTP_H_ */
