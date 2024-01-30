#include<bits/stdc++.h>
using namespace std;

bool check(char c);
int Expr();
int Expr1(int p);
int Term();
int Term1(int p);
int Factor();
bool AddOp(char c);
bool MulOp(char c);
void Input();
void Output();
void bfs(int p);


const int maxlen=1000;
char str[maxlen];
int f1,f2,len;  //f1: position of the char in input; f2: position of the node of tree; len: length of input

struct node
{
    char c;      //operate
    int pl,pr;   //child's point
    node(char tchar='0',int pleft=-1,int pright=-1)
        {
            c=tchar;pl=pleft;pr=pright;
        }
}nd[maxlen];

//judge if the char is legal
bool check(char c)
{
    if((c>='0'&&c<='9')||(c>='a'&&c<='z')
       ||(c>='A'&&c<='Z')||(c=='_'))
        return true;
    else
        return false;
}

int Expr()
{
        int p=Term();
        if(p==-1)   //error
            return p;
        return Expr1(p);
}

bool AddOp(char c)
{
    if(c=='+'||c=='-')
        return true;
    else
        return false;
}

int Expr1(int p)
{
    if(AddOp(str[f1])){     //match('+','-')
        char ch=str[f1];
        ++f1;
        int p1=Term();
        if(p1==-1)
            return p1;   //error
        int p2=++f2;
        nd[p2]=node(ch,p,p1);   //create node
        return Expr1(p2);
    }
    else if(str[f1]==')'||str[f1]==';'){
        return p;             //match Follow set
    }
    else{     //error
        return -1;
    }
}

int Term(){
        int p=Factor();
        if(p==-1)
            return p;   //error
        return Term1(p);
}

bool MulOp(char c)
{
    if(c=='*'||c=='/')
        return true;
    else
        return false;
}

int Term1(int p){
    if(MulOp(str[f1]))
        {
        char ch=str[f1];
        ++f1;               //match('*','/')
        int p1=Factor();
        if(p1==-1)
        return p1;      //error
        int p2=++f2;        //create node
        nd[p2]=node(ch,p,p1);
        return Term1(p2);
    }
    else if(AddOp(str[f1])
            ||str[f1]==')'||str[f1]==';'){
                return p;     //match follow set
    }
    else{     //error
        return -1;
    }
}

int Factor(){
    if(check(str[f1])){
        int p=++f2;
        nd[p]=node(str[f1]); //create leaf node
         ++f1;             //match(id or number)
        return p;
    }
    else if(str[f1]=='('){
        ++f1;             //match '('
        int p=Expr();
        if(p==-1)
            return p; //error
        if(str[f1]==')'){ //match(')')
            ++f1;
            return p;
        }
        else{ //error
            return -1;
        }
    }
    else{     //Error
        return -1;
    }
}

//层序遍历
void Print_BFS(int p){
     const int axlen=24;
    queue<int> q0; //节点位置
    queue<int> q1;  //行数
    q0.push(p);
    q1.push(1);
    queue<int> q2;
    q2.push(int(axlen/2));
    char axes[axlen][axlen];
    for (int i=0;i<axlen;i++)
        for(int j=0;j<axlen;j++)
            axes[i][j]=' ';
    while(!q0.empty()){        //队列为空时结束遍历
        int pp=q0.front();
        int row=q1.front();
        q0.pop();q1.pop();
        int col=q2.front();
        q2.pop();
        while(axes[row][col]!=' ')
            ++col;
            axes[row][col]=nd[pp].c;
        if(nd[pp].pl!=-1){      //如果该节点不是叶子节点，则将其左右孩子添加进队列
            q0.push(nd[pp].pl);q1.push(row+1);
            q0.push(nd[pp].pr);q1.push(row+1);
            q2.push(col-2);
            q2.push(col+2);
        }
    }
    for (int i=0;i<axlen;i++)
        {
            for(int j=0;j<axlen;j++)
            cout<<axes[i][j];
            cout<<"\n";
            }
}

void Input()
{
    f1=f2=0;
    cout<<"Input your arithmetic expression:(end with ;)\n";
    cin>>str;
}

void Output(int p){
    if(p==-1){
        printf("Error\n");
    }
    else{
        Print_BFS(p);
    }
}

int main()
{
    Input();
    int p=Expr();
    Output(p);
    return 0;
}
