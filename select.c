#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stropts.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>
/*
#include <sys/filio.h>
*/
int main(){
        int serversockd;
        int length = sizeof(struct sockaddr_in);       
        serversockd = socket(AF_INET,SOCK_STREAM,0);
        if(serversockd < 0){
                printf("Create socket unsuccessfully\n");
                return 0;
        }
        struct sockaddr_in myaddr;
        myaddr.sin_family = AF_INET;
        myaddr.sin_port = htons(8000);
        myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        bzero(&(myaddr.sin_zero),sizeof(struct sockaddr));
        if(bind(serversockd,(struct sockaddr*)&myaddr,sizeof(struct sockaddr)) < 0){
                printf("Bind unsuccessfully\n");
                return 0;
        }
        if(listen(serversockd,10)<0){
                printf("Listen unsuccessfully\n");
                return 0;
        }
        struct sockaddr_in otheraddr;
        int clientsockd, result;
       
        fd_set testfds;
        int maxfds,fd,readflag;
        fd_set rwfds;
        FD_ZERO(&rwfds);
        maxfds = serversockd;  
        FD_SET(serversockd, &rwfds);
        while(1){
                testfds = rwfds;
                result = select(maxfds+1,&testfds,NULL,NULL,NULL);
                if(result < 1){
                        printf("Select unsuccessfully\n");
                        break;
                }
                for(fd=0; fd < FD_SETSIZE; fd++){
                        if(FD_ISSET(fd,&testfds)){
                                if(fd == serversockd){
                                        clientsockd = accept(serversockd,(struct sockaddr*)&otheraddr,&length);
                                        if(clientsockd > 0){
                                                if(clientsockd > maxfds){
                                                        maxfds = clientsockd;
                                                }
                                                FD_SET(clientsockd,&rwfds);
                                                printf("The incoming socket address is %s:%d \n", inet_ntoa(otheraddr.sin_addr),
                                                                                                  ntohs(otheraddr.sin_port));  
                                        }
                                }
                                else{
                                        ioctl(fd,FIONREAD,&readflag);
                                        if(readflag == 0){
                                                close(fd);
                                                FD_CLR(fd,&rwfds);
                                        }
                                        else{
                                                char buffer[254]= "hello,world\n";
                                                //{0};
                                                while(read(fd, buffer, 254)!=0)
                                                {
                                                    write(clientsockd, buffer, strlen(buffer));
                                                    printf("The receive buffer is %s\n",buffer);    
                                                };
                                                shutdown(clientsockd);
                                                
                                                //
                                                //close(clientsockd);
                                                //close(clientsockd);
                                                
                                        }
                                }
                        }
                }
        }
        for(fd = 0; fd < FD_SETSIZE; fd++){
                close(fd);
                FD_CLR(fd,&rwfds);     
        }      
        return 1;
}