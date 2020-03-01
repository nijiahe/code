
/* Result Sets Interface */
#ifndef SQL_CRSR
#  define SQL_CRSR
  struct sql_cursor
  {
    unsigned int curocn;
    void *ptr1;
    void *ptr2;
    unsigned int magic;
  };
  typedef struct sql_cursor sql_cursor;
  typedef struct sql_cursor SQL_CURSOR;
#endif /* SQL_CRSR */

/* Thread Safety */
typedef void * sql_context;
typedef void * SQL_CONTEXT;

/* Object support */
struct sqltvn
{
  unsigned char *tvnvsn; 
  unsigned short tvnvsnl; 
  unsigned char *tvnnm;
  unsigned short tvnnml; 
  unsigned char *tvnsnm;
  unsigned short tvnsnml;
};
typedef struct sqltvn sqltvn;

struct sqladts
{
  unsigned int adtvsn; 
  unsigned short adtmode; 
  unsigned short adtnum;  
  sqltvn adttvn[1];       
};
typedef struct sqladts sqladts;

static struct sqladts sqladt = {
  1,1,0,
};

/* Binding to PL/SQL Records */
struct sqltdss
{
  unsigned int tdsvsn; 
  unsigned short tdsnum; 
  unsigned char *tdsval[1]; 
};
typedef struct sqltdss sqltdss;
static struct sqltdss sqltds =
{
  1,
  0,
};

/* File name & Package Name */
struct sqlcxp
{
  unsigned short fillen;
           char  filnam[13];
};
static const struct sqlcxp sqlfpn =
{
    12,
    "5_dynamic.pc"
};


static unsigned int sqlctx = 282147;


static struct sqlexd {
   unsigned int   sqlvsn;
   unsigned int   arrsiz;
   unsigned int   iters;
   unsigned int   offset;
   unsigned short selerr;
   unsigned short sqlety;
   unsigned int   occurs;
      const short *cud;
   unsigned char  *sqlest;
      const char  *stmt;
   sqladts *sqladtp;
   sqltdss *sqltdsp;
            void  **sqphsv;
   unsigned int   *sqphsl;
            int   *sqphss;
            void  **sqpind;
            int   *sqpins;
   unsigned int   *sqparm;
   unsigned int   **sqparc;
   unsigned short  *sqpadto;
   unsigned short  *sqptdso;
   unsigned int   sqlcmax;
   unsigned int   sqlcmin;
   unsigned int   sqlcincr;
   unsigned int   sqlctimeout;
   unsigned int   sqlcnowait;
              int   sqfoff;
   unsigned int   sqcmod;
   unsigned int   sqfmod;
   unsigned int   sqlpfmem;
            void  *sqhstv[4];
   unsigned int   sqhstl[4];
            int   sqhsts[4];
            void  *sqindv[4];
            int   sqinds[4];
   unsigned int   sqharm[4];
   unsigned int   *sqharc[4];
   unsigned short  sqadto[4];
   unsigned short  sqtdso[4];
} sqlstm = {13,4};

/* SQLLIB Prototypes */
extern void sqlcxt (void **, unsigned int *,
                    struct sqlexd *, const struct sqlcxp *);
extern void sqlcx2t(void **, unsigned int *,
                    struct sqlexd *, const struct sqlcxp *);
extern void sqlbuft(void **, char *);
extern void sqlgs2t(void **, char *);
extern void sqlorat(void **, unsigned int *, void *);

/* Forms Interface */
static const int IAPSUCC = 0;
static const int IAPFAIL = 1403;
static const int IAPFTL  = 535;
extern void sqliem(unsigned char *, signed int *);

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* cud (compilation unit data) array */
static const short sqlcud0[] =
{13,4130,852,0,0,
5,0,0,1,0,0,17,89,0,0,1,1,0,1,0,1,97,0,0,
24,0,0,1,0,0,11,95,0,0,1,1,0,1,0,1,32,0,0,
43,0,0,1,0,0,15,103,0,0,0,0,0,1,0,
58,0,0,2,0,0,29,104,0,0,0,0,0,1,0,
73,0,0,3,0,0,30,108,0,0,0,0,0,1,0,
88,0,0,0,0,0,27,137,0,0,4,4,0,1,0,1,97,0,0,1,10,0,0,1,10,0,0,1,10,0,0,
119,0,0,1,0,0,19,204,0,0,1,1,0,1,0,3,32,0,0,
138,0,0,1,0,0,20,249,0,0,1,1,0,1,0,3,32,0,0,
157,0,0,1,0,0,14,341,0,0,1,0,0,1,0,2,32,0,0,
};


