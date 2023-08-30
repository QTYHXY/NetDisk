#include "server.h"
char receiveInfo[30];
char singleAccount[12];
char singlePassword[12];
int chooseNum;

int main(void)
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int listenfd, connfd;
    pthread_t tid;
    struct s_info ts[256]; // 根据最大线程数创建结构体数组.
    int i = 0;

    threadpool_t *threadpool = threadpool_create(3, 100, 100); /*创建线程池，池里最小3个线程，最大100，队列最大100*/

    listenfd = Socket(AF_INET, SOCK_STREAM, 0); // 创建一个socket, 得到lfd

    // 使套接字sockfd关联的地址在套接字关闭后立即释放
    int on = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    bzero(&servaddr, sizeof(servaddr)); // 地址结构清零
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // 指定本地任意IP
    servaddr.sin_port = htons(SERV_PORT);         // 指定端口号 8000

    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)); // 绑定

    Listen(listenfd, 128); // 设置同一时刻链接服务器上限数

    printf("服务器启动成功\n");

    while (1)
    {
        cliaddr_len = sizeof(cliaddr);
        connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len); // 阻塞监听客户端链接请求
        ts[i].cliaddr = cliaddr;
        ts[i].connfd = connfd;
        ts[i].threadpool = threadpool;
        printf("客户端%d已连接，IP为%s,端口号为%d\n", connfd - 3, inet_ntoa(cliaddr.sin_addr), htons(cliaddr.sin_port));

        /* 达到线程最大数时，pthread_create出错处理, 增加服务器稳定性 */
        pthread_create(&tid, NULL, mainProcess, (void *)&ts[i]);
        // threadpool_add(threadpool, do_work, (void *)&ts[i]);
        // threadpool_add(threadpool, mainProcess, (void *)&ts[i]); /* 向线程池中添加任务 */
        i++;
    }

    return 0;
}
