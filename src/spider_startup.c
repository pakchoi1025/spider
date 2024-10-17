#include <baike_spider.h>


//爬虫启动器
int Spider_StartUp(char * Alpha_url){
    url_t node;//用于传入
    url_t tmpnode;//用于传出
    printf("Spider Starting...\n");
    if ((result_fd = open("Result.html",O_RDWR|O_CREAT,0664))==-1){
        perror("Spider_Startup >> Create Result.html Failed.");
        exit(0);
    }
    //写入html头部信息
    Spider_Save_Result(NULL,NULL,NULL);
    container_t * E_ct = Spider_Container_Create(1000);
    container_t * P_ct = Spider_Container_Create(_RESULT_MAX);
    strcpy(node.origin_url,Alpha_url);
    
    if(Spider_Remove_Duplication(E_ct,P_ct,node.origin_url))
        Spider_Container_add(E_ct,node);
    
    while(E_ct->cur > 0 && P_ct->cur < _RESULT_MAX){
        if(E_ct->cur >= 500){
            analytical_shutdown = 0;
            printf("Analytical Shutdown [Close].");
        }else if(E_ct->cur <= 50){
            analytical_shutdown = 1;
            printf("Analytical Shutdown [Open].");
        }
        Spider_Container_get(E_ct,&tmpnode);
        if(Spider_Interactive_Process(&tmpnode) == -1){
            continue;
        }
        Spider_Container_add(P_ct,tmpnode);
        Spider_Analytical_HTML(tmpnode,E_ct,P_ct);

    }

    printf("词条爬虫：抓取数据量 [%d].\n",P_ct->cur);
    return 0;
}