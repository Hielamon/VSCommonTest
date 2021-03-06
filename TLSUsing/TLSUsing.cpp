#include <windows.h> 
#include <stdio.h> 

#define THREADCOUNT 4 
DWORD dwTlsIndex;

VOID ErrorExit(LPSTR);

VOID CommonFunc(VOID)
{
	LPVOID lpvData;

	// Retrieve a data pointer for the current thread. 

	lpvData = TlsGetValue(dwTlsIndex);
	if ((lpvData == 0) && (GetLastError() != ERROR_SUCCESS))
		ErrorExit("TlsGetValue error");

	// Use the data stored for the current thread. 

	printf("common: thread %d: lpvData=%lx\n",
		   GetCurrentThreadId(), lpvData);

	Sleep(5000);
}

DWORD WINAPI ThreadFunc(VOID)
{
	LPVOID lpvData;

	// Initialize the TLS index for this thread. 
	lpvData = (LPVOID)LocalAlloc(LPTR, 256);
	if (!TlsSetValue(dwTlsIndex, lpvData))
		ErrorExit("TlsSetValue error");

	printf("thread %d: lpvData=%lx\n", GetCurrentThreadId(), lpvData);

	CommonFunc();

	// Release the dynamic memory before the thread returns. 

	lpvData = TlsGetValue(dwTlsIndex);
	if (lpvData != 0)
		LocalFree((HLOCAL)lpvData);


	return 0;
}

DWORD WINAPI ThreadFunc2(VOID)
{
	LPVOID lpvData;

	// Initialize the TLS index for this thread. 

	if ((dwTlsIndex = TlsAlloc()) == TLS_OUT_OF_INDEXES)
		ErrorExit("TlsAlloc failed");

	lpvData = (LPVOID)LocalAlloc(LPTR, 256);
	if (!TlsSetValue(dwTlsIndex, lpvData))
		ErrorExit("TlsSetValue error");

	printf("thread %d: lpvData=%lx\n", GetCurrentThreadId(), lpvData);

	CommonFunc();

	// Release the dynamic memory before the thread returns. 

	lpvData = TlsGetValue(dwTlsIndex);
	if (lpvData != 0)
		LocalFree((HLOCAL)lpvData);

	if(!TlsFree(dwTlsIndex))
		ErrorExit("TlsFree error");

	return 0;
}

int main(VOID)
{
	DWORD IDThread;
	HANDLE hThread[THREADCOUNT];
	HANDLE hThread2;
	int i;

	// Allocate a TLS index. 

	/*if ((dwTlsIndex = TlsAlloc()) == TLS_OUT_OF_INDEXES)
		ErrorExit("TlsAlloc failed");*/

	// Create multiple threads. 

	hThread2 = CreateThread(NULL, // default security attributes 
							0,                           // use default stack size 
							(LPTHREAD_START_ROUTINE)ThreadFunc2, // thread function 
							NULL,                    // no thread function argument 
							0,                       // use default creation flags 
							&IDThread);              // returns thread identifier 

													 // Check the return value for success. 
	if (hThread2 == NULL)
		ErrorExit("CreateThread error\n");

	WaitForSingleObject(hThread2, INFINITE);
	TlsFree(dwTlsIndex);



	for (i = 0; i < THREADCOUNT; i++)
	{
		hThread[i] = CreateThread(NULL, // default security attributes 
								  0,                           // use default stack size 
								  (LPTHREAD_START_ROUTINE)ThreadFunc, // thread function 
								  NULL,                    // no thread function argument 
								  0,                       // use default creation flags 
								  &IDThread);              // returns thread identifier 

														   // Check the return value for success. 
		if (hThread[i] == NULL)
			ErrorExit("CreateThread error\n");
	}

	for (i = 0; i < THREADCOUNT; i++)
		WaitForSingleObject(hThread[i], INFINITE);



	return 0;
}

VOID ErrorExit(LPSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);
	exit(0);
	ExitProcess(0);
}