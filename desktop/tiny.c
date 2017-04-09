/* 
 * Original source code: https://github.com/ankushagarwal/nweb
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tiny.h"
#define VERSION 23
#define BUFSIZE 8096
#define ERROR      42
#define LOG        44
#define FORBIDDEN 403
#define NOTFOUND  404

#ifndef SIGCLD
#   define SIGCLD SIGCHLD
#endif

struct {
    char *ext;
    char *filetype;
} extensions [] = {
    {"gif", "image/gif" },
    {"jpg", "image/jpg" },
    {"jpeg","image/jpeg"},
    {"png", "image/png" },
    {"ico", "image/ico" },
    {"zip", "image/zip" },
    {"gz",  "image/gz"  },
    {"tar", "image/tar" },
    {"htm", "text/html" },
    {"html","text/html" },
    {"css","text/css" },
    
    {"xml","application/octet-stream" },
    {"js","text/javascript" },
    {0,0} };
const char* genericMimetype= "application/octet-stream";

void logger(int type, char *s1, char *s2, int socket_fd)
{
    int fd ;
    char logbuffer[BUFSIZE*2];
    
    switch (type) {
        case ERROR: (void)sprintf(logbuffer,"ERROR: %s:%s Errno=%d exiting pid=%d",s1, s2, errno,getpid());
            break;
        case FORBIDDEN:
            (void)write(socket_fd, "HTTP/1.1 403 Forbidden\nContent-Length: 185\nConnection: close\nContent-Type: text/html\n\n<html><head>\n<title>403 Forbidden</title>\n</head><body>\n<h1>Forbidden</h1>\nThe requested URL, file type or operation is not allowed on this simple static file webserver.\n</body></html>\n",271);
            (void)sprintf(logbuffer,"FORBIDDEN: %s:%s",s1, s2);
            break;
        case NOTFOUND:
            (void)write(socket_fd, "HTTP/1.1 404 Not Found\nContent-Length: 136\nConnection: close\nContent-Type: text/html\n\n<html><head>\n<title>404 Not Found</title>\n</head><body>\n<h1>Not Found</h1>\nThe requested URL was not found on this server.\n</body></html>\n",224);
            (void)sprintf(logbuffer,"NOT FOUND: %s:%s",s1, s2);
            break;
       // case LOG: (void)sprintf(logbuffer," INFO: %s:%s:%d",s1, s2,socket_fd); break;
    }
    /* No checks here, nothing can be done with a failure anyway */
    if((fd = open("nweb.log", O_CREAT| O_WRONLY | O_APPEND,0644)) >= 0) {
        (void)write(fd,logbuffer,strlen(logbuffer));
        (void)write(fd,"\n",1);
        (void)close(fd);
    }
    if(type == ERROR || type == NOTFOUND || type == FORBIDDEN) exit(3);
}

