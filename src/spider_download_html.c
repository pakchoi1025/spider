#include <baike_spider.h>

//发送请求，接收响应，完成认证，完成下载流程
int Spider_Download_HTML(int webfd,char * Request,url_t node, ssl_t * ssl){
    int statcode;
    char buffer[8192];
    char Response[4096];
    char * pos = NULL;
    int recvlen;
    int fd;

    bzero(buffer,sizeof(buffer));
    bzero(Response,sizeof(Response));
    SSL_write(ssl->ssl_socket,Request,strlen(Request));//发送请求
    printf("Spider Send Request Success.\n");
    recvlen = SSL_read(ssl->ssl_socket,buffer,sizeof(buffer));//第一次读取响应
    if((pos = strstr(buffer,"\r\n\r\n"))==NULL){
        printf("strstr Call Failed,not Find Request Head!\n");
        exit(0);
    }

    snprintf(Response,pos - buffer + 4, "%s" , buffer);//将响应写入Response
    printf("Spider Response Head:\n%s",Response);

    //创建文件保存网页源码
    if((fd = open(node.file_name,O_RDWR|O_CREAT,0664)) == -1){
        printf("Spider_Download_HTML,Create HTML Call Failed!\n");
        exit(0);
    }


    //将第一次读取的部分响应体，写入到文件
    if((statcode =  Spider_Get_StateCode(Response)) == 200){
        printf("Spider Response StateCode=%d.\n",statcode);
        write(fd,pos+4,recvlen - (pos - buffer + 4));
        while((recvlen = SSL_read(ssl->ssl_socket,buffer,sizeof(buffer)))>0){
           write(fd,buffer,recvlen);
           bzero(buffer,sizeof(buffer));
        }
        printf("Spider Download HTML Success.\n");
        close(fd);
        close(webfd);
        free(ssl);
        ssl = NULL;
        return 0;
    }else{
        printf("Spider Response StateCode=%d.\n",statcode);
        close(webfd);
        free(ssl);
        ssl = NULL;
        return -1;
    }

}