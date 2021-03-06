#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
//#include <sqlite3.h>
#include "define.h"
#include "var.h"

#ifdef _DEBUG_
#define qz_printf(format,args...) printf(format, ##args)
#else
#define qz_printf(format,args...) 
#endif

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

	fd = open("result.txt",O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR);
	if(fd == -1)
	{
		printf("error:open result file\n");
		exit(0);
	}
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
	qz_printf("create file ok !\r\n");

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

	printf("into print_result!\n");
	fd = open("html.txt",O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
	if(fd == -1)
	{
		printf("error:open html file\n");
		return -1;
	}
	printf("create html.txt success!\n");
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
int http_connect()
{
	int cfd;
	struct sockaddr_in s_add,c_add;

	cfd = socket(AF_INET,SOCK_STREAM,0);
	if(cfd == -1)
	{
		printf("error: socket create\n");
		return 0;
	}

	qz_printf("socket ok!\n");
	bzero(&s_add,sizeof(struct sockaddr_in));
	s_add.sin_family=AF_INET;
	s_add.sin_addr.s_addr= inet_addr(DestIp);
	s_add.sin_port=htons(DestPort);
	qz_printf("s_addr = %#x ,port : %#x\r\n",s_add.sin_addr.s_addr,s_add.sin_port);

	if(-1 == connect(cfd,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
	{
		printf("connect fail !\r\n");
		exit(0);
	}
	qz_printf("connect ok !\r\n");

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
	//qz_printf("%s\n",strRequest);
	if(-1 == (recbytes = write(cfd,strRequest,nRequestLen)))
	{
		printf("read data fail !\r\n");
		return -1;
	}

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
	qz_printf("size_html:%d\n",size_html);

	return size_html;
}

int no_date;
int do_things(int rfd)
{
	int rd;
	char *p,*f,*e;
	int i,num;
	char var_buf[100],seg_buf[100];
	char buff[100];
	char sql_buff[1024];
	int str_len;

#if 0
	fd1 = open("result.txt",O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR);
	if(fd1 == -1)
	{
		printf("error:open result file\n");
		return 0;
	}
	fd2 = open("html.txt",O_RDONLY);
	if(fd2 == -1)
	{
		printf("error:open html file\n");
		return -1;
	}
	rd = read(fd2,buff,RES_BUFF_LEN);
	if(rd <= 0)
	{
		printf("read num:0\n");
		return 0;
	}
	printf("rd:%d\n",rd);
#endif

	qz_printf("haha\n");
	//qz_printf("%s",html_buff);
	memset(res_buff,0,sizeof(res_buff));
	no_date++;
	sprintf(res_buff,"%d:",no_date);
	num = sizeof(req_args)/sizeof(struct var);
	f = html_buff;
	for(i=0; i< num; i++)
	{
		qz_printf("i == %d\n",i);
		f = strstr(f,req_args[i].front);
		qz_printf("f:%d\n",f-html_buff);
		if(f == 0 && i==8)
		{
			i+=2;
			f = html_buff;
			continue;
		}
		e = strstr(f+strlen(req_args[i].f_str),req_args[i].end);
		p = f + strlen(req_args[i].f_str);

		str_len = e - f - strlen(req_args[i].f_str);
		memcpy(var_buf, p, str_len);
		var_buf[str_len] = 0;

		sprintf(seg_buf,"%10s\t",var_buf);
		strcat(res_buff,seg_buf);
		f += strlen(req_args[i].f_str);
	}
	res_buff[strlen(res_buff)] = '\n';
	//qz_printf("%s\n",res_buff);
	printf("ok\n");

#ifdef DB_FILE
	sprintf(sql_buff,"INSERT INTO \"test_tb\" VALUES( NULL , 1 , 1 , '200605011206', 18.9 );");
	rd = write_db(sql_buff);
#else
	rd = write(rfd,res_buff,strlen(res_buff));
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
int main(int argc, char **argv)
{
	int i;
	int ret;
	int rfd,cfd,nfd;
	int start_num,sum_num;
	char id_buff[50];
	int fpid;

	for(;;)
	{
		fpid = fork();
		if(fpid < 0)
		{printf("fork error!\n"); return 0;}
		else if(fpid == 0)
		{
			qz_printf("fork success!\n");
			nfd = read_start_no(&start_num);
#ifdef DB_FILE
			create_db_file();  
#else 
			rfd = create_result_file();
#endif

			for(i=0; i< SUM_NUM; i++)
			{
				qz_printf("i==%d:",start_num + i);
				cfd = http_connect();
				if(cfd <= 0)
				{
				//	printf("sleep:%ds\n",SLEEP_TIME);
				//	sleep(SLEEP_TIME);
				//	i--;
				//	continue;
					return 0;
				}
			//	sprintf(id_buff,"%d            ",start_num + i);
			//	lseek(nfd,0,SEEK_SET);
			//	write(nfd,id_buff,strlen(id_buff));

				sprintf(strRequest,"GET /%d HTTP/1.1\r\nHost: %s\r\nConnection: Close\r\n\r\n",start_num + i,DestIp);
				ret = send_msg(cfd);
				if (ret < 40*1024)
				{
					printf("\n");
					continue;
				}
				do_things(rfd);
				close(cfd);
			}

#ifdef DB_FILE
			close(db);
#else
			close(rfd);
#endif
			//close(cfd);
			close(nfd);
			return 0;
		}
		else 
		{
			waitpid(fpid,0,0);	
			qz_printf("child process exit!\n");
			return 0;
		}
	}
}
