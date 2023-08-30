#ifndef _CLIENTSEND_H_
#define _CLIENTSEND_H_
// 头文件
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "wrap.h"
// 宏定义
#define MAXLINE 1024
#define BUFMAX 1024
#define SERV_PORT 9527
// 函数
int CsendInfo(int sockfd, char *account, char *password, int num);
int CsendFileName(int sockfd, char *fileName, int num);
int CsendUpDown(int sockfd, int num);
const char *getFileName(const char *path);
int CsendSFile(int sockfd, int num);
#endif