#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;
string KEYWORD[5]={"if","else","while","then","do"};      //关键字

char SEPARATER[8]={';',',','{','}','[',']','(',')'};    //分隔符
char OPERATOR[8]={'+','-','*','/','>','<','=','|'};     //运算符
char FILTER[4]={' ','\t','\r','\n'};                    //过滤符
const int IDENTIFIER=100;         //标识符值
const int CONSTANT=101;           //常数值
const int FILTER_VALUE=102;       //过滤字符值
const int INT8=103;
const int INT10=104;
const int INT16=105;
const int EQU=200;
const int MORE=201;
const int LESS=202;
const int ADD=203;
const int MINUS=204;
const int MUL=205;
const int DIC=206;
const int LBRAC=207;
const int RBRAC=208;
const string None=" "; 

int ProcedureE(FILE*fpin);
int ProcedureC(FILE*fpin);
int ProcedureT(FILE*fpin);
int ProcedureS(FILE*fpin);
int ProcedureF(FILE*fpin);
 
class Token{
	public :
		int type;
		string value;            
		string name;
	Token(){
		type=0;
		value=" ";
		
	}
	Token(int type,string value,string name):type(type),value(value),name(name){
	}
	~Token(){}
}; 
 
 
typedef struct{
	char code[500];
	int begin;
	int next;
	
}AttrS;

typedef struct{
	char code[500];
	int cfalse;
	int ctrue;
	
}AttrC;


typedef struct{
	char code[500];
    char place[200];
	
}AttrE;

typedef struct{
	char code[500];
    char place[200];	
}AttrT;

typedef struct{
	char code[500];
    char place[200];	
}AttrF; 
 
/*typedef struct{
    char idname[200];
	int entry;	
}AttrIDN;*/
 
/**判断是否为关键字**/
bool IsKeyword(string word){
    for(int i=0;i<5;i++){
        if(KEYWORD[i]==word){
            return true;
        }
    }
    return false;
}
/**判断是否为分隔符**/
bool IsSeparater(char ch){
    for(int i=0;i<8;i++){
        if(SEPARATER[i]==ch){
            return true;
        }
    }
    return false;
}
 
/**判断是否为运算符**/
bool IsOperator(char ch){
    for(int i=0;i<8;i++){
        if(OPERATOR[i]==ch){
            return true;
        }
    }
    return false;
}
/**判断是否为过滤符**/
bool IsFilter(char ch){
    for(int i=0;i<4;i++){
        if(FILTER[i]==ch){
            return true;
        }
    }
    return false;
}
/**判断是否为大写字母**/
bool IsUpLetter(char ch){
    if(ch>='A' && ch<='Z') return true;
    return false;
}
/**判断是否为小写字母**/
bool IsLowLetter(char ch){
    if(ch>='a' && ch<='z') return true;
    return false;
}
/**判断是否为数字**/
bool IsDigit(char ch){
    if(ch>='0' && ch<='9') return true;
    return false;
}

int valueof8(char* int8)
{
 int len=strlen(int8);
 int s=0;
 int j=0;
 for(int i=len;i>0;i--)
 {
  int n=int8[i]-48;
  for(int k=0;k<j;k++)
  {
   n*=8;
  }
  s+=n;
 }
 return s;
}

