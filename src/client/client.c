#include "client.h"

int main()
{
    char account[12];
    char password[12];
    int ret;
    int sockfd;
    int chooseNum;
    // 连接服务器
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.8.181", &servaddr.sin_addr.s_addr);
    servaddr.sin_port = htons(SERV_PORT);

    Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    while (1)
    {
    again:
        clientUI();
        scanf("%d", &chooseNum);
        switch (chooseNum)
        {
        case 1:
            printf("请输入账号：");
            scanf("%s", account);
            printf("请输入密码：");
            scanf("%s", password);
            ret = CsendInfo(sockfd, account, password, chooseNum);
            if (ret == 2)
            {
                printf("登录成功\n");
                while (1)
                {
                    serverUI();
                    int funcNum;
                    scanf("%d", &funcNum);
                    switch (funcNum)
                    {
                    case 1:
                    {
                        char fileName[20];
                        printf("1.默认路径\n2.自定义路径\n");
                        int num;
                        scanf("%d", &num);
                        if (num == 1)
                        {
                            CsendFileName(sockfd, "shareFile", 7);
                        }
                        if (num == 2)
                        {
                            printf("请输入路径名\n");
                            scanf("%s", fileName);
                            // printf("fileName=%s\n", fileName);
                            CsendFileName(sockfd, fileName, 7);
                        }
                        break;
                    }
                    case 2:
                    {
                        CsendUpDown(sockfd, 9);
                        break;
                    }
                    case 3:
                        CsendSFile(sockfd, 10);
                        break;
                    case 4:
                    {
                        char deleName[20];
                        printf("请输入你要删除的文件名及其路径");
                        scanf("%s", deleName);
                        const char *tempName = getFileName(deleName);
                        // printf("File Name: %s\n", tempName);
                        if (unlink(deleName) == 0)
                        {
                            printf("成功删除文件: %s\n", tempName);
                        }
                        else
                        {
                            printf("%s删除失败\n", tempName);
                        }
                        break;
                    }
                    case 5:
                        ret = CsendInfo(sockfd, account, password, funcNum);
                        if (ret == 2)
                        {
                            char newPassword[12];
                            char newAgainPassword[12];
                            clienChangePass(newPassword, newAgainPassword);
                            CsendInfo(sockfd, account, newPassword, funcNum);
                            // printf("newPassword=%s\n", newPassword);
                            // printf("newAgainPassword=%s\n", newAgainPassword);
                        }
                        break;
                    case 6:
                        printf("将要返回登录界面\n");
                        goto again;
                        sleep(1);
                        break;
                    case 7:
                        printf("将要退出系统...\n");
                        sleep(1);
                        exit(0);
                    default:
                        break;
                    }
                }
            }
            if (ret == 3)
                printf("服务器文件丢失\n");
            if (ret == 0)
                printf("没有此账户信息\n");
            if (ret == 1)
                printf("账号或密码错误\n");
            break;
        case 2:
            registerInfo(account, password);
            ret = CsendInfo(sockfd, account, password, chooseNum);
            if (ret == 2)
                printf("注册成功\n");
            if (ret == 5)
                printf("此账号已经存在\n");
            break;
        case 3:
            printf("将要退出系统...\n");
            sleep(1);
            exit(0);
        default:
            printf("输入错误，将要退出系统...\n");
            sleep(1);
            exit(0);
            break;
        }
    }
}