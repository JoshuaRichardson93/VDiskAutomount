#include "HardDiskListing.hpp"

#include <iostream>
#include <fstream>

namespace VDisk {

	/*
	==================
	HardDiskListing - Default Constructor
	==================
	*/
	HardDiskListing::HardDiskListing() : m_pPaths(0) {

	}

	/*
	==================
	bool HardDiskListing::Read(const char* ListFile)
	==================
	*/
	bool HardDiskListing::Read(const char* ListFile) {

		Poco::Path		CurrentPath;
		std::ifstream	DriveListingFile(ListFile);
		char			CurrentLine[2048];
		m_pPaths		= new std::vector<Poco::Path>();

		if (DriveListingFile.is_open()) {
			while (DriveListingFile.getline(CurrentLine, 2048)) {
				if (CurrentPath.tryParse(CurrentLine, Poco::Path::PATH_WINDOWS)) {
					m_pPaths->push_back(Poco::Path(CurrentLine));
				}
			}
		}
		else {
			return false;
		}

		return true;
	}

	/*
	==================
	std::vector<Poco::Path>* HardDiskListing::GetPaths()
	==================
	*/
	std::vector<Poco::Path>* HardDiskListing::GetPaths() {
		if (m_pPaths->size() == 0) {
			return 0;
		}
		return m_pPaths;
	}
	
	/*
	==================
	HardDiskListing::~HardDiskListing()
	==================
	*/
	HardDiskListing::~HardDiskListing() {
		
	}

}