int valueof16(char* int16)
{
 int len=strlen(int8);
 int s=0;
 int j=0;
 for(int i=len;i>0;i--)
 {
  if(int16[i]>=48 && int16[i]<=58)
   int n=int16[i]-48;
  else 
   int n=int16[i]-55;
  for(int k=0;k<j;k++)
  {
   n*=16;
  }
  s+=n;
 }
 return s;
}
/**返回每个字的值**/
template <class T>
int value(T *a,int n,T str){
	for(int i=0;i<n;i++){
		if(a[i]==str) return i+1;
	}
	return -1;
}
/**词法分析**/
Token* analyse(FILE * fpin){
    char ch=' ';
    string arr="";
    while((ch=fgetc(fpin))!=EOF){
        arr="";
        if(IsFilter(ch)){}              //判断是否为过滤符
        else if(IsLowLetter(ch)){       //判断是否为关键字
            while(IsLowLetter(ch)){
				arr += ch;
				ch=fgetc(fpin);
            }
			//fseek(fpin,-1L,SEEK_CUR);
			if(IsKeyword(arr)){
                printf("%3d    ",value(KEYWORD,5,arr));
				cout<<arr<<"  关键字"<<endl;
				fseek(fpin,-1L,SEEK_CUR);
				return new Token((value(KEYWORD,5,arr)),None,arr); //None not define declared 
			}
			else
            {          
			    while(IsLowLetter(ch)||IsUpLetter(ch)||IsDigit(ch)) {
			    	arr+=ch;
			    	ch=fgetc(fpin);
			    
				}	
                printf("%3d    ",IDENTIFIER);
                cout<<arr<<"  标识符"<<endl;
                fseek(fpin,-1L,SEEK_CUR);
                return new Token(IDENTIFIER,arr,arr);
            }
        }
        else if(IsDigit(ch)){           //判断是否为数字
            if(ch=='0')
            {
            	arr += ch;
                ch=fgetc(fpin);
                if(ch>='0'&&ch<'8')
            	{
            		arr += ch;
                	ch=fgetc(fpin);
                	while(ch>='0'&&ch<'8'||ch=='.')
                	{
                		
                		arr += ch;	
						if(ch=='.') 
						{
							ch=fgetc(fpin);
							break;
						}
                		ch=fgetc(fpin);
                	
					}

					while(ch>='0'&&ch<'8')
                	{
                		arr += ch;
                		ch=fgetc(fpin);
					}
					fseek(fpin,-1L,SEEK_CUR);  //回退  -1L 回退一个 SEEK_CUR 当前位置      至于为何再次回退还没完全懂 
            		printf("%3d    ",INT8);
                    cout<<arr<<endl;
                    return new Token(INT8,arr,arr);
				}
				else if(ch=='x'||ch=='X')
				{
					arr += ch;
                	ch=fgetc(fpin);
                	arr += ch;
                	ch=fgetc(fpin);
                	while(IsDigit(ch)||ch>='a'&&ch<'f'||ch=='.')
                	{
                		
                		arr += ch;	
						if(ch=='.') 
						{
							ch=fgetc(fpin);
							break;
						}
                		ch=fgetc(fpin);
                	
					}
						while(IsDigit(ch)||ch>='a'&&ch<'f')
                	{
                		arr += ch;
                		ch=fgetc(fpin);
					}
					fseek(fpin,-1L,SEEK_CUR);
					printf("%3d    ",INT16);
                    cout<<arr<<endl;
                    return new Token(INT16,arr,arr);
				}
				else if(ch=='.'){
					arr+=ch;
					ch=fgetc(fpin);
				while(IsDigit(ch))
                {
                	arr += ch;
                	ch=fgetc(fpin);
				}
            	fseek(fpin,-1L,SEEK_CUR);
            	printf("%3d    ",CONSTANT);
            	cout<<arr<<"  整形数"<<endl;
				return new Token(CONSTANT,arr,arr);	
				}
			}
            else
            {	
				while(IsDigit(ch)||ch=='.'/*||(ch=='.'&&IsDigit(fgetc(fpin)))*/){
                		arr += ch;	
						if(ch=='.') 
						{
							ch=fgetc(fpin);
							break;
						}
                		ch=fgetc(fpin);
            	}
            	while(IsDigit(ch))
                {
                	arr += ch;
                	ch=fgetc(fpin);
				}
            	fseek(fpin,-1L,SEEK_CUR);
            	printf("%3d    ",CONSTANT);
            	cout<<arr<<"  整形数"<<endl;
            	return new Token(CONSTANT,arr,arr);	
        	}
        }
        else if(IsUpLetter(ch)||IsLowLetter(ch)||ch=='_'){
            while(IsUpLetter(ch)||IsLowLetter(ch)||ch=='_'||IsDigit(ch)){
                arr += ch;
                ch=fgetc(fpin);
            }
            fseek(fpin,-1L,SEEK_CUR);
            
            printf("%3d    ",IDENTIFIER);
            cout<<arr<<"  标识符"<<endl;
            return new Token(IDENTIFIER,arr,arr);	
        }
        else switch(ch){
        case '+':
        case '-':
        case '*':
        case '/':
        case '>':
        case '<':
        case '=':
        case '!':
            {
                arr += ch;
                printf("%3d    ",value(OPERATOR,8,*arr.data())+200);
                cout<<arr<<"  运算符"<<endl;
                return new Token(value(OPERATOR,8,*arr.data())+200,arr,arr);	
                break;
            }
        case ';':
        case ',':
        case '(':
        case ')':
        case '[':
        case ']':
        case '{':
        case '}':
            {
              arr += ch;
              printf("%3d    ",value(SEPARATER,8,*arr.data())+300);
              cout<<arr<<"  分隔符"<<endl;
              return new Token(value(SEPARATER,8,*arr.data())+300,arr,arr);	
              break;
            }
        default :cout<<"\""<<ch<<"\":无法识别的字符！"<<endl;
        }
    }
 
}

