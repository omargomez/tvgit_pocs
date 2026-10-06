#include "commit_json_data_access.hpp"

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "commit_item.hpp"
#include "util.hpp"

std::vector<CommitItem> CommitJsonDataAccess::get_commits() const
{
    const std::string commit_json = get_config_file_content("commits.json");
    const nlohmann::json parsed = nlohmann::json::parse(commit_json);

    std::vector<CommitItem> commits;
    commits.reserve(parsed.size());

    for (const auto& item : parsed) {
        commits.push_back(map_commit_item(item));
    }

    return commits;
}
