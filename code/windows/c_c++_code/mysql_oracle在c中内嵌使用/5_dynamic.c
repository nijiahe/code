
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
/*Cͷ�ļ�*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <setjmp.h>

/*SQLͷ�ļ�*/  
#include <sqlcpr.h>
#include <sqlda.h>  
#include <sqlca.h>

#define MAX_ITEMS  40//��������м���
#define MAX_VNAME_LEN 24//���������ַ�����󳤶�
#define MAX_NAME_LEN 24//�������е����ַ�����󳤶�

/*
		/opt/app/oracle/product/12.2.0/dbhome_1/precomp/public
*/

/*�������������ѡ����������ָ��,��4_�е����������������������*/
/*��4����������4����������ansi��׼����,���˴��ֶ�����*/
/*������ÿ��ֻ�洢һ�е�����,ÿ��ͨ��fetch�������������µ�����*/
//struct SQLDA {
  /* ub4    */ int        N; /* Descriptor size in number of entries        *//*�����и���*/
  /* text** */ char     **V; /* Ptr to Arr of addresses of main variables   *//*�洢���ݵĵ�ַ*/
  /* ub4*   */ int       *L; /* Ptr to Arr of lengths of buffers            *//*�洢���ݵ�size*/
  /* sb2*   */ short     *T; /* Ptr to Arr of types of buffers              *//*�洢�������������*/
  /* sb2**  */ short    **I; /* Ptr to Arr of addresses of indicator vars   *//*ָ������ĵ�ַ*/
  /* sb4    */ int        F; /* Number of variables found by DESCRIBE       *//*ʵ�ʵ��и���*/
  /* text** */ char     **S; /* Ptr to Arr of variable name pointers        *//*�洢�����Ķ���ָ��*/
  /* ub2*   */ short     *M; /* Ptr to Arr of max lengths of var. names     *//*�洢������������*/
  /* ub2*   */ short     *C; /* Ptr to Arr of current lengths of var. names *//*�洢ÿ�������ĳ���*/
  /* text** */ char     **X; /* Ptr to Arr of ind. var. name pointers       */
  /* ub2*   */ short     *Y; /* Ptr to Arr of max lengths of ind. var. names*/
  /* ub2*   */ short     *Z; /* Ptr to Arr of cur lengths of ind. var. names*/
 // };
 /*�ṹ��Ķ�����:*/
/*
 		/opt/app/oracle/product/12.2.0/dbhome_1/precomp/public/sqlda.h
*/
SQLDA* bind_dp;
SQLDA* select_dp;

/* EXEC SQL BEGIN DECLARE SECTION; */ 

	char sql_stat[100];//����û����������
	char current_date[20];
	char username[20];
	char passwd[20];
	char server[20];
	//char* serverid="system/A512666#asdf@orcl";
	char* serverid="c##scott/tiger@orcl";
/* EXEC SQL END DECLARE SECTION; */ 


void sqlerr();//SQL��䷢������ʱ��ִ��
void connet();//�������ݿ⺯��
void alloc_descriptors(int size,int max_vname_len,int max_iname_len);//����ռ�  
void dealloc_descriptors();//�ͷſռ�
void set_bind_variables();//�����������ݵĺ���(�󶨱��� :a,:b)(�����ð󶨱���)
void process_select_list();//����������ݵĺ���
void printfstr(char* str,int size);

int main()
{

		/* EXEC SQL WHENEVER SQLERROR DO sqlerr(); */ 


		/*���ӵ�½���ݿ�*/
		connet();
		
		/*�����������������ڴ�*/
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
				//1.׼��SQL��̬���
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


				//2.������
				/* EXEC SQL DECLARE my_cursor CURSOR FOR my_pre_sql; */ 

				//3.�����������(�����ð󶨱���)
				set_bind_variables();
				//4.���α�
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


				
				/*�����select���,�����������*/
				if(strncmp(sql_stat,"select",6)==0||strncmp(sql_stat,"select",6)==0)
				{
						process_select_list();
				}
				//5.�ر��α�
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

//�ύ

		}
		dealloc_descriptors();//�ͷ�������
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

//�ύ���Ͽ�
		return 0;
		
}

void sqlerr()  
{ 
    /* ��ʾSQL���� */  
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
		/*����SQL�ṩ�ķ����������ĺ��������������ڴ�*/
		/*���еĶ���ָ��ֻ������ָ�������ڴ�,���������ڴ���Ҫ�Լ�����*/
		bind_dp=SQLSQLDAAlloc(0 ,size, MAX_VNAME_LEN, max_iname_len);
		select_dp=SQLSQLDAAlloc(0 , size , MAX_VNAME_LEN, max_iname_len);
		
		/* Ϊָʾ�������󶨱�����ѡ���б�������ڴ� */  
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
  
    /* �ͷ�ָʾ�������󶨱�����ѡ���б���ռ�õ��ڴ� */
    /*���ͷ��Լ������*/
    for(i = 0 ; i != MAX_ITEMS ; ++i)  
    {  
        if(bind_dp->V[i] != (char*)0)  
            free(bind_dp->V[i]);  
        free(bind_dp->I[i]);  
  
        if(select_dp->V[i] != (char*)0)  
            free(select_dp->V[i]);  
        free(select_dp->I[i]);  
    }  
  
    /* �ͷŰ���������ѡ�������� */  
    SQLSQLDAFree(0 , bind_dp);  
    SQLSQLDAFree(0 , select_dp);  
}  

