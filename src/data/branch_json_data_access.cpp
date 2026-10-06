#include "branch_json_data_access.hpp"

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "branch.hpp"
#include "util.hpp"

std::vector<BranchEntry> BranchJsonDataAccess::get_branches() const
{
    const std::string branch_json = get_config_file_content("branches.json");
    const nlohmann::json parsed = nlohmann::json::parse(branch_json);

    std::vector<BranchEntry> branches;
    branches.reserve(parsed.size());

    for (const auto& item : parsed) {
        branches.push_back(map_branch_entry(item));
    }

    return branches;
}