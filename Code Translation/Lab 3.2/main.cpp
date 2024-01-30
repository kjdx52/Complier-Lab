#include <bits/stdc++.h>

using namespace std;
struct Ele//每个节点的属性
{
    int i; //继承
    int s; //综合
    int ireg=-1;   //继承的为寄存器（1）还是立即数（0），初始化为未知类型（-1）
    int sreg=-1;   //综合的为寄存器（1）还是立即数（0），初始化为未知类型（-1）
};
int reg[200];//寄存器
int r=0; //分配存储器位置的指针
int line=0; //存储汇编指令的行数

struct ID       //记录id存储的寄存器
{
    string name;
    int reg_id;
}id[50];

int fid=0;  //  统计共存储了多少个id

struct JumpStorage  //跳转指令存储位置
{
    string name;
    int line;
}jumps[50];
int js=0;


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
int Findid(string y);//寻找这个id存放的寄存器，如果没有之前定义，则返回-1
bool IfId(int r);//判断这个寄存器是否是存放id
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
void BOOL(int t);
int ROP();
Ele EXPR(Ele e);
Ele EXPR1(Ele e);
Ele TERM(Ele e);
Ele TERM1(Ele e);
Ele FACTOR(Ele e);
Ele code(int op, Ele e1, Ele e2);//对数据进行运算
void Output();//输出结果

bool IfId(int r)
{
    int i;
    for (i=0;i<fid;i++)
    {
        if(id[i].reg_id==r)
            return true;
    }
        return false;
}

int Findid(string y)
{
    int i;
    for (i=0;i<fid;i++)
    {
        if (y==id[i].name)
        {
             break;
        }

    }
    if(i==fid)
        i=-1;
    else
        i=id[i].reg_id;
    return i;
}

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
    string y=ele[cnt].value;

    if(x==23){                     //id
        cnt++;
        id[fid].name=y;
        id[fid].reg_id=r;
        cout<<"(给"<<y<<"分配reg"<<r<<")\n";
        r++;
        fid++;

    }
    else{       //Error
        error=1;
    }
}

void STMTS(){
    //cout<<"进入STMTS\n";
    int x=ele[cnt].type;            //x记录当前单词的类别
        STMTS1();
}

void STMTS1(){
    //cout<<"进入STMTS1\n";
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
    string y=ele[cnt].value;
    //cout<<"进入STMT且x,y为\n"<<x<<"\t"<<y<<"\n";
    if(x==23){                    //类别(id),赋值语句
        ++cnt;
        if(ele[cnt].type!=6){
            error=1;
            return;
        }
        ++cnt;                  //match('=')
        Ele E;
        E=EXPR(E);

        if(error==1) return;      //如果出现错误，直接return
        if(ele[cnt].type==19){     //match(';')
            ++cnt;
        }
        else{
            error=1;
        }
        int idreg=Findid(y);
        if(idreg!=-1)
        {
        reg[idreg]=reg[E.s];
        id[idreg].name=y;
         cout<<line<<":\tMOV\treg"<<idreg<<"\treg"<<E.s<<"\n";   //打印汇编指令，形成三元组
        line++;
        }
        else
        cout<<"变量未提前声明\n";


    }
    else if(x==1){              //类别('if')
        ++cnt;
        if(ele[cnt].type!=21){     //match(
            error=1;
            return;
        }
        ++cnt;
        BOOL(x);
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
            cout<<line<<":\tJMP\tIFFINISH\n";
            line++;
            cout<<line<<":\tIFNEXT:\n";
            jumps[js].name="IFNEXT";
            jumps[js].line=line;
            js++;
            line++;
            ++cnt;
            STMT();
            cout<<line<<":\tIFFINISH:\n";
            jumps[js].name="IFFINISH";
            jumps[js].line=line;
            js++;
            line++;
        }
        else
            {cout<<line<<":\tIFNEXT:\n";
            jumps[js].name="WHILEBEGIN";
            jumps[js].line=line;
            js++;
            line++;}
    }
    else if(x==3){              //类别('while')
        ++cnt;
        if(ele[cnt].type!=21){     //match('(')
            error=1;
            return;
        }
        ++cnt;
        cout<<line<<":\tWHILEBEGIN:\n";
        jumps[js].name="WHILEBEGIN";
        jumps[js].line=line;
        js++;
        line++;
        BOOL(x);
        if(error==1) return;      //如果出现错误，直接return
        if(ele[cnt].type!=22){     //match(')')
            error=1;
            return;
        }
        ++cnt;
        STMT();
        cout<<line<<":\tJMP\tWHILEBEGIN\n";
        line++;

        cout<<line<<":\tWHILENEXT:\n";
        jumps[js].name="WHILENEXT";
        jumps[js].line=line;
        js++;
        line++;

    }
    else if(x==17){              //类别('{')
        BLOCK();
    }
    else if(x==5)       //return
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

