#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<cstring>
using namespace std;
string KEYWORD[6]={"if","else","while","then","do","int"};      //关键字

char SEPARATER[8]={';',',','{','}','[',']','(',')'};    //分隔符
char OPERATOR[8]={'+','-','*','/','>','<','=','|'};     //运算符
char FILTER[4]={' ','\t','\r','\n'};                    //过滤符

int wrongcheck=0;
int leftcheck=0;
int rightcheck=0;
int leftcheck1=0;
int rightcheck1=0;

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
const int WRONG=210;
const string None=" "; 

int count_1=-1;
int count_2=0;
int flagwhile=0;
int flagelse=0;

typedef struct
{
	char code[500];
}AttrP;

typedef struct
{
	char code[500];
}AttrL;

typedef struct
{
	char code[500];
	int begin;
	int next;
}AttrS;

typedef struct
{
	char code[500];
	int c_false;
	int c_true;
}AttrC;

typedef struct
{
	char code[500];
	char place[200];
}AttrE;

typedef struct
{
	char code[500];
	char place[200];
}AttrT;

typedef struct
{
	char code[500];
	char place[200];
}AttrF;

double valueof8(string int8);
double valueof16(string int16);
int ProcedureE(FILE*fpin, AttrE &e);
int ProcedureC(FILE*fpin, AttrC &c);
int ProcedureT(FILE*fpin, AttrT &t);
int ProcedureS(FILE*fpin, AttrS &s);
int ProcedureF(FILE*fpin, AttrF &f);
int ProcedureL(FILE*fpin, AttrL &l);
int ProcedureP(FILE*fpin, AttrP &p);
int ProcedureSn(FILE *fpin, AttrS &s,AttrC &c);

int newlabel();
int thislabel();
char* newtemp();
 
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
 
int newlabel()
{
	count_1++;
	return count_1;
}

int thislabel()
{
	return count_1;
}
char* newtemp()
{
	static char s[100]="";
	count_2++;
	sprintf(s,"t%d",count_2);
	return s;
} 

double valueof8(string int8)
{
	char temp[100]="";
	strcpy(temp,int8.c_str());
 	int len=strlen(temp);
 	double s=0;
 	double n=0;
 	int check=0;
 	int j=0;
 	int i,k,q;

 	for(q=len-1;q>0;q--){
 		if(temp[q]=='.'){
 			check=1;
 			break;
		 }
	 }
	 
 	if(check==1){
	 	for(i=q+1;i<len;i++)
	 	{
	 		n=temp[i]-48;
	 		for(k=0;k<j+1;k++)
	  		{
	   			n/=8;
	  		}
	  		j++;
	  		s+=n;
	 	}

		k=0;j=0;

	 	for(i=q-1;i>0;i--){
	  		n=temp[i]-48;
	  		for(k=0;k<j;k++)
	  		{
	   			n*=8;
	  		}
	  		j++;
	  		s+=n;
 		}
	 }
	 else{
	 	for(i=len-1;i>0;i--){
	  		int n=temp[i]-48;
	  		for(k=0;k<j;k++)
	  		{
	   		n*=8;
	  		}
	  		j++;
	  		s+=n;
 		}
	 }
 	return s;
}