int ProcedureS(FILE*fpin,AttrS* s){
	AttrC c;
	AttrS s1;
	AttrE e;
	char temp_idnname[50];
    //cout<<"S"<<endl;
    Token* token=analyse(fpin);
    //string arr = "if";
    if(token->type==value(KEYWORD,5,KEYWORD[0])){ //if
        c.ctrue=NL();
        s1.begin=c.ctrue;
        s1.next=c.cfalse=s.next;
    	//cout<<token->name<<endl;
    	ProcedureC(fpin,c);
    	token=analyse(fpin);
        if(token->type==(value(KEYWORD,5,KEYWORD[3]))){  //then
        	//cout<<token->name<<endl;
        	ProcedureS(fpin,s1);
        	sprintf_s(s.code,"\n\t%s\nL%d:\t%s",c.code,c.ctrue,s1.code);
       	
		}
		else{
			exit(-1);
		}
		
	}
	else if(token->type==(value(KEYWORD,5,KEYWORD[2]))){ //while
		//cout<<token->name<<endl;
		s1.next=s.begin=NL();
		c.ctrue=s1.begin=NL();
		c.cfalse=s.next;
		ProcedureC(fpin,c);
		token=analyse(fpin);
		if(token->type==(value(KEYWORD,5,KEYWORD[4]))){  //do
			//cout<<token->name<<endl;
			ProcedureS(fpin,s);
			sprintf_s(s.code,"\nL%d:\t%s\nL%d:\t%s\n\tgoto L%d ",s.begin,c.code,c.ctrue,s1.code,s.begin);
		}else{
			exit(-1);
		}
		
	}else if(token->type==IDENTIFIER){
	//	cout<<"id: "<<token->name<<endl;
	    strcpy_s(temp_idnname,token->name.c_str());
		token=analyse(fpin);
		if(token->type==value(OPERATOR,8,'=')+200){
		//	cout<<token->name<<endl;
			ProcedureE(fpin,e);
		}else{
			exit(-1);
		}
		
	}
	return 0;	
} 

int ProcedureC(FILE* fpin,AttrC*c){
	AttrE e1;
	AttrE e2;
	//cout<<"C"<<endl;
	Token*token;
	ProcedureE(fpin,e1);
	token=analyse(fpin);
	if(token->type==value(OPERATOR,8,'>')+200){
		//cout<<token->name<<endl;
		ProcedureE(fpin,e2);
		sprintf_s(c.code,"%s%s\n\tif %s>%s goto L%d\n\tgoto L%d",e1.code,e2.code,e1.place,e2.place,c.ctrue,c.cfalse);
	}
	else if(token->type==value(OPERATOR,8,'<')+200){
	//	cout<<token->name<<endl;
		ProcedureE(fpin,e2);
		sprintf_s(c.code,"%s%s\n\tif %s<%s goto L%d\n\tgoto L%d",e1.code,e2.code,e1.place,e2.place,c.ctrue,c.cfalse);
	}else{
		exit(-1);
	}
	return 0;
}

