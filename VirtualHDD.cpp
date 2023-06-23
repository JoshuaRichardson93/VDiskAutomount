#include "VirtualHDD.hpp" 

/*
==================
void PrintErrorMessage(ULONG ErrorId);
==================
*/
void PrintErrorMessage(ULONG ErrorId);

namespace VDisk {

	/*
	==================
	VirtualHDD - Default Constructor
	==================
	*/
	VirtualHDD::VirtualHDD(const char* Filename) : m_pFilename() {
		memset(m_pFilename, 0, 4096);
		MultiByteToWideChar(CP_ACP, 0, Filename, strlen(Filename), m_pFilename, 4096);
	}

	/*
	==================
	bool VirtualHDD::Init()
	==================
	*/
	bool VirtualHDD::Init() {
		OPEN_VIRTUAL_DISK_PARAMETERS	oparams;
		
		_VIRTUAL_STORAGE_TYPE			VHDStorageType = {
			VIRTUAL_STORAGE_TYPE_DEVICE_VHD,
			VIRTUAL_STORAGE_TYPE_VENDOR_MICROSOFT
		};
		oparams.Version =			OPEN_VIRTUAL_DISK_VERSION_1;
		oparams.Version1.RWDepth =	OPEN_VIRTUAL_DISK_RW_DEPTH_DEFAULT;
		

		DWORD Result = OpenVirtualDisk(&VHDStorageType, m_pFilename, VIRTUAL_DISK_ACCESS_ATTACH_RW | VIRTUAL_DISK_ACCESS_GET_INFO | VIRTUAL_DISK_ACCESS_DETACH, 
			OPEN_VIRTUAL_DISK_FLAG_NONE, &oparams, &m_Handle);

		if (Result != ERROR_SUCCESS) {
			PrintErrorMessage(GetLastError());
			return false;
		}
		return true;
	}

	/*
	==================
	bool VirtualHDD::Attatch()
	==================
	*/
	bool VirtualHDD::Attatch() {
		ATTACH_VIRTUAL_DISK_PARAMETERS	iparams;
		iparams.Version = ATTACH_VIRTUAL_DISK_VERSION_1;

		DWORD Result = AttachVirtualDisk(m_Handle, 0, ATTACH_VIRTUAL_DISK_FLAG_PERMANENT_LIFETIME, 0, &iparams, 0);

		if (Result != ERROR_SUCCESS) {
			PrintErrorMessage(GetLastError());
			return false;
		}
		return true;
	}

	/*
	==================
	VirtualHDD::~VirtualHDD()
	==================
	*/
	VirtualHDD::~VirtualHDD() {
	}


}

void PrintErrorMessage(ULONG ErrorId)
{
	PVOID Message = NULL;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		ErrorId,
		0,
		(LPWSTR)&Message,
		16,
		NULL);

	OutputDebugString((LPWSTR)Message);
	OutputDebugStringA("\n");
	LocalFree(Message);
}