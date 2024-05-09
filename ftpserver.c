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
  int serv_sockfd,portno,client,newsockfd,n;
  char command[10]={0},filename[10]={0},buffer[1024]={0};
  portno=atoi(argv[1]);
  struct sockaddr_in serv_addr,client_addr;
  serv_sockfd=socket(AF_INET,SOCK_STREAM,0);
  if(serv_sockfd<0)
    printf("error");
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_port=htons(portno);
  serv_addr.sin_addr.s_addr=INADDR_ANY;
  bind(serv_sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
  listen(serv_sockfd,5);
  client=sizeof(client_addr);
  newsockfd=accept(serv_sockfd,(struct sockaddr *) &client_addr,&client);
  n=read(newsockfd,command,sizeof(command));
  if(n<0)
    printf("error");
  n=read(newsockfd,filename,sizeof(filename));
  if(n<0)
    printf("error");
   FILE *fp;
   if(!strcmp(command,"get"))
   {
     fp=fopen(filename,"r");
     fgets(buffer,sizeof(buffer),fp);
     n=write(newsockfd,buffer,1023);
     if(n<0)
      printf("error");
     fclose(fp);
    }
    else if(!strcmp(command,"put"))
    {
      fp=fopen("newFilePut1.txt","w");
      n=read(newsockfd,buffer,1023);
      if(n<0)
       printf("error");
      fprintf(fp,"%s",buffer);
      fclose(fp);
     }
     else
     {
       printf("wrong command...!");
       exit(0);
     }
}
