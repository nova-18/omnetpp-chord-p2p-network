#include <string.h>
#include <omnetpp.h>
#include <bits/stdc++.h>
#include "omnetpp/distrib.h"
#include <fstream>
#include <mutex>
#include <openssl/sha.h>
#include "message_m.h"
#include "config.h"
using namespace omnetpp;


std::ofstream logFile("logs.log", std::ios::app);
std::mutex logMutex;

// Thread-safe log function
void threadSafeLog(const std::string& msg) {
    std::lock_guard<std::mutex> lock(logMutex);

    // Get simulation time
    std::string simTimeStr = simTime().str();  // e.g., "1.234s"

    // Log with newline
    if (logFile.is_open()) {
        logFile << "[" << simTimeStr << "] " << msg << '\n';  // 👈 uses simTime
        logFile.flush(); // Optional
    } else {
        std::cerr << "Unable to write to log file!" << std::endl;
    }
}

std::string sha256( std::string& str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(str.c_str()), str.size(), hash);

    std::stringstream ss;
    for (unsigned char c : hash) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    }
    return ss.str();
}

class chordHashTable{
    private :
    int currNode;
    int tableSize;
    int MOD;
    std::vector<int>hashTable;

    public :

    void setTable(int thisNode, int ringSize){
        currNode = thisNode;
        MOD = ringSize;
        tableSize = 0;
        int temp = 1;
        while(temp < ringSize){
            temp *= 2;
            tableSize++;
        }
        for(int i = 0; i<tableSize;i++){
            int connection = (currNode + (1<<i))%MOD;
            hashTable.push_back(connection);
        }
    }

    std::pair<int,int> findRoute(int dest){
        for(int i = 0;i<tableSize-1;i++){
            int low = hashTable[i];
            int upp = hashTable[i+1];
            if(low < upp && low <= dest &&  dest < upp){
                return {i,low};
            }
            else if(low > upp && (low <= dest || dest < upp)){
                return {i,low};
            }
            else{
                continue;
            }
        }
        return {tableSize-1, hashTable[tableSize-1]};
    }

    std::vector<int>getNeighbours(){
        std::vector<int> out;
        for(auto val : hashTable){
            out.push_back(val);
        }
        return out;
    }

};

class taskManager{
    private :
    int tasknum;
    int subtaskCount;
    std::vector<int>task;
    std::vector<std::vector<int>>subtasks;
    std::unordered_map<int,int>subtaskResponses;
    int answer;

    public:

    void setManager(int tasknumber, int subtaskcounts, std::vector<int>&thisTask, std::vector<std::vector<int>>&subTaskDet){
        tasknum = tasknumber;
        subtaskCount = subtaskcounts ;
        task = thisTask;
        subtasks = subTaskDet; 
    }

    void updResp(int subtasknum, int ans){
        subtaskResponses[subtasknum] = ans;
    }

    int getSubtaskCount(){
        return subtaskCount;
    }

    int processTask(){
        int answer = subtaskResponses[0];

        for (auto &val : subtaskResponses){
            int recv = val.second;
            answer = std::max(answer,recv);
        }
        // for(auto val = subtaskResponses.begin();val!=subtaskResponses.end();val++){
        //     int recv = val->second;
        //     answer = max(answer,recv);
        // }
        return answer;
    }
};

class Client: public cSimpleModule
{

protected:
    int taskSent = 0;
    int taskCompleted = 0;
    int subtaskRespCount = 0;
    int gossipRecv = 0;
    chordHashTable navigation;
    std::unordered_map<int,taskManager>taskMap;
    std::unordered_map<std::string,std::string>messageList;
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void createAndSendTask(int taskno, int networkSize);
    virtual void processTask(int taskno);
    virtual void sendGossip(int taskno, int answer);
    virtual void processGossip(gossip * Msg);
    virtual void triggerNextTask();

private:
    cMessage *startTaskMsg = nullptr;
    std::vector<int> generateRandomArray(int arraySize, int lowerBound, int upperBound) {
        std::vector<int> randomArray(arraySize);
        for (int i = 0; i < arraySize; i++) {
            randomArray[i] = intuniform(lowerBound, upperBound);
        }
        return randomArray;
    }