void BOOL(int t){
    int x=ele[cnt].type;           //x记录当前单词的类别
    Ele e1,e2;
    e1=EXPR(e1);
    if(error==1) exit(1);
    int rop = ROP();
    if(error==1) exit(1);
    e2=EXPR(e2);
    if(error==1) exit(1);

    switch(rop)
    {
    case 11:    //>
         cout<<line<<":\tCMP\treg"<<e1.s<<"\treg"<<e2.s<<"\n";   //打印汇编指令，形成三元组
         line++;
         if(t==1)//if
            {

            cout<<line<<":\tJLE\tIFNEXT\n";
            line++;

            }
         else if(t==3)//while
            {

            cout<<line<<":\tJLE\tWHILENEXT\n";
            line++;

            }
            break;
    case 12:    //<
        cout<<line<<":\tCMP\treg"<<e1.s<<"\treg"<<e2.s<<"\n";   //打印汇编指令，形成三元组
        line++;
         if(t==1)//if
            {

            cout<<line<<":\tJGE\tIFNEXT\n";
            line++;

            }
         else if(t==3)//while
            {

            cout<<line<<":\tJGE\tWHILENEXT\n";
            line++;

            }
break;
    case 13:    //==
        cout<<line<<":\tCMP\treg"<<e1.s<<"\treg"<<e2.s<<"\n";   //打印汇编指令，形成三元组
        line++;
         if(t==1)//if
            {

            cout<<line<<":\tJNZ\tIFNEXT\n";
            line++;

            }
         else if(t==3)//while
            {

            cout<<line<<":\tJNZ\tWHILENEXT\n";
            line++;

            }
            break;
    case 14:    // !=
        cout<<line<<":\tCMP\treg"<<e1.s<<"\treg"<<e2.s<<"\n";   //打印汇编指令，形成三元组
        line++;
         if(t==1)//if
            {

            cout<<line<<":\tJZ\tIFNEXT\n";
            line++;

            }
         else if(t==3)//while
            {

            cout<<line<<":\tJZ\tWHILENEXT\n";
            line++;

            }
            break;
    case 15:    //>=
        cout<<line<<":\tCMP\treg"<<e1.s<<"\treg"<<e2.s<<"\n";   //打印汇编指令，形成三元组
        line++;
         if(t==1)//if
            {

            cout<<line<<":\tJL\tIFNEXT\n";
            line++;

            }
         else if(t==3)//while
            {

            cout<<line<<":\tJL\tWHILENEXT\n";
            line++;

            }
            break;
    case 16:    //<=
        cout<<line<<":\tCMP\treg"<<e1.s<<"\treg"<<e2.s<<"\n";   //打印汇编指令，形成三元组
        line++;
         if(t==1)//if
            {

            cout<<line<<":\tJG\tIFNEXT\n";
            line++;

            }
         else if(t==3)//while
            {

            cout<<line<<":\tJG\tWHILENEXT\n";
            line++;

            }

    }
}

int ROP(){
    int x=ele[cnt].type;           //x记录当前单词的类别
    if(x>=11&&x<=16){       //>, <, ==, !=, >=, <=
        ++cnt;
        return x;
    }
    else{    //Error
        error=1;
    }
}