#define _CRT_SECURE_NO_WARNINGS
/*C头文件*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <setjmp.h>

/*SQL头文件*/  
#include <sqlcpr.h>
#include <sqlda.h>  
#include <sqlca.h>

#define MAX_ITEMS  40//定义最多有几列
#define MAX_VNAME_LEN 24//定义列名字符串最大长度
#define MAX_NAME_LEN 24//定义列中的项字符串最大长度

/*
		/opt/app/oracle/product/12.2.0/dbhome_1/precomp/public
*/

/*定义绑定描述区和选择描述区的指针,如4_中的输入描述区和输出描述区*/
/*和4的区别在于4的描述区由ansi标准分配,而此处手动分配*/
/*描述区每次只存储一行的数据,每次通过fetch到描述区接受新的数据*/
//struct SQLDA {
  /* ub4    */ int        N; /* Descriptor size in number of entries        *//*最大的列个数*/
  /* text** */ char     **V; /* Ptr to Arr of addresses of main variables   *//*存储数据的地址*/
  /* ub4*   */ int       *L; /* Ptr to Arr of lengths of buffers            *//*存储数据的size*/
  /* sb2*   */ short     *T; /* Ptr to Arr of types of buffers              *//*存储列项的数据类型*/
  /* sb2**  */ short    **I; /* Ptr to Arr of addresses of indicator vars   *//*指针变量的地址*/
  /* sb4    */ int        F; /* Number of variables found by DESCRIBE       *//*实际的列个数*/
  /* text** */ char     **S; /* Ptr to Arr of variable name pointers        *//*存储列名的二级指针*/
  /* ub2*   */ short     *M; /* Ptr to Arr of max lengths of var. names     *//*存储最大的列名长度*/
  /* ub2*   */ short     *C; /* Ptr to Arr of current lengths of var. names *//*存储每列列名的长度*/
  /* text** */ char     **X; /* Ptr to Arr of ind. var. name pointers       */
  /* ub2*   */ short     *Y; /* Ptr to Arr of max lengths of ind. var. names*/
  /* ub2*   */ short     *Z; /* Ptr to Arr of cur lengths of ind. var. names*/
 // };
 /*结构体的定义在:*/
/*
 		/opt/app/oracle/product/12.2.0/dbhome_1/precomp/public/sqlda.h
*/
SQLDA* bind_dp;
SQLDA* select_dp;

/* EXEC SQL BEGIN DECLARE SECTION; */ 

	char sql_stat[100];//存放用户输入的命令
	char current_date[20];
	char username[20];
	char passwd[20];
	char server[20];
	//char* serverid="system/A512666#asdf@orcl";
	char* serverid="c##scott/tiger@orcl";
/* EXEC SQL END DECLARE SECTION; */ 


void sqlerr();//SQL语句发生错误时被执行
void connet();//链接数据库函数
void alloc_descriptors(int size,int max_vname_len,int max_iname_len);//分配空间  
void dealloc_descriptors();//释放空间
void set_bind_variables();//处理输入数据的函数(绑定变量 :a,:b)(即设置绑定变量)
void process_select_list();//处理输出数据的函数
void printfstr(char* str,int size);