double valueof16(string int16)
{
	char temp[100];
	strcpy(temp,int16.c_str());
 	int len=strlen(temp);
 	double s=0;
 	int j=0;
 	int i,k,q;
 	double n;
 	int check=0;
 	
 	for(q=len-1;q>0;q--){
 		if(temp[q]=='.'){
 			check=1;
 			break;
		 }
	}
	
	if(check==1){
	 	for(i=q+1;i<len;i++)
	 	{
	 		if(temp[i]>='0' && temp[i]<='9')
   				n=temp[i]-'0';
  			else if(temp[i]>='a' && temp[i]<='f')
   				n=temp[i]-'a'+10;
   			else if(temp[i]>='A' && temp[i]<='F')
				n=temp[i]-'A'+10;
   			
   				
   				
	 		for(k=0;k<j+1;k++)
	  		{
	   			n/=16;
	  		}
	  		j++;
	  		s+=n;
	 	}

		k=0;j=0;

	 	for(i=q-1;i>1;i--){
	 		if(temp[i]>='0' && temp[i]<='9')
   				n=temp[i]-'0';
  			else if(temp[i]>='a' && temp[i]<='f')
   				n=temp[i]-'a'+10;
   			else if(temp[i]>='A' && temp[i]<='F')
				n=temp[i]-'A'+10;
	  		for(k=0;k<j;k++)
	  		{
	   			n*=16;
	  		}
	  		j++;
	  		s+=n;
 		}
	 }
	 else{
	 	for(i=len-1;i>1;i--){
	 		if(temp[i]>='0' && temp[i]<='9')
   				n=temp[i]-'0';
  			else if(temp[i]>='a' && temp[i]<='f')
   				n=temp[i]-'a'+10;
   			else if(temp[i]>='A' && temp[i]<='F')
				n=temp[i]-'A'+10;
				
	  		for(k=0;k<j;k++)
	  		{
	   		n*=16;
	  		}
	  		j++;
	  		s+=n;
 		}
	 }
 	return s;
}


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
            while(IsLowLetter(ch)||IsDigit(ch)||IsUpLetter(ch)){
				arr += ch;
				ch=fgetc(fpin);
            }
                  
			//fseek(fpin,-1L,SEEK_CUR);
			if(IsKeyword(arr)){
               	// printf("%3d    ",value(KEYWORD,5,arr));
				//	cout<<arr<<"  关键字"<<endl;
				fseek(fpin,-1L,SEEK_CUR);
				return new Token((value(KEYWORD,5,arr)),None,arr); //None not define declared 
			}
			else
            {              
               // printf("%3d    ",IDENTIFIER);
              //  cout<<arr<<"  标识符"<<endl;
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
                	int cnt=0,check=0;

            		while(IsUpLetter(ch)||IsLowLetter(ch)||IsDigit(ch)||ch=='.')
                	{
						if(ch>='0'&&ch<'8'||ch=='.'){
							arr += ch;	
							if(ch=='.') 
							{
								cnt++;
								//ch=fgetc(fpin);
								//arr += ch;
							}
                			ch=fgetc(fpin);
						}
						else{
							check=1;
							arr += ch;	
                			ch=fgetc(fpin);
						}	
            		}
            		if(check==1){
            			fseek(fpin,-1L,SEEK_CUR);
            			wrongcheck=1;
            			cout<<"错误位置："<<ftell(fpin)<<"\t错误 wrong 8 number："<<arr<<endl;
            			return new Token(WRONG,arr,arr);
					}
            		
            		fseek(fpin,-1L,SEEK_CUR);
            		if(cnt<=1)	return new Token(INT8,arr,arr);
            		else if(cnt>1) {
            			wrongcheck=1;
						cout<<"错误位置："<<ftell(fpin)<<"\t错误 wrong use of'.'："<<arr<<endl;
            			return new Token(WRONG,arr,arr);
					}
				}
				else if(ch=='x'||ch=='X')
				{
					arr += ch;
                	ch=fgetc(fpin);
                	//arr += ch;
                	//ch=fgetc(fpin);
                	int cnt=0,check=0;
					
					while(IsUpLetter(ch)||IsLowLetter(ch)||IsDigit(ch)||ch=='.')
                	{
						if(IsDigit(ch)||ch>='a'&&ch<='f'||ch=='.'){
							arr += ch;	
							if(ch=='.') 
							{
								cnt++;
								//ch=fgetc(fpin);
								//arr += ch;
							}
                			ch=fgetc(fpin);
						}
						else{
							check=1;
							arr += ch;	
                			ch=fgetc(fpin);
						}	
            		}
            		if(check==1){
            			fseek(fpin,-1L,SEEK_CUR);
            			wrongcheck=1;
            			cout<<"错误位置："<<ftell(fpin)<<"\t错误 wrong 16 number："<<arr<<endl;
            			return new Token(WRONG,arr,arr);
					}
					
					fseek(fpin,-1L,SEEK_CUR);
            		if(cnt<=1)	return new Token(INT16,arr,arr);
            		else if(cnt>1) {
            			wrongcheck=1;
						cout<<"错误位置："<<ftell(fpin)<<"\t错误 wrong use of'.'："<<arr<<endl;
            			return new Token(WRONG,arr,arr);
            		}
				}
				else if(ch=='.'){
					int cnt=0;	
					while(IsDigit(ch)||ch=='.'/*||(ch=='.'&&IsDigit(fgetc(fpin)))*/){
                		arr += ch;	
						if(ch=='.') 
						{
							cnt++;
							//ch=fgetc(fpin);
							//arr += ch;
						}
                		ch=fgetc(fpin);
            		}
					
					//cout<<cnt<<"****"<<endl;
					
            		fseek(fpin,-1L,SEEK_CUR);
            		if(cnt<=1)	return new Token(INT10,arr,arr);
            		else if(cnt>1) {
            			//cout<<"cnt"<<cnt<<endl;
            			wrongcheck=1;
						cout<<"错误位置："<<ftell(fpin)<<"\t错误 wrong use of'.'："<<arr<<endl;
            			return new Token(WRONG,arr,arr);
					}
				}
				else {
					while (IsUpLetter(ch)||IsLowLetter(ch)||IsDigit(ch)){
						arr+=ch;
						ch=fgetc(fpin);
					}
					
					fseek(fpin,-1L,SEEK_CUR);
					
					if(arr=="0") return new Token(INT10,arr,arr);
					
					wrongcheck=1;
					cout<<"错误位置："<<ftell(fpin)<<"\t错误 wrong number："<<arr<<endl;
					return new Token(WRONG,arr,arr);
				}
			}
            else
            {
				int cnt=0,check=0;	
				
				while(IsUpLetter(ch)||IsLowLetter(ch)||IsDigit(ch)||ch=='.'){
					if(IsDigit(ch)||ch=='.'){
						arr += ch;	
						if(ch=='.') 
						{
							cnt++;
						}
                		ch=fgetc(fpin);
					}
					else{
							check=1;
							arr += ch;	
                			ch=fgetc(fpin);
						}	
				}
				
				if(check==1){
						fseek(fpin,-1L,SEEK_CUR);
            			wrongcheck=1;
            			cout<<"错误位置："<<ftell(fpin)<<"\t错误 wrong 10 number："<<arr<<endl;
            			return new Token(WRONG,arr,arr);
					}
				
				/*while(IsDigit(ch)||ch=='.'){
                		arr += ch;	
						if(ch=='.') 
						{
							cnt++;
							//ch=fgetc(fpin);
							//arr += ch;
						}
                		ch=fgetc(fpin);
                		//arr += ch;
            	}*/

            	fseek(fpin,-1L,SEEK_CUR);
            	if(cnt<=1)	return new Token(INT10,arr,arr);
            	else if(cnt>1) {
            		//cout<<"cnt"<<cnt<<endl;
            		wrongcheck=1;
					cout<<"错误位置："<<ftell(fpin)<<"\t错误 wrong use of'.'："<<arr<<endl;
            		return new Token(WRONG,arr,arr);
				}
        	}
        }
        else if(IsUpLetter(ch)||IsLowLetter(ch)||ch=='_'){  //!!!!!!!! 
            while(IsUpLetter(ch)||IsLowLetter(ch)||ch=='_'||IsDigit(ch)){
                arr += ch;
                ch=fgetc(fpin);
            }
            fseek(fpin,-1L,SEEK_CUR);
            
           // printf("%3d    ",IDENTIFIER);
           // cout<<arr<<"  标识符"<<endl;
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
               // printf("%3d    ",value(OPERATOR,8,*arr.data())+200);
               // cout<<arr<<"  运算符"<<endl;
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
             // printf("%3d    ",value(SEPARATER,8,*arr.data())+300);
              //cout<<arr<<"  分隔符"<<endl;
             return new Token(value(SEPARATER,8,*arr.data())+300,arr,arr);	
              break;
            }
        default :cout<<"\""<<ch<<"\":无法识别的字符！"<<endl;
        }

    }
    return new Token(-1,"#","#");
 
}



