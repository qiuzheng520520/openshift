#define START_NUM  10000000		//开始ID
#define SUM_NUM	1		//总数

#define DestIp "59.151.18.26"			//www.jiayuan.com
#define DestPort 80
#define SLEEP_TIME 20

struct var{
	char *front;
	char *end;
	char *f_str;
	char *e_str;
};

char CR[]={0x0D,0x0A,0x0};				//回车
struct var req_args[]={
	{"个人资料_",	"（",	"个人资料_",	"（"},		//网名
	{"佳缘ID:",	"）",	"佳缘ID:",	"）"},				//ID
	{"member_name","，","member_name\">","，"},						//年龄
	{"岁","，来自","岁，","，来自"},							//婚否
	{"来自","</h6>","来自","</h6>"},					//地区
	{"<em>","</em>","<em>","</em>"},					//学历
	{" <em>","</em>"," <em>","</em>"},					//身高
	{"<em  >","</em>","<em  >","</em>"},				//体重
	{"<em>","</em>","<em>","</em>"},					//星座
	{"<em  >","</em>","<em  >","</em>"},				//名族
	{"<em>","</em>","<em>","</em>"},					//属相
	{"js_text",CR,"js_text\">\
		                            　　",CR},					//自我介绍
	{"爱好\"></span>","</li>","爱好\"></span>","</li>"},					//爱好
	{"职业职位：","</em>","职业职位：</span>\
		                                        <div class=\"ifno_r_con\"><em  >","</em>"},					//职位
	{"公司行业","</em>","公司行业：</span>\
		                                        <div class=\"ifno_r_con\"><em  class=\"info_null\" msg_id=\"31\"  >","</em>"},					//属相
//	{"身高：",		"厘米",	"身高：</b>",	"厘米"},
//	{"学历：",		"</span>",	"学历：</b>",	"</span>"},
//	{"婚姻：",		"</span>",	"婚姻：</b>",	"</span>"},
//	{"民族：",		"</span>",	"民族：</b>",	"</span>"},
//	{"我的佳缘标签",		"/",		"我的佳缘标签",	"/"},
//	{"<li>",		"</li>",		"<li>",	"</li>"},
//	{"生　　肖：",		"</li>",	"生　　肖：</span>",	"</li>"},
//	{"公司名称：",		"</li>",		"公司名称：</span>",	"</li>"},
//	{"毕业学校：",		"</li>",		"毕业学校：</span>",	"</li>"},
};

struct result_str{
	char net_name[40];
	char id[20];
	char age[20];
	char marry[40];
	char aray[40];
	char school[20];
	char high[20];
	char hight[20];
	char star[20];
	char nation[40];
	char zodiac[20];
	char explain[4096];
};

