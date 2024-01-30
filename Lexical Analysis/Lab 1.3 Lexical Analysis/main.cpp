#include <iostream>
#include<String.h>
using namespace std;
struct Id
{
    int index=-1;
    string Name="NULL";
    string OtherAttr;
    Id *Next=NULL;
};



string keywords[4]={"struct","int","return","char"};
char operation[5]={'+','-','*','/','='};

int is_number(char c)
{
    if(c<='9'&&c>='0')
        return 1;
    return 0;
}

int is_operation(char c)
{
    int i;
    for(i=0;i<5;i++)
    {
        if(c==operation[i])
            return 1;
    }
            return 0;
}

int find_id_index(Id *head,string s)
{
    while (head!=NULL)
    {
        if(head->Name==s)
            return head->index;
        head=head->Next;
    }
    return -1;
}

int is_id(Id *head,string s)
{
    while (head!=NULL)
    {
        if(head->Name==s)
            return 1;
        head=head->Next;
    }
    return 0;
}

int is_key(string s)
{
    int i;
    for (i=0;i<4;i++)
    {
        if(s==keywords[i])
            return 1;
    }
    return 0;
}

int is_letter(char c)
{
    if((c>='a'&& c<='z')||(c>='A'&&c<='Z')||(c=='_'))
        return 1;
    return 0;
}

int is_word(char c)
{
    if((c>='a'&& c<='z')||(c>='A'&&c<='Z')||(c=='_')||(c<='9'&&c>='0'))
        return 1;
    return 0;
}
Id find_id(char *str)
{
    int  flag = 0,i=0,j=0;
    char str1[15];
j=0;
Id *Oldid= new Id;
Id *head=Oldid;
int idcount=0;
for(i=0;i<strlen(str);i++)
{
    if(flag==0)
    {
        if(str[i]=='"')
        {
            flag=2;
        }

        if(is_letter(str[i]))
        {
            str1[j]=str[i];
            j++;
            flag=1;
        }
        if(is_number(str[i]))
        {
            str1[j]=str[i];
            j++;
            flag=3;
        }
    }
    else if(flag==1)
    {
        if(is_word(str[i]))
        {
           str1[j]=str[i];
            j++;
        }
        else
        {
            flag=0;
            str1[j]='\0';
            j=0;
            if(!is_key(str1))
            {
                if(!is_id(head,str1))
                {
                   Oldid->index=idcount;
                    idcount++;
                    Oldid->Name=str1;
                    Id *Newid= new Id;
                    Oldid->Next= Newid;
                    Oldid=Newid;
                    cout<<"(id,"<<find_id_index(head,str1)<<")\n";
                }
                else
                {
                    cout<<"(id,"<<find_id_index(head,str1)<<")\n";
                }

            }
            else
            {
                cout<<"("<<str1<<",keywords)\n";
            }

            i--;// avoid " to bring trouble
        }
    }
    else if (flag == 2)
    {
        if(str[i]=='"'&&str[i-1]!='\\')
        {
            flag=0;
        }
    }
    else if (flag == 3)
    {
        if(is_number(str[i]))
        {
            str1[j]=str[i];
            j++;
        }
        else
        {
            flag=0;
            str1[j]='\0';
            j=0;
            cout<<"(int,"<<str1<<")\n";
            //cout<<str1<<"\n";
        }
    }

    if(is_operation(str[i]))
    {
        cout<<'('<<str[i]<<",-)"<<"\n";
    }
}
return *head;
}
int main()
{
 FILE *p;
 int  flag = 0,i=0,j=0;
 char str[1000],str1[1000],c;
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

Id *head= new Id;
*head=find_id(str);
cout<<"\nID&index:\n";
Id *pid =new Id;
*pid= *head;
while(pid!=NULL)
{
    cout<<pid->Name<<" "<<pid->index<<"\n";
    pid=pid->Next;
}

}