Ele EXPR(Ele e){
    //cout<<"进入EXPR\n";
    int x=ele[cnt].type;           //x记录当前单词的类别
        Ele T,E1,E;
        E=e;    //E获得继承的属性
        T=TERM(T);  //T获得综合属性
        E1.i=T.s;   //E1获得继承属性
        E1.ireg=T.sreg;
        //if(error==1) exit(1);      //如果出现Error，直接return
        E1=EXPR1(E1);
        E.s=E1.s;   //E获得综合属性
        E.sreg=E1.sreg;
        if(E.sreg==0)
        {
            reg[r]=E.s;
            E.sreg=1;
            E.s=r;
            cout<<line<<":\tMOV\treg"<<r<<"\t"<<reg[r]<<"\n";
            line++;
            r++;
        }
        return E;
}

Ele EXPR1(Ele e){
    int x=ele[cnt].type;        //x记录当前单词的类别
    if(x==7||x==8){         //ADDOP
        ++cnt;               //match('+' or '-')
        Ele E1,T,E2;
        E1=e;
        T=TERM(T);
        E1=code(x,T,E1);    //进行加减计算
        E2.i=E1.i;  //继承
        E2.ireg=E1.ireg;
        //if(error==1) exit(1);   //如果出现Error，直接return
        E2=EXPR1(E2);
        E1.s=E2.s;  //综合
        E1.sreg=E2.sreg;
        return E1;
    }
    else if(x==22||x==19||(x>=11&&x<=16)){
        Ele E1=e;
        E1.s=E1.i;  //综合得到自身的继承属性
        E1.sreg=E1.ireg;
        return E1;
    }
    else{     //Error
        error=1;
    }
}

Ele TERM(Ele e){
    //cout<<"进入TERM\n";
    Ele T,F,T1;
    T=e;

    F=FACTOR(F);
    T1.i=F.s;   //继承来自兄弟的属性
    T1.ireg=F.sreg;
        //if(error==1) exit(1);   //如果出现Error，直接return
    T1=TERM1(T1);
    T.s=T1.s;   //综合
    T.sreg=T1.sreg;
    return T;

}

Ele TERM1(Ele e){

    int x=ele[cnt].type;        //x记录当前单词的类别
    //cout<<"进入TERM1且x="<<x<<"\n";
    if(x==9||x==10){         //MULOP
        ++cnt;               //match('*' or '/')
        Ele T1,F,T2;
        T1=e;
        F=FACTOR(F);
        T1=code(x,F,T1);    //进行乘除计算
        T2.i=T1.i;  //继承
        T2.ireg=T1.ireg;
        //if(error==1)
            //exit(1);   //如果出现Error，直接return
        T2=TERM1(T2);
        T1.s=T2.s;  //综合
        T1.sreg=T2.sreg;
        return T1;
    }
    else if((x>=7&&x<=8)||x==22||x==19||(x>=11&&x<=16)){
                Ele T1=e;
                T1.s=T1.i;//综合得到自身的继承属性
                T1.sreg=T1.ireg;
                return T1;     //match follow set
    }
    else{     //Error
        error=1;
    }
}

