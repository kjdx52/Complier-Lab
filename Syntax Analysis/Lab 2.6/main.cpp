#include <bits/stdc++.h>

using namespace std;

string keyword[23]={"int","if","else","while","main","return","=","+","-","*", //0-9
                    "/",">",">=","<","<=","==","!=","{","}",";"                //10-19
					,",","(",")"};                                             //20-22
struct element
{
    int type=-1;
    string value;
}ele[100];
int e=0;//element的指针
int cnt=0;//element句法遍历
int error=0;//1:有错；0:无措
//判断字母

void BLOCK();
void DECLS();
void DECLS1();
void DECL();
void NAMES();
void NAMES1();
void NAME();
void TYPE();
void STMTS();
void STMTS1();
void STMT();
void BOOL();
void ROP();
void EXPR();
void EXPR1();
void TERM();
void TERM1();
void FACTOR();

bool IsChar(char c){
	if(c>='a'&&c<='z'||c>='A'&&c<='Z'||c=='_')
		return true;
	else
		return false;
}

bool IsNum(char c){
	if(c>='0'&&c<='9')
		return true;
	else
		return false;
}

//判断id字符
bool IsId(char c){
	if(IsNum(c)||IsChar(c))
		return true;
	else
		return false;
}

bool IsPun(char c){
	if((c>='('&&c<='/')||(c>=';'&&c<='>')||c=='{'||c=='}')
		return true;
	else
		return false;
}

void AddEle(string c,int f)
{
    //char ccc[10];
    //strcpy(ccc,c);
    //cout<<e<<"\n";
    if(f==1)//字符串
    {
        int i;
        for(i=0;i<=5;i++)
        {
            if(c==keyword[i])
                {
                    ele[e].value=c;
                    ele[e].type=i;
                    e++;
                    break;
                }
        }
        if(i==6)
        {
            ele[e].value=c;
            ele[e].type=23;
            e++;
        }
    }
    else if(f==2)//数字
    {
        ele[e].value=c;
        ele[e].type=0;
        e++;
    }
    else if(f==3)//标点
    {
        int i;
        for(i=6;i<=22;i++)
        {
            if(c==keyword[i])
                {
                    ele[e].value=c;
                    ele[e].type=i;
                    e++;
                    break;
                }
        }
        if(i==23)
            error=1;
    }
    else
        error=1;
}
void cifa(char* str)
{
    char str1[10];
    int i=0;
    int len=strlen(str);
   while(i<len)
   {
    if (str[i]==' '||str[i]=='\n')
        i++;
    else
    {
        if(IsChar(str[i]))
        {
            int j=0;
            str1[j]=str[i];
            j++;i++;
            while(IsId(str[i]))
            {
                str1[j]=str[i];
                j++;i++;
            }
            str1[j]='\0';
            AddEle(str1,1);

            //cout<<ele[e-1].value<<"   "<<ele[e-1].type<<"\n";
        }

        if(IsNum(str[i]))
        {
            int j=0;
            str1[j]=str[i];
            j++;i++;
            while(IsNum(str[i]))
            {
                str1[j]=str[i];
                j++;i++;
            }
            str1[j]='\0';
            AddEle(str1,2);

            //cout<<ele[e-1].value<<"   "<<ele[e-1].type<<"\n";
        }

        if(IsPun(str[i]))
        {
            int j=0;
            str1[j]=str[i];
            j++;i++;
            while((str[i-1]<='>'&&str[i-1]>='<')&&(str[i]<='>'&&str[i]>='<'))
            {
                str1[j]=str[i];
                j++;i++;
            }
            str1[j]='\0';
            AddEle(str1,3);

            //cout<<ele[e-1].value<<"   "<<ele[e-1].type<<"\n";
        }
    }
   }


}

void PROG(){
int x=ele[cnt].type;
if(x==0){   //int
    cnt++;
    if(ele[cnt].type==4){//main
      cnt++;
    }else
    {
        error=1;
        return;
    }
    if(ele[cnt].type==21){//(
      cnt++;
    }else
    {
        error=1;
        return;
    }
    if(ele[cnt].type==22){//)
      cnt++;
    }else
    {
        error=1;
        return;
    }
    BLOCK();
}else
{
    error=1;
    return;
}
}

void BLOCK(){
    int x=ele[cnt].type;            //x记录当前单词的类别
    if(x==17){                    //match {
        cnt++;
        DECLS();

        if(error==1) return;       //如果出现错误，直接return
        STMTS();
        if(error==1) return;       //如果出现错误，直接return
        if(ele[cnt].type==18){      //match }
            cnt++;
        }
        else{                     //如果不是'}'，令error=1
            error=1;
        }
    }
    else{     //Error
        error=1;
    }
}

void DECLS(){
    int x=ele[cnt].type;            //x记录当前单词的类别
        DECLS1();
}

void DECLS1(){
    int x=ele[cnt].type;            //x记录当前单词的类别
    if(x==0){                    //如果是 first-int
        DECL();
        if(error==1) return;       //如果出现错误，直接return
        DECLS1();
    }
    else if(x==23||x==1||x==3||x==17||x==18||x==5){ //Follow

        return;
    }
    else{      //Error
        error=1;
    }
}

void DECL(){
    int x=ele[cnt].type;            //x记录当前单词的类别

        TYPE();

        if(error==1) return;       //如果出现错误，直接return
        NAMES();

        if(error==1) return;       //如果出现错误，直接return
        if(ele[cnt].type==19){      //match ;
            cnt++;
        }
        else{                     //如果不存在';'，令error=1
            error=1;
        }


}

void TYPE(){
    int x=ele[cnt].type;            //x记录当前单词的类别
    if(x==0){
        cnt++;
    }
    else{       //Error
        error=1;
    }
}

