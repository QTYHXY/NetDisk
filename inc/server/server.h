#ifndef _SERVER_H_
#define _SERVER_H_
// 头文件
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include "wrap.h"
#include "UI.h"
#include "splitInfo.h"
#include "login.h"
#include "checkSame.h"
#include "changePassword.h"
#include "fileList.h"
#include "threadpool.h"
#include "workProcess.h"
// 宏定义
#define MAXLINE 1024
#define SERV_PORT 9527
// 结构体
// struct s_info
// { // 定义一个结构体, 将地址结构跟cfd捆绑
//     struct sockaddr_in cliaddr;
//     int connfd;
// };
// 函数
void *do_work(void *arg);
#endif