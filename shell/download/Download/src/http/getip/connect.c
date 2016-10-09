#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
//#include <sqlite3.h>
#include "var.h"

//#define Req "GET /38061262 HTTP/1.1\r\nHost: 59.151.18.26\r\nConnection: Close\r\n\r\n"
#define BUFSIZE 1024
#define BUFF_LEN 1024*1
#define RES_BUFF_LEN 1024*1024*1
char buff[RES_BUFF_LEN];
char res_buff[RES_BUFF_LEN];
char html_buff[RES_BUFF_LEN];

int create_result_file()
{
	int fd;
	char buff[1024];
	time_t   now;
	struct   tm     *timenow; 

	time(&now);
	timenow   =   localtime(&now);

	fd = open("result.txt",O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
	if(fd == -1)
	{
		printf("error:open result file\n");
		exit(0);
	}
#if 0
	sprintf(buff,"*******************************************\n");
	write(fd,buff,strlen(buff));
	sprintf(buff,"			http get date		\n");
	write(fd,buff,strlen(buff));
	sprintf(buff,"			time:%d-%d-%d %d:%d		\n",timenow->tm_year+1900,timenow->tm_mon+1,timenow->tm_mday,timenow->tm_hour,timenow->tm_min);
	write(fd,buff,strlen(buff));
	sprintf(buff,"*******************************************\n");
	write(fd,buff,strlen(buff));
	sprintf(buff,"no	name	id		age\n");
	write(fd,buff,strlen(buff));
	sprintf(buff,"-------------------------------------------\n");
	write(fd,buff,strlen(buff));
#endif
	printf("create file ok !\r\n");

	return fd;
}

#ifdef DB_FILE
sqlite3 *db;  
int create_db_file()  
{
	char sql[128];  

	sqlite3_open("test.db", &db); 

	memset(sql, 0, 128);  
	sprintf(sql, "%s%s%s", "create table ",	"test_tb",	"(id INTEGER PRIMARY KEY, data TEXT)");  
	sqlite3_exec(db, sql, NULL, NULL, NULL);  
	return 0;
}
int write_db(char *sql)
{
	sqlite3_exec(db, sql, NULL, NULL, NULL);  
}
#endif
#if 1
int print_result(char *buf, int len)
{
	int fd;
	int result;

	fd = open("html.txt",O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
	if(fd == -1)
	{
		printf("error:open html file\n");
		return -1;
	}
	result = write(fd,buf,len);
	if(result == -1)
	{
		printf("error:write html file\n");
		return -1;
	}
	close(fd);
}
#endif

char strRequest[BUFSIZE];
int http_connect(char *DestIp)
{
	int cfd;
	struct sockaddr_in s_add,c_add;

	cfd = socket(AF_INET,SOCK_STREAM,0);
	if(cfd == -1)
	{
		printf("error: socket create\n");
		return 0;
	}

	printf("socket ok!\n");
	bzero(&s_add,sizeof(struct sockaddr_in));
	s_add.sin_family=AF_INET;
	s_add.sin_addr.s_addr= inet_addr(DestIp);
	s_add.sin_port=htons(DESTPORT);
	printf("s_addr = %#x ,port : %#x\r\n",s_add.sin_addr.s_addr,s_add.sin_port);

	if(-1 == connect(cfd,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
	{
		printf("connect fail !\r\n");
		exit(0);
	}
	printf("connect ok !\r\n");

	return cfd;
}

int send_msg(int cfd)
{
	char strResponse[BUFSIZE]={0};
	int nRequestLen;
	int recbytes;
	int size_html;
	int i;

	nRequestLen = strlen(strRequest);
	//	strncpy(strRequest, Req,strlen(Req));
	printf("%s\n",strRequest);
	if(-1 == (recbytes = write(cfd,strRequest,nRequestLen)))
	{
		printf("read data fail !\r\n");
		return -1;
	}

	printf("recbytes==%d\n",recbytes);
	size_html = 0;
	memset(html_buff,0,sizeof(html_buff));
	while(1)
	{
		i = read(cfd,strResponse,BUFSIZE-1);	
		if(0 >= i){
			break;
		}
		strResponse[i]='\0';
		strcat(html_buff,strResponse);

		size_html += i;
	}
	print_result(html_buff,size_html);
	printf("size_html:%d\n",size_html);

	return size_html;
}

int no_date;
int do_things(int rfd)
{
	int rd;
	int fd1;
	char *p,*f,*e;
	int i,num;
	char var_buf[100],seg_buf[100];
	char buff[100];
	int str_len;

#if 0
	fd1 = open("html.txt",O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR);
	if(fd1 == -1)
	{
		printf("error:open result file\n");
		return 0;
	}
	rd = write(fd1,html_buff,strlen(html_buff));
	if(rd <= 0)
	{
		printf("write html file error!\n");	
		return 0;
	}
	close(fd1);
#endif

#if 1
	memset(res_buff,0,sizeof(res_buff));
	no_date++;
	//sprintf(res_buff,"%d:",no_date);
	num = sizeof(req_args)/sizeof(struct var);
	f = html_buff;
	for(i=0; i< num; i++)
	{
		f = strstr(f,req_args[i].front);
		if(f == 0 && i==8)
		{
			i+=2;
			f = html_buff;
			continue;
		}
		e = strstr(f,req_args[i].end);
		p = f + strlen(req_args[i].f_str);

		str_len = e - f - strlen(req_args[i].f_str);
		memcpy(var_buf, p, str_len);
		var_buf[str_len] = 0;

		sprintf(seg_buf,"%10s\t",var_buf);
		strcat(res_buff,seg_buf);
	}
	res_buff[strlen(res_buff)] = '\n';
	printf("%s\n",res_buff);
	printf("ok\n");

#ifdef DB_FILE
	rd = write(rfd,res_buff,strlen(res_buff));
#else
	rd = write(rfd,res_buff,strlen(res_buff));
#endif
#endif
	return rd;
}

int read_start_no(int *start_num)
{
	int fd;
	int ret;
	char buff[100];

	fd = open("start_no.txt",O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if(fd <= 0)
	{
		printf("error:open start_no file\n");
		exit(0);
	}

	lseek(fd,0,SEEK_SET);
	ret = read(fd,buff,100);
	if(ret <= 0)
		*start_num = START_NUM;
	else
		*start_num = atoi(buff)+1;

	return fd;
}
char result_url[100];
int read_result_file()
{
	int fd;
	int ret;

	fd = open("result.txt",O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if(fd <= 0)
	{
		printf("error:open result file\n");
		exit(0);
	}

	memset(result_url,0,sizeof(result_url));
	ret = read(fd,result_url,100);
	if(ret <= 0)
		return 0;
	else
		return 1;
}

int get_host_by_name(char *url,char *DestIp)
{
	char   *ptr, **pptr;
	struct hostent *hptr;
	char   str[32];

	if((hptr = gethostbyname(url)) == NULL)
	{
		printf(" gethostbyname error for host:%s\n", ptr);
		return 0; 
	}
	printf("official hostname:%s\n",hptr->h_name);
	for(pptr = hptr->h_aliases; *pptr != NULL; pptr++)
		printf(" alias:%s\n",*pptr);

	printf("*******\n");
	switch(hptr->h_addrtype)
	{
		case AF_INET:
		case AF_INET6:
			pptr=hptr->h_addr_list;
			for(; *pptr!=NULL; pptr++)
			{
				inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str));
				printf("address: %s\n",str);
				memcpy(DestIp,str,strlen(str));
			}
					inet_ntop(hptr->h_addrtype, hptr->h_addr, str, sizeof(str));
			printf(" first address: %s\n", str);
			break;
		default:
			printf("unknown address type\n");
			break;
	}

	return 0;
}

#define URL_LEN 50
int anger_url(char *font,char *end)
{
	char *p;

	memset(font,0,URL_LEN);
	memset(end,0,URL_LEN);
	p = strstr(result_url,"com\/");
	printf("strlen(result_url) == %d\n",strlen(result_url));
	printf("p-result_url == %d\n",p-result_url);
	if(p == NULL)
		return 0;
	else
	{
		memcpy(font,result_url+strlen("http://"),p-result_url-strlen("http://")+strlen("com"));	
		memcpy(end,p+strlen("com/"),strlen(p+strlen("com/")));	
		printf("font:%s\n",font);
		printf("end:%s\n",end);
	}

	return 0;
}
int main(int argc, char **argv)
{
	int i;
	int ret;
	int rfd,cfd,nfd;
	int start_num,sum_num;
	char id_buff[URL_LEN];
	int fpid;
	char DestIp[URL_LEN];
	char font[URL_LEN],end[URL_LEN];

	rfd = create_result_file();
	sprintf(strRequest,"GET / HTTP/1.1\r\nHost: www.ip138.com\r\nConnection: Close\r\n\r\n");
	memset(DestIp,0,sizeof(DestIp));
	get_host_by_name(URL,DestIp);
	cfd = http_connect(DestIp);
	ret = send_msg(cfd);
	do_things(rfd);
	close(cfd);
	close(rfd);

	read_result_file();
	anger_url(font,end);
	sprintf(strRequest,"GET /%s HTTP/1.1\r\n%s\r\nConnection: Close\r\n\r\n",end,font);
	printf("%s",strRequest);
	memset(DestIp,0,sizeof(DestIp));
	get_host_by_name(font,DestIp);
	cfd = http_connect(DestIp);
	ret = send_msg(cfd);
	do_things(rfd);
	close(cfd);
	close(rfd);

}
