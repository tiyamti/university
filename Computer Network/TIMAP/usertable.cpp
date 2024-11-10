#include "usertable.h"
#include "commandss.h"
#include "commandr.h"
#include "commandp.h"
#include "commandsp.h"
#include "commandsn.h"
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
usertable::usertable(QObject *parent)
    : QObject{parent}
{

}
void usertable::menu(){
    commandsS sS;
    commandr r;
    commandp p;
    commandsn sn;
    commandsp sp;
    QList<int> ports;
    qDebug()<<"tmp>";
    string command;

    do{
        getline(cin, command);
        istringstream iss(command);
        vector<string> tokens;
        string token;

        while (iss >> token) {
            tokens.push_back(token);
        }
        for (size_t i = 0; i < tokens.size(); ++i) {
            if (tokens[i] == "-h") {
                if (i + 1 < tokens.size()) {
                    cout << "Error: IP Address should not be provided after -h" << endl;
                } else {
                    std::cout << "\033[1;32m";
                    std::cout << R"(
        The following commands are available:
        - -h: Displays help information about the tool.
        - -sS: Shows the online status of a host.
        - -r: Tests all ports of a specified IP address to determine whether they are open or closed.
        - -p: Tests selected ports. After using this command, specify the ports as numbers, followed by the IP address.
        - -sp: Selects the type of HTTP request to be used.
          - -sp --get: Chooses the GET request type, requiring you to specify the ID.
          - -sp --post: Chooses the POST request type, also requiring you to specify the ID.
        Use these commands to effectively manage your networking tasks!
        - -sN: trace ping of IP, U can send hole part of IP xxx.xxx.xxx.xxx or xxx.xxx.xxx. if you send like that it trace of all ranges of xxx.xxx.xxx.1 to 254
    )" << std::endl;
                    std::cout << "\033[0m";
                }
            }
            if (tokens[i] == "-r") {
                if (i + 1 < tokens.size()) {
                    r.scanPorts(QString::fromStdString(tokens[i+1]));
                } else {
                    cout << "No IP Address provided after -r" << endl;
                }
            }
            if (tokens[i] == "-sS") {
                if (i + 1 < tokens.size()) {
                    if(i+2<tokens.size()){
                        sS.statechecker(QString::fromStdString(tokens[i + 1]), stoi(tokens[i + 2]));
                    }
                    else{
                        sS.statechecker(QString::fromStdString(tokens[i + 1]), 0);
                    }
                } else {
                    cout << "No IP Address provided after -sS" << endl;
                }
            }
            if (tokens[i] == "-p") {
                if (i + 1 < tokens.size()) {
                    for (size_t j = i+2; j < tokens.size(); ++j){
                        ports.append( stoi(tokens[j]));
                    }
                    p.scanPorts(QString::fromStdString(tokens[i + 1]),ports);
                } else {
                    cout << "No IP Address provided after -p" << endl;
                }
            }
            if (tokens[i] == "-sN") {
                if (i + 1 < tokens.size()) {
                    sn.scanSingleIP(QString::fromStdString(tokens[i+1]));
                } else {
                    cout << "No IP Address provided after -r" << endl;
                }
            }
            if (tokens[i] == "-sP") {
                if (i + 1 < tokens.size()) {
                    if(tokens[i+1]=="GET"){
                        sp.formRequest(QString::fromStdString(tokens[i+1]),QString::fromStdString(tokens[i+2]));
                    }
                    if(tokens[i+1]=="POST"){
                    sp.formRequest(QString::fromStdString(tokens[i+1]),QString::fromStdString(tokens[i+2]),QString::fromStdString(tokens[i+3]));
                    }
                } else {
                    cout << "No command provided after -sP" << endl;
                }
            }

        }
    }while(command != "exit");
}
