# NWP_myftp_2018
Second year project in C++ in which the goal is to create a FTP server. It implements request sequences that are explained in the protocol RFC959. The network communication is achieved through the use of TCP sockets.The server MUST be able to handle several clients at the same time and have an authentification/register protal.

USAGE: ./myftp port path.

port is the port number on which the server socket listens path is the path to the home directory for the Anonymous user.
