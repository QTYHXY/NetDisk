c语言网盘项目

gcc server.c splitInfo.c login.c checkSame.c changePassword.c fileList.c workProcess.c updown.c ../share/wrap.c ../share/threadpool.c -o 
server -I ../../inc/server -I ../../inc/share -lpthread

gcc client.c clientSend.c register.c clientChangePass.c ../share/wrap.c -o client -I ../../inc/client -I ../../inc/share -l ui -L ../../lib



代码块
正则表达式