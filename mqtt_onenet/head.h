#ifndef HEAD_H
#define HEAD_H


#include <MQTTAsync.h>
#include <MQTTClient.h>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include <string.h>
#define ADDRESS     "tcp://218.201.45.7:1883"
#define CLIENTID    "first_device"
#define PAYLOAD     "Hello World!"
#define QOS         0
#define TIMEOUT     10000L
//#define __cplusplus
#endif // HEAD_H