void NAMES(){
    int x=ele[cnt].type;            //x记录当前单词的类别
        NAME();

        if(error==1) return;       //如果出现错误，直接return
        NAMES1();

}

void NAMES1(){
    int x=ele[cnt].type;            //x记录当前单词的类别

    if(x==20){                    //,
        cnt++;
        NAME();

        if(error==1) return;       //如果出现错误，直接return
        NAMES1();
    }
    else if(x==19){               //Follow集合
        return;
    }
    else{       //Error
        error=1;
    }
}

void NAME(){
    int x=ele[cnt].type;            //x记录当前单词的类别
    if(x==23){                     //id
        cnt++;
    }
    else{       //Error
        error=1;
    }
}

void STMTS(){
    int x=ele[cnt].type;            //x记录当前单词的类别
        STMTS1();
}

void STMTS1(){
    int x=ele[cnt].type;            //x记录当前单词的类别
    if(x==23||x==1||x==3||x==17||x==5){//id if while {
        STMT();
        if(error==1) return;       //如果出现错误，直接return
        STMTS1();
    }
    else if(x==18){               //Follow集合
        return;
    }
    else{       //Error
        error=1;
    }
}

void STMT(){
    int x=ele[cnt].type;           //x记录当前单词的类别
    if(x==23){                    //类别(id)
        ++cnt;
        if(ele[cnt].type!=6){
            error=1;
            return;
        }
        ++cnt;                  //match('=')
        EXPR();
        if(error==1) return;      //如果出现错误，直接return
        if(ele[cnt].type==19){     //match(';')
            ++cnt;
        }
        else{
            error=1;
        }
    }
    else if(x==1){              //类别('if')
        ++cnt;
        if(ele[cnt].type!=21){     //match(
            error=1;
            return;
        }
        ++cnt;
        BOOL();
        if(error==1) return;      //如果出现错误，直接return
        if(ele[cnt].type!=22){     //match(')')
            error=1;
            return;
        }
        ++cnt;
        STMT();
        if(error==1) return;      //如果出现错误，直接return
        if(ele[cnt].type==2)     //展望一步是否为else
        {
            ++cnt;
            STMT();

        }
    }
    else if(x==3){              //类别('while')
        ++cnt;
        if(ele[cnt].type!=21){     //match('(')
            error=1;
            return;
        }
        ++cnt;
        BOOL();
        if(error==1) return;      //如果出现错误，直接return
        if(ele[cnt].type!=22){     //match(')')
            error=1;
            return;
        }
        ++cnt;
        STMT();
    }
    else if(x==17){              //类别('{')
        BLOCK();
    }
    else if(x==5)
    {

        ++cnt;
        if(ele[cnt].type!=0){     //int
            error=1;
            return;

        }
        ++cnt;
        if(ele[cnt].type!=19){     //;
            error=1;
            return;
        }
        ++cnt;
    }
    else{       //Error
        error=1;
    }
}

void BOOL(){
    int x=ele[cnt].type;           //x记录当前单词的类别
    EXPR();
    if(error==1) return;
    ROP();
    if(error==1) return;
    EXPR();
    if(error==1) return;
}

void ROP(){
    int x=ele[cnt].type;           //x记录当前单词的类别
    if(x>=11&&x<=16){       //>, <, ==, !=, >=, <=
        ++cnt;
        return;
    }
    else{    //Error
        error=1;
    }
}

void EXPR(){
    int x=ele[cnt].type;           //x记录当前单词的类别
        TERM();
        if(error==1) return;      //如果出现Error，直接return
        EXPR1();
}

void EXPR1(){
    int x=ele[cnt].type;        //x记录当前单词的类别
    if(x==7||x==8){         //ADDOP
        ++cnt;               //match('+' or '-')
        TERM();
        if(error==1) return;   //如果出现Error，直接return
        EXPR1();
    }
    else if(x==22||x==19||(x>=11&&x<=16)){
        return;               //匹配到Follow集，直接return
    }
    else{     //Error
        error=1;
    }
}

void TERM(){
        FACTOR();
        if(error==1) return;   //如果出现Error，直接return
        TERM1();

}

void TERM1(){
    int x=ele[cnt].type;        //x记录当前单词的类别
    if(x==9||x==10){         //MULOP
        ++cnt;               //match('*' or '/')
        FACTOR();

        if(error==1) return;   //如果出现Error，直接return
        TERM1();
    }
    else if((x>=7&&x<=8)||x==22||x==19||(x>=11&&x<=16)){
        return;               //匹配到Follow集，直接return
    }
    else{     //Error
        error=1;
    }
}

void FACTOR(){
    int x=ele[cnt].type;      //x记录当前单词的类别

    if(x==23||x==0){         //类别('id')，(int)
        ++cnt;             //match(id or number)

    }
    else if(x==21){
        ++cnt;             //match('(')
        EXPR();

        if(error==1) return; //如果出现Error，直接return
        if(ele[cnt].type==22){//match(')')
            ++cnt;

        }
        else{
            error=1;
        }
    }
    else{     //Error
        error=1;
    }
}

int main()
{
 FILE *p;
 int  i=0;
 char str[1000],c;
 if((p=fopen("input.txt","rt"))==NULL){
  printf("Can not open!");
  return  0;
 }
 else{
  while((c=getc(p))!=EOF){
   str[i++] = c;
  }
  fclose(p);
 }
 str[i]='\0';

 cifa(str);


i=0;
while (ele[i].type!=-1)
{
    cout<<ele[i].value<<"   "<<ele[i].type<<"\n";
    i++;
}cout<<"error in DECLS1"<<error<<"  "<<endl;
PROG();
 if(error==0)
    cout<<"程序无误！";
    else
    cout<<"程序出现错误";
}
