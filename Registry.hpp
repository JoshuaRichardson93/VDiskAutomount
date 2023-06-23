#pragma once
/* 
 * Worth noting this: https://msdn.microsoft.com/en-us/library/windows/desktop/ms724072(v=vs.85).aspx
 * 64-bit entries come under the Wow6432Node'
 * This will be used to store any settings we need.
 *
 */
#include "Poco/Util/WinRegistryKey.h"

using namespace Poco::Util;

#include <vector>

namespace VDisk {

	class Registry {
		
	public:
		Registry();
		~Registry();

	public:
		bool ReadRegistry();
		void WriteRegistry(const char* DriveListingLocation);
		void ClearRegistry();

	public:
		const char* GetDriveListLocation();

	private:
		char m_DriveListLocation[4096];

	private:
		WinRegistryKey* m_RegistryEntry;

	};

}