int ProcedureSn(FILE *fpin, AttrS &s,AttrC &c){
	AttrS s1;
	strcpy(s1.code,"");
	s1.next=s.next;
	Token* token=analyse(fpin);
	
	//cout<<"SSSSSSSSSSSNNNNNNN"<<token->name<<endl;
	
	if(token->name=="else"){
		//!cout<<token->name<<endl;
		//!cout<<"S_new"<<endl;
		ProcedureS(fpin,s1);
		sprintf(s.code,"\n\tgoto L%d\nL%d:\t%s",s.next,c.c_false,s1.code);
	}
	else{
		
			for(int i=0;i<(int)token->name.length();i++){//*******************************
			//	cout<<"**************"<<endl;
				fseek(fpin,-1L,SEEK_CUR);
			}
		
		
		return 0;
	}
	
	
	return 0;
	
}

int ProcedureL(FILE *fpin, AttrL &l){
	AttrS s;
	strcpy(s.code,"");
	s.next=thislabel();
	//!cout<<"L"<<endl;
	//cout<<"\nLLLLLLLL\n"<<endl;
	ProcedureS(fpin,s);
	sprintf(l.code,"%s",s.code);
	Token* token=analyse(fpin);
	
	//cout<<"LLLLLLLLLLLLLLL"<<token->name<<endl;

	char ch;
	if(token->name==";"){
	} 
	else{
		if(leftcheck==1 && rightcheck==0){
			cout<<"错误位置："<<ftell(fpin)<<"\twrong {}, miss '} '"<<endl;
			exit(-1);
		}
		else{
			cout<<"wrong ;"<<endl;
			exit(-1);
		}
		
	}

	return 0;
}
int ProcedureP(FILE *fpin,AttrP &p){
	AttrP p1;
	strcpy(p1.code,"");
	AttrL l;
	strcpy(l.code,"");
	char ch;
	Token* token=analyse(fpin);
	
	//cout<<"PPPPPPPPPPPPPPP"<<token->name<<endl;
	
	if(token->name=="#"){
		//cout<<p.code<<endl;
		return 0;
	}
	else if(token->type==INT8||token->type==INT10||token->type==INT16){
		cout<<"错误位置："<<ftell(fpin)<<"\t"<<token->name<<"  need to be IDENTIFIER"<<endl;
		exit(-1);
	}
	else{
			//cout<<"\nPPPPPPPPP\n"<<endl;
			fseek(fpin,-1L*(int)token->name.length(),SEEK_CUR);
		
	}
	
	int temp=newlabel();
	ProcedureL(fpin,l);
	sprintf(p.code,"%s",l.code); 
	
	Token* token1=analyse(fpin);
	
	//cout<<"PPPPPPPPPPPPP"<<token1->name<<endl;

	if(token1->name!="#"&&token1->name!="}"){
	
		//if(ch==';'){
		//cout<<"end of a project2"<<endl;
		//	return 0;}
		//!cout<<"P"<<endl;
		fseek(fpin,-1L*(int)token1->name.length(),SEEK_CUR);
		ProcedureP(fpin,p1);
	
		sprintf(p.code,"%s\nL%d:\t%s",p.code,temp,p1.code);	
		}
	else if(token1->name=="}") {
		if(leftcheck==0){
			cout<<"错误位置："<<ftell(fpin)<<"\twrong {}, miss '{ '"<<endl;
			exit(-1);
	}
		fseek(fpin,-1L*(int)token1->name.length(),SEEK_CUR);
		
		return 0;
	}
	
	else{
		//cout<<"bye"<<endl;
		return 0;
	}
	
}




