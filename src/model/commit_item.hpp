#pragma once

#include <string>
#include <utility>
#include <nlohmann/json.hpp>

class CommitItem
{
public:
    CommitItem(
        std::string commit_value = "",
        std::string author_value = "",
        std::string email_value = "",
        std::string date_value = "",
        std::string subject_value = ""
    ) :
        commit(std::move(commit_value)),
        author(std::move(author_value)),
        email(std::move(email_value)),
        date(std::move(date_value)),
        subject(std::move(subject_value))
    {
    }

    std::string commit;
    std::string author;
    std::string email;
    std::string date;
    std::string subject;
};

CommitItem map_commit_item(const nlohmann::json& value);
