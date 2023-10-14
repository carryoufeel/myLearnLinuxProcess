#include <stdio.h>
#include "head.h"
// onenet version demo  
const char* topic[]={
"$sys/XgGX8VRvEg/first_device/thing/property/post/reply",    //订阅
"$sys/XgGX8VRvEg/first_device/thing/property/post",         //发布
};
volatile MQTTClient_deliveryToken deliveredtoken;
// 发送成功后callback
void delivered(void *context, MQTTClient_deliveryToken dt)
{
	printf("Message with token value %d delivery confirmed\n", dt);
	deliveredtoken = dt;
}
// 接收到消息的callback
int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
	int i;
	char* payloadptr;

	printf("Message arrived\n");
	printf("     topic: %s\n", topicName);
	printf("   message: ");

	payloadptr = (char*)message->payload;
	for(i=0; i<message->payloadlen; i++)
	{
		putchar(*payloadptr++);
	}
	putchar('\n');
	MQTTClient_freeMessage(&message);
	MQTTClient_free(topicName);
	return 1;
}
// 掉线后的callback
void connlost(void *context, char *cause)
{

	printf("\nConnection lost\n");
	printf("     cause: %s\n", cause);

}
// 主流程
int do_handle()
{

    MQTTClient client;

    int rc = MQTTClient_create(&client, ADDRESS, CLIENTID,
                               MQTTCLIENT_PERSISTENCE_NONE, NULL);
    int ch;
    if(MQTTCLIENT_SUCCESS != rc)
    {
        printf("create mqtt client failre...\n");
        exit(1);
    }
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.username="XgGX8VRvEg";
    conn_opts.password="version=2018-10-31&res=products%2FXgGX8VRvEg%2Fdevices%2Ffirst_device&et=1837255523&method=md5&sign=v35WGqGxdjsa4coTU0hmJg%3D%3D";
    rc = MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);
    if(MQTTCLIENT_SUCCESS !=rc )
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }
#if 0
    //订阅单个主题  如果需要订阅的话    
    MQTTClient_subscribe(client, topic[0], QOS);
    printf("Subscribing to topic %s\nfor client %s using QoS%d\n\n"
           , topic[0], CLIENTID, QOS);

#endif 

    MQTTClient_deliveryToken deliveryToken;
    MQTTClient_message test2_pubmsg = MQTTClient_message_initializer;
    // 需要发送的正文
    char message[1024]={0};
    test2_pubmsg.qos = QOS;
    test2_pubmsg.retained = 0;
    test2_pubmsg.payload =message;
    int i = 20;
    int vol = 0;
    int curr=0;
    int temp = 0 ;
    int id =10000;
    srand(time(NULL));

    while(i--)
    {
        vol  = rand()%20+100;
        curr = rand()%15+50;
        temp = rand()%10+20;
        sprintf(message,"{\"id\":\"%d\",\"version\":\"1.0\",\"params\":{\"current\":{\"value\":%d},\"relay\":{\"value\":true},\"temp\":{\"value\":%d},\"voltage\":{\"value\":%d}}}",id++,curr,temp,vol);
        test2_pubmsg.payloadlen = strlen(message);

        printf("%s\n",message);
        rc = MQTTClient_publishMessage(client,topic[1],&test2_pubmsg,&deliveryToken);
        if(MQTTCLIENT_SUCCESS != rc)
        {
            printf("client to publish failure.. %lu\n",pthread_self());
            exit(1);
        }
        printf("Waiting for up to %d seconds for publication on topic %s for client with ClientID: %s\n"
               ,(int)(TIMEOUT/1000), topic[0], CLIENTID);
        MQTTClient_waitForCompletion(client,deliveryToken,TIMEOUT);
        sleep(3);
    }


    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return rc;
}
int main(void)
{

    do_handle();
    printf("Hello World!\n");
    return 0;
}

