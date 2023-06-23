#pragma once

#include <windows.h> 
#include <stdio.h> 
#define DEFIND_GUID 
#include <initguid.h> 
#include <virtdisk.h> 
#pragma comment(lib, "VirtDisk.lib") 

namespace VDisk {

	class VirtualHDD {

	public:
		VirtualHDD(const char* Filename);
		~VirtualHDD();

	public:
		bool Init();
		bool Attatch();

	private:
		wchar_t m_pFilename[4096];
		HANDLE m_Handle;

	};

}

