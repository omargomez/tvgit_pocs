#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <utility>
#include <nlohmann/json.hpp>

class CommitEntry
{
public:
    CommitEntry(
        std::string commit_value = "",
        std::optional<std::string> merge_value = std::nullopt,
        std::string author_value = "",
        std::string author_email_value = "",
        std::string date_value = "",
        std::string message_value = "",
        std::int64_t epoch_value = 0,
        std::optional<std::int64_t> epoch_utc_value = std::nullopt
    ) :
        commit(std::move(commit_value)),
        merge(std::move(merge_value)),
        author(std::move(author_value)),
        author_email(std::move(author_email_value)),
        date(std::move(date_value)),
        message(std::move(message_value)),
        epoch(epoch_value),
        epoch_utc(epoch_utc_value)
    {
    }

    std::string commit;
    std::optional<std::string> merge;
    std::string author;
    std::string author_email;
    std::string date;
    std::string message;
    std::int64_t epoch {};
    std::optional<std::int64_t> epoch_utc;
};

CommitEntry map_commit_entry(const nlohmann::json& value);
