
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Server.h"

using namespace std;

Server::Server(int port)throw (const char*) {
    //fd = socket id
    fd = socket(AF_INET,SOCK_STREAM,0);
    //check socket function worked
    if (fd < 0){
        throw "socket failed";
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    //check binding the socket with port works.
    if(bind(fd,(struct sockaddr*)&server, sizeof(server)) < 0) {
        throw "bind failure";
    }

    //check the sever can listen
    if(listen(fd, 3) < 0) {
        throw "listen failure";
    }
}

void Server::start(ClientHandler& ch)throw(const char*){
    t = new thread([&ch, this] (){
        cout<<"waiting for a client"<<endl;
        socklen_t clientSize = sizeof(client);
        int aClient = accept(fd, (struct sockaddr*)&client, &clientSize);
        //check accept worked
        if(aClient < 0) {
            throw "accept failure";
        }
        cout <<"client connected!"<<endl;
        ch.handle(aClient);
        close(aClient);
        close(fd);
    })
}

void Server::stop(){
	t->join(); // do not delete this!
}

Server::~Server() {
}

