#include<bits/stdc++.h>
using namespace std;

struct ele//每个节点的属性
{
    int i; //继承
    int s; //综合
    int ireg=-1;   //继承的为寄存器（1）还是立即数（0），初始化为未知类型（-1）
    int sreg=-1;   //综合的为寄存器（1）还是立即数（0），初始化为未知类型（-1）
};
int reg[200];//寄存器
int r=0; //分配存储器位置的指针
int rid;//记录存储着id内容的寄存器，小于等于rid的寄存器都存储着id的内容
int ID[130];   //根据ASCII值定位某个ID所在存储器的位置
const int maxlen=1000;
char str[maxlen];
int f1=0;//指向当前分析输入字符

int inreg(char a);//判断ID是否存储在寄存器中
void error();//报错并退出程序
ele code(char op, ele e1, ele e2);//对数据进行运算
int check(char c);//判断传入字符的类型
bool AddOp(char c);//判断是否为加减运算符
bool MulOp(char c);//判断是否为乘除运算符
void Input();//输入必要的数据
void Output();//输出相关结果
ele Expr(ele e);
ele Expr1(ele e);
ele Term(ele e);
ele Term1(ele e);
ele Factor(ele e);




int inreg(char a)
{
    int ascii=int(a);//将传入的字符转换成ASCII码
    return ID[ascii];//返回ID存储的寄存器，如果没有提前定义则返回默认值-1，初始化在Input完成
}

void error()
{
    cout<<"Error!\n";
    exit(1);    //报错并退出程序
}

ele code(char op, ele e1, ele e2)
{
    if(e2.ireg==0)  //e2作为最后运算结果存放的位置需要有一个寄存器来存储结果，如果是一个立即数则需要将立即数放入到寄存器中
             {
                 reg[r]=e2.i;   //将立即数放到寄存器中
                 e2.ireg=1;     //修改e2继承属性标志为寄存器
                 e2.i=r;        //将e2的继承的值改为寄存器的位置
                 cout<<"MOV\treg"<<r<<"\t"<<reg[r]<<"\n";   //打印汇编指令，形成三元组
                 r++;
             }
    else if(e2.i<=rid)  //如果e2是存储着id内容的寄存器，在算术表达式中，id的内容不改变，所以需要赋值到一个新的寄存器中
            {
                 reg[r]=reg[e2.i];   //将id的值放到新寄存器中
                 int temp=e2.i;
                 e2.i=r;              //将e2的继承的值改为新寄存器的位置
                 cout<<"MOV\treg"<<r<<"\treg"<<temp<<"\n";   //打印汇编指令，形成三元组
                 r++;
            }

    switch(op)  //根据不同的操作符有不同的操作
    {
    case '+':
             if(e1.sreg==0)    //立即数
             {
                 reg[e2.i]=reg[e2.i]+e1.s;  //计算结果，并存到目标寄存器中
                 cout<<"ADD\treg"<<e2.i<<"\t"<<e1.s<<"\treg"<<e2.i<<"\n";//打印汇编指令，形成四元组
             }
             else   //寄存器
             {
                 reg[e2.i]=reg[e2.i]+reg[e1.s];//计算结果，并存到目标寄存器中
                 cout<<"ADD\treg"<<e2.i<<"\treg"<<e1.s<<"\treg"<<e2.i<<"\n";//打印汇编指令，形成四元组
             }
        return e2;
    case '-':
            if(e1.sreg==0)    //立即数
             {
                 reg[e2.i]=reg[e2.i]-e1.s;//计算结果，并存到目标寄存器中
                 cout<<"SUB\treg"<<e2.i<<"\t"<<e1.s<<"\treg"<<e2.i<<"\n";//打印汇编指令，形成四元组
             }
             else   //寄存器
             {
                 reg[e2.i]=reg[e2.i]-reg[e1.s];//计算结果，并存到目标寄存器中
                 cout<<"SUB\treg"<<e2.i<<"\treg"<<e1.s<<"\treg"<<e2.i<<"\n";//打印汇编指令，形成四元组
             }
        return e2;
    case '*':
            if(e1.sreg==0)    //立即数
             {
                 reg[e2.i]=reg[e2.i]*e1.s;//计算结果，并存到目标寄存器中
                 cout<<"MUL\treg"<<e2.i<<"\t"<<e1.s<<"\treg"<<e2.i<<"\n";//打印汇编指令，形成四元组
             }
             else   //寄存器
             {
                 reg[e2.i]=reg[e2.i]*reg[e1.s];//计算结果，并存到目标寄存器中
                 cout<<"MUL\treg"<<e2.i<<"\treg"<<e1.s<<"\treg"<<e2.i<<"\n";//打印汇编指令，形成四元组
             }
        return e2;
    case '/':
            if(e1.sreg==0)    //立即数
             {
                 reg[e2.i]=reg[e2.i]/e1.s;//计算结果，并存到目标寄存器中
                 cout<<"DIV\treg"<<e2.i<<"\t"<<e1.s<<"\treg"<<e2.i<<"\n";//打印汇编指令，形成四元组
             }
             else   //寄存器
             {
                 reg[e2.i]=reg[e2.i]/reg[e1.s];//计算结果，并存到目标寄存器中
                 cout<<"DIV\treg"<<e2.i<<"\treg"<<e1.s<<"\treg"<<e2.i<<"\n";//打印汇编指令，形成四元组
             }
        return e2;
    default:
        cout<<"运算符出错";
        error();
        return e2;
    }
}

