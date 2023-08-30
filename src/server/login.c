#include "login.h"
#include "UI.h"
int count = 0;
// 单链表的初始化（结构体函数）
struct siglelist *list_init()
{
    struct siglelist *head = malloc(sizeof(struct siglelist));
    head->count = 0; // 第一个数据
    // strcpy(head->account, NULL);
    // strcpy(head->password, NULL);
    head->next = NULL; // 暂时不知道后面的数据是谁
    // printf("第一个节点首地址： %p\n", head);
    return head;
}

// 插入数据--》尾插
int list_insert(struct siglelist *list, char *account, char *password)
{
    // 第一步：准备好新的节点
    struct siglelist *newnode = malloc(sizeof(struct siglelist));
    count += 1;
    newnode->count = count;
    strcpy(newnode->account, account);
    strcpy(newnode->password, password);
    newnode->next = NULL;

    // 第二步：找到链表的尾部
    struct siglelist *p = list; // 指针p指向链表的头
    while (p->next != NULL)
        p = p->next; // p往后挪动，循环结束的时候，p指向的就是链表最后面的那个节点

    p->next = newnode;
    return 0;
}

// 查询打印数据
int showList(struct siglelist *list)
{
    struct siglelist *p = list; // p指向链表的头节点
    while (p->next != NULL)
    {
        p = p->next;
        printf("链表中存放id是: %d\n", p->count);
        printf("链表中存放账号是: %s\n", p->account);
        printf("链表中存放密码是: %s\n", p->password);
    }
    return 0;
}

// 对比账号和密码
int contrastList(struct siglelist *list, char *account, char *password)
{
    struct siglelist *p = list; // p指向链表的头节点
    while (p->next != NULL)
    {

        if (!strcmp(p->account, account) && !strcmp(p->password, password))
        {
            printf("登录成功\n");
            return 2;
        }
        else if (!strcmp(p->account, account) || !strcmp(p->password, password))
        {
            printf("账号或密码错误\n");
            return 1;
        }
        p = p->next;
    }
    printf("没有数据请注册账号\n");
    return 0;
}
// 链表的销毁
int list_uninit(struct siglelist *list)
{
    while (list->next != NULL)
    {
        // 每一次删除最后一个节点，所有的节点删除完毕，最后释放头结点
        struct siglelist *q = list;
        struct siglelist *p = list->next;
        while (p->next != NULL)
        {
            p = p->next;
            q = q->next;
        }
        q->next = NULL;
        free(p);
    }
    // 当循环结束的时候，就只剩下一个头结点
    free(list); // 释放头
    return 0;
}
int login(char *account, char *password, siglelist *infoList)
{
    FILE *saveFile;
    saveFile = fopen("./info/clientInfo.txt", "r");
    if (saveFile == NULL)
    {
        printf("存放账号密码的文件丢失\n");
        fclose(saveFile);
        return 3;
    }

    int ret;
    struct stat mystat;

    ret = stat("./info/clientInfo.txt", &mystat);
    if (ret == -1)
    {
        printf("获取文件属性失败了!\n");
        return -1;
    }
    // printf("文件的大小是: %lu\n", mystat.st_size);

    char allInfo[mystat.st_size];
    fread(allInfo, mystat.st_size, 1, saveFile);
    // printf("allInfo=%s\n", allInfo);

    char singleAccount[12];
    char singlePassword[12];
    int retSscanf;
    char *singleInfo = strtok(allInfo, "|");
    // printf("singleInfo=%s\n", singleInfo);
    retSscanf = sscanf(singleInfo, "%[0-9a-zA-Z]*%[0-9a-zA-Z]", singleAccount, singlePassword);
    list_insert(infoList, singleAccount, singlePassword);
    // printf("singleAccount=%s\nsinglePassword=%s\n", singleAccount, singlePassword);
    while (singleInfo != NULL)
    {
        singleInfo = strtok(NULL, "|");
        if (singleInfo == NULL)
        {
            break;
        }
        else
        {
            // printf("singleInfo=%s\n", singleInfo);
            retSscanf = sscanf(singleInfo, "%[0-9a-zA-Z]*%[0-9a-zA-Z]", singleAccount, singlePassword);
            // printf("singleAccount=%s\nsinglePassword=%s\n", singleAccount, singlePassword);
            list_insert(infoList, singleAccount, singlePassword);
        }
    }
    // printf("开始比对\n");
    // 对比
    ret = contrastList(infoList, account, password);
    // showList(infoList);
    return ret;
}

// int main()
// {
//     siglelist *infoList = list_init();
//     login("12345", "dasd", infoList);
//     // showList(infoList);
// }