int ProcedureS(FILE*fpin, AttrS &s){
	AttrC c;
	AttrS s1,s2;
	strcpy(s1.code,"");
	strcpy(s2.code,"");
	AttrE e;
	strcpy(e.code,"");
	strcpy(e.place,"");
	AttrP p;
	strcpy(p.code,"");;
	char temp_idn_name[50];
    //!cout<<"S"<<endl;
    Token* token=analyse(fpin);

	//cout<<"SSSSSSSSSSSS1"<<token->name<<endl;
	
	
	if(token->type==INT8||token->type==INT10||token->type==INT16){
		cout<<"错误位置："<<ftell(fpin)<<"\t"<<token->name<<"  need to be IDENTIFIER"<<endl;
		exit(-1);
	}
    //string arr = "if";

 /*  if(token->name=="else"){
    	cout<<"Snew"<<endl;
    	ProcedureS(fpin);
	}*/
	
   if(token->name=="if"){//IF 
    	//!cout<<token->name<<endl;
    	int backlength=0;
    	c.c_true=newlabel();
    	s1.begin=c.c_true;
    	s2.next=s1.next=s.next;
    	int front=ftell(fpin);
		//cout<<"front:"<<front<<endl; 
		while(1){
			Token * token2=analyse(fpin);
			
			if(token2->name=="#"||token2->name=="if"){//删除分号 
			
				backlength=ftell(fpin)-front;//当前距离文件首的的距离-开始距离文件首的距离 
					c.c_false=s.next;
					fseek(fpin,-1L*backlength,SEEK_CUR);
					
				break;
				
				
				
			}
			else if (token2->name=="else"){
			
				backlength=ftell(fpin)-front;
					c.c_false=newlabel();
				flagelse=1;
				for(int i=0;i<backlength;i++){//*******************************
				
				fseek(fpin,-1L,SEEK_CUR);
			
			}
			

			//	Token * token3=analyse(fpin);
			//	cout<<"::"<<token2->name<<endl;
			//	Token * token4=analyse(fpin);
			//	cout<<"::"<<token4->name<<endl;
				break;
			}
			
			
			
		} 
    	
    	
    	
    	
    	ProcedureC(fpin,c);
    	token=analyse(fpin);
    	
    	//cout<<"SSSSSSSSSSSS"<<token->name<<endl;

        if(token->name=="then"){//THEN
        	//!cout<<token->name<<endl;
        	token=analyse(fpin);
        	if(token->name=="while")
        	{
        		flagwhile=1;
			}
			else{
				flagwhile=0;
			}
			for(int i=0;i<(int)token->name.length();i++){//*******************************
			//	cout<<"**************"<<endl;
				fseek(fpin,-1L,SEEK_CUR);
			}
        	ProcedureS(fpin,s1);
       		ProcedureSn(fpin,s2,c);
       		if(flagwhile==1)
       		{
       			sprintf(s.code,"\t%s\n\t%s%s",c.code,s1.code,s2.code);
       			flagwhile=0;
			}
			else
			{
       			sprintf(s.code,"\t%s\nL%d:\t%s%s",c.code,c.c_true,s1.code,s2.code);
       		}
       		
       		//cout<<s1.code<<endl;
		}
		else{
			cout<<"错误位置："<<ftell(fpin)<<"\twrong: miss 'then'"<<endl;
			cout<<"add 'then' correctly!"<<endl;
			
			fseek(fpin,-1L*token->name.length(),SEEK_CUR);
			token=analyse(fpin);
        	if(token->name=="while")
        	{
        		flagwhile=1;
			}
			else{
				flagwhile=0;
			}
			for(int i=0;i<(int)token->name.length();i++){//*******************************
			//	cout<<"**************"<<endl;
				fseek(fpin,-1L,SEEK_CUR);
			}
        	ProcedureS(fpin,s1);
       		ProcedureSn(fpin,s2,c);
       		if(flagwhile==1)
       		{
       			sprintf(s.code,"\t%s\n\t%s%s",c.code,s1.code,s2.code);
       			flagwhile=0;
			}
			else
			{
       			sprintf(s.code,"\t%s\nL%d:\t%s%s",c.code,c.c_true,s1.code,s2.code);
       		}
			
			//exit(-1);
		}
		
	}
	else if(token->name=="while"){//WHILE
		//!cout<<token->name<<endl;
		//cout<<"\nSSSSSSSSSwhile\n"<<endl;
		//s.next=newlabel();
		c.c_false=s.next;
		int flagwhile_temp=0;
		if(flagwhile==1)
			flagwhile_temp=1;
		if(flagwhile_temp==1)
		{
			if(flagelse==1)
			{
				s1.next=s.begin=thislabel()-1;
				flagelse=0;
			}
			else
			{
				s1.next=s.begin=thislabel();
			}
			flagwhile_temp=0;
			//flagwhile=0;
			
		}
		else 
		{
			if(flagelse==1)
			{
				s1.next=s.begin=newlabel()-1;
				flagelse=0;
			}
			else
			{
				s1.next=s.begin=newlabel();
			}
		}
		c.c_true=s1.begin=newlabel();
		
		ProcedureC(fpin,c);
		token=analyse(fpin);
		if(token->name==";"){
			fseek(fpin,-1L,SEEK_CUR);
			//cout<<s.code<<endl;
			return 0;
		}
		if(token->name=="do"){//DO
			//!cout<<token->name<<endl;
			ProcedureS(fpin,s1);
			sprintf(s.code,"\nL%d:\t%s\nL%d:\t%s\n\tgoto L%d ",s.begin,c.code,c.c_true,s1.code,s.begin);
			//cout<<s.code<<endl;
		}else{
			cout<<"错误位置："<<ftell(fpin)<<endl<<"wrong: miss 'do'"<<endl;
			cout<<"add 'do' correctly!"<<endl;
			
			fseek(fpin,-1L*token->name.length(),SEEK_CUR);
			ProcedureS(fpin,s1);
			sprintf(s.code,"\nL%d:\t%s\nL%d:\t%s\n\tgoto L%d ",s.begin,c.code,c.c_true,s1.code,s.begin);
			
			//exit(-1);
		}
		
	}else if(token->type==IDENTIFIER){
		//!cout<<"id: "<<token->name<<endl;
		strcpy(temp_idn_name,token->name.c_str());
		Token *token1=analyse(fpin);
		if(token1->name==";"){
			fseek(fpin,-1L,SEEK_CUR);
			return 0;
		}
		if(token1->name=="="){
			ProcedureE(fpin,e);
			sprintf(s.code,"%s\n\t%s=%s",e.code,temp_idn_name,e.place);
		}else{
			cout<<"错误位置："<<ftell(fpin)<<endl<<"wrong: illegal"<<endl;
			exit(-1);
		}
		
	}

	
	
	else if(token->name=="{"){
		//cout<<token->name<<endl;
		//cout<<token->name<<endl;
		leftcheck=1;
		ProcedureP(fpin,p);
		sprintf(s.code,"%s",p.code);
		Token* token=analyse(fpin);

		if(token->name=="}"){
		//!cout<<token->name<<endl;
		//cout<<token->name<<endl;
		rightcheck=1;
		}
		else {
			cout<<"错误位置："<<ftell(fpin)<<"\twrong {}, miss '} '"<<endl;
			exit(-1);
		}			
		
	}
	 
	return 0;	
} 

