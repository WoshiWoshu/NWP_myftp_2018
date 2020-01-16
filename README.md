# NWP_myftp_2018
Second year project in C in which the goal is to create a FTP server. It implements request sequences that are explained in the protocol RFC959. The network communication is achieved through the use of TCP sockets. The server handle several clients at the same time and have an authentification/register protal.

USAGE: ./myftp port path.

port is the port number on which the server socket listens path is the path to the home directory for the Anonymous user.

Here are the lists of commands :

            USER <SP> <username> <CRLF>   : Specify user for authentication
            
            PASS <SP> <password> <CRLF>   : Specify password for authentication

            CWD  <SP> <pathname> <CRLF>   : Change working directory
            CDUP <CRLF>                   : Change working directory to parent directory

            QUIT <CRLF>                   : Disconnection

            DELE <SP> <pathname> <CRLF>   : Delete file on the server

            PWD  <CRLF>                   : Print working directory

            PASV <CRLF>                   : Enable "passive" mode for data transfer

            PORT <SP> <host-port> <CRLF>  : Enable "active" mode for data transfer


            HELP [<SP> <string>] <CRLF>   : List available commands

            NOOP <CRLF>                   : Do nothing

            (the following are commands using data transfer )

            RETR <SP> <pathname> <CRLF>   : Download file from server to client
            STOR <SP> <pathname> <CRLF>   : Upload file from client to server
            LIST [<SP> <pathname>] <CRLF> : List files in the current working directory 
