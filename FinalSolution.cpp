/* run using ./server <port> */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>
#include "http_server.cpp"
#include <pthread.h>
#include<bits/stdc++.h>
#define deadpool 30

queue<int *> client_q;
pthread_t thread_pool[deadpool];
pthread_mutex_t Mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;

int done = 0;


void error(char *msg) {
  perror(msg);
  exit(1);
}


void *handle_connection(void *args)
{
  int *socket = (int *)args;
  int newsockfd = *socket; // converting args to int
  int n;
  char buffer[8056];
  string req;
  n = read(newsockfd,buffer,8055);
  req = buffer;
  string ans;
  HTTP_Response *obj = handle_request(req.c_str());
  n = write(newsockfd,obj->get_string().c_str(),obj->get_string().length());
  
  pthread_exit(NULL);

}


void * thread_function(void *args)
{
  while(true)
  {
    int *pclient;
    pthread_mutex_lock(&Mutex); // first we lock the mutex 
    /*if((pclient = dequeue() )== NULL) // doing two things at a time, first is queue empty, and also if not empty then returnig the value to variable pclient.
        pthread_cond_wait(&condition_var,&Mutex);*/
      while(client_q.empty())
        pthread_cond_wait(&condition_var,&Mutex); // checking if q is empty, in that case, it should wait.. checking it in while loop so that multiple threads should not cause any problems


    pclient = client_q.front();  // pclient gets new client socketfd

        
    pthread_mutex_unlock(&Mutex); // now we unlock the Mutex
    if(pclient != NULL)   // checking just once more just to be sure
    {
      handle_connection(pclient);
    }
  }
}
int main(int argc, char *argv[]) 
{
  int sockfd, newsockfd, portno;
  socklen_t clilen;
  //char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  int n;

  if (argc < 2) {
    fprintf(stderr, "ERROR, no port provided\n");
    exit(1);
  }

  for(int i = 0;i<deadpool;i++)
  {
    pthread_create(&thread_pool[i],NULL,thread_function,NULL);
  }

  /* create socket */

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error("ERROR opening socket");

  /* fill in port number to listen on. IP address can be anything (INADDR_ANY)
   */

  bzero((char *)&serv_addr, sizeof(serv_addr));
  portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);



  /* bind socket to this port number on this machine */

  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR on binding");

  /* listen for incoming connection requests */

  listen(sockfd, 5);
  clilen = sizeof(cli_addr);

  while(1)
  {
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0)
      error("ERROR on accept");
    pthread_mutex_lock(&Mutex);// locking with a mutex 
    client_q.push(&newsockfd);
    pthread_cond_signal(&condition_var); // signalling the condition variable
    pthread_mutex_unlock(&Mutex); // now unlocking
  }
}


