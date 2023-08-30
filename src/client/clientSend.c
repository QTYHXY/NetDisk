#include "clientSend.h"

typedef struct clientInfo
{
    char account[12];
    char password[12];
} clientInfo;

int CsendInfo(int sockfd, char *account, char *password, int num)
{
    struct sockaddr_in servaddr;

    char buf[MAXLINE];
    int n;

    snprintf(buf, sizeof(buf), "$%d$%s#%s|", num, account, password);

    write(sockfd, buf, strlen(buf));
    bzero(buf, MAXLINE);
    n = Read(sockfd, buf, MAXLINE);
    if (n == 0)
    {
        printf("服务端已关闭，客户端即将退出...\n");
        sleep(2);
        exit(0);
    }
    // Write(STDOUT_FILENO, buf, n); // 写出至屏幕
    int ret;
    if (!strcmp(buf, "success"))
    {
        ret = 2;
    }
    else if (!strcmp(buf, "infofile loss"))
    {
        ret = 3;
    }
    else if (!strcmp(buf, "notfound info"))
    {
        ret = 0;
    }
    else if (!strcmp(buf, "accout or password error"))
    {
        ret = 1;
    }
    else if (!strcmp(buf, "account exist"))
    {
        ret = 5;
    }

    printf("buf=%s\n", buf);
    printf("ret=%d\n", ret);
    return ret;
}

int CsendFileName(int sockfd, char *fileName, int num)
{
    char buf[MAXLINE];
    char temp[MAXLINE];
    char singleName[MAXLINE];
    char recvfileName[MAXLINE];
    int n, fileCount, dircount, size;
    int i;
    int retSscanf;
    snprintf(buf, sizeof(buf), "$%d$%s#%s|", num, fileName, fileName);

    write(sockfd, buf, strlen(buf));
    bzero(buf, MAXLINE);
    n = Read(sockfd, buf, MAXLINE);
    if (n == 0)
    {
        printf("服务端已关闭，客户端即将退出...\n");
        sleep(2);
        exit(0);
    }
    // printf("buf=%s\n", buf);
    strcpy(temp, buf);
    // sscanf(buf, "$%d$%d$%s", &fileCount, &dircount, recvfileName);
    sscanf(temp, "$%d$%d$%s<%d>", &fileCount, &dircount, recvfileName, &size);
    printf("可下载文件数量有：%d\n", fileCount);
    printf("可打开目录数量有：%d\n", dircount);
    // printf("recvfileName有：%s\n", recvfileName);
    char *singleInfo = strtok(recvfileName, "|");
    retSscanf = sscanf(recvfileName, "%s|", singleName);
    printf("%s\n", singleName);
    while (singleInfo != NULL)
    {
        singleInfo = strtok(NULL, "|");
        if (singleInfo == NULL)
        {
            break;
        }
        else
        {
            retSscanf = sscanf(singleInfo, "%s|", singleName);
            printf("%s\n", singleName);
        }
    }
}

const char *getFileName(const char *path)
{
    const char *fileName = strrchr(path, '\\'); // 在Windows中使用反斜杠'\\'作为分隔符
    if (!fileName)
    {
        fileName = strrchr(path, '/'); // 在Linux和macOS中使用斜杠'/'作为分隔符
    }
    if (!fileName)
    {
        return path; // 如果找不到分隔符，则路径本身即为文件名
    }
    return fileName + 1; // 返回文件名（去除分隔符）
}

