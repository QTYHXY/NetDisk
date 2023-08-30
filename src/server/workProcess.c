#include "workProcess.h"
char receiveInfo[30];
char singleAccount[MAX_CANON];
char singlePassword[MAX_CANON];

void *mainProcess(void *info)
{
    int chooseNum;
    pthread_detach(pthread_self()); // 子线程分离,防止僵线程产生.
    int n, i, ret;
    struct s_info *ts = (struct s_info *)info;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN]; // #define INET_ADDRSTRLEN 16  可用"[+d"查看
    while (1)
    {
        bzero(buf, sizeof(buf));
        n = Read(ts->connfd, buf, MAXLINE); // 读客户端
        if (n == 0)
        {
            printf("客户端%d已关闭...\n", ts->connfd - 3);
            break; // 跳出循环,关闭cfd
        }
        printf("收到来自IP为%s端口号为%d的消息\n",
               inet_ntop(AF_INET, &(*ts).cliaddr.sin_addr, str, sizeof(str)),
               ntohs((*ts).cliaddr.sin_port)); // 打印客户端信息(IP/PORT)
        bzero(receiveInfo, sizeof(receiveInfo));
        strcpy(receiveInfo, buf);
        printf("receiveInfo=%s\n", receiveInfo);
        splitInfo(receiveInfo, &chooseNum, singleAccount, singlePassword);
        printf("chooseNum=%d\n", chooseNum);
        printf("singleAccount=%s\n", singleAccount);
        printf("singlePassword=%s\n", singlePassword);
        if (chooseNum == 1)
        {
            siglelist *infoListLogin = list_init();

            ret = login(singleAccount, singlePassword, infoListLogin);
            if (ret == 0)
            {
                char retbuf[20] = "notfound info";
                Write(ts->connfd, retbuf, sizeof(retbuf)); // 回写给客户端
            }
            else if (ret == 1)
            {
                char retbuf[30] = "accout or password error";
                Write(ts->connfd, retbuf, sizeof(retbuf)); // 回写给客户端
            }
            else if (ret == 2)
            {
                char retbuf[10] = "success";
                Write(ts->connfd, retbuf, sizeof(retbuf)); // 回写给客户端
            }
            else if (ret == 3)
            {
                char retbuf[20] = "infofile loss";
                Write(ts->connfd, retbuf, sizeof(retbuf)); // 回写给客户端
            }
        }
        if (chooseNum == 2)
        {
            siglelist *infoListregister = list_init();
            // 注册
            ret = checkInfo(infoListregister, singleAccount, singlePassword);
            if (ret == 2)
            {
                char retbuf[20] = "register success";
                Write(ts->connfd, retbuf, sizeof(retbuf)); // 回写给客户端
            }
            else if (ret == 5)
            {
                char retbuf[20] = "account exist";
                Write(ts->connfd, retbuf, sizeof(retbuf)); // 回写给客户端
            }
        }
        if (chooseNum == 5)
        {
            siglelist *infoListchange = list_init();
            ret = changePassword(infoListchange, singleAccount, singlePassword);
            if (ret == 2)
            {
                char retbuf[20] = "success";
                Write(ts->connfd, retbuf, sizeof(retbuf)); // 回写给客户端
                list_uninit(infoListchange);
            }
            else if (ret == 6)
            {
                char retbuf[20] = "notfound info";
                Write(ts->connfd, retbuf, sizeof(retbuf)); // 回写给客户端
                list_uninit(infoListchange);
            }
        }
        if (chooseNum == 7)
        {
            showFileList(ts->connfd, singleAccount);
        }
        if (chooseNum == 9)
        {
            // 文件上传
            ret = upFile(ts->connfd, singleAccount);
            if (ret == 1)
            {
                char retbuf[20] = "file success";
                // Write(ts->connfd, retbuf, sizeof(retbuf)); // 回写给客户端
            }
            else
            {
                char retbuf[15] = "updown error";
                Write(ts->connfd, retbuf, sizeof(retbuf)); // 回写给客户端
            }
        }
        if (chooseNum == 10)
        {
            ret = downFile(ts->connfd, singleAccount);
            if (ret == 1)
            {
                char retbuf[20] = "file success";
                // Write(ts->connfd, retbuf, sizeof(retbuf)); // 回写给客户端
            }
            else
            {
                char retbuf[15] = "updown error";
                Write(ts->connfd, retbuf, sizeof(retbuf)); // 回写给客户端
            }
        }
        if (chooseNum == 11)
        {
            specifiedPath(ts->connfd, singleAccount, singlePassword);
        }
    }

    Close(ts->connfd);
    printf("关闭套接字了！！！！！\n");
    pthread_exit(NULL);
}

//  void *userProcess(void *info)
// {
//     pthread_detach(pthread_self()); // 子线程分离,防止僵线程产生.
//     int n, i, ret;
//     struct s_info *ts = (struct s_info *)info;
//     char buf[MAXLINE];
//     char str[INET_ADDRSTRLEN];
//     while (1)
//     {
//         n = Read(ts->connfd, buf, MAXLINE); // 读客户端
//         if (n == 0)
//         {
//             printf("客户端%d已关闭...\n", ts->connfd - 3);
//             break; // 跳出循环,关闭cfd
//         }
//         printf("收到来自IP为%s端口号为%d的消息\n",
//                inet_ntop(AF_INET, &(*ts).cliaddr.sin_addr, str, sizeof(str)),
//                ntohs((*ts).cliaddr.sin_port)); // 打印客户端信息(IP/PORT)
//         bzero(receiveInfo, sizeof(receiveInfo));
//         strcpy(receiveInfo, buf);
//         // Write(STDOUT_FILENO, buf, n); // 写出至屏幕
//         // printf("\n");
//         // Write(ts->connfd, buf, n);    // 回写给客户端
//         scanf("%d", &chooseNum);
//         // printf("receiveInfo=%s\n", receiveInfo);
//         splitInfo(receiveInfo, &chooseNum, singleAccount, singlePassword);
//         scanf("%d", &chooseNum);
//         printf("chooseNum=%d\n", chooseNum);
//         printf("singleAccount=%s\n", singleAccount);
//         printf("singlePassword=%s\n", singlePassword);
//         if (chooseNum == 5)
//         {
//             siglelist *infoListchange = list_init();
//             ret = changePassword(infoListchange, singleAccount, singlePassword);
//             if (ret == 2)
//             {
//                 char retbuf[10] = "success";
//                 Write(ts->connfd, retbuf, sizeof(retbuf)); // 回写给客户端
//                 list_uninit(infoListchange);
//             }
//             else if (ret == 6)
//             {
//                 char retbuf[20] = "notfound info";
//                 Write(ts->connfd, retbuf, sizeof(retbuf)); // 回写给客户端
//                 list_uninit(infoListchange);
//             }
//         }
//         if (chooseNum == 7)
//         {
//             showFileList(ts->connfd, singleAccount);
//         }
//     }
// }