    std::vector<std::vector<int>> divideArray(const std::vector<int>& arr, int n) {
        int arraySize = arr.size();
        int baseSize = arraySize / n;
        int remainder = arraySize % n;
    
        std::vector<std::vector<int>> subarrays(n);
        int index = 0;
    
        for (int i = 0; i < n; i++) {
            int currentSize = baseSize + (i < remainder ? 1 : 0);
            subarrays[i].resize(currentSize);
    
            for (int j = 0; j < currentSize; j++) {
                subarrays[i][j] = arr[index++];
            }
        }
        return subarrays;
    }

    int getMax(std::vector<int>&task_arr){
        int maxi = task_arr[0];
        for (int  i = 0; i< task_arr.size();i++){
            int num = task_arr[i];
            maxi = std::max(maxi,num);
        }
        return maxi;
    }

    int getthisNode(){
        std::string moduleName(getName());
        int moduleId = -1;

        if (moduleName.length() > 1 && moduleName[0] == 'c') {
            moduleId = std::stoi(moduleName.substr(1));  // Convert substring to int
        }
        return moduleId;
    }
};

Define_Module(Client);

void::Client::triggerNextTask(){
    if(taskSent < Total_Task_Count){
        int networkSize  = getParentModule()->par("numClients").intValue();
        createAndSendTask(taskSent+1,networkSize);
    }
}

void Client::createAndSendTask(int taskno, int networkSize)
{
    int subtaskCount = intuniform(networkSize+1, networkSize * 2);
    int taskSize = intuniform(2*subtaskCount, 5*subtaskCount);
    std::vector<int>task = generateRandomArray(taskSize, 0, 1e5);
    std::vector<std::vector<int>>subtasks = divideArray(task,subtaskCount);

    taskManager tm;
    tm.setManager(taskno,subtaskCount,task,subtasks);
    taskMap[taskno] = tm;
    std::ostringstream os2;
    os2<<getName()<<" : Task Created : No. : "<< taskno<<" Length : "<<taskSize;
    threadSafeLog(os2.str());
    EV<<getName()<<" : Task Created : No. : "<< taskno<<" Length : "<<taskSize<<endl;
    
    std::ostringstream os1;
    os1<<"Task :";
    EV<<" Task : ";
    for(auto val : task){
        EV<<val<<" ";
        os1<<val<<" ";
    }EV<<endl;
    threadSafeLog(os1.str());


    for(int subtaskNum = 0; subtaskNum<subtaskCount;subtaskNum++){
        int source = getthisNode();
        int destination = subtaskNum % networkSize;
        std::pair<int,int> routing = navigation.findRoute(destination);
        int routingDest = routing.second;
        int routingPort = routing.first;
        // std::vector<int>thisSubtask = subtasks[subtaskNum];
        int subtasklen = subtasks[subtaskNum].size();

        subtask * sub = new subtask("subtask");
        sub->setSourceId(source);
        sub->setDestId(destination);
        sub->setQueryLen(subtasklen);
        sub->setQueryArraySize(subtasklen);
        for(int i = 0;i<subtasklen;i++){
            sub->setQuery(i,subtasks[subtaskNum][i]);
        }
        sub->setTaskNum(taskno);
        sub->setSubTaskNum(subtaskNum);
        sub->setTimestamp(simTime());

        send(sub,"out",routingPort);
        EV<<getName()<<" : SubTask "<<subtaskNum<<" sent "<< " from : "<< source<<" to : "<< destination<< " routed to : "<<routingDest<<endl;
        std::ostringstream oss;
        oss<<getName()<<" : SubTask "<<subtaskNum<<" sent "<< " from : "<< source<<" to : "<< destination<< " routed to : "<<routingDest<<endl;
        threadSafeLog(oss.str());
    }
    taskSent++;
}

void Client::processTask(int taskno)
{
    int taskAns = taskMap[taskno].processTask();
    EV<<getName()<<" : Task Solved : Task Num : "<<taskno<<" Answer :"<<taskAns<<endl;
    std::ostringstream oss;
    oss<<getName()<<" : Task Solved : Task Num : "<<taskno<<" Answer :"<<taskAns<<endl;
    threadSafeLog(oss.str());
    taskCompleted++;
    sendGossip(taskno,taskAns);
    subtaskRespCount =  0;
    

}

