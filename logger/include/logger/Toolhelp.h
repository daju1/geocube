#pragma once

#include "logger/CmnHdr.h"     /* See Appendix A. */
#include <tlhelp32.h>
#include <tchar.h>



namespace Logger
{


class ToolHelp
{
private:
   HANDLE m_hSnapshot;

public:
   ToolHelp (DWORD dwFlags     = 0,
             DWORD dwProcessID = 0);
   ~ToolHelp();

   BOOL CreateSnapshot(DWORD dwFlags, DWORD dwProcessID = 0);

   BOOL ProcessFirst(PPROCESSENTRY32 ppe) const;
   BOOL ProcessNext(PPROCESSENTRY32 ppe) const;
   BOOL ProcessFind(DWORD dwProcessId, PPROCESSENTRY32 ppe) const;

   BOOL ModuleFirst(PMODULEENTRY32 pme) const;
   BOOL ModuleNext(PMODULEENTRY32 pme) const;
   BOOL ModuleFind(PVOID pvBaseAddr, PMODULEENTRY32 pme) const;
   BOOL ModuleFind(PTSTR pszModName, PMODULEENTRY32 pme) const;
   
   BOOL ThreadFirst(PTHREADENTRY32 pte) const;
   BOOL ThreadNext(PTHREADENTRY32 pte) const;
   
   BOOL HeapListFirst(PHEAPLIST32 phl) const;
   BOOL HeapListNext(PHEAPLIST32 phl) const;
   int  HowManyHeaps() const;

