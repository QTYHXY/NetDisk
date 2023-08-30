#include "clientChangePass.h"
int clienChangePass(char *newPassword, char *newAgainPassword)
{
    while (1)
    {
        printf("请输入新密码(十位数以内)\n");
        // char newPassword[12];
        // char newAgainPassword[12];
        while (1)
        {
            scanf("%s", newPassword);
            if (strlen(newPassword) <= 10)
            {
                break;
            }
            else if (strlen(newPassword) == 0)
            {
                printf("\t\t\t密码为空，请重新输入\n");
            }
            else
            {
                printf("\t\t密码长度为%ld为，密码长度过长,请重新输入", strlen(newPassword));
            }
        }
        printf("请再输入一遍确认密码\n");
        while (1)
        {
            scanf("%s", newAgainPassword);
            if (strlen(newAgainPassword) <= 10)
            {
                break;
            }
            else if (strlen(newAgainPassword) == 0)
            {
                printf("\t\t\t密码为空，请重新输入\n");
            }
            else
            {
                printf("\t\t密码长度为%ld为，密码长度过长,请重新输入", strlen(newAgainPassword));
            }
        }
        if (!strcmp(newPassword, newAgainPassword))
        {
            printf("密码修改成功\n");
            break;
        }
        else
        {
            printf("前后密码不一致,请重新输入\n");
        }
    }
}