void Client::sendGossip(int taskno, int ans){
    // int networkSize  = getParentModule()->par("numClients").intValue();
    std::vector<int>dests = navigation.getNeighbours();
    for(int index = 0; index <dests.size() ;index++){
        gossip * g = new gossip("gossip");
        int thisClient = getthisNode();
        int destination = dests[index];
        int routing = index;
        // std::pair<int,int>p = navigation.findRoute(destination);
        std::string GOSSIP = "";
        GOSSIP += simTime().str() + ":"+std::string(getName())+":"+std::to_string(taskno)+":"+std::to_string(ans);
        g->setSourceId(thisClient);
        g->setDestId(destination);
        g->setTaskNum(taskno);
        g->setTaskResult(ans);
        g->setGossipMsg(GOSSIP.c_str());
        g->setTimestamp(simTime());
        send(g,"out",routing);
        EV<<getName()<<" : Gossip Sent From : "<<thisClient<<" : to : "<<destination<<endl;
        std::ostringstream oss;
        oss<<getName()<<" : Gossip Sent From : "<<thisClient<<" : to : "<<destination<<endl;
        threadSafeLog(oss.str());
    }   
}

void Client::processGossip(gossip * Msg){
    int source = Msg->getSourceId();
    std::string GOSSIP = std::string(Msg->getGossipMsg());
    std::string hash = sha256(GOSSIP);

    if(messageList.count(hash) != 1){
        EV<<getName()<<" : Gossip recv from : "<<source<<" Gossip = "<<GOSSIP<<endl;
        std::ostringstream oss;
        oss<<getName()<<" : Gossip recv from : "<<source<<" Gossip = "<<GOSSIP<<endl;
        threadSafeLog(oss.str());
        gossipRecv++;
        messageList[hash] = GOSSIP;
        std::vector<int>dests = navigation.getNeighbours();
        for(int index = 0; index <dests.size() ;index++){
            if(dests[index] == source) continue;
            gossip * g = new gossip("gossip");
            // g = Msg;
            // int thisClient = getthisNode();
            int destination = dests[index];
            int routing = index;
            // // std::pair<int,int>p = navigation.findRoute(destination);
            // std::string GOSSIP = "";
            // GOSSIP += simTime().str() + ":"+std::string(getName())+std::to_string(taskno)+":"+std::to_string(ans);
            g->setSourceId(getthisNode());
            g->setDestId(destination);
            g->setTaskNum(Msg->getTaskNum());
            g->setTaskResult(Msg->getTaskResult());
            g->setGossipMsg(GOSSIP.c_str());
            g->setTimestamp(simTime());
            send(g,"out",routing);
            EV<<getName()<<" : Gossip Forwarded to : "<<destination<<endl;
            std::ostringstream oss;
            oss<<getName()<<" : Gossip Forwarded to : "<<destination<<endl;
            threadSafeLog(oss.str());
        }
    }
    int networkSize  = getParentModule()->par("numClients").intValue(); 
    if(gossipRecv == networkSize){
        gossipRecv = 0;
        triggerNextTask();
    }
}

void Client::initialize()
{
    int networkSize  = getParentModule()->par("numClients").intValue(); 
    int thisNode = getthisNode();
    EV << "Node initialized : " << thisNode << endl;
    std::ostringstream oss;
    oss<< "Node initialized : " << thisNode << endl;
    threadSafeLog(oss.str());
    navigation.setTable(thisNode,networkSize);
    startTaskMsg = new cMessage("startTask");
    scheduleAt(simTime() + 0.2, startTaskMsg);
    // createAndSendTask(1,networkSize);
}

