#include "util.hpp"

#include <cstdlib>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <nlohmann/json.hpp>

// TODO: using json = nlohmann::json;

std::filesystem::path get_app_config_path() {
    if (const char* home = std::getenv("HOME"); home != nullptr && *home != '\0') {
        return std::filesystem::path(home) / ".gitvision";
    }

#ifdef _WIN32
    if (const char* userProfile = std::getenv("USERPROFILE");
        userProfile != nullptr && *userProfile != '\0') {
        return std::filesystem::path(userProfile) / ".gitvision";
    }

    const char* homeDrive = std::getenv("HOMEDRIVE");
    const char* homePath = std::getenv("HOMEPATH");
    if (homeDrive != nullptr && *homeDrive != '\0' && homePath != nullptr && *homePath != '\0') {
        return std::filesystem::path(std::string(homeDrive) + homePath) / ".gitvision";
    }
#endif

    // TODO: Use same path as exec
    throw std::runtime_error("Unable to determine the home directory path.");
}

std::string get_config_file_content(const std::string& config_file_name) {
    const std::filesystem::path config_file_path = get_app_config_path() / config_file_name;

    std::ifstream config_file(config_file_path, std::ios::in | std::ios::binary);
    if (!config_file.is_open()) {
        throw std::runtime_error("Unable to open config file: " + config_file_path.string());
    }

    // TODO: make sure is utf8
    return std::string(std::istreambuf_iterator<char>(config_file), std::istreambuf_iterator<char>());
}

std::vector<std::string> get_repo_list() {
    auto repo_str = get_config_file_content("repo_list.json");
    nlohmann::json parsed = nlohmann::json::parse(repo_str);
    return parsed.get<std::vector<std::string>>();
}