int ProcedureC(FILE* fpin, AttrC &c){
	//!cout<<"C"<<endl;
	Token*token;
	AttrE e1;
	strcpy(e1.code,"");
	strcpy(e1.place,"");
	AttrE e2;
	strcpy(e2.code,"");
	strcpy(e2.place,"");
	ProcedureE(fpin,e1);
	token=analyse(fpin);

	if(token->name==";"){
		fseek(fpin,-1L,SEEK_CUR);
			return 0;
		}
	if(token->name==">"){
		//!cout<<token->name<<endl;
		ProcedureE(fpin,e2);
		sprintf(c.code,"%s%s\n\tif %s>%s goto L%d\n\tgoto L%d",e1.code,e2.code,e1.place,e2.place,c.c_true,c.c_false);
	}
	else if(token->name=="<"){
		//!cout<<token->name<<endl;
		ProcedureE(fpin,e2);
		sprintf(c.code,"%s%s\n\tif %s<%s goto L%d\n\tgoto L%d",e1.code,e2.code,e1.place,e2.place,c.c_true,c.c_false);
	}
	else if(token->name=="="){
		//!cout<<token->name<<endl;
		ProcedureE(fpin,e2);
		//cout<<"check"<<e1.place;
		sprintf(c.code,"%s%s\n\tif %s=%s goto L%d\n\tgoto L%d",e1.code,e2.code,e1.place,e2.place,c.c_true,c.c_false);
	}
	else{
		exit(-1);
	}
	return 0;
}