/* this is a child web server process, so we can exit on errors */
void web(int fd, int hit)
{
    int j, file_fd, buflen;
    long i, ret, len;
    char * fstr;
    static char buffer[BUFSIZE+1]; /* static so zero filled */
    
    ret =read(fd,buffer,BUFSIZE);   /* read Web request in one go */
    if(ret == 0 || ret == -1) {  /* read failure stop now */
        logger(FORBIDDEN,"failed to read browser request","",fd);
    }
    if(ret > 0 && ret < BUFSIZE)  /* return code is valid chars */
        buffer[ret]=0;    /* terminate the buffer */
    else buffer[0]=0;
    for(i=0;i<ret;i++)  /* remove CF and LF characters */
        if(buffer[i] == '\r' || buffer[i] == '\n')
            buffer[i]='*';
    logger(LOG,"request",buffer,hit);
    if( strncmp(buffer,"GET ",4) && strncmp(buffer,"get ",4) ) {
        logger(FORBIDDEN,"Only simple GET operation supported",buffer,fd);
    }
    for(i=4;i<BUFSIZE;i++) { /* null terminate after the second space to ignore extra stuff */
        if(buffer[i] == ' ') { /* string is "GET URL " +lots of other stuff */
            buffer[i] = 0;
            break;
        }
    }
    for(j=0;j<i-1;j++)   /* check for illegal parent directory use .. */
        if(buffer[j] == '.' && buffer[j+1] == '.') {
            logger(FORBIDDEN,"Parent directory (..) path names not supported",buffer,fd);
        }
    if( !strncmp(&buffer[0],"GET /\0",6) || !strncmp(&buffer[0],"get /\0",6) ) /* convert no filename to index file */
        (void)strcpy(buffer,"GET /index.html");
    
    /* work out the file type and check we support it */
    buflen=strlen(buffer);
    
    
    
    // Disabled original code to support any file extension
    fstr = genericMimetype;
    /*fstr = (char *)0;
    for(i=0;extensions[i].ext != 0;i++) {
        len = strlen(extensions[i].ext);
        if( !strncmp(&buffer[buflen-len], extensions[i].ext, len)) {
            fstr =extensions[i].filetype;
            break;
        }
    }
    if(fstr == 0) logger(FORBIDDEN,"file extension type not supported",buffer,fd);
    */
    
    if(( file_fd = open(&buffer[5],O_RDONLY)) == -1) {  /* open the file for reading */
        logger(NOTFOUND, "failed to open file",&buffer[5],fd);
    }
    logger(LOG,"SEND",&buffer[5],hit);
    len = (long)lseek(file_fd, (off_t)0, SEEK_END); /* lseek to the file end to find the length */
    (void)lseek(file_fd, (off_t)0, SEEK_SET); /* lseek back to the file start ready for reading */
    (void)sprintf(buffer,"HTTP/1.1 200 OK\nServer: nweb/%d.0\nContent-Length: %ld\nConnection: close\nContent-Type: %s\n\n", VERSION, len, fstr); /* Header + a blank line */
    logger(LOG,"Header",buffer,hit);
    (void)write(fd,buffer,strlen(buffer));
    
    /* send file in 8KB block - last block may be smaller */
    while (  (ret = read(file_fd, buffer, BUFSIZE)) > 0 ) {
        (void)write(fd,buffer,ret);
    }
    sleep(1);  /* allow socket to drain before signalling the socket is closed */
    close(fd);
    exit(1);
}



int serveFiles(char* dir, int port)
{
    int i, pid, listenfd, socketfd, hit;
    socklen_t length;
    static struct sockaddr_in cli_addr; // static = initialised to zeros
    static struct sockaddr_in serv_addr; // static = initialised to zeros
    
    if( !strncmp(dir,"/"   ,2 ) || !strncmp(dir,"/etc", 5 ) ||
       !strncmp(dir,"/bin",5 ) || !strncmp(dir,"/lib", 5 ) ||
       !strncmp(dir,"/tmp",5 ) || !strncmp(dir,"/usr", 5 ) ||
       !strncmp(dir,"/dev",5 ) || !strncmp(dir,"/sbin",6) ){
        (void)printf("ERROR: Bad top directory %s, see nweb -?\n",dir);
        exit(3);
    }
    if(chdir(dir) == -1){
        (void)printf("ERROR: Can't Change to directory %s\n",dir);
        exit(4);
    }
    // Become deamon + unstopable and no zombies children (= no wait())
    if(fork() != 0)
        return 0; // parent returns OK to shell
    
    (void)signal(SIGCLD, SIG_IGN); // ignore child death
    (void)signal(SIGHUP, SIG_IGN); // ignore terminal hangups
    //for(i=0;i<32;i++)
//        (void)close(i);    // close open files
    (void)setpgrp();    // break away from process group
    
    logger(LOG,"nweb starting", port, getpid());
    
    // setup the network socket
    if((listenfd = socket(AF_INET, SOCK_STREAM,0)) <0)
        logger(ERROR, "system call","socket",0);
    
    if(port < 0 || port >60000)
        logger(ERROR,"Invalid port number (try 1->60000)",port,0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);
    if(bind(listenfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) <0)
        logger(ERROR,"system call","bind",0);
    if( listen(listenfd,64) <0)
        logger(ERROR,"system call","listen",0);
    for(hit=1; ;hit++) {
        length = sizeof(cli_addr);
        if((socketfd = accept(listenfd, (struct sockaddr *)&cli_addr, &length)) < 0)
            logger(ERROR,"system call","accept",0);
        if((pid = fork()) < 0) {
            logger(ERROR,"system call","fork",0);
        }
        else {
            if(pid == 0) {   // child
                (void)close(listenfd);
                web(socketfd,hit); // never returns
            } else {   // parent
                (void)close(socketfd);
            }
        }
    }
}
