#include <baike_spider.h>


//获取一个资源
int Spider_Container_get(container_t * ct, url_t * node){
    if(ct->cur == 0){
        return -1;
    }
    *node = ct->url_list[ct->rear];
    ct->rear = (ct->rear + 1)%ct->max;
    --ct->cur;
    return 0;
}