int ProcedureE(FILE*fpin, AttrE &e){
    //cout<<"E"<<endl;
    AttrT t1;
    strcpy(t1.code,"");
    strcpy(t1.place,"");
    AttrT t2;
    strcpy(t2.code,"");
    strcpy(t2.place,"");
	Token*token;
	ProcedureT(fpin,t1);
	while (true){
		token=analyse(fpin);
		//cout<<"proE:"<<token->name<<endl;
		/*if(token->name==";"){
			fseek(fpin,-1L,SEEK_CUR);
			break;
		}*/

		if(token->name=="+"){
			//!cout<<token->name<<endl;
			ProcedureT(fpin,t2);
			//cout<<t2.place<<"###"<<endl;
			strcpy(e.place,newtemp());
			sprintf(e.code,"%s%s\n\t%s=%s+%s",t1.code,t2.code,e.place,t1.place,t2.place);
			//cout<<e.code<<"###"<<endl;
			strcpy(t1.code,e.code);
			strcpy(t1.place,e.place);
			
		}else if(token->name=="-"){
			//!cout<<token->name<<endl;
			ProcedureT(fpin,t2);
			strcpy(e.place,newtemp());
			sprintf(e.code,"%s%s\n\t%s=%s-%s",t1.code,t2.code,e.place,t1.place,t2.place);
			strcpy(t1.code,e.code);
			strcpy(t1.place,e.place);
		}else{
			//cout<<"EEEEEEEEEEEE"<<token->name<<endl;
			
		//	cout<<"huitui "<<token->name.length()<<":"<<token->name<<endl;
			for(int i=0;i<(int)token->name.length();i++){//*******************************
			//	cout<<"**************"<<endl;
				fseek(fpin,-1L,SEEK_CUR);
			}
			strcpy(e.place,t1.place);
			sprintf(e.code,"%s",t1.code);
			break;
		}
	}
	//cout<<e.code<<endl;
	return 0;
}


