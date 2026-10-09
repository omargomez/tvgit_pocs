#include "commit_item.hpp"

CommitItem map_commit_item(const nlohmann::json& value)
{
    CommitItem item;
    item.commit = value.at("commit").get<std::string>();
    item.author = value.at("author").get<std::string>();
    item.email = value.at("email").get<std::string>();
    item.date = value.at("date").get<std::string>();
    item.subject = value.at("subject").get<std::string>();
    return item;
}
