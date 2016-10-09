#define START_NUM  10000000		//开始ID
#define SUM_NUM	10000		//总数

//#define DESTIP "163.177.171.209"			//www.ip138.com
#define URL "www.ip138.com"			//www.ip138.com
#define DESTPORT 80
#define SLEEP_TIME 20

struct var{
	char *front;
	char *end;
	char *f_str;
	char *e_str;
};

struct var req_args[]={
	{"src","\" rel","src=\"","\" "}
#if 0
	{"个人资料_",	"（",	"个人资料_",	"（"},
	{"佳缘ID:",	"）",	"佳缘ID:",	"）"},
	{"查看详细信息",		"，",	"查看详细信息&gt;&gt;</a>",	"，"},
	{"查看详细信息",		"岁，",	"查看详细信息&gt;&gt;</a>女，",	"岁，"},
//	{"查看详细信息",		"座，",	"查看详细信息&gt;&gt;</a>女，28岁，",	"座，"},
	{"查看详细信息",		"</h2>",	"查看详细信息&gt;&gt;</a>女，28岁，天秤座，来自",	"</h2>"},
	{"身高：",		"厘米",	"身高：</b>",	"厘米"},
	{"学历：",		"</span>",	"学历：</b>",	"</span>"},
	{"婚姻：",		"</span>",	"婚姻：</b>",	"</span>"},
//	{"民族：",		"</span>",	"民族：</b>",	"</span>"},
	{"我的佳缘标签",		"/",		"我的佳缘标签",	"/"},
	{"<li>",		"</li>",		"<li>",	"</li>"},
	{"生　　肖：",		"</li>",	"生　　肖：</span>",	"</li>"},
	{"公司名称：",		"</li>",		"公司名称：</span>",	"</li>"},
	{"毕业学校：",		"</li>",		"毕业学校：</span>",	"</li>"},
#endif
};
