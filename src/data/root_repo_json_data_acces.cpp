#include "root_repo_json_data_acces.hpp"

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "root_repo.hpp"
#include "util.hpp"

std::vector<RootRepo> RootRepoJsonDataAccess::get_root_repos() const
{
    const std::string repo_json = get_config_file_content("repo_list.json");
    const nlohmann::json parsed = nlohmann::json::parse(repo_json);

    std::vector<RootRepo> repos;
    repos.reserve(parsed.size());

    for (const auto& item : parsed) {
        repos.push_back(map_root_repo(item));
    }

    return repos;
}
