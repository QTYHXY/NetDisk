#ifndef _LOGIN_H_
#define _LOGIN_H_
// 头文件
#include <sys/stat.h>
#include <string.h>
// 链表
typedef struct siglelist
{
    int count;
    char account[12];
    char password[12];
    struct siglelist *next;
} siglelist;

// 函数
int login(char *account, char *password, siglelist *infoList);

// 链表
struct siglelist *list_init(void);
int list_insert(struct siglelist *list, char *account, char *password);
int contrastList(struct siglelist *list, char *account, char *password);
int showList(struct siglelist *list);
int list_uninit(struct siglelist *list);
#endif