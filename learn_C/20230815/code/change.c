#include<stdio.h>
#include<string.h>
int strReplaceAll(char * str, char * sub, char * replace){
 
	if(NULL == str || NULL == sub || NULL == replace){
		printf("mystrcat param error\n");
	}	
 
	char * p = NULL;
	char * t = NULL;
	char * q = NULL;
	char * dst = NULL;
	char * src = NULL;
	
 
	int len = strlen(str);
	int len1 = strlen(sub);
	int len2 = strlen(replace);
 
	p = str;
	while('\0' != *p){
		t = str + len;
		q = strstr(str, sub);
		if(NULL == q) /*没有子串了，那么直接返回吧*/{
			break;
		}
 
		src = q + len1; /*源头, 原有sub后的一个字符*/
		dst = q + len2; /*目的，放完replace后的一个字符*/
		memcpy(dst, src, t - src); /*原有字符串后移，放出空间*/
		memcpy(q, replace, len2); /*将replace字符拷贝进来*/
		len = len + len2 - len1;
		
		p = q + len2; /* p 下一轮replace后的一个字符 */
	}
	
	str[len] = '\0';
	return 0;/*通过'\0'表示结尾*/
 
}
 
 
void teststrReplaceAll(void){
	char str[] = "GET /?app=weather.realtime&cityNm=whatis&ag=today,futureDay,lifeIndex,futureHour&appkey=69832&sign=a99d50a35007641b8e3fe21ea0c6acb3&format=json HTTP/1.1";
	char sub[100] = "whatis";
	char replace[100] = "西安";
	//char replace[100] = "2";
	int num0  = 0, num1 = 0;
 
	printf("\n************  teststrReplaceAll ************ \n");
	
	strReplaceAll(str, sub, replace);
	
	printf("After replace all, str is : %s\n", str);
 
	return;	
}
int main()
{
	teststrReplaceAll();
}

