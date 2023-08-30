#include "register.h"
int registerInfo(char *account, char *password)
{

    registerUI();
    while (1)
    {
        printf("\t\t请输入账号(十位数以内): ");
        scanf("%s", account);
        if (strlen(account) <= 10)
        {
            break;
        }
        else if (strlen(account) == 0)
        {
            printf("\t\t\t账号为空，请重新输入\n");
        }
        else
        {
            printf("\t\t账号长度为%ld为，账号长度过长,请重新输入", strlen(account));
        }
    }
    while (1)
    {
        printf("\t\t请输入密码(十位数以内): ");
        scanf("%s", password);
        if (strlen(password) <= 10)
        {
            break;
        }
        else if (strlen(password) == 0)
        {
            printf("密码为空，请重新输入\n");
        }
        else
        {
            printf("密码长度为%ld为，账号长度过长,请重新输入", strlen(password));
        }
    }
    // printf("账号：%d\n密码：%d\n", strlen(account), strlen(password));
    // printf("账号：%s\n密码：%s\n", account, password);

    // printf("\t\t\t\t注册成功\n");
    // return 1;
}

// int main()
// {
//     registerInfo();
// }