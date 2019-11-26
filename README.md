# TrapPages
Simple program to demonstrate the use of trap pages, a technique that can be used to detect memory scanners.

# What is a trap page?
A 'trap page' is a page of memory allocated by [VirtualAlloc](https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualalloc) which is intended to never be accessed. Accessing this memory in any way can be detected.

When memory is allocated with [VirtualAlloc](https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualalloc), the newly allocated pages are considered to be invalid until their memory is accessed somehow. Once the memory within a given page is accessed, the page is committed to real physical memory and the page becomes valid. This is usually invisible and generally not important, however this technique relies upon that behaviour.

[QueryWorkingSetEx](https://docs.microsoft.com/en-us/windows/win32/api/psapi/nf-psapi-queryworkingsetex) can be used to inspect memory allocated by [VirtualAlloc](https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualalloc) to determine whether or not the pages are valid. Pages that have never been accessed will show as invalid, whereas pages which have been accessed will be shown as valid.

This program allocates a page of memory and continuously checks that page to see whether it has became valid. The program never accesses the allocated page, so it can expect that the page is always invalid. If a memory scanner such as Cheat Engine is used to scan the running program, it will trigger the trap page and the program will stop working.

##### Note: for whatever reason, this only works when running as a standalone program and not when launched with the Visual Studio Debugger
