#pragma once

#include <vector>
#include <Windows.h>

#include "Poco\Path.h"
using Poco::Path;

namespace VDisk {

	class HardDiskListing {
		
	public:
		HardDiskListing();
		~HardDiskListing();

	public:
		bool						Read(const char* ListFile);
		std::vector<Poco::Path>*	GetPaths();

	private:
		std::vector<Poco::Path>*	m_pPaths;

	};

}