   // Note: The heap block functions do not reference a snapshot and
   // just walk the process's heap from the beginning each time. Infinite 
   // loops can occur if the target process changes its heap while the
   // functions below are enumerating the blocks in the heap.
   BOOL HeapFirst(PHEAPENTRY32 phe, DWORD dwProcessID, 
      UINT_PTR dwHeapID) const;
   BOOL HeapNext(PHEAPENTRY32 phe) const;
   int  HowManyBlocksInHeap(DWORD dwProcessID, DWORD dwHeapId) const;
   BOOL IsAHeap(HANDLE hProcess, PVOID pvBlock, PDWORD pdwFlags) const;

public:
   static BOOL EnablePrivilege(PCTSTR szPrivilege, BOOL fEnable = TRUE);
   static BOOL ReadProcessMemory(DWORD dwProcessID, LPCVOID pvBaseAddress, 
      PVOID pvBuffer, SIZE_T cbRead, SIZE_T* pNumberOfBytesRead = NULL);
};



inline ToolHelp::ToolHelp(DWORD dwFlags,
                          DWORD dwProcessID)
{
   m_hSnapshot = INVALID_HANDLE_VALUE;
   CreateSnapshot(dwFlags, dwProcessID);
}



inline ToolHelp::~ToolHelp()
{
   if (m_hSnapshot != INVALID_HANDLE_VALUE)
      CloseHandle(m_hSnapshot);
}



inline BOOL ToolHelp::CreateSnapshot(DWORD dwFlags, DWORD dwProcessID)
{
   if (m_hSnapshot != INVALID_HANDLE_VALUE)
      CloseHandle(m_hSnapshot);

   if (dwFlags == 0)
   {
      m_hSnapshot = INVALID_HANDLE_VALUE;
   }
   else
   {
      m_hSnapshot = CreateToolhelp32Snapshot(dwFlags, dwProcessID);
   }

   return(m_hSnapshot != INVALID_HANDLE_VALUE);
}



inline BOOL ToolHelp::EnablePrivilege(PCTSTR szPrivilege,
                                      BOOL   fEnable)
{
   // Enabling the debug privilege allows the application to see
   // information about service applications
   BOOL   fOk = FALSE;    // Assume function fails
   HANDLE hToken;

   // Try to open this process's access token
   if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
   {
      // Attempt to modify the given privilege
      TOKEN_PRIVILEGES tp;
      tp.PrivilegeCount = 1;
      LookupPrivilegeValue(NULL, szPrivilege, &tp.Privileges[0].Luid);
      tp.Privileges[0].Attributes = fEnable ? SE_PRIVILEGE_ENABLED : 0;
      AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
      fOk = (GetLastError() == ERROR_SUCCESS);

      // Don't forget to close the token handle
      CloseHandle(hToken);
   }

   return(fOk);
}



inline BOOL ToolHelp::ReadProcessMemory(DWORD   dwProcessID,
                                        LPCVOID pvBaseAddress,
                                        PVOID   pvBuffer,
                                        SIZE_T  cbRead,
                                        SIZE_T* pNumberOfBytesRead)
{
   return(Toolhelp32ReadProcessMemory(dwProcessID, pvBaseAddress, pvBuffer, cbRead, pNumberOfBytesRead));
}



inline BOOL ToolHelp::ProcessFirst(PPROCESSENTRY32 ppe) const
{
   BOOL fOk = Process32First(m_hSnapshot, ppe);

   if (fOk && (ppe->th32ProcessID == 0))
      fOk = ProcessNext(ppe); // Remove the "[System Process]" (PID = 0)

   return(fOk);
}



inline BOOL ToolHelp::ProcessNext(PPROCESSENTRY32 ppe) const
{
   BOOL fOk = Process32Next(m_hSnapshot, ppe);

   if (fOk && (ppe->th32ProcessID == 0))
      fOk = ProcessNext(ppe); // Remove the "[System Process]" (PID = 0)

   return(fOk);
}



inline BOOL ToolHelp::ProcessFind(DWORD dwProcessId, PPROCESSENTRY32 ppe) const
{
   BOOL fFound = FALSE;

   for (BOOL fOk = ProcessFirst(ppe); fOk; fOk = ProcessNext(ppe))
   {
      fFound = (ppe->th32ProcessID == dwProcessId);

      if (fFound)
         break;
   }

   return(fFound);
}



inline BOOL ToolHelp::ModuleFirst(PMODULEENTRY32 pme) const
{
   return(Module32First(m_hSnapshot, pme));
}



inline BOOL ToolHelp::ModuleNext(PMODULEENTRY32 pme) const
{
   return(Module32Next(m_hSnapshot, pme));
}



inline BOOL ToolHelp::ModuleFind(PVOID pvBaseAddr, PMODULEENTRY32 pme) const
{
   BOOL fFound = FALSE;

   for (BOOL fOk = ModuleFirst(pme); fOk; fOk = ModuleNext(pme))
   {
      fFound = (pme->modBaseAddr == pvBaseAddr);

      if (fFound)
         break;
   }

   return(fFound);
}



inline BOOL ToolHelp::ModuleFind(PTSTR pszModName, PMODULEENTRY32 pme) const
{
   BOOL fFound = FALSE;

   for (BOOL fOk = ModuleFirst(pme); fOk; fOk = ModuleNext(pme))
   {
      fFound = (lstrcmpi(pme->szModule,  pszModName) == 0) || 
               (lstrcmpi(pme->szExePath, pszModName) == 0);

      if (fFound)
         break;
   }

   return(fFound);
}



inline BOOL ToolHelp::ThreadFirst(PTHREADENTRY32 pte) const
{
   return(Thread32First(m_hSnapshot, pte));
}



inline BOOL ToolHelp::ThreadNext(PTHREADENTRY32 pte) const
{
   return(Thread32Next(m_hSnapshot, pte));
}



inline int ToolHelp::HowManyHeaps() const
{
   int nHowManyHeaps = 0;

   HEAPLIST32 hl = { sizeof(hl) };

   for (BOOL fOk = HeapListFirst(&hl); fOk; fOk = HeapListNext(&hl))
      nHowManyHeaps++;

   return(nHowManyHeaps);
}



inline int ToolHelp::HowManyBlocksInHeap(DWORD dwProcessID,
                                         DWORD dwHeapID) const
{
   int nHowManyBlocksInHeap = 0;

   HEAPENTRY32 he = { sizeof(he) };

   BOOL fOk = HeapFirst(&he, dwProcessID, dwHeapID);

   for (; fOk; fOk = HeapNext(&he))
      nHowManyBlocksInHeap++;

   return(nHowManyBlocksInHeap);
}



inline BOOL ToolHelp::HeapListFirst(PHEAPLIST32 phl) const
{
   return(Heap32ListFirst(m_hSnapshot, phl));
}



inline BOOL ToolHelp::HeapListNext(PHEAPLIST32 phl) const
{
   return(Heap32ListNext(m_hSnapshot, phl));
}



inline BOOL ToolHelp::HeapFirst(PHEAPENTRY32 phe,
                                DWORD        dwProcessID,
                                UINT_PTR     dwHeapID) const
{
   return(Heap32First(phe, dwProcessID, dwHeapID));
}



inline BOOL ToolHelp::HeapNext(PHEAPENTRY32 phe) const
{
   return(Heap32Next(phe));
}



inline BOOL ToolHelp::IsAHeap(HANDLE hProcess,
                              PVOID  pvBlock,
                              PDWORD pdwFlags) const
{
   HEAPLIST32 hl = { sizeof(hl) };

   for (BOOL fOkHL = HeapListFirst(&hl); fOkHL; fOkHL = HeapListNext(&hl))
   {
      HEAPENTRY32 he = { sizeof(he) };

      BOOL fOkHE = HeapFirst(&he, hl.th32ProcessID, hl.th32HeapID);

      for (; fOkHE; fOkHE = HeapNext(&he))
      {
         MEMORY_BASIC_INFORMATION mbi;
         VirtualQueryEx(hProcess, (PVOID) he.dwAddress, &mbi, sizeof(mbi));

         if (chINRANGE(mbi.AllocationBase, pvBlock, 
            (PBYTE) mbi.AllocationBase + mbi.RegionSize))
         {
            *pdwFlags = hl.dwFlags;
            return(TRUE);
         }
      }
   }

   return(FALSE);
}


} // namespace Logger
