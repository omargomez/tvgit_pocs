#include "commit.hpp"

CommitEntry map_commit_entry(const nlohmann::json& value)
{
    CommitEntry entry;
    entry.commit = value.at("commit").get<std::string>();
    entry.author = value.at("author").get<std::string>();
    entry.author_email = value.at("author_email").get<std::string>();
    entry.date = value.at("date").get<std::string>();
    entry.message = value.at("message").get<std::string>();
    entry.epoch = value.at("epoch").get<std::int64_t>();

    if (value.contains("merge")) {
        entry.merge = value.at("merge").get<std::string>();
    }

    if (value.contains("epoch_utc") && !value.at("epoch_utc").is_null()) {
        entry.epoch_utc = value.at("epoch_utc").get<std::int64_t>();
    }

    return entry;
}
