message subtask{
	int sourceId;
	int destId;
	int queryLen;
	int query[];
	int TaskNum;
	int subTaskNum;
	simtime_t timestamp;
}

message subtaskResp{
	int sourceId;
	int destId;
	int answer;
	int TaskNum;
	int SubTaskNum;
	simtime_t timestamp;
}

message gossip{
	int sourceId;
	int destId;
	int TaskNum;
	int TaskResult;
	string GossipMsg;
	simtime_t timestamp;
}