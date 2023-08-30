#ifndef _PROCESS_H_
#define _PROCESS_H_
// 头文件
#include <stdio.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "wrap.h"
#include "UI.h"
#include "splitInfo.h"
#include "login.h"
#include "checkSame.h"
#include "changePassword.h"
#include "fileList.h"
#include "threadpool.h"
#include "updown.h"
// 宏定义
#define MAXLINE 1024
#define SERV_PORT 9527
// 结构体
struct s_info
{ // 定义一个结构体, 将地址结构跟cfd捆绑
    struct sockaddr_in cliaddr;
    threadpool_t *threadpool;
    int connfd;
    int chooseNum;
    char account[12];
    char password[12];
};
// 函数
void *do_work(void *arg);
void *mainProcess(void *info);
void *userProcess(void *info);
#endif