#include<stdio.h>
#include<string.h>
struct Date
{
	int year;
	int month;
	int day;
};
struct Student
{
	int id;
	char Name[20];
	float score;
	struct Date birthday;
};
int namecmp(struct Student *s1,struct Student *s2)
{
	if(strcmp(s1->Name,s2->Name)<0)
	{
		return 1;
	}
	else if(strcmp(s1->Name,s2->Name)==0)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}
int scorecmp(struct Student *s1,struct Student *s2)
{
	if(s1->score>s2->score)
	{
		return 1;
	}
}
void swap(struct Student *a,struct Student *b)
{
	struct Student t;
	t=*a;
	*a=*b;
	*b=t;
}
void printStudents(struct Student *s,int len)
{
	for(int i=0;i<len;++i)
	{
		printf("%d %s %f %d-%d-%d\n",(s+i)->id,(s+i)->Name,
			   (s+i)->score,(s+i)->birthday.year,
			   (s+i)->birthday.month,(s+i)->birthday.day);
	}
}
void sort(struct Student *s,int len,int(*pfn)(struct Student *,struct Student *))
{
	for(int i=0;i<len-1;++i)
	{
		for(int j=i;j<len;++j)
		{
			if(pfn(s+i,s+j)<0)
			{
				swap(s+i,s+j);
			}
		}
	}
}
void reverseStudent(struct Student *s,int len)
{
	for(int i=0;i<len/2;++i)
	{
		swap(s+i,s+len-i-1);
	}
}
int main()
{
	struct Student s[3]={{1,"xx",60,{2002,10,10}}
						,{2,"yy",59,{2001,9,10}}
						,{3,"zz",30,{2001,10,1}}};
	sort(s,sizeof(s)/sizeof(*s),namecmp);
	//reverseStudent(s,sizeof(s)/sizeof(*s));
	printStudents(s,sizeof(s)/sizeof(*s));
}
