#include <baike_spider.h>


int Spider_Interactive_Process(url_t * node){
    

	char Request[4096];
    ssl_t * ssl = NULL;
	
    int sockfd = Spider_Net_Init();
	Spider_Analytical_URL(node);
	Spider_Connect_Web(sockfd,node);
	Spider_Create_RequestHead(node,Request);

    if(node->http_type){
        ssl = Spider_Openssl_Create(sockfd);
    }
    
    if((Spider_Download_HTML(sockfd,Request,*node,ssl)) == 0){
        return 0;
    }else{
        return -1;
    }
}