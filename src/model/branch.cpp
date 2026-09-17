#include "branch.hpp"

BranchEntry map_branch_entry(const nlohmann::json& value)
{
    BranchEntry entry;
    entry.date = value.at("date").get<std::string>();
    entry.branch = value.at("branch").get<std::string>();
    entry.author = value.at("author").get<std::string>();
    entry.subject = value.at("subject").get<std::string>();
    return entry;
}
