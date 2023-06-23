#include "Registry.hpp"

namespace VDisk {

	/*
	==================
	Registry - Default Constructor
	==================
	*/
	Registry::Registry() {
		m_RegistryEntry = new WinRegistryKey("HKEY_LOCAL_MACHINE\\SOFTWARE\\Fridayplans", false, KEY_ALL_ACCESS);
		memset(m_DriveListLocation, 0, 4096);
	}

	/*
	==================
	bool Registry::ReadRegistry()
	==================
	*/
	bool Registry::ReadRegistry() {
		if (!m_RegistryEntry->exists()) {
			return false;
		}
		if (!m_RegistryEntry->exists("DriveListFile")) {
			return false;
		}
		strncpy(m_DriveListLocation, m_RegistryEntry->getString("DriveListFile").c_str(), strlen(m_RegistryEntry->getString("DriveListFile").c_str()));
		return true;
	}

	/*
	==================
	void Registry::WriteRegistry(const char* DriveListingLocation)
	==================
	*/
	void Registry::WriteRegistry(const char* DriveListingLocation) {
		m_RegistryEntry->setString("DriveListFile", DriveListingLocation);
	}

	/*
	==================
	void Registry::ClearRegistry() 
	==================
	*/
	void Registry::ClearRegistry() {
		m_RegistryEntry->deleteKey();
	}

	/*
	==================
	const char* Registry::GetDriveListLocation()
	==================
	*/
	const char* Registry::GetDriveListLocation() {
		return m_DriveListLocation;
	}

	/*
	==================
	Registry::~Registry()
	==================
	*/
	Registry::~Registry() {

	}

}