int check(char c)
{
    if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c=='_'))
        return 1;       //id
    else if(c>='0'&&c<='9')
        return 2;       //number
    else
        return 0;
}

bool AddOp(char c)
{
    if(c=='+'||c=='-')
        return true;
    else
        return false;
}

bool MulOp(char c)
{
    if(c=='*'||c=='/')
        return true;
    else
        return false;
}

ele Expr(ele e)
{
        ele T,E1,E;
        E=e;    //E获得继承的属性
        T=Term(T);  //T获得综合属性
        E1.i=T.s;   //E1获得继承属性
        E1.ireg=T.sreg;
        E1=Expr1(E1);
        E.s=E1.s;   //E获得综合属性
        E.sreg=E1.sreg;
        if(E.sreg==0)   //为只有一个数字的情况提供
        {
            reg[r]=E.s;
            E.s=r;
            E.sreg=1;
            cout<<"MOV\treg"<<r<<"\t"<<reg[r]<<"\n";
            r++;
        }
        return E;
}



ele Expr1(ele e)
{
    if(AddOp(str[f1])){     //match('+','-')
        ele E1,T,E2;
        E1=e;
        char addop=str[f1];
        ++f1;
        T=Term(T);  //综合的结果
        E1=code(addop,T,E1);    //进行加减计算
        E2.i=E1.i;  //继承
        E2.ireg=E1.ireg;
        E2=Expr1(E2);
        E1.s=E2.s;  //综合
        E1.sreg=E2.sreg;
        return E1;
    }
    else if(str[f1]==')'||str[f1]==';'){    //E1->空  match Follow set
        ele E1=e;
        E1.s=E1.i;  //综合得到自身的继承属性
        E1.sreg=E1.ireg;
        return E1;
    }
    else{     //error
        cout<<"算术表达式格式错误";
        error();

    }
}

ele Term(ele e){
    ele T,F,T1;
    T=e;

    F=Factor(F);
    T1.i=F.s;   //继承来自兄弟的属性
    T1.ireg=F.sreg;
    T1=Term1(T1);
    T.s=T1.s;   //综合
    T.sreg=T1.sreg;
    return T;
}

ele Term1(ele e){
    if(MulOp(str[f1]))
        {
        ele T1,F,T2;
        T1=e;
        char mulop=str[f1];
        ++f1;               //match('*','/')
        F=Factor(F);
        T1=code(mulop,F,T1);    //进行乘除计算
        T2.i=T1.i;  //继承
        T2.ireg=T1.ireg;
        T2=Term1(T2);
        T1.s=T2.s;  //综合
        T1.sreg=T2.sreg;
        return T1;
    }
    else if(AddOp(str[f1])
            ||str[f1]==')'||str[f1]==';'){  //T1->空  match Follow set
                ele T1=e;
                T1.s=T1.i;//综合得到自身的继承属性
                T1.sreg=T1.ireg;
                return T1;     //match follow set
    }
    else{     //error
        cout<<"算术表达式格式错误";
        error();

    }
}

ele Factor(ele e){
    int b=check(str[f1]);
    if(b==1){       //id
        char id=str[f1];
         ++f1;             //match(id)
         ele F=e;
         int rreg=inreg(id);
        if(rreg!=-1)
        {
            F.s= rreg;
            F.sreg=1;     //综合的为一个寄存器
            return F;
        }
        else
        {
            cout<<"变量未提前定义！";
            error();
        }
    }
    else if(b==2)       //number
    {
        char num =str[f1];
        ++f1;       //match(number)
        ele F=e;
        F.s= num-'0';
        F.sreg=0;      //综合的为一个立即数
        return F;
    }
    else if(str[f1]=='('){
        ++f1;             //match '('
        ele F,E;
        F=e;
        E=Expr(E);
        F.s=E.s;
        F.sreg=E.sreg;
        if(str[f1]==')'){ //match(')')
            ++f1;

        }
        else{ //error
            cout<<"算术表达式格式错误(括号不完整)";
            error();
        }
        return F;
    }
    else{     //Error
       cout<<"算术表达式格式错误";
       error();

    }
}



void Input()
{
    for(int i=0;i<130;i++)  //初始化ID数组
        ID[i]=-1;
    cout<<"Input some IDs you will use later (a,2)(input # in ID to end this process):\n";
    char id;    //键入id的名称
    int val;    //id存储的数值
    while(1)
    {
        cout<<"input a new ID(# to end)\n";
        cin>>id;
        if(id=='#') //退出循环的条件
            break;
        cout<<"input above ID's value\n";
        cin>>val;
        reg[r]=val; //将内容存入寄存器
        ID[int(id)]=r;  //记录该id相对应的寄存器
        r++;
    }
    rid=r-1;    //记录存储着id内容的寄存器
    cout<<"\nInput your arithmetic expression:(end with ;)\n";
    cin>>str;
}
void Output()
{
    ele e;
    cout<<"CMD\tA1/Resl\tA2\tResl\n";
    e=Expr(e);
    cout<<"\nFinal result:"<<reg[e.s]<<"\n";    //显示算数表达式最后的结果

    cout<<"\nPrint all used Regs:\n";
    for(int i=0;i<r;i++)    //打印运算结束之后所有的寄存器及其内容
    {
        cout<<"Reg"<<i<<":\t"<<reg[i]<<"\n";
    }
}


int main()
{
    Input();
    Output();
    return 0;
}
