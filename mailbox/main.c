#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "list.h"

#include "queue.h"
#define ENTER_CRITICAL_AREA(mutex)  do{pthread_mutex_lock(mutex);}while(0)
#define QUIT_CRITICAL_AREA(mutex)  do{pthread_mutex_unlock(mutex);}while(0)

unsigned pthread_index;

LIST_LINK *end_list = NULL;

//typedef struct thread_node
//{
//    pthread_t tid;         //线程id号
//    char name[256];        //线程名字 ,必须唯一
//    Que *amil_head, *mail_tail;
//    th_fun th;              //线程函数

//}TH_NODE;

typedef struct mail_box_system
{
    pthread_mutex_t mutex;  //保护邮件系统
    LIST_LINK *thread_list;
}MBS;
MBS* mbs;

int send_msg(MBS*msb,char*recvname,DATATYPE data);
int recv_msg(MBS*msb,char*sendname,DATATYPE *data);

/* 邮箱系统初始化 */
MBS* create_mail_box_system()
{
    MBS *temp =(MBS*)malloc(sizeof(MBS));

    if(NULL ==  temp)
    {
        perror("create_mail_box_system mutex malloc failure\n");
        return NULL;
    }
    int ret = pthread_mutex_init(&temp->mutex,NULL);
    if(0 != ret)
    {
        perror("create_mail_box_system mutex init failure\n");
        return NULL;
    }
    temp->thread_list = malloc(sizeof(LIST_LINK));
   // memset(temp->thread_list, 0, sizeof(LIST_LINK));
    temp->thread_list->next = NULL;
    printf("mail box create ok!! \n");
    return temp;
}

/* 回收日志系统申请的空间 */
int destroy_mail_box_system(MBS*mbs)
{
    pthread_mutex_destroy(&mbs->mutex);
    LIST_LINK *temp = NULL;
    LIST_LINK *find = mbs->thread_list;
    while(find !=  NULL)
    {
        temp = find;
        find = find->next;
        free(temp);
    }
    free(mbs);
    return 0;
}

/* 向邮箱中注册一个新的线程 */
int  register_to_mail_system(MBS *mbs,char name[],th_fun th)
{
    LIST_LINK* temp =  malloc(sizeof(LIST_LINK));
    if(NULL == temp)
    {
        perror("register to mail malloc  \n");
        return -1;
    }
    strcpy(temp->elem.name ,name);
    temp->elem.th = th;
    init_que(temp);

    list_add(mbs->thread_list, temp);
    pthread_t ret = pthread_create(&temp->elem.tid,NULL,th,NULL);
    if(0!=ret)
    {
        perror("register to mail thread create\n");
        return -1;
    }

    printf("register mail system  |%s|  ok \n", temp->elem.name);

    return 0;
}

int unregister_from_mailbox(MBS*msb,char*name)
{
    LIST_LINK* find=msb->thread_list->next;
    LIST_LINK *temp = msb->thread_list;
	
    while(find !=  NULL)
    {
//		printf("================%s\n", find->elem.name);
        if(0 == strcmp(find->elem.name ,name))
        {
            destroy(find);
			pthread_cancel(find->elem.tid);
//			printf("cancel tid = %ld\n", find->elem.tid);
			pthread_join(find->elem.tid, NULL);
			temp->next=find->next;
            free(find);
            return 0;
        }
		else
		{
			temp = find;
			find = find->next;
		}
    }

    return -1;
}

/* 等待所有线程任务执行结束 */
int wait_all_end(MBS*msb)
{
    LIST_LINK *find=msb->thread_list->next;
    LIST_LINK *end=end_list;
    while(find != end)
    {
        // pthread_join(find,NULL);

        pthread_join(find->elem.tid,NULL);
        find = find->next;
    }
   
    return 0;
}

void* data_collect_th(void* arg)
{
    while(1)
    {
//        printf("this is the data th\n");
        sleep(3);
		
		DATATYPE data;
		data.id = 1;
		data.temp = 35;
		data.deep = 10;

        send_msg(mbs,"show", data);
        send_msg(mbs,"sock", data);

    }
    return NULL;
}

void* show_th(void* arg)
{

    while(1)
    {
//        printf("this is the show th\n");
        char sendname[256];
        DATATYPE data;
        recv_msg(mbs,sendname,&data);
        printf("show tid = %ld, recv msg from %s msg is %f, %f\n", pthread_self(),sendname, data.temp, data.deep);
        sleep(1);
    }
    return NULL;
}

void* sock_th(void* arg)
{
    while(1)
    {
//        printf("this is the sock th\n");
        DATATYPE data;
        char sendname[256];
        recv_msg(mbs,sendname,&data);
        printf("scok recv msg from %s msg is %f, %f\n", sendname, data.temp, data.deep);
        sleep(1);
    }
    return NULL;
}

char *get_th_name(MBS*msb)
{
    pthread_t tid = pthread_self();
    LIST_LINK *find = msb->thread_list->next;
    LIST_LINK *end = end_list;
    while(find != end)
    {
        if(find->elem.tid == tid)
            break;
        find = find->next;
    }
    if(find != NULL && find->elem.tid == tid)
    {
        //printf("cant find the recv th\n");
        return find->elem.name;
    }
    else
        return NULL;
}

int send_msg(MBS*msb, char*recvname, DATATYPE data)
{
    MAIL_DATA* temp =  malloc(sizeof(MAIL_DATA));

    //strcpy(temp->data, data);
	memcpy(&(temp->data), &data, sizeof(DATATYPE));

    temp->id_of_sender = pthread_self();

    LIST_LINK *find = list_for_each(msb->thread_list, recvname);
    if (find == NULL)
    {
        printf("can,t find msg \n");
		return -1;
    }

    char* name = get_th_name(msb);
    strcpy(temp->name_of_sender,name);
    strcpy(temp->name_of_recver,recvname);
    ENTER_CRITICAL_AREA(&msb->mutex);
    in_queue(find, temp);
    QUIT_CRITICAL_AREA(&msb->mutex);
//    printf("send msg is ok |%s| msg is %s\n", temp->name_of_recver, temp->data);
    return 0;

}

int recv_msg(MBS*msb,char*sendname,DATATYPE *data)
{
    MAIL_DATA* temp =  malloc(sizeof(MAIL_DATA));
    pthread_t tid =  pthread_self();

    LIST_LINK *find = msb->thread_list->next;

    while(find != NULL)
    {
        if( find->elem.tid == tid)
            break;
        find = find->next;
    }

    if( find != NULL && find->elem.tid == tid)
    {
        while (1)
        {
            if(find->elem.mail_head != find->elem.mail_tail)
            {
                ENTER_CRITICAL_AREA(&msb->mutex);
                out_queue(find, temp);
                QUIT_CRITICAL_AREA(&msb->mutex);
                break;
            }
        }
    }

    strcpy(sendname, temp->name_of_sender);
    memcpy(data, &(temp->data), sizeof(DATATYPE));

    free(temp);

    return 0;

}
int main()
{
    mbs = create_mail_box_system();

    register_to_mail_system(mbs,"show",show_th);
    register_to_mail_system(mbs,"sock",sock_th);
    register_to_mail_system(mbs,"data",data_collect_th);


    wait_all_end(mbs);
    destroy_mail_box_system(mbs);

    return 0;
}



