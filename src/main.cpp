#include "main.hpp"
#include "storageParser.hpp"
#include "interface.hpp"

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0}; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
// other config tools such as config-utils don't use this config, so it can be removed if those are in use
Configuration& getConfig() {
    static Configuration config(modInfo);
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(CModInfo& info) {
    info.id = modInfo.id.c_str();
    info.version = modInfo.version.c_str();
    info.version_long = modInfo.versionLong;
	
    getConfig().Load();
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();
    SafeStorage::Parser::validateStorage();
    SafeStorage::Parser::findPath();

    getLogger().info("Initialized File Storage!");
}