void Client::handleMessage(cMessage *msg)
{
    if (msg == startTaskMsg) {
        int networkSize = getParentModule()->par("numClients").intValue();
        createAndSendTask(1, networkSize);
        delete startTaskMsg;
        startTaskMsg = nullptr;
    }
    else if (dynamic_cast<subtask *>(msg)) {
        subtask *Msg = check_and_cast<subtask *>(msg);
        int thisNode = getthisNode();

        if(Msg->getDestId() == thisNode){
            int len = Msg->getQueryLen();
            EV<<getName()<<" : Subtask recieved : "<<"From : "<<Msg->getSourceId()<<" Task Num : "<<Msg->getTaskNum()<<endl;
            std::ostringstream oss, os1,os2,os3,os4;
            oss<<getName()<<" : Subtask recieved : "<<"From : "<<Msg->getSourceId()<<" Task Num : "<<Msg->getTaskNum();
            threadSafeLog(oss.str());
            EV<<"Sub Task Num : "<<Msg->getSubTaskNum()<< " : Sub Task Length : "<<Msg->getQueryLen()<<endl;
            os1<<"Sub Task Num : "<<Msg->getSubTaskNum()<< " : Sub Task Length : "<<Msg->getQueryLen();
            threadSafeLog(os1.str());
            EV<<"Subtask : ";os2<<"Subtask : ";
            // std::string templog = "Subtask : ";
            std::vector<int>v;
            for(int i = 0;i<len;i++){
                v.push_back(Msg->getQuery(i));
                EV<<Msg->getQuery(i)<<" ";
                os2<<Msg->getQuery(i)<<" ";
                // templog += Msg->getQuery(i) + " ";
            }EV<<endl;
            threadSafeLog(os2.str());
           
            int ans = getMax(v);
            EV<<"Answer : "<<ans<<endl;
            os3<<"Answer : "<<ans<<endl;
            threadSafeLog(os3.str());
            std::pair<int,int> routing = navigation.findRoute(Msg->getSourceId());
            int routingDest = routing.second;
            int routingPort = routing.first;

            subtaskResp * resp = new subtaskResp("subtaskResp");
            resp->setSourceId(getthisNode());
            resp->setDestId(Msg->getSourceId());
            resp->setAnswer(ans);
            resp->setTaskNum(Msg->getTaskNum());
            resp->setSubTaskNum(Msg->getSubTaskNum());
            resp->setTimestamp(simTime());
            send(resp, "out", routingPort);
            EV<<getName()<<" : Subtask response sent to : "<<Msg->getSourceId()<<endl;
            os4<<getName()<<" : Subtask response sent to : "<<Msg->getSourceId()<<endl;
            threadSafeLog(os4.str());
            delete Msg;
        }
        
        else{
            int dest = Msg->getDestId();
            std::pair<int,int> routing = navigation.findRoute(dest);
            int routingDest = routing.second;
            int routingPort = routing.first;
            send(Msg,"out",routingPort);
            std::ostringstream oss;
            oss<<getName()<<" : Task routed to : "<<routingDest<<" : Destination : "<<Msg->getDestId()<<endl;
            EV<<getName()<<" : Task routed to : "<<routingDest<<" : Destination : "<<Msg->getDestId()<<endl;
            threadSafeLog(oss.str());
        }
        // EV<<"MSG from : "<<Msg->getSourceId()<<endl;
        //    processResponse(Msg);
    }

    else if (dynamic_cast<subtaskResp *>(msg)){
        int thisNode = getthisNode();
        subtaskResp *Msg = check_and_cast<subtaskResp *>(msg);
        if(Msg->getDestId() == thisNode){
            int taskNum = Msg->getTaskNum();
            int subtaskNum = Msg->getSubTaskNum();
            int ans = Msg->getAnswer();
            taskMap[taskNum].updResp(subtaskNum,ans); 
            subtaskRespCount++;
            EV<<getName()<<" : Sub Task Resp recv : From : "<<Msg->getSourceId()<<" : task num : "<<taskNum<<" : subtask num : "<<subtaskNum<<" : answer :"<<ans<<endl ;
            std::ostringstream oss;
            oss<<getName()<<" : Sub Task Resp recv : From : "<<Msg->getSourceId()<<" : task num : "<<taskNum<<" : subtask num : "<<subtaskNum<<" : answer :"<<ans<<endl;
            threadSafeLog(oss.str());
            if(subtaskRespCount == taskMap[taskNum].getSubtaskCount()){
                processTask(taskNum);
            }
            delete Msg;
        }
        else{
            int dest = Msg->getDestId();
            std::pair<int,int> routing = navigation.findRoute(dest);
            int routingDest = routing.second;
            int routingPort = routing.first;
            send(Msg,"out",routingPort);
            EV<<getName()<<" : Sub Task resp routed to "<<routingDest<<" : Destination : "<<Msg->getDestId()<<endl;
            std::ostringstream oss;
            oss<<getName()<<" : Sub Task resp routed to "<<routingDest<<" : Destination : "<<Msg->getDestId()<<endl;;
        }
    }

    else if(dynamic_cast<gossip *>(msg)){
        int thisNode = getthisNode();
        gossip *Msg = check_and_cast<gossip *>(msg);
        std::ostringstream oss;
        if(thisNode != Msg->getDestId()){
            EV<<getName()<<" : Gossip Error : Recv error :"<<endl;
            oss<<getName()<<" : Gossip Error : Recv error :"<<endl;
            threadSafeLog(oss.str());
        }
        else{
            processGossip(Msg);
        }
        delete Msg;
    }

    else{
    EV<<"Unknown message"<<endl;
   }

}