Ele FACTOR(Ele e){

    int x=ele[cnt].type;      //x记录当前单词的类别
    string y=ele[cnt].value;
    //cout<<"进入FACTOR且x，y为\n"<<x<<"\t"<<y<<"\n";
    if(x==23){         //类别('id')

        ++cnt;             //match(id)
        Ele F=e;
        int idreg=Findid(y);
        if(idreg!=-1)
        {
        F.s=idreg;
        F.sreg=1;
        return F;
        }
        else
        {
           cout<<"ID未定义";
           exit(1);
        }

    }
    else if(x==0)  //(int)
    {
        ++cnt;
        Ele F=e;
        F.s= atoi(y.c_str());
        //cout<<"F.S="<<F.s<<"\n";
        F.sreg=0;      //综合的为一个立即数
        return F;
    }
    else if(x==21){
        ++cnt;             //match('(')
        Ele F,E;
        F=e;
        E=EXPR(E);
        F.s=E.s;
        F.sreg=E.sreg;

        if(error==1) exit(1); //如果出现Error，直接return
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

Ele code(int op, Ele e1, Ele e2)
{
    if(e2.ireg==0)  //e2作为最后运算结果存放的位置需要有一个寄存器来存储结果，如果是一个立即数则需要将立即数放入到寄存器中
             {
                 reg[r]=e2.i;   //将立即数放到寄存器中
                 e2.ireg=1;     //修改e2继承属性标志为寄存器
                 e2.i=r;        //将e2的继承的值改为寄存器的位置
                 cout<<line<<":\tMOV\treg"<<r<<"\t"<<reg[r]<<"\n";   //打印汇编指令，形成三元组
                 line++;
                 r++;
             }
             else if (IfId(e2.i))//如果e2是存储着id内容的寄存器，在算术表达式中，id的内容不改变，所以需要赋值到一个新的寄存器中
             {
                 reg[r]=reg[e2.i];   //将id的值放到新寄存器中
                 int temp=e2.i;
                 e2.i=r;              //将e2的继承的值改为新寄存器的位置
                 cout<<line<<":\tMOV\treg"<<r<<"\treg"<<temp<<"\n";   //打印汇编指令，形成三元组
                 line++;
                 r++;
             }


    switch(op)  //根据不同的操作符有不同的操作
    {
    case 7:
             if(e1.sreg==0)    //立即数
             {
                 reg[e2.i]=reg[e2.i]+e1.s;  //计算结果，并存到目标寄存器中
                 cout<<line<<":\tADD\treg"<<e2.i<<"\t"<<e1.s<<"\n";//打印汇编指令，形成四元组
                 line++;
             }
             else   //寄存器
             {
                 reg[e2.i]=reg[e2.i]+reg[e1.s];//计算结果，并存到目标寄存器中
                 cout<<line<<":\tADD\treg"<<e2.i<<"\treg"<<e1.s<<"\n";//打印汇编指令，形成四元组
                 line++;
             }
        return e2;
    case 8:
            if(e1.sreg==0)    //立即数
             {
                 reg[e2.i]=reg[e2.i]-e1.s;//计算结果，并存到目标寄存器中
                 cout<<line<<":\tSUB\treg"<<e2.i<<"\t"<<e1.s<<"\n";//打印汇编指令，形成四元组
                 line++;
             }
             else   //寄存器
             {
                 reg[e2.i]=reg[e2.i]-reg[e1.s];//计算结果，并存到目标寄存器中
                 cout<<line<<":\tSUB\treg"<<e2.i<<"\treg"<<e1.s<<"\n";//打印汇编指令，形成四元组
                 line++;
             }
        return e2;
    case 9:
            if(e1.sreg==0)    //立即数
             {
                 reg[e2.i]=reg[e2.i]*e1.s;//计算结果，并存到目标寄存器中
                 cout<<line<<":\tMUL\treg"<<e2.i<<"\t"<<e1.s<<"\n";//打印汇编指令，形成四元组
                 line++;
             }
             else   //寄存器
             {
                 reg[e2.i]=reg[e2.i]*reg[e1.s];//计算结果，并存到目标寄存器中
                 cout<<line<<":\tMUL\treg"<<e2.i<<"\treg"<<e1.s<<"\n";//打印汇编指令，形成四元组
                 line++;
             }
        return e2;
    case 10:
            if(e1.sreg==0)    //立即数
             {
                 reg[e2.i]=reg[e2.i]/e1.s;//计算结果，并存到目标寄存器中
                 cout<<line<<":\tDIV\treg"<<e2.i<<"\t"<<e1.s<<"\n";//打印汇编指令，形成四元组
                 line++;
             }
             else   //寄存器
             {
                 reg[e2.i]=reg[e2.i]/reg[e1.s];//计算结果，并存到目标寄存器中
                 cout<<line<<":\tDIV\treg"<<e2.i<<"\treg"<<e1.s<<"\n";//打印汇编指令，形成四元组
                 line++;
             }
        return e2;
    default:
        cout<<"运算符出错";
        exit(1);
        return e2;
    }
}

void Output()
{

    cout<<"line\tCMD\tA1/Resl\tA2\n";
    PROG();
    cout<<"\nPrint all storage of jump instruction:\n";
    for(int i=0;i<js;i++)
    {
        cout<<jumps[i].name<<":   line"<<jumps[i].line<<"\n";
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
Output();


}
