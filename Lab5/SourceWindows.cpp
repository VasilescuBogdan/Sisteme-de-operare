#include <windows.h> 
#include <tchar.h>
#include <stdio.h> 
#include <iostream>

HANDLE g_hChildStd_IN_Rd[10] = { NULL };
HANDLE g_hChildStd_IN_Wr[10] = { NULL };
HANDLE g_hChildStd_OUT_Rd[10] = { NULL };
HANDLE g_hChildStd_OUT_Wr[10] = { NULL };

void CreateChildProcess(void); 
void WriteToPipe(void); 
void ReadFromPipe(void); 
void ErrorExit(PTSTR);

HANDLE g_hInputFile = NULL;

int main(tchar argv[]){
    
    SECURITY_ATTRIBUTES saAttr; 
 
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
    saAttr.bInheritHandle = TRUE; 
    saAttr.lpSecurityDescriptor = NULL; 

    for (int k = 0; k < 10; k++){
 
    if ( ! CreatePipe(&g_hChildStd_OUT_Rd[k], &g_hChildStd_OUT_Wr[k], &saAttr, 0) ) 
        ErrorExit(TEXT("StdoutRd CreatePipe")); 

    if ( ! SetHandleInformation(g_hChildStd_OUT_Rd[k], HANDLE_FLAG_INHERIT, 0) )
        ErrorExit(TEXT("Stdout SetHandleInformation"));  
 
    if (! CreatePipe(&g_hChildStd_IN_Rd[k], &g_hChildStd_IN_Wr[k], &saAttr, 0)) 
        ErrorExit(TEXT("Stdin CreatePipe")); 

    if ( ! SetHandleInformation(g_hChildStd_IN_Wr[k], HANDLE_FLAG_INHERIT, 0) )
        ErrorExit(TEXT("Stdin SetHandleInformation"));
   }

   CreateChildProcess();


   g_hInputFile = CreateFile(
       argv[1], 
       GENERIC_READ, 
       0, 
       NULL, 
       OPEN_EXISTING, 
       FILE_ATTRIBUTE_READONLY, 
       NULL); 

   if ( g_hInputFile == INVALID_HANDLE_VALUE ) 
      ErrorExit(TEXT("CreateFile"));

    for (int i = 1; i <= 10000; i++){
        int count = 0;
        for (int j = 2; j <= i / 2; j++){
            
            if (i % j == 0){
                count++;
            }
        }
        if (count == 0)
            std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}