int CsendUpDown(int sockfd, int num)
{
    char sendbuf[MAXLINE];
    char recvbuf[MAXLINE];
    char fileName[20];
    char spliName[100];
    int retSscanf;
    int n;
    printf("请输入要下载的文件名：");
    scanf("%s", fileName);
    bzero(sendbuf, MAXLINE);
    bzero(recvbuf, MAXLINE);
    snprintf(sendbuf, sizeof(sendbuf), "$%d$%s#%s|", num, fileName, fileName);
    write(sockfd, sendbuf, strlen(sendbuf));
    // printf("sendbuf=%s\n", sendbuf);
    printf("文件名：%s\n", fileName);
    n = Read(sockfd, recvbuf, MAXLINE);
    int fileSize = atoi(recvbuf);
    // printf("fileSize=%d\n", fileSize);
back:
    printf("1.下载到指定路径下\n2.下载到默认路径下且不更改文件名\n");
    int choose1;
    char pathName[100];
    scanf("%d", &choose1);
    if (choose1 == 1)
    {
        printf("请输入路径名\n");
        bzero(pathName, 100);
        scanf("%s", pathName);
        printf("是否重新命名该文件\n1.重命名\n2.采用原文件名\n3.返回\n");
        int choose2;
        scanf("%d", &choose2);
        if (choose2 == 1)
        {
            bzero(spliName, 100);
            printf("请输入新的文件名\n");
            char newFileName[12];
            scanf("%s", newFileName);
            snprintf(spliName, 100, "%s/%s", pathName, newFileName);
            printf("拼接后的名字=%s\n", spliName);
        }
        if (choose2 == 2)
        {
            const char *tempName = getFileName(fileName);
            printf("File Name: %s\n", tempName);
            snprintf(spliName, 100, "%s/%s", pathName, tempName);
            printf("拼接后的名字=%s\n", spliName);
        }
        if (choose2 == 3)
        {
            goto back;
        }
    }
    if (choose1 == 2)
    {
        bzero(pathName, 100);
        strcpy(pathName, "download");
        bzero(spliName, 100);
        const char *tempName = getFileName(fileName);
        printf("File Name: %s\n", tempName);
        snprintf(spliName, 100, "%s/%s", pathName, tempName);
        printf("拼接后的名字=%s\n", spliName);
    }

    int file = open(spliName, O_CREAT | O_RDWR | O_TRUNC);
    int everyRead = 0;
    // int n;
    while (everyRead < fileSize)
    {
        int ret;
        n = Read(sockfd, recvbuf, MAXLINE);
        // printf("recvbuf=%s\n", recvbuf);
        // printf("n=%d\n", n);
        ret = Write(file, recvbuf, n);
        // ret = write(file, recvbuf, n);
        // printf("ret=%d\n", ret);
        everyRead += ret;
        // printf("everyRead=%d\n", everyRead);
        fprintf(stderr, "\r已发送: %d/%d", everyRead, fileSize);
        if (n == 0)
        {
            printf("服务端已关闭，客户端即将退出...\n");
            sleep(2);
            exit(0);
        }
    }
    close(file);
    if (everyRead == fileSize && fileSize != 0)
    {
        printf("下载完成\n");
    }
    else
    {
        printf("下载失败\n");
    }
}

int checktype(char *fileName)
{
    struct stat buf;
    int result;
    result = stat(fileName, &buf);
    if (S_IFDIR & buf.st_mode)
    {
        printf("%s是目录\n", fileName);
        return 1;
    }
    else if (S_IFREG & buf.st_mode)
    {
        printf("%s是文件\n", fileName);
        return 2;
    }
}
int fileSize;
int checkFileSize(char *fileName)
{
    int ret;
    // 定义结构体变量，存放你要获取的那个文件的属性信息
    struct stat mystat;
    // stat函数的大小
    ret = stat(fileName, &mystat);
    if (ret == -1)
    {
        printf("获取文件属性失败了!\n");
        return -1;
    }
    fileSize = mystat.st_size;
    // printf("文件的大小是: %lu\n", mystat.st_size);
    return fileSize;
}

