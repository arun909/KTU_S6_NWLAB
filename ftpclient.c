#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int main(int argc,char * argv[])
{
  char command[10]={0},filename[10]={0},buffer[1024]={0};
  int sockfd,portno,n;
  portno=atoi(argv[1]);
  struct sockaddr_in serv_addr;
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_port=htons(portno);
  serv_addr.sin_addr.s_addr=INADDR_ANY;
  printf("enter command:");
  scanf("%s",command);
  printf("enter file name:");
  scanf("%s",filename);
  connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
  n=write(sockfd,command,sizeof(command));
  if(n<0)
    printf("error");
  n=write(sockfd,filename,sizeof(filename));
  if(n<0)
    printf("error");
   FILE *fp;
   if(!strcmp(command,"get"))
   {
     fp=fopen("newFileGet1.txt","w");
     n=read(sockfd,buffer,1023);
     if(n<0)
       printf("error");
     fprintf(fp,"%s",buffer);;
     fclose(fp);
    }
    else if(!strcmp(command,"put"))
    {
      fp=fopen(filename,"r");
      fgets(buffer,sizeof(buffer),fp);
      n=write(sockfd,buffer,1023);
      if(n<0)
      printf("error");
      fclose(fp);
    }
    else
    {
      printf("wrong command...!");
    }
}
  
