/*************************************************************************
	> File Name: client.c
	> Author: keaidema
	> Mail: 541609206@qq.com
	> Created Time: 2018年08月23日 星期四 10时32分18秒
 ************************************************************************/

#include "source.h"

int main(int argc, char** argv) {
    int port;
    char*host;
    if (argc == 1) {
        return 0;
    } else if (argc == 2) {
        host = argv[1];
        port = 6666;
    } else {
        host = argv[1];
        port = atoi(argv[2]);
    }

    int socketfd;
    if ((socketfd = socket_connect(port, host)) == -1) {
        perror("socket_connect");
        exit(1);
    } 
    char buffer[MAXLINE];
    memset(buffer, 0, sizeof(buffer));
    int pid = fork();
    if (pid > 0) {
        while (1) {
            scanf("%s", buffer);
            int n;
            if ((n = send(socketfd, buffer, strlen(buffer), 0)) == -1) {
                perror("send");
                exit(1);
            }
        }
    } else {
        while (1) {
            if ((recv(socketfd, buffer, MAXLINE, 0)) == -1) {
                perror("recv");
                exit(1);
            }
            puts(buffer);
        }
    }
    close(socketfd);
    return 0;
}