int ProcedureE(FILE*fpin,AttrE*e){
	AttrT t1;
	AttrT t2;
    //cout<<"E"<<endl;
	Token*token;
	ProcedureT(fpin,t1);
	while (true){
		token=analyse(fpin);
		if(token->type=value(OPERATOR,8,'+')+200){
	//	cout<<token->name<<endl;
		ProcedureT(fpin,t2); 
		strcpy_s(e.place,NT());
		sprintf_s(e.code,"%s%s\n\t%s=%s+%s",t1.code,t2.code,e.place,t1.place,t2.place);
		strcpy_s(t1.code,e.code);
		strcpy_s(t1.place,e.place);
		}else if(token->type==value(OPERATOR,8,'-')+200){
		//	cout<<token->name<<endl;
			ProcedureT(fpin,t2);
			strcpy_s(e.place,NT());
			sprintf_s(e.code,"%s%s\n\t%s=%s-%s",t1.code,t2.code,e.place,t1.place,t2.place);
			strcpy_s(t1.code,e.code);
		    strcpy_s(t1.place,e.place);
		}else{
			for(int i=0;i<(int)token->name.length();i++){//*******************************
				cout<<"**************"<<endl;
				fseek(fpin,-1L,SEEK_CUR);
			}
			strcpy_s(e.place,t1.place);
			sprintf_s(e.code,"%s",t1.code);
			break;
		}
	}
	return 0;
}


int ProcedureT(FILE*fpin,AttrT*t){
	AttrF f1;
	AttrF f2;
	//cout<<"T"<<endl;
	Token*token;
	ProcedureF(fpin,f1);
	while(true){
		token=analyse(fpin);
		if(token->type==value(OPERATOR,8,'*')+200){
			//cout<<token->name<<endl;
			ProcedureF(fpin,f2);
			strcpy_s(t.place,NT());
			sprintf_s(t.code,"%s%s\n\t%s=%s*%s",f1.code,f2.code,t.place,f1.place,f2.place);
			strcpy_s(f1.code,t.code);
			strcpy_s(f1.place,t.place);
		}
		else if(token->type==value(OPERATOR,8,'/')+200){
		 //   cout<<token->name<<endl;
			ProcedureF(fpin,f2);
			strcpy_s(t.place,NT());
			sprintf_s(t.code,"%s%s\n\t%s=%s/%s",f1.code,f2.code,t.place,f1.place,f2.place);
			strcpy_s(f1.code,t.code);
			strcpy_s(f1.place,t.place);
		}else{
		/*	for(int i=0;i<(int)token->name.length();i++){//*******************************
			cout<<"$$$$$$$$$$"<<endl;
			fseek(fpin,-1L,SEEK_CUR);
			}*/
		strcpy_s(t.place,f1.place);
			sprintf_s(e.code,"%s",f1.code);
			break;
		}
	}
	return 0;
}

int ProcedureF(FILE*fpin,AttrF*f){
	//cout<<"F"<<endl;
	AttrE e;
	Token*token;
	char temp_value[50];
	token=analyse(fpin);
    
	if(token->type==LBRAC){
		cout<<token->name<<endl;
		ProcedureE(fpin,e);
		strcpy_s(f.place,e.place);
		sprintf_s(f.code,"%s",e.code);
		
	//	cout<<"#################"<<endl;
		token=analyse(fpin);
	//	cout<<token->name<<endl;
	}

	if(token->type==IDENTIFIER){
		//cout<<"id: "<<token->name<<endl;
		strcpy_s(f.place,token->name.c_str());
		sprintf_s(f.code,"\0");
	}
	if(token->type==INT8){
//	char strint8[256]={0};
	//	cout<<"int8: "<<token->name<<endl;
	sprintf_s(temp_value,"%d",valueof8(token->value));
	strcpy_s(f.place,temp_value);
	sprintf_s(f.code,"\0");
	}
	if(token->type==INT10){
	//	cout<<"int10: "<<token->name<<endl;
	strcpy_s(f.place,token->value.c_str());
	sprintf_s(f.code,"\0");
	}
	if(token->type==INT16){
	//	cout<<"int16: "<<token->name<<endl;
	sprintf_s(temp_value,"%d",valueof16(token->value));
	strcpy_s(f.place,temp_value);
	sprintf_s(fcode,"\0");

	}
	return 0;
}




int main()
{
    char inFile[40];
    FILE *fpin;
   // cout<<"请输入源文件名（包括路径和后缀）:";
    while(true){
        //cin>>inFile;
        if((fpin=fopen("C:\\Users\\23854\\Desktop\\jzl.txt","r"))!=NULL)
            break;
        else{
            cout<<"文件名错误！"<<endl;
            cout<<"请输入源文件名（包括路径和后缀）:";
        }
 
    }
    cout<<"------词法分析如下------"<<endl;
    //while(1){
    //	analyse(fpin);
    //}	
    ProcedureS(fpin);
	
	return 0;
}
