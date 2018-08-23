/*************************************************************************
	> File Name: master.c
	> Author: keaidema
	> Mail: 541609206@qq.com
	> Created Time: 2018年08月23日 星期四 10时38分32秒
 ************************************************************************/

#include "source.h"

int main() {
    int port=5555;
    int socketfd, connfd;
    int n;

    if ((socketfd = socket_create(port)) == -1) {
        perror("socket_create");
        return 1;
    }
    printf("waiting for client's request\n"); 
        if ((connfd = accept(socketfd, (struct sockaddr*)NULL, NULL)) == -1) { 
        perror("accept");
        return 1;
    }

    while(1) { 
        /*
        struct sockaddr_in peer;
        socklen_t peer_len = sizeof(struct sockaddr_in);
        bzero(&peer, sizeof(struct sockaddr_in));
        getpeername(connfd, (struct sockaddr*)&peer, &peer_len);
        char buff_peer[64] = {'\0'};
        inet_ntop(AF_INET, (void*)&peer.sin_addr, buff_peer, 63);
        */
        int pid = fork();
        if (pid < 0)
            printf("Error forking child process");
        if (pid > 0) {
            char buffer[MAXLINE];
            memset(buffer, 0, sizeof(buffer));

            while ((n = recv(connfd, buffer, MAXLINE, 0)) > 0) {
                //printf("%s:%d: recv %s\n", buff_peer, ntohs(peer.sin_port), buffer);
                puts(buffer);
                fflush(stdout);
                memset(buffer, 0, sizeof(buffer));
            }
            close(connfd);
            exit(0);
        } else {
            while (1) {
                char buffer[MAXLINE];
                memset(buffer, 0, sizeof(buffer));
                scanf("%s", buffer);
                int num = send(connfd, buffer, MAXLINE, 0);
                if (num == 0) {
                    printf("Send");
                    break;
                }
            }
            close(connfd);
        }
    } 
    close(socketfd); 
}
