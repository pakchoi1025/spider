#include <baike_spider.h>


int Spider_Net_Init(void){
        struct sockaddr_in myaddr;
        myaddr.sin_family = AF_INET;
        myaddr.sin_port = htons(8000);
        myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        int mysock;
        mysock = socket(AF_INET,SOCK_STREAM,0);
        bind(mysock,(struct sockaddr *)&myaddr,sizeof(myaddr));
        printf("Spider Net Init Success,Socket[%d].\n",mysock);
	return mysock;
}

