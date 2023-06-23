#pragma once

#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Exception.h"
#include "Poco/EventLogChannel.h"

#include "HardDiskListing.hpp"
#include "Registry.hpp"
#include "VirtualHDD.hpp"

#include <vector>
#include <iostream>

using namespace Poco::Util;

namespace VDisk {

	class HardDiskService : public ServerApplication {

	public:
		HardDiskService();
		~HardDiskService();

	public: //ServerApplication
		void initialize(Application& self);
		void uninitialize();
		void defineOptions(OptionSet& options);
		void handleHelp(const std::string& name, const std::string& value);
		void handleInstall(const std::string& name, const std::string& value);
		void handleUninstall(const std::string& name, const std::string& value);
		void displayHelp();
		int main(const ArgVec& args);

	private:
		bool m_HelpRequested;
		HardDiskListing m_HDDLIst;
		Registry m_Registry;
		std::vector<VirtualHDD> m_VirtualHDDs;
		Poco::AutoPtr<Poco::EventLogChannel> m_ELChannel;
	};

}