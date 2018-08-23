/*************************************************************************
	> File Name: source.h
	> Author: keaidema
	> Mail: 541609206@qq.com
	> Created Time: 2018年08月23日 星期四 10时36分41秒
 ************************************************************************/

#ifndef _SOURCE_H
#define _SOURCE_H

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <errno.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <time.h>
#include <stdarg.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <signal.h>
#include <unistd.h>

#define MAXLINE 4096 

int socket_create(int port) {
    int socketfd;
    struct sockaddr_in sock_addr;
    if ((socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        perror("socket_create");
        return -1;
    }

    sock_addr.sin_family = AF_INET; 
    sock_addr.sin_port = htons(port); 
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY); 

    if (bind(socketfd, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) == -1) { 
        perror("bind");
        return -1;
    }   
    if(listen(socketfd, 10) == -1) {
        perror("listen");
        return -1;
    }
    return socketfd;
}

int socket_connect(int port, char*host) {
    int socketfd;
    struct sockaddr_in dest_addr;
    if ((socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        perror("socket_connect");
        return -1;
    }

    dest_addr.sin_family = AF_INET; 
    dest_addr.sin_port = htons(port); 
    dest_addr.sin_addr.s_addr = inet_addr(host); 
    
    if (connect(socketfd, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) == -1) { 
        perror("connect");
        return -1;
    } 
    
    return socketfd;
}

int get_con_val(char *pathname, char *key_name, char *val) {
    FILE*fp;
    char*temp;
    char arm[100];
    int flag = 0;
    if (!(fp = fopen(pathname, "r"))) perror("fopen"), exit(1);
    while (fscanf(fp, "%s", arm) != EOF) {
        if ((temp = strtok(arm, "=")) && !strcmp(temp, key_name) && !flag++) 
            strncpy(val, strtok(NULL, "="), strlen(val));
    }
    fclose(fp);
    flag ? printf("get value success: %s->%s\n", key_name, val) : printf("%s: can't get value\n", __func__);
    return flag; 
}

#endif
