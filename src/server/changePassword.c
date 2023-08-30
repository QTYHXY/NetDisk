#include <changePassword.h>

int change(struct siglelist *list, char *account, char *password)
{
    struct siglelist *p = list; // p指向链表的头节点

    while (p->next != NULL)
    {
        p = p->next;
        if (!strcmp(p->account, account))
        {
            printf("已找到此账号信息\n");
            strcpy(p->password, password);
            return 2;
        }
    }
}
int coverFile(struct siglelist *list)
{
    char saveInfo[30];
    struct siglelist *p = list; // p指向链表的头节点
    FILE *coverFileArg;
    coverFileArg = fopen("./info/clientInfo.txt", "w+");
    while (p->next != NULL)
    {
        p = p->next;
        snprintf(saveInfo, sizeof(saveInfo), "%s*%s|", p->account, p->password);
        // printf("saveInfo=%s\n", saveInfo);
        fprintf(coverFileArg, "%s", saveInfo);
    }
    fclose(coverFileArg);
}
int changePassword(siglelist *infoList, char *account, char *password)
{
    FILE *checkFile;
    checkFile = fopen("./info/clientInfo.txt", "a+");
    if (checkFile == NULL)
    {
        printf("changePassword存放账号密码的文件丢失\n");
        fclose(checkFile);
        return 3;
    }

    int ret;
    struct stat mystat;

    ret = stat("./info/clientInfo.txt", &mystat);
    if (ret == -1)
    {
        printf("changePassword获取文件属性失败了!\n");
        return -1;
    }
    // printf("文件的大小是: %lu\n", mystat.st_size);

    char allInfo[mystat.st_size];
    fread(allInfo, mystat.st_size - 1, 1, checkFile);
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
    ret = change(infoList, account, password);
    if (ret == 2)
    {
        coverFile(infoList);
        showList(infoList);
    }
    return ret;
}
