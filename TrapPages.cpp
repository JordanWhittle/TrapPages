#include <Windows.h>
#include <Psapi.h>
#include <iostream>

BOOL isPageValid(HANDLE hProcess, PVOID pvAddress)
{
	PSAPI_WORKING_SET_EX_INFORMATION info;
	info.VirtualAddress = pvAddress;
	if (QueryWorkingSetEx(hProcess, &info, sizeof(PSAPI_WORKING_SET_EX_INFORMATION)))
	{
		if (info.VirtualAttributes.Valid)
		{
			return TRUE;
		}
	}
	return FALSE;
}

int main()
{
	// Allocate (reserve) a page of virtual memory.
	// The page is invalid until the memory within is accessed, at which point the page will be committed to physical memory and become valid.
	PVOID page = VirtualAlloc(NULL, 1, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (NULL != page)
	{
		std::cout << "Allocated trap memory page at 0x" << std::hex << page << std::endl;
		HANDLE currentProcess = GetCurrentProcess();
		for(;;)
		{
			// Perform a query on the page to see whether or not it is valid.
			// Because this program never accesses the page that was allocated, the page should always be invalid.
			// If this page is valid, then something else has accessed the virtual memory meaning we have detected tampering.
			if (isPageValid(currentProcess, page))
			{
				std::cout << "Memory scanning detected!" << std::endl;
				std::cin.get();
			}
			Sleep(1);
		}
	}
}
