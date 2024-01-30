#include <iostream>
#include<String.h>
using namespace std;

string keywords[4]={"struct","int","return","char"};

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
void find_id(char *str)
{
    int  flag = 0,i=0,j=0;
    char str1[15];
j=0;
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
                cout<<str1<<"\n";
            }

            i--;// avoid " to bring trouble
        }
    }
    else
    {
        if(str[i]=='"'&&str[i-1]!='\\')
        {
            flag=0;
        }
    }
}
}

int main()
{
 FILE *p;
 int  flag = 0,i=0,j=0;
 char str[1000],c;
 if((p=fopen("1\\input.txt","rt"))==NULL){
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

find_id(str);



}