int CsendSFile(int sockfd, int num)
{
    char fileName[100];
    char sendbuf[BUFMAX];
    int fileSize;
againFile:
    printf("请输入要上传的文件名(可包含路径)\n");
    scanf("%s", fileName);
    const char *fileNameSend = getFileName(fileName);
    // printf("File Name: %s\n", fileNameSend);
    int ret = checktype(fileName);
    if (ret == 1)
    {
        printf("str为路径，暂未完善\n");
    }
    if (ret == 2)
    {
    againPath:
        printf("1.上传到默认路径\n2.上传到指定路径\n");
        fileSize = checkFileSize(fileName);
        // printf("fileSize=%d\n", fileSize);
        int choose1;
        scanf("%d", &choose1);
        if (choose1 == 1)
        {
            char pathName[100];
            char spliName[100];
            strcpy(pathName, "upload");
            snprintf(spliName, 100, "%d/%s/%s", fileSize, pathName, fileNameSend);
            snprintf(sendbuf, sizeof(sendbuf), "$%d$%s#%s|", num, spliName, spliName);
            // printf("sendbuf: %s\n", sendbuf);
            write(sockfd, sendbuf, strlen(sendbuf)); // 写文件名
            // char size[20];
            // snprintf(size, 20, "%d", fileSize);
            // write(sockfd, size, strlen(size)); // 写文件大小
            int file = open(fileName, O_RDONLY);
            char sendbuf[BUFMAX];
            int totalRead = 0; // 已接收文件大小
            int n;
            // printf("284\n");
            // printf("fileSize====%d\n", fileSize);
            while (totalRead < fileSize)
            {
                bzero(sendbuf, BUFMAX);
                n = Read(file, sendbuf, sizeof(sendbuf));
                // printf("fread n =%d\n", n);
                n = Write(sockfd, sendbuf, n);
                // printf("fwrite n =%d", n);
                totalRead += n;
                fprintf(stderr, "\r已上传: %d/%d", totalRead, fileSize);
            }
            Close(file);
            if (totalRead == fileSize && fileSize != 0)
            {
                printf("上传完成\n");
            }
            else
            {
                printf("上传失败\n");
            }
        }
        else if (choose1 == 2)
        {
            printf("请输入路径名\n");
            char pathName[100];
            scanf("%s", pathName);
            printf("是否要重命名\n");
            printf("1.重命名\n2.默认\n3.返回重新选择要上传的文件名\n4.返回路径选择\n");
            int choose2;
            scanf("%d", &choose2);
            switch (choose2)
            {
            case 1:
            {
                /* code */
                num = 11;
                char newName[20];
                char spliName[40];
                char tempName[40];
                printf("请输入新的名字\n");
                scanf("%s", newName);
                snprintf(tempName, 100, "%d/%s", fileSize, newName);
                snprintf(spliName, 40, "$%d$%s#%s|", num, pathName, tempName);
                // printf("spliName=%s\n", spliName);
                write(sockfd, spliName, strlen(spliName));

                int file = open(fileName, O_RDONLY);
                char sendbuf[BUFMAX];
                int totalRead = 0; // 已接收文件大小
                int n;
                while (totalRead < fileSize)
                {
                    bzero(sendbuf, BUFMAX);
                    n = Read(file, sendbuf, sizeof(sendbuf));
                    // printf("fread n =%d\n", n);
                    n = Write(sockfd, sendbuf, n);
                    // printf("fwrite n =%d", n);
                    totalRead += n;
                    fprintf(stderr, "\r已上传: %d/%d", totalRead, fileSize);
                }
                Close(file);
                if (totalRead == fileSize && fileSize != 0)
                {
                    printf("上传完成\n");
                }
                else
                {
                    printf("上传失败\n");
                }
                break;
            }
            case 2:
            {
                num = 11;
                char spliName[40];
                char tempName[40];
                snprintf(tempName, 40, "%d/%s", fileSize, fileNameSend);
                snprintf(spliName, 40, "$%d$%s#%s|", num, pathName, tempName);
                // printf("spliName=%s\n", spliName);
                write(sockfd, spliName, strlen(spliName));
                // char size[20];
                // snprintf(size, 20, "%d", fileSize);
                // write(sockfd, size, strlen(size)); // 写文件大小
                int file = open(fileName, O_RDONLY);
                char sendbuf[BUFMAX];
                int totalRead = 0; // 已接收文件大小
                int n;
                while (totalRead < fileSize)
                {
                    bzero(sendbuf, BUFMAX);
                    n = Read(file, sendbuf, sizeof(sendbuf));
                    // printf("fread n =%d\n", n);
                    n = Write(sockfd, sendbuf, n);
                    // printf("fwrite n =%d", n);
                    totalRead += n;
                    fprintf(stderr, "\r已上传: %d/%d", totalRead, fileSize);
                }
                Close(file);
                if (totalRead == fileSize && fileSize != 0)
                {
                    printf("上传完成\n");
                }
                else
                {
                    printf("上传失败\n");
                }
                /* code */
                break;
            }
            case 3:
                /* code */
                goto againFile;
                break;
            case 4:
                /* code */
                goto againPath;
                break;
            default:
                printf("请输入正确的选项\n");
                break;
            }
        }
    }
    // else
    // {
    //     printf("请重新输入\n");
    //     goto againFile;
    // }
    return 1;
}