int ProcedureT(FILE*fpin, AttrT &t){
	//cout<<"T"<<endl;
	AttrF f1;
	strcpy(f1.code,"");
	strcpy(f1.place,"");
	AttrF f2;
	strcpy(f2.code,"");
	strcpy(f2.place,"");
	Token*token;
	ProcedureF(fpin,f1);
	while(true){
		token=analyse(fpin);
		/*if(token->name==";"){
			fseek(fpin,-1L,SEEK_CUR);
			break;
		}*/
		if(token->name=="*"){
			//!cout<<token->name<<endl;
			ProcedureF(fpin,f2);
			strcpy(t.place,newtemp());
			sprintf(t.code,"%s%s\n\t%s=%s*%s",f1.code,f2.code,t.place,f1.place,f2.place);
			strcpy(f1.code,t.code);
			strcpy(f1.place,t.place);
			//cout<<t.code<<endl;
		}
		else if(token->name=="/"){
		    //!cout<<token->name<<endl;		
			token=analyse(fpin);
		    if(token->name=="0"){
		    	cout<<"错误位置："<<ftell(fpin)<<endl<<"wrong: division by 0"<<endl;
				exit(-1);
			}
			/*if(token->name==";"){
				cout<<"错误位置："<<ftell(fpin)<<endl<<"wrong: miss number or id"<<endl;
				exit(-1);
			}*/
			
			fseek(fpin,-1L*token->name.length(),SEEK_CUR);
			
			ProcedureF(fpin,f2);
			strcpy(t.place,newtemp());		
			sprintf(t.code,"%s%s\n\t%s=%s/%s",f1.code,f2.code,t.place,f1.place,f2.place);
			strcpy(f1.code,t.code);
			strcpy(f1.place,t.place);
			//cout<<t.code<<endl;
		}else{
			//cout<<"TTTTTTTTTTT"<<token->name<<endl;
			
			if(token->name==")" && rightcheck1==0 && leftcheck1==0){
				cout<<"错误位置："<<ftell(fpin)<<"\twrong (), miss '( '"<<endl;
				exit(-1);
			}
			
			fseek(fpin,-1L*(int)token->name.length(),SEEK_CUR);
			
			strcpy(t.place,f1.place);
			//cout<<t.code<<"???"<<endl;
			sprintf(t.code,"%s",f1.code);
			//cout<<t.code<<"!!!"<<endl;
			break;
		}
	}
	//cout<<t.code<<endl;
	return 0;
}

