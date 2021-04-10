#include<iostream>
#include<windows.h>
#include<string>
using namespace std;
int main()
{
	HANDLE hCom;
	hCom=CreateFile("COM6",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
	if(hCom==(HANDLE)-1)
	{
		cout<<"open failed";
		return 0;
	}
	else
	{
		cout<<"串口打开成功"<<endl;
	}
	SetupComm(hCom,1024,1024);
	

	COMMTIMEOUTS TimeOuts;
	TimeOuts.ReadIntervalTimeout=1000;
	TimeOuts.ReadTotalTimeoutMultiplier=500;
	TimeOuts.ReadTotalTimeoutConstant=5000;
	TimeOuts.WriteTotalTimeoutMultiplier=500;
	TimeOuts.WriteTotalTimeoutConstant=2000;
	SetCommTimeouts(hCom,&TimeOuts);

DCB dcb;
	dcb.BaudRate=115200;
	dcb.ByteSize=8;
	dcb.Parity=0;
	dcb.StopBits=1;
	SetCommState(hCom,&dcb);

	PurgeComm(hCom,PURGE_RXCLEAR|PURGE_TXCLEAR);

	char lpOutBuffer[]={'d','a','\r'};
	char lpOutBuffer1[]={'f','f','3','0','0','0','\r'};
	char lpOutBuffer2[]={'m','c','1','6','\r'};
    /*lpOutBuffer[0]='d';
	lpOutBuffer[1]='a';
	lpOutBuffer[2]='\r';*/

	//lpOutBuffer[2]='\n';
	DWORD dwByteWrite=sizeof(lpOutBuffer);  //3;
	DWORD dwByteWrite1=sizeof(lpOutBuffer1); 
	DWORD dwByteWrite2=sizeof(lpOutBuffer2); 
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
   // cin.getline(lpOutBuffer,'\n');
	ClearCommError(hCom,&dwErrorFlags,&ComStat);//cout<<dwErrorFlags<<endl;
	//Sleep(1000);
	bWriteStat=WriteFile(hCom,lpOutBuffer,dwByteWrite,&dwByteWrite,NULL);
    if(bWriteStat)
	{
		cout<<"COM写成功"<<endl;
	}
	else
	{
		cout<<"COM写失败"<<endl;
	}
    PurgeComm(hCom,PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);

	char str[100]={0};
	DWORD wCount=18;
	BOOL bReadStat;
	bReadStat=ReadFile(hCom,str,20,&wCount,NULL);
	if(bReadStat)
	{
		cout<<"COM读成功"<<endl;
	}
	else
	{
		cout<<"COM读失败"<<endl;
	}
    while(1)
	{
		if(bReadStat) 
		{	
          for(int i=0;i<wCount;i++)
		  {
			if(str[i]==13)
				cout<<endl;
			cout<<str[i];
		  }
		  bReadStat=0;
		  cout<<endl;
		}
	}
CloseHandle(hCom);
system("pause");
	return 0;
}