int main()
{

		/* EXEC SQL WHENEVER SQLERROR DO sqlerr(); */ 


		/*链接登陆数据库*/
		connet();
		
		/*分配两个描述区的内存*/
		alloc_descriptors(MAX_ITEMS,MAX_VNAME_LEN,MAX_NAME_LEN);
		
		while(1)
		{
				printf("<SQL>");
				fgets(sql_stat,100,stdin);
				int len=strlen(sql_stat);
				sql_stat[len-1]='\0';
				if(sql_stat[len-2]==';')
				{
						sql_stat[len-2]='\0';
				}
				if(strncmp(sql_stat,"quit",4)==0||strncmp(sql_stat,"quit",4)==0)
				{
						break;
				}
				//1.准备SQL动态语句
				/* EXEC SQL PREPARE my_pre_sql FROM :sql_stat; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 1;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )5;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)sql_stat;
    sqlstm.sqhstl[0] = (unsigned int  )100;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         void  *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned int  )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sqlerr();
}


				//2.定义光标
				/* EXEC SQL DECLARE my_cursor CURSOR FOR my_pre_sql; */ 

				//3.处理输入变量(即设置绑定变量)
				set_bind_variables();
				//4.打开游标
				/* EXEC SQL OPEN my_cursor USING DESCRIPTOR bind_dp; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 1;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )24;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.sqlpfmem = (unsigned int  )0;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqcmod = (unsigned int )0;
    sqlstm.sqhstv[0] = (         void  *)bind_dp;
    sqlstm.sqhstl[0] = (unsigned int  )0;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         void  *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned int  )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sqlerr();
}


				
				/*如果是select语句,处理输出变量*/
				if(strncmp(sql_stat,"select",6)==0||strncmp(sql_stat,"select",6)==0)
				{
						process_select_list();
				}
				//5.关闭游标
				/* EXEC SQL CLOSE my_cursor; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 1;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )43;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sqlerr();
}


				/* EXEC SQL COMMIT; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 1;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )58;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sqlerr();
}

//提交

		}
		dealloc_descriptors();//释放描述区
		/* EXEC SQL COMMIT WORK RELEASE; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 1;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )73;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
  if (sqlca.sqlcode < 0) sqlerr();
}

//提交并断开
		return 0;
		
}

void sqlerr()  
{ 
    /* 显示SQL错误 */  
    printf("%.*s\n" , sqlca.sqlerrm.sqlerrml , sqlca.sqlerrm.sqlerrmc);
    exit(1); 
}  
  

void connet()
{
		/*int len;
		printf("username:");
		fgets(username,sizeof(username),stdin);
		len=strlen(username);
		username[len-1]='\0';
		printf("passwd:");
		fgets(passwd,sizeof(passwd),stdin);
		len=strlen(passwd);
		passwd[len-1]='\0';
		printf("server:");
		fgets(server,sizeof(server),stdin);
		len=strlen(server);
		server[len-1]='\0';
		EXEC SQL CONNECT :username IDENTIFIED by :passwd USING :server;*/
		/* EXEC SQL CONNECT :serverid; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )10;
  sqlstm.offset = (unsigned int  )88;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)serverid;
  sqlstm.sqhstl[0] = (unsigned int  )0;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqphsv = sqlstm.sqhstv;
  sqlstm.sqphsl = sqlstm.sqhstl;
  sqlstm.sqphss = sqlstm.sqhsts;
  sqlstm.sqpind = sqlstm.sqindv;
  sqlstm.sqpins = sqlstm.sqinds;
  sqlstm.sqparm = sqlstm.sqharm;
  sqlstm.sqparc = sqlstm.sqharc;
  sqlstm.sqpadto = sqlstm.sqadto;
  sqlstm.sqptdso = sqlstm.sqtdso;
  sqlstm.sqlcmax = (unsigned int )100;
  sqlstm.sqlcmin = (unsigned int )2;
  sqlstm.sqlcincr = (unsigned int )1;
  sqlstm.sqlctimeout = (unsigned int )0;
  sqlstm.sqlcnowait = (unsigned int )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
  if (sqlca.sqlcode < 0) sqlerr();
}


		printf("connect success\n");
	


				
}

void printfstr(char* str,int size)
{
		int len=strlen(str);
		int i;
		printf("%s",str);
		for(i=0;i<size-len;i++)
		{
				printf(" ");
		}
}

void alloc_descriptors(int size,int max_vname_len,int max_iname_len)
{
		int i;
		/*调用SQL提供的分配描述区的函数分配描述区内存*/
		/*其中的二级指针只分配了指针数组内存,数组内容内存需要自己分配*/
		bind_dp=SQLSQLDAAlloc(0 ,size, MAX_VNAME_LEN, max_iname_len);
		select_dp=SQLSQLDAAlloc(0 , size , MAX_VNAME_LEN, max_iname_len);
		
		/* 为指示变量、绑定变量和选择列表项分配内存 */  
    for(i = 0 ; i != MAX_ITEMS ; ++i)  
    {  
        bind_dp->I[i] = (short*)malloc(sizeof(short));  
        select_dp->I[i] = (short*)malloc(sizeof(short));  
  
        bind_dp->V[i] = (char*)malloc(1);  
        select_dp->V[i] = (char*)malloc(1);  
    }
}

void dealloc_descriptors()  
{  
    int i;  
  
    /* 释放指示变量、绑定变量和选择列表项占用的内存 */
    /*先释放自己分配的*/
    for(i = 0 ; i != MAX_ITEMS ; ++i)  
    {  
        if(bind_dp->V[i] != (char*)0)  
            free(bind_dp->V[i]);  
        free(bind_dp->I[i]);  
  
        if(select_dp->V[i] != (char*)0)  
            free(select_dp->V[i]);  
        free(select_dp->I[i]);  
    }  
  
    /* 释放绑定描述区和选择描述区 */  
    SQLSQLDAFree(0 , bind_dp);  
    SQLSQLDAFree(0 , select_dp);  
}  

void set_bind_variables()  
{  
    char bind_var[64];  
    /*设置绑定变量最大个数*/  
    bind_dp->N = MAX_ITEMS;  
  
    /* 绑定变量名称: 绑定描述区*/  
    /* exec sql describe bind variables for my_pre_sql into bind_dp; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 13;
    sqlstm.arrsiz = 4;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )119;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)bind_dp;
    sqlstm.sqhstl[0] = (unsigned int  )0;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         void  *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned int  )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sqlerr();
}

  
  
    /* 设置绑定变量实际个数*/ 
    bind_dp->N = bind_dp->F;  
  
    /* 循环处理绑定变量 */
    int i;
    for(i = 1 ; i <= bind_dp->F ; i++)  
    {  
        /*显示绑定变量名*/  
        printf("请输入绑定变量%.*s的值：" , (int)bind_dp->C[i] , bind_dp->S[i]);  
        
        /* 输入绑定变量的值 */  
        fgets(bind_var,sizeof(bind_var),stdin);
        int len=strlen(bind_var);
        bind_var[len-1]='\0';
  
        /* 设置绑定变量的长度成员 */  
        bind_dp->L[i] = strlen(bind_var);  
  
        /* 为绑定变量数据缓冲区重新分配内存(多一位，留给'\0') */  
        bind_dp->V[i] = (char*)realloc(bind_dp->V[i] , bind_dp->L[i] + 1);  
  
        /* 绑定变量数据: 数据缓冲区 */  
        strcpy(bind_dp->V[i] , bind_var);  
  
        /* 设置指示变量，处理NULL */  
        if(0 == strncmp(bind_var , "NULL" , 4) || 0 == strncmp(bind_var , "null" , 4))  
            *bind_dp->I[i] = -1;  
        else  
            *bind_dp->I[i] = 0;  
  
        /* 设置数据缓冲区数据类型代码->char */  
        bind_dp->T[i] = 1;  
    }  
}

void process_select_list()//处理输出的函数,可以动态获取输出一共有几列数据,然后每次通过游标fetch到每一行并输出
{
		char title[MAX_VNAME_LEN];
		
		/* Descriptor size in number of entries        */
		/*即最多几列*/
		select_dp->N=MAX_ITEMS;
		/*选择描述区,给描述区起名*/
		/* EXEC SQL DESCRIBE SELECT LIST FOR my_pre_sql INTO select_dp; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )138;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)select_dp;
  sqlstm.sqhstl[0] = (unsigned int  )0;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqphsv = sqlstm.sqhstv;
  sqlstm.sqphsl = sqlstm.sqhstl;
  sqlstm.sqphss = sqlstm.sqhsts;
  sqlstm.sqpind = sqlstm.sqindv;
  sqlstm.sqpins = sqlstm.sqinds;
  sqlstm.sqparm = sqlstm.sqharm;
  sqlstm.sqparc = sqlstm.sqharc;
  sqlstm.sqpadto = sqlstm.sqadto;
  sqlstm.sqptdso = sqlstm.sqtdso;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
  if (sqlca.sqlcode < 0) sqlerr();
}


		/*设置列实际数量*/
		/*F: Number of variables found by DESCRIBE       */
		select_dp->N=select_dp->F;
		
    int i;
    for(i=0;i<select_dp->F;i++)
    {
    		int null_ok;
    		int scale;
    		int precision;
    		/* 清除select_dp->T[i]的高位->null */
        SQLColumnNullCheck(0,(unsigned short*)&select_dp->T[i],(unsigned short*)&select_dp->T[i],&null_ok);
    		switch(select_dp->T[i])  
        {  
        		/*2代表是数字*/
        		case 2:
    				/* number类型，取得精度与标度 */
    				/*调用这个函数会使scale保存一个值*/
    						SQLNumberPrecV6(0 , (unsigned long*)&select_dp->L[i] , &precision , &scale); 
    						if(scale > 0)  
                		/* 实数: 显示长度:float  */
                		{
                				select_dp->L[i] = sizeof(float);	
                		}
            		else  
                		/* 整数: 显示长度 int */
                		{
                				select_dp->L[i] = sizeof(int);	
                		}
         				break;
         		case 12:  
            		/* DATA数据类型(DD-MON-YY) */  
            		select_dp->L[i] = 9;  
            		break;  
        }
        /*重新为列表数据数组分配内存*/
        if(select_dp->T[i]!=2)
        {
        		select_dp->V[i]=(char*)realloc(select_dp->V[i] , select_dp->L[i] + 1);
        }
        else
        {
        		/* number类型 */
            select_dp->V[i] = (char*)realloc(select_dp->V[i] , select_dp->L[i]);
        }
        /* 初始化title */  
        memset(title , ' ' , MAX_VNAME_LEN);
        /* 选择列表项名称: title */  
        strncpy(title , select_dp->S[i] , select_dp->C[i]);  
  
        /* 显示列名 */
        /*是数字*/
        if(select_dp->T[i]==2)
        {
            if(scale > 0)  
                printf("%*.*s",MAX_VNAME_LEN,MAX_VNAME_LEN,title);  
            else  
                printf("%*.*s",MAX_VNAME_LEN,MAX_VNAME_LEN,title);
        }
        else//是日期
        {  
            printf("%*.*s",MAX_VNAME_LEN,MAX_VNAME_LEN,title);  
        }
        /* 根据Oracle内部类型确定外部数据类型(显示类型) */  
        if(select_dp->T[i]==2)  
        {  
            /* number 类型*/  
            if(scale > 0)  
                /* float */  
                select_dp->T[i] = 4;  
            else  
                /* int */  
                select_dp->T[i] = 3;  
        }  
        else  
            /* char */  
            select_dp->T[i] = 1;  
    }
    printf("\n");
    for(i=0;i<select_dp->F;i++)
    {
    		int j;
    		for(j=0;j<MAX_VNAME_LEN;j++)
    		{
    				printf("-");
    		}
    }
    printf("\n");
    /* EXEC SQL WHENEVER NOT FOUND DO break; */ 

    while(1)
    {
    		/* EXEC SQL FETCH my_cursor USING DESCRIPTOR select_dp; */ 

{
      struct sqlexd sqlstm;
      sqlstm.sqlvsn = 13;
      sqlstm.arrsiz = 4;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )157;
      sqlstm.selerr = (unsigned short)1;
      sqlstm.sqlpfmem = (unsigned int  )0;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)4352;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqfoff = (           int )0;
      sqlstm.sqfmod = (unsigned int )2;
      sqlstm.sqhstv[0] = (         void  *)select_dp;
      sqlstm.sqhstl[0] = (unsigned int  )0;
      sqlstm.sqhsts[0] = (         int  )0;
      sqlstm.sqindv[0] = (         void  *)0;
      sqlstm.sqinds[0] = (         int  )0;
      sqlstm.sqharm[0] = (unsigned int  )0;
      sqlstm.sqadto[0] = (unsigned short )0;
      sqlstm.sqtdso[0] = (unsigned short )0;
      sqlstm.sqphsv = sqlstm.sqhstv;
      sqlstm.sqphsl = sqlstm.sqhstl;
      sqlstm.sqphss = sqlstm.sqhsts;
      sqlstm.sqpind = sqlstm.sqindv;
      sqlstm.sqpins = sqlstm.sqinds;
      sqlstm.sqparm = sqlstm.sqharm;
      sqlstm.sqparc = sqlstm.sqharc;
      sqlstm.sqpadto = sqlstm.sqadto;
      sqlstm.sqptdso = sqlstm.sqtdso;
      sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
      if (sqlca.sqlcode == 1403) break;
      if (sqlca.sqlcode < 0) sqlerr();
}

//获取行数据输出到输出描述区
    		for(i=0;i<select_dp->F;i++)
    		{
    				if(*select_dp->I[i] < 0)
    				{  
                /* 处理NULL */  
                printf("%-*.*s",MAX_NAME_LEN,MAX_NAME_LEN,"NULL");
            }
            else
            {  
                if(select_dp->T[i]==3) 
                		{  
                    /* int */
                    char str[MAX_NAME_LEN];
                    memset(str,0,MAX_NAME_LEN);
                    snprintf(str,MAX_NAME_LEN-1,"%d",*(int*)select_dp->V[i]);
                    printf("%-*.*s",MAX_NAME_LEN,MAX_NAME_LEN,str);  
                }
                else if(select_dp->T[i]==4)
                {  
                    /* float */
                    int num=*(float*)select_dp->V[i];
                   	char str[MAX_NAME_LEN];
                    memset(str,0,MAX_NAME_LEN);
                    snprintf(str,MAX_NAME_LEN-1,"%d",num);
                    printf("%-*.*s",MAX_NAME_LEN,MAX_NAME_LEN,str);
                    
                }
                else
                {  
                  	/* char */  
                    printf("%-*.*s",MAX_NAME_LEN,MAX_NAME_LEN,select_dp->V[i]);
                }  
             } 
    		}
    		printf("\n");
	}
}