/*
Name:threads.h
Description:Thread and processes module header.
Authors:Amit Herman Raz Rajwan

*/

#ifndef _THREADS_H_
#define _THREADS_H_
#include "HardCodedData.h"
#include <windows.h>
#include <stdio.h>

//Shortcut for ReleaseMutex
#define release ReleaseMutex



HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine,
	LPDWORD p_thread_id, LPVOID lpParam);

int Init_Threads(int N, LPTHREAD_START_ROUTINE p_start_routine, HANDLE p_thread_handles[], DWORD p_thread_ids[]);
int Close_Threads(int N, HANDLE p_thread_handles[]);
void KillThreads(DWORD code1, DWORD code2, HANDLE h_Threads[]);



//------------------process and threads 

//Warp for signaleobject if not succed return correspnding error code 
int WaitForSingleObjectWrap(HANDLE handle, uli time_ms);
//Warp for WaitForMultipleObjectsWra if not succed return correspnding error code 
int WaitForMultipleObjectsWrap(uli num_of_threads, HANDLE* handle_arr, uli time_ms, BOOL bWaitAll);
//------------------semphoros and mutex-- 
//Warp for  CreateSemphore if not succed return correspnding error code 
int CreateSemphoreWrap(int max_count, HANDLE* OUT semphore, int initialcount);
//Warp for  CreateMutex if not succed return correspnding error code 
int CreateMutexWrap(BOOL bInitialOwner, HANDLE* OUT mutex);
//Warp for  OpenSemphore if not succed return correspnding error code 
int OpenSemphoreWrap(HANDLE* OUT semphore, const char* name);
int ReleaseSemphoreWrap(HANDLE semphore, int lReleaseCount);

int ReleaseMutexeWrap(HANDLE mutex);

int create_event_simple(HANDLE* event);








#endif
