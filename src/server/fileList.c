#include "fileList.h"
int fileSize;

int checkSize(char *fileName)
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

// void showFile(char *sourcePath)
// {
//     printf("%s\n", sourcePath);
// }

int showFileList(int sockfd, char *fileName)
// int showFile(char *fileName)
{
    char srcPath[PATH_MAX];
    char srcPathTemp[PATH_MAX];
    char srcPathSend[PATH_MAX];
    bzero(srcPath, PATH_MAX);
    bzero(srcPathTemp, PATH_MAX);
    bzero(srcPathSend, PATH_MAX);
    int filecount = 0;
    int dircount = 0;
    struct dirent *entry;
    DIR *dp = opendir(fileName);

    if (dp == NULL)
    {
        fprintf(stderr, "无法打开源目录\n");
        return 0;
    }
    while ((entry = readdir(dp)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(srcPath, sizeof(srcPath), "%s/%s", fileName, entry->d_name);

        struct stat st;
        stat(srcPath, &st);

        if (S_ISDIR(st.st_mode))
        {
            // showList(srcPath);
            printf("%s\n", srcPath);
            snprintf(srcPathSend, sizeof(srcPathSend), "%s|%s", srcPathTemp, srcPath);
            strcpy(srcPathTemp, srcPathSend);
            printf("Path dir=%s\n", srcPathSend);
            dircount += 1;
            printf("目录个数：%d\n", dircount);
        }
        if (S_ISREG(st.st_mode))
        {
            printf("%s\n", srcPath);
            int size = checkSize(srcPath);
            printf("%s文件大小=%d\n", srcPath, size);
            // showFile(srcPath);
            snprintf(srcPathSend, sizeof(srcPathSend), "%s|%s<%d>", srcPathTemp, srcPath, size);
            strcpy(srcPathTemp, srcPathSend);
            printf("Path reg=%s\n", srcPathSend);
            filecount += 1;
            printf("文件个数：%d\n", filecount);
        }
    }
    snprintf(srcPathSend, sizeof(srcPathSend), "$%d$%d$%s", filecount, dircount, srcPathTemp);
    printf("srcPathSend=%s\n", srcPathSend);
    write(sockfd, srcPathSend, strlen(srcPathSend));
}

// int main()
// {
//     char dirFile[20];
//     printf("请输入文件路径\n");
//     scanf("%s", dirFile);
//     showFile(dirFile);
// }