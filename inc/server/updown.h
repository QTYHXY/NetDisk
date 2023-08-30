#ifndef _UPDOWN_H_
#define _UPDOWN_H_
// 头文件
#include <stdio.h>
#include <sys/stat.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "wrap.h"
// 宏定义
#define BUFMAX 1024
#define MAXLINE 1024
// 函数
int checkFileSize(char *fileName);
int checktype(char *fileName);
int upFile(int sockfd, char *fileName);
int downFile(int sockfd, char *fileName);
int specifiedPath(int sockfd, char *path, char *fileName);
#endif