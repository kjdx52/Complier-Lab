#include<bits/stdc++.h>
using namespace std;

struct ele//ÿ���ڵ������
{
    int i; //�̳�
    int s; //�ۺ�
    int ireg=-1;   //�̳е�Ϊ�Ĵ�����1��������������0������ʼ��Ϊδ֪���ͣ�-1��
    int sreg=-1;   //�ۺϵ�Ϊ�Ĵ�����1��������������0������ʼ��Ϊδ֪���ͣ�-1��
};
int reg[200];//�Ĵ���
int r=0; //����洢��λ�õ�ָ��
int rid;//��¼�洢��id���ݵļĴ�����С�ڵ���rid�ļĴ������洢��id������
int ID[130];   //����ASCIIֵ��λĳ��ID���ڴ洢����λ��
const int maxlen=1000;
char str[maxlen];
int f1=0;//ָ��ǰ���������ַ�

int inreg(char a);//�ж�ID�Ƿ�洢�ڼĴ�����
void error();//�����˳�����
ele code(char op, ele e1, ele e2);//�����ݽ�������
int check(char c);//�жϴ����ַ�������
bool AddOp(char c);//�ж��Ƿ�Ϊ�Ӽ������
bool MulOp(char c);//�ж��Ƿ�Ϊ�˳������
void Input();//�����Ҫ������
void Output();//�����ؽ��
ele Expr(ele e);
ele Expr1(ele e);
ele Term(ele e);
ele Term1(ele e);
ele Factor(ele e);




int inreg(char a)
{
    int ascii=int(a);//��������ַ�ת����ASCII��
    return ID[ascii];//����ID�洢�ļĴ��������û����ǰ�����򷵻�Ĭ��ֵ-1����ʼ����Input���
}

void error()
{
    cout<<"Error!\n";
    exit(1);    //�����˳�����
}

ele code(char op, ele e1, ele e2)
{
    if(e2.ireg==0)  //e2��Ϊ�����������ŵ�λ����Ҫ��һ���Ĵ������洢����������һ������������Ҫ�����������뵽�Ĵ�����
             {
                 reg[r]=e2.i;   //���������ŵ��Ĵ�����
                 e2.ireg=1;     //�޸�e2�̳����Ա�־Ϊ�Ĵ���
                 e2.i=r;        //��e2�ļ̳е�ֵ��Ϊ�Ĵ�����λ��
                 cout<<"MOV\treg"<<r<<"\t"<<reg[r]<<"\n";   //��ӡ���ָ��γ���Ԫ��
                 r++;
             }
    else if(e2.i<=rid)  //���e2�Ǵ洢��id���ݵļĴ��������������ʽ�У�id�����ݲ��ı䣬������Ҫ��ֵ��һ���µļĴ�����
            {
                 reg[r]=reg[e2.i];   //��id��ֵ�ŵ��¼Ĵ�����
                 int temp=e2.i;
                 e2.i=r;              //��e2�ļ̳е�ֵ��Ϊ�¼Ĵ�����λ��
                 cout<<"MOV\treg"<<r<<"\treg"<<temp<<"\n";   //��ӡ���ָ��γ���Ԫ��
                 r++;
            }

    switch(op)  //���ݲ�ͬ�Ĳ������в�ͬ�Ĳ���
    {
    case '+':
             if(e1.sreg==0)    //������
             {
                 reg[e2.i]=reg[e2.i]+e1.s;  //�����������浽Ŀ��Ĵ�����
                 cout<<"ADD\treg"<<e2.i<<"\t"<<e1.s<<"\treg"<<e2.i<<"\n";//��ӡ���ָ��γ���Ԫ��
             }
             else   //�Ĵ���
             {
                 reg[e2.i]=reg[e2.i]+reg[e1.s];//�����������浽Ŀ��Ĵ�����
                 cout<<"ADD\treg"<<e2.i<<"\treg"<<e1.s<<"\treg"<<e2.i<<"\n";//��ӡ���ָ��γ���Ԫ��
             }
        return e2;
    case '-':
            if(e1.sreg==0)    //������
             {
                 reg[e2.i]=reg[e2.i]-e1.s;//�����������浽Ŀ��Ĵ�����
                 cout<<"SUB\treg"<<e2.i<<"\t"<<e1.s<<"\treg"<<e2.i<<"\n";//��ӡ���ָ��γ���Ԫ��
             }
             else   //�Ĵ���
             {
                 reg[e2.i]=reg[e2.i]-reg[e1.s];//�����������浽Ŀ��Ĵ�����
                 cout<<"SUB\treg"<<e2.i<<"\treg"<<e1.s<<"\treg"<<e2.i<<"\n";//��ӡ���ָ��γ���Ԫ��
             }
        return e2;
    case '*':
            if(e1.sreg==0)    //������
             {
                 reg[e2.i]=reg[e2.i]*e1.s;//�����������浽Ŀ��Ĵ�����
                 cout<<"MUL\treg"<<e2.i<<"\t"<<e1.s<<"\treg"<<e2.i<<"\n";//��ӡ���ָ��γ���Ԫ��
             }
             else   //�Ĵ���
             {
                 reg[e2.i]=reg[e2.i]*reg[e1.s];//�����������浽Ŀ��Ĵ�����
                 cout<<"MUL\treg"<<e2.i<<"\treg"<<e1.s<<"\treg"<<e2.i<<"\n";//��ӡ���ָ��γ���Ԫ��
             }
        return e2;
    case '/':
            if(e1.sreg==0)    //������
             {
                 reg[e2.i]=reg[e2.i]/e1.s;//�����������浽Ŀ��Ĵ�����
                 cout<<"DIV\treg"<<e2.i<<"\t"<<e1.s<<"\treg"<<e2.i<<"\n";//��ӡ���ָ��γ���Ԫ��
             }
             else   //�Ĵ���
             {
                 reg[e2.i]=reg[e2.i]/reg[e1.s];//�����������浽Ŀ��Ĵ�����
                 cout<<"DIV\treg"<<e2.i<<"\treg"<<e1.s<<"\treg"<<e2.i<<"\n";//��ӡ���ָ��γ���Ԫ��
             }
        return e2;
    default:
        cout<<"���������";
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
        E=e;    //E��ü̳е�����
        T=Term(T);  //T����ۺ�����
        E1.i=T.s;   //E1��ü̳�����
        E1.ireg=T.sreg;
        E1=Expr1(E1);
        E.s=E1.s;   //E����ۺ�����
        E.sreg=E1.sreg;
        if(E.sreg==0)   //Ϊֻ��һ�����ֵ�����ṩ
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
        T=Term(T);  //�ۺϵĽ��
        E1=code(addop,T,E1);    //���мӼ�����
        E2.i=E1.i;  //�̳�
        E2.ireg=E1.ireg;
        E2=Expr1(E2);
        E1.s=E2.s;  //�ۺ�
        E1.sreg=E2.sreg;
        return E1;
    }
    else if(str[f1]==')'||str[f1]==';'){    //E1->��  match Follow set
        ele E1=e;
        E1.s=E1.i;  //�ۺϵõ�����ļ̳�����
        E1.sreg=E1.ireg;
        return E1;
    }
    else{     //error
        cout<<"�������ʽ��ʽ����";
        error();

    }
}