int ProcedureF(FILE*fpin, AttrF &f){
	AttrE e;
	strcpy(e.code,"");
	strcpy(e.place,"");
	int st8;
	int st16;
	char temp_value[50];
	//cout<<"F"<<endl;
	Token*token;
	token=analyse(fpin);
	
	//cout<<"FFFFFFFF"<<token->name<<endl;

	if(token->name==";" ||token->name==")" ||token->name=="*" ||token->name=="/" ){//顺序疑似有误 
			cout<<"错误位置："<<ftell(fpin)<<endl<<"wrong: miss number or id"<<endl;
			exit(-1);
			fseek(fpin,-1L,SEEK_CUR);
			return 0;
			
		}

	if(token->name=="("){
		//!cout<<token->name<<endl;
		leftcheck1=1;
		ProcedureE(fpin,e);
		strcpy(f.place,e.place);
		sprintf(f.code,"%s",e.code);
		token=analyse(fpin);
		if(token->name!=")"){
			cout<<"错误位置："<<ftell(fpin)<<"\twrong (), miss ') '"<<endl;
			//cout<<"wrong"<<endl;
			exit(-1);
		}
		else if(token->name==";"){
			fseek(fpin,-1L,SEEK_CUR);
			return 0;
		}
		else{
			leftcheck1=0;
		}
	
		//!cout<<token->name<<endl;
	}

	if(token->type==IDENTIFIER){
	//	cout<<"??"<<endl;
		//!cout<<"id: "<<token->name<<endl;
		strcpy(f.place,token->name.c_str());
		sprintf(f.code,"\0");
		//cout<<f.place<<"###"<<endl;
	}
	if(token->type==INT8){
		//!cout<<"int8: "<<token->name<<endl;
		
		st8=(int)valueof8(token->value);
        if(st8!=valueof8(token->value))
		{		
		    sprintf(temp_value,"%lf",valueof8(token->value));
    	}
    	else
    	{
    		sprintf(temp_value,"%d",st8);
		}
		strcpy(f.place,temp_value);
		sprintf(f.code,"\0");
	}
	if(token->type==INT10){
		//!cout<<"int10: "<<token->name<<endl;
		strcpy(f.place,token->name.c_str());
		sprintf(f.code,"\0");
	}
	if(token->type==INT16){
		//!cout<<"int16: "<<token->name<<endl;
		st16=(int)valueof16(token->value);
		if(st16!=valueof16(token->value))
		{		
		    sprintf(temp_value,"%lf",valueof16(token->value));
    	}
    	else
    	{
    		sprintf(temp_value,"%d",st16);
		}
		strcpy(f.place,temp_value);
		sprintf(f.code,"\0");
	}
	
	/*else{
		cout<<"错误位置："<<ftell(fpin)<<"\twrong (), miss number or IDENTIFIER"<<endl;
		//cout<<"wrong"<<endl;
		exit(-1);
	}*/
	
	//cout<<f.place<<endl;
	return 0;
}


int main()
{
	//cout<<valueof16("0xa.1111")<<endl;
    char inFile[40];
    FILE *fpin;
   // cout<<"请输入源文件名（包括路径和后缀）:";
    while(true){
        //cin>>inFile;
        if((fpin=fopen("C:\\Users\\23854\\Desktop\\ceshiyongli.txt","r"))!=NULL)
            break;
        else{
            cout<<"文件名错误！"<<endl;
            cout<<"请输入源文件名（包括路径和后缀）:";
        }
 
    }
    

	//!cout<<"P"<<endl;
	AttrP p;
	 
	ProcedureP(fpin,p);
	cout<<"------语法分析如下------"<<endl;
	//cout<<wrongcheck<<endl;
    if(!wrongcheck){
		cout<<p.code<<endl;
	}

	return 0;
}
