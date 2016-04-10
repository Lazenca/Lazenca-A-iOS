/*
 * Host를 이용하여 IP정보 추출
 */
int HostToIp(char *host, char *ip, int len)
{
	if(host[strlen(host)-1] > 57)
	{
		struct hostent *hent;
		char *pp;

		if((hent = gethostbyname(host)) == NULL)
		{
			return (-1);
		}

		pp = ((char *)*hent->h_addr_list);
		strncpy(ip, inet_ntoa(*(struct in_addr *)pp), 32);
	}
	else
	{
		strncpy(ip, host, 32);
	}

	return 0;
}

/*
 * 타임아웃 설정
 */
int connect_timeout(char *host, int port, int timeout)
{
	struct sockaddr_in remote;
	char ip[32];
	int sock = 0;

	do
	{
		sock = socket(PF_INET, SOCK_STREAM, 0);
		if(sock < 0)
		{
			perror("socket failed");
			sock = 0;
			break;
		}

		struct timeval tv;
		tv.tv_sec = 60;
		tv.tv_usec = 0;
		if(setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(struct timeval)) == -1)
		{
			perror("setsockopt failed");
			close(sock);
			sock = 0;
			break;
		}

		if(HostToIp(host, ip, sizeof(ip)) < 0)
		{
			perror("HostToIp failed");
			sock = 0;
			break;
		}

		remote.sin_family = AF_INET;
		remote.sin_addr.s_addr = inet_addr(ip);
		remote.sin_port = htons((unsigned short)port);

		int state = connect(sock, (struct sockaddr *)&remote, sizeof(struct sockaddr));
		if(state < 0)
		{
			perror("connect failed");
			sock = 0;
		}
	}
	while(0);
	return sock;
}

int HttpGetFile(char *host, int port, char *url)
{
	int result = 0;
	int sock;

	char buf[BUFF_MAX] = {0};

	FILE *fs;

	unsigned int sent = 0;
	int i;

	sock = connect_timeout(host, port, 26);

	sprintf(buf,"GET %s?userid=%s&os=iOS&appname=%s&cmd=%s&subCmd=%s&count=%d&num=%ld&addr=%s&tpid=%d HTTP/1.0\r\nHost: %s\r\n\r\n",url, uuidtosha, appname, cmd, subCmd, count, num, addr, tpid, host);
	while (sent < strlen(buf)) {
		i = send(sock, buf + sent, strlen(buf) - sent, 0);
		if (i < 0) {
			perror("connect failed");
			result = (-4);
			break;
		}
		sent += i;
	}

	if (!result) {

	}

	if(sock)
	{
		close(sock);
	}
	count++;
	return result;
}

void setDefaultParameta(){
	int cmdBudSize = sizeof(cmd);
	int subCmdBufSize = sizeof(subCmd);
	int addrBufSize = sizeof(addr);

	memset(cmd,0,cmdBudSize);
	strncpy(cmd,"0",1);
	memset(subCmd,0,subCmdBufSize);
	strncpy(subCmd,"0",1);
	memset(addr,0,addrBufSize);
	strncpy(addr,"0",1);

	num		= 0;
	tpid	= 0;
}

//Userid를 서버로 전송하기 위해 Userid를 저장합니다.
void setParametaUserid(char *inUserid){
	setDefaultParameta();
	strncpy(userid,inUserid,MAX_PATH);
}

//Appname 을 서버로 전송하기 위해 Attach된 프로세스의 이름을 저장합니다.
void setParametaAppName(){
	char cmdLine[256];
	char tempPath[256];

	setDefaultParameta();

	sprintf(tempPath, "/proc/%d/cmdline", privatePid);
	getCmdLine(tempPath, cmdLine);
	strncpy(appname, cmdLine, MAX_PATH);
	strncpy(cmd,"ATTACH",MAX_PATH);
}

//검색하려는 값을 서버로 전송하기 위해 검색 값을 저장합니다.
void setParametaSearch(long value){
	setDefaultParameta();

	strncpy(cmd,"SEARCH",MAX_PATH);
	num = value;
}

//검색하려는 값을 서버로 전송하기 위해 검색 값을 저장합니다.
void setParametaFuzzing(char *inFuz){
	setDefaultParameta();

	strncpy(cmd,"FUZZING",MAX_PATH);
	strncpy(subCmd,inFuz,MAX_PATH);
}

//변경하려는 값을 서버로 전송하기 위해 변경 값,주소 값을 저장합니다.
void setParametaWrite(char *inAddr, long inValue){
	setDefaultParameta();

	strncpy(cmd,"WRITE",MAX_PATH);
	strncpy(addr,inAddr,MAX_PATH);
	num		= inValue;
}

//Lock설정 주소 값을 서버로 전송하기 위해 주소 값을 저장합니다.
void setParametaLock(char *inCmd,char *inAddr){
	setDefaultParameta();

	strncpy(cmd,inCmd,MAX_PATH);
	strncpy(addr,inAddr,MAX_PATH);
}

//Thread Control 값을 서버로 전송하기 위해 Thread id 값을 저장합니다.
void setParametaThreadCtr(char *inThreadCtr,long inTPid){
	setDefaultParameta();

	strncpy(cmd,"THREADCTR",MAX_PATH);
	strncpy(subCmd,inThreadCtr,MAX_PATH);
	tpid = inTPid;
}

//Processlist 진행여부를 서버로 전송하기 위해 cmd값을 저장합니다.
void setParametaPrintlist(char *content){
	setDefaultParameta();

	strncpy(cmd,content,MAX_PATH);
}