ele Term(ele e){
    ele T,F,T1;
    T=e;

    F=Factor(F);
    T1.i=F.s;   //�̳������ֵܵ�����
    T1.ireg=F.sreg;
    T1=Term1(T1);
    T.s=T1.s;   //�ۺ�
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
        T1=code(mulop,F,T1);    //���г˳�����
        T2.i=T1.i;  //�̳�
        T2.ireg=T1.ireg;
        T2=Term1(T2);
        T1.s=T2.s;  //�ۺ�
        T1.sreg=T2.sreg;
        return T1;
    }
    else if(AddOp(str[f1])
            ||str[f1]==')'||str[f1]==';'){  //T1->��  match Follow set
                ele T1=e;
                T1.s=T1.i;//�ۺϵõ�����ļ̳�����
                T1.sreg=T1.ireg;
                return T1;     //match follow set
    }
    else{     //error
        cout<<"�������ʽ��ʽ����";
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
            F.sreg=1;     //�ۺϵ�Ϊһ���Ĵ���
            return F;
        }
        else
        {
            cout<<"����δ��ǰ���壡";
            error();
        }
    }
    else if(b==2)       //number
    {
        char num =str[f1];
        ++f1;       //match(number)
        ele F=e;
        F.s= num-'0';
        F.sreg=0;      //�ۺϵ�Ϊһ��������
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
            cout<<"�������ʽ��ʽ����(���Ų�����)";
            error();
        }
        return F;
    }
    else{     //Error
       cout<<"�������ʽ��ʽ����";
       error();

    }
}



void Input()
{
    for(int i=0;i<130;i++)  //��ʼ��ID����
        ID[i]=-1;
    cout<<"Input some IDs you will use later (a,2)(input # in ID to end this process):\n";
    char id;    //����id������
    int val;    //id�洢����ֵ
    while(1)
    {
        cout<<"input a new ID(# to end)\n";
        cin>>id;
        if(id=='#') //�˳�ѭ��������
            break;
        cout<<"input above ID's value\n";
        cin>>val;
        reg[r]=val; //�����ݴ���Ĵ���
        ID[int(id)]=r;  //��¼��id���Ӧ�ļĴ���
        r++;
    }
    rid=r-1;    //��¼�洢��id���ݵļĴ���
    cout<<"\nInput your arithmetic expression:(end with ;)\n";
    cin>>str;
}
void Output()
{
    ele e;
    cout<<"CMD\tA1/Resl\tA2\tResl\n";
    e=Expr(e);
    cout<<"\nFinal result:"<<reg[e.s]<<"\n";    //��ʾ�������ʽ���Ľ��

    cout<<"\nPrint all used Regs:\n";
    for(int i=0;i<r;i++)    //��ӡ�������֮�����еļĴ�����������
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