void set_bind_variables()  
{  
    char bind_var[64];  
    /*���ð󶨱���������*/  
    bind_dp->N = MAX_ITEMS;  
  
    /* �󶨱�������: ��������*/  
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

  
  
    /* ���ð󶨱���ʵ�ʸ���*/ 
    bind_dp->N = bind_dp->F;  
  
    /* ѭ������󶨱��� */
    int i;
    for(i = 1 ; i <= bind_dp->F ; i++)  
    {  
        /*��ʾ�󶨱�����*/  
        printf("������󶨱���%.*s��ֵ��" , (int)bind_dp->C[i] , bind_dp->S[i]);  
        
        /* ����󶨱�����ֵ */  
        fgets(bind_var,sizeof(bind_var),stdin);
        int len=strlen(bind_var);
        bind_var[len-1]='\0';
  
        /* ���ð󶨱����ĳ��ȳ�Ա */  
        bind_dp->L[i] = strlen(bind_var);  
  
        /* Ϊ�󶨱������ݻ��������·����ڴ�(��һλ������'\0') */  
        bind_dp->V[i] = (char*)realloc(bind_dp->V[i] , bind_dp->L[i] + 1);  
  
        /* �󶨱�������: ���ݻ����� */  
        strcpy(bind_dp->V[i] , bind_var);  
  
        /* ����ָʾ����������NULL */  
        if(0 == strncmp(bind_var , "NULL" , 4) || 0 == strncmp(bind_var , "null" , 4))  
            *bind_dp->I[i] = -1;  
        else  
            *bind_dp->I[i] = 0;  
  
        /* �������ݻ������������ʹ���->char */  
        bind_dp->T[i] = 1;  
    }  
}

void process_select_list()//��������ĺ���,���Զ�̬��ȡ���һ���м�������,Ȼ��ÿ��ͨ���α�fetch��ÿһ�в����
{
		char title[MAX_VNAME_LEN];
		
		/* Descriptor size in number of entries        */
		/*����༸��*/
		select_dp->N=MAX_ITEMS;
		/*ѡ��������,������������*/
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


		/*������ʵ������*/
		/*F: Number of variables found by DESCRIBE       */
		select_dp->N=select_dp->F;
		
    int i;
    for(i=0;i<select_dp->F;i++)
    {
    		int null_ok;
    		int scale;
    		int precision;
    		/* ���select_dp->T[i]�ĸ�λ->null */
        SQLColumnNullCheck(0,(unsigned short*)&select_dp->T[i],(unsigned short*)&select_dp->T[i],&null_ok);
    		switch(select_dp->T[i])  
        {  
        		/*2����������*/
        		case 2:
    				/* number���ͣ�ȡ�þ������� */
    				/*�������������ʹscale����һ��ֵ*/
    						SQLNumberPrecV6(0 , (unsigned long*)&select_dp->L[i] , &precision , &scale); 
    						if(scale > 0)  
                		/* ʵ��: ��ʾ����:float  */
                		{
                				select_dp->L[i] = sizeof(float);	
                		}
            		else  
                		/* ����: ��ʾ���� int */
                		{
                				select_dp->L[i] = sizeof(int);	
                		}
         				break;
         		case 12:  
            		/* DATA��������(DD-MON-YY) */  
            		select_dp->L[i] = 9;  
            		break;  
        }
        /*����Ϊ�б�������������ڴ�*/
        if(select_dp->T[i]!=2)
        {
        		select_dp->V[i]=(char*)realloc(select_dp->V[i] , select_dp->L[i] + 1);
        }
        else
        {
        		/* number���� */
            select_dp->V[i] = (char*)realloc(select_dp->V[i] , select_dp->L[i]);
        }
        /* ��ʼ��title */  
        memset(title , ' ' , MAX_VNAME_LEN);
        /* ѡ���б�������: title */  
        strncpy(title , select_dp->S[i] , select_dp->C[i]);  
  
        /* ��ʾ���� */
        /*������*/
        if(select_dp->T[i]==2)
        {
            if(scale > 0)  
                printf("%*.*s",MAX_VNAME_LEN,MAX_VNAME_LEN,title);  
            else  
                printf("%*.*s",MAX_VNAME_LEN,MAX_VNAME_LEN,title);
        }
        else//������
        {  
            printf("%*.*s",MAX_VNAME_LEN,MAX_VNAME_LEN,title);  
        }
        /* ����Oracle�ڲ�����ȷ���ⲿ��������(��ʾ����) */  
        if(select_dp->T[i]==2)  
        {  
            /* number ����*/  
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

//��ȡ��������������������
    		for(i=0;i<select_dp->F;i++)
    		{
    				if(*select_dp->I[i] < 0)
    				{  
                /* ����NULL */  
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