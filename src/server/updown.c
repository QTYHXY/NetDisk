#include "updown.h"
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
int checktype(char *fileName)
{
    struct stat buf;
    int result;
    result = stat(fileName, &buf);
    if (S_IFDIR & buf.st_mode)
    {
        printf("folder\n");
        return 1;
    }
    else if (S_IFREG & buf.st_mode)
    {
        printf("file\n");
        return 2;
    }
}
int upFile(int sockfd, char *fileName)
{
    int ret;
    int size;
    char sizeBuf[10];
    ret = checktype(fileName);
    if (ret == 1)
    {
        printf("str为路径，暂未完善\n");
    }
    if (ret == 2)
    {
        size = checkFileSize(fileName);
        printf("%s的大小：%d\n", fileName, size);
        snprintf(sizeBuf, sizeof(sizeBuf), "%d", size);
        write(sockfd, sizeBuf, strlen(sizeBuf));
        if (size == -1)
        {
            return -1;
        }
        int file = open(fileName, O_RDONLY);
        char sendbuf[BUFMAX];
        int totalRead = 0; // 已接收文件大小
        int n;
        while (totalRead < size)
        {
            bzero(sendbuf, BUFMAX);
            n = Read(file, sendbuf, sizeof(sendbuf));
            // printf("fread n =%d\n", n);
            Write(sockfd, sendbuf, n);
            // printf("fwrite n =%d", n);
            totalRead += n;
            fprintf(stderr, "\r已发送: %d/%d", totalRead, size);
        }
        Close(file);
        return 1;
    }
}

char *getFileName(char *path)
{
    char *lastPath = strrchr(path, '/');

    if (lastPath == NULL)
    {
        return NULL;
    }

    return lastPath + 1;
}

int downFile(int sockfd, char *fileName)
{
    int ret;
    int n = 1024;
    char recvbuf[MAXLINE];
    char fileNameSpli[20];

    printf("fileName: %s\n", fileName);
    char fileSize[10];
    char *tempName = getFileName(fileName);
    strcpy(fileSize, strtok(fileName, "/"));
    int Size = atoi(fileName);
    printf("fileSize======%d\n", Size);
    snprintf(fileNameSpli, 20, "%s/%s", "upload", tempName);
    printf("fileNameSpli %s\n", fileNameSpli);
    int file = open(fileNameSpli, O_CREAT | O_RDWR | O_TRUNC, 0666);
    int everyRead = 0;
    // n = Read(sockfd, recvbuf, MAXLINE);
    // int fileSize = atoi(recvbuf);
    // printf("fileSize======%d\n", fileSize);
    // printf("everyread=====%d\n", everyRead);

    // int n;
    while (everyRead < Size)
    {
        // printf("1\n");
        bzero(recvbuf, MAXLINE);
        n = Read(sockfd, recvbuf, sizeof(recvbuf));
        // printf("n=%d\n", n);
        // printf("buf=%s\n", recvbuf);
        ret = Write(file, recvbuf, n);
        everyRead += ret;
        // printf("everyread=%d\n", everyRead);
    }
    close(file);
    printf("文件上传完成\n");
    return 1;
}

int specifiedPath(int sockfd, char *path, char *fileName)
{
    int ret;
    int n;
    char recvbuf[MAXLINE];
    mkdir(path, 0777);
    char pathBuf[40];
    char *tempName = getFileName(fileName);
    char fileSize[10];
    strcpy(fileSize, strtok(fileName, "/"));
    int Size = atoi(fileName);
    printf("fileSize======%d\n", Size);

    printf("tempName %s\n", tempName);
    snprintf(pathBuf, sizeof(pathBuf), "%s/%s", path, tempName);
    int file = open(pathBuf, O_CREAT | O_RDWR | O_TRUNC, 0666);
    int everyRead = 0;
    // n = Read(sockfd, recvbuf, MAXLINE);
    // int fileSize = atoi(recvbuf);
    bzero(recvbuf, MAXLINE);
    printf("fileSize=%d\n", Size);
    // int n;
    while (everyRead < Size)
    {
        n = read(sockfd, recvbuf, sizeof(recvbuf));
        // printf("n=%d\n", n);
        // printf("buf=%s\n", recvbuf);
        ret = write(file, recvbuf, n);
        everyRead += ret;
        // printf("everyread=%d\n", everyRead);
    }
    close(file);
    printf("文件上传完成\n");
    return 1;
}