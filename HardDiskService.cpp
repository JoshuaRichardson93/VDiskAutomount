#include "HardDiskService.hpp"

namespace VDisk {

	/*
	==================
	HardDiskListing - Default Constructor
	==================
	*/
	HardDiskService::HardDiskService() : m_HelpRequested(false), m_HDDLIst(), m_Registry(), m_VirtualHDDs(), m_ELChannel(new Poco::EventLogChannel("VDF Automount")) {

	}

	/*
	==================
	void HardDiskService::initialize(Application& self)
	==================
	*/
	void HardDiskService::initialize(Application& self) {
		loadConfiguration();
		ServerApplication::initialize(self);
		logger().root().setChannel(m_ELChannel);
		logger().information("Automount Service Started.");
	}

	/*
	==================
	void HardDiskService::uninitialize()
	==================
	*/
	void HardDiskService::uninitialize() {
		ServerApplication::uninitialize();
	}
	
	/*
	==================
	void HardDiskService::defineOptions(OptionSet& options)
	==================
	*/
	void HardDiskService::defineOptions(OptionSet& options) {
		ServerApplication::defineOptions(options);
		// How do we automaticly set displayname 
		options.addOption(
			Option("help", "h", "Display help information on command line arguments")
			.required(false)
			.repeatable(false)
			.callback(OptionCallback<HardDiskService>(this, &HardDiskService::handleHelp)));

		options.addOption(
			Option("map", "m", "Sets the drive listing file for use upon startup")
			.required(false)
			.repeatable(false)
			.argument("file")
			.callback(OptionCallback<HardDiskService>(this, &HardDiskService::handleInstall)));

		options.addOption(
			Option("clear", "c", "Clears registry entries from the host system.")
			.required(false)
			.repeatable(false)
			.callback(OptionCallback<HardDiskService>(this, &HardDiskService::handleUninstall)));
	}
	
	/*
	==================
	void HardDiskService::handleHelp(const std::string& name, const std::string& value)
	==================
	*/
	void HardDiskService::handleHelp(const std::string& name, const std::string& value) {
		m_HelpRequested = true;
		displayHelp();
		stopOptionsProcessing();
	}
	
	/*
	==================
	void HardDiskService::displayHelp()
	==================
	*/
	void HardDiskService::displayHelp() {
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("A 'Should Have Already Existed Program' that will auto-mount VHD images on startup.");
		helpFormatter.format(std::cout);
	}

	/*
	==================
	void HardDiskService::handleInstall(const std::string& name, const std::string& value)
	==================
	*/
	void HardDiskService::handleInstall(const std::string& name, const std::string& value) {
		m_HelpRequested = true; // not really help but dont want to continue all the same
		m_Registry.WriteRegistry(value.c_str());
		stopOptionsProcessing();
	}

	/*
	==================
	void HardDiskService::handleUninstall(const std::string& name, const std::string& value)
	==================
	*/
	void HardDiskService::handleUninstall(const std::string& name, const std::string& value) {
		m_HelpRequested = true; // not really help but dont want to continue all the same
		m_Registry.ClearRegistry();
		stopOptionsProcessing();
	}
	
	/*
	==================
	int HardDiskService::main(const ArgVec& args)
	==================
	*/
	int HardDiskService::main(const ArgVec& args) {
		//if (!m_HelpRequested && config().getBool("application.runAsService", false)) {
		if (!m_HelpRequested) {
			if (!m_Registry.ReadRegistry()) {
				logger().error("Unable to read registry entry!");
				return Application::EXIT_OSERR;
			}

			m_HDDLIst.Read(m_Registry.GetDriveListLocation());

			for (unsigned int i = 0; i < m_HDDLIst.GetPaths()->size(); i++) {
				VirtualHDD CurrentHDD(m_HDDLIst.GetPaths()->at(i).absolute().toString().c_str());

				if (!CurrentHDD.Init()) {
					logger().error("Unable to open VHD: %s", m_HDDLIst.GetPaths()->at(i).absolute().toString().c_str());
				}

				if (!CurrentHDD.Attatch()) {
					logger().error("Unable to mount VHD: %s", m_HDDLIst.GetPaths()->at(i).absolute().toString().c_str());
					continue;
				}

			}

			waitForTerminationRequest();
		}
		return Application::EXIT_OK;
	}

	/*
	==================
	HardDiskService::~HardDiskService()
	==================
	*/
	HardDiskService::~HardDiskService() {

	}

}