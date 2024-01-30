#include <iostream>
#include<String.h>
using namespace std;

int main()
{
 FILE *p;
 int  flag = 0,i=0,j=0;
 char str[1000],str1[1000],c;
 if((p=fopen("3\\input.txt","rt"))==NULL){
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
 i=0;
 int line=1;//line=1:/* */in the same line
for(i=0;i<strlen(str);i++){
if(flag==0){
   if(str[i]!='/')
   {
       str1[j]=str[i];
       j++;
   }
   else
   {
     if (str[i+1]=='/')
        flag=1;
     else if (str[i+1]=='*')
        flag=2;
     else
     {
         str1[j]=str[i];
         j++;
     }
   }
}
else if (flag==1)
{
    if (str[i]=='\n')
        {
            flag=0;
            str1[j]='\n';
            j++;
        }
}
else
{
   if(str[i]=='/'&&str[i-1]=='*')
        {
        flag=0;
        if(line==0)//not in the same line
        {
           if(str[i+1]!='\n')
           {
               str1[j]='\n';
                j++;
           }
        }
        }
        else if(str[i]=='\n')
        {
            line=0;
        }
}

}
if (flag==2)
    {
        str1[j++]='\n';
        str1[j++]='e';
        str1[j++]='r';
        str1[j++]='r';
        str1[j++]='o';
        str1[j++]='r';
    }
str1[j]='\0';
cout<<str1;

}
