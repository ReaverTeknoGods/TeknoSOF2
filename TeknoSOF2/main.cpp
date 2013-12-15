#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "PE.h"
void main()
{
		char str[256];
		bool found1 = false;
		bool found2 = false;
		printf("------------------\n");
		printf("Soldier of Fortune 2 Gold Windows Vista/7 fix\n");
		printf("By: Reaver\n");
		printf("-- www.teknogods.com --\n");
		printf("------------------\n");
		printf("Have you backed up the executables? (y/n)\n");
		while(1)
		{
			memset(str, 0, 256);
			scanf("%s", &str);
			if(strcmp(str, "n") == 0)
			{
				printf("Please take backup and then rerun me!\n");
				_getch();
				return;
			}
			else if(strcmp(str, "y") == 0) break;
		}
		HANDLE SPExe = CreateFile("SoF2.exe",GENERIC_ALL, FILE_SHARE_READ,NULL,	OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if(!SPExe || (DWORD)SPExe == -1)
		{
			printf("Unable to open SoF2.exe");
			_getch();
			return;
		}
		HANDLE SPMPExe = CreateFile("SoF2MP.exe",GENERIC_ALL, FILE_SHARE_READ,NULL,	OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if(!SPMPExe || (DWORD)SPMPExe == -1)
		{
			printf("Unable to open SoF2MP.exe");
			_getch();
			return;
		}
		DWORD size = GetFileSize(SPExe, 0);
		DWORD lolread = 0;
		LPBYTE oldfile = new BYTE[size];
		SetFilePointer(SPExe, 0, 0, FILE_BEGIN);
		ReadFile(SPExe, oldfile, size, &lolread, 0);
		for(int i = 0; i < size; i++)
		{
			if(*(WORD *)(oldfile + i) == 0x6850)
				if(*(BYTE *)(oldfile + i + 6) == 0xE8)
					if(*(BYTE *)(oldfile + i + 11) == 0xA1)
						if(*(WORD *)(oldfile + i + 16) == 0xC483)
							if(*(BYTE *)(oldfile + i + 18) == 0x20)
							{
								printf("Pattern found in SoF2.exe, patching!\n");
								SetFilePointer(SPExe, i+6, 0, FILE_BEGIN);
								WriteFile(SPExe, "\x90\x90\x90\x90\x90", 5, &lolread, 0);
								CloseHandle(SPExe);
								printf("Patched!\n");
								found1 = true;
							}
		}
		if(found1 == false)
		{
			printf("Unable to find pattern in SoF2.exe!\n");
		}
		size = GetFileSize(SPMPExe, 0);
		lolread = 0;
		LPBYTE oldfile2 = new BYTE[size];
		SetFilePointer(SPMPExe, 0, 0, FILE_BEGIN);
		ReadFile(SPMPExe, oldfile2, size, &lolread, 0);
		for(int i = 0; i < size; i++)
		{
			if(*(BYTE *)(oldfile2 + i) == 0x68)
				if(*(BYTE *)(oldfile2 + i + 5) == 0x68)
					if(*(DWORD *)(oldfile2 + i + 10) == 0x15FF006A)
						if(*(BYTE *)(oldfile2 + i + 18) == 0xA1)
							if(*(WORD *)(oldfile2 + i + 23) == 0xC483)
								if(*(BYTE *)(oldfile2 + i + 25) == 0x44)
								{
									printf("Pattern found in SoF2MP.exe, patching!\n");
									SetFilePointer(SPMPExe, i+12, 0, FILE_BEGIN);
									WriteFile(SPMPExe, "\x90\x90\x90\x90\x90\x90", 6, &lolread, 0);
									CloseHandle(SPMPExe);
									printf("Patched!\n");
									found2 = true;
								}
		}
		if(found2 == false)
		{
			printf("Unable to find pattern in SoF2MP.exe!\n");
		}
		printf("Have fun and remember to visit www.teknogods.com for latest updates!\n");
		_getch();
}	 