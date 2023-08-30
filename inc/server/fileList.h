#ifndef _FILELIST_H_
#define _FILELIST_H_
// 头文件
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
// 宏定义

// 函数
int checkSize(char *fileName);
int showFile(char *sourcePath);
int showFileList(int sockfd, char *fileName);

#endif