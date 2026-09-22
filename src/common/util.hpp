#pragma once

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>
#include "../model/branch.hpp"

std::filesystem::path get_app_config_path();
std::string get_config_file_content(const std::string& config_file_name);
std::vector<std::string> get_repo_list();
std::vector<BranchEntry> get_branch_list();
