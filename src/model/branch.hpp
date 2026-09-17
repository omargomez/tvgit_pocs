#pragma once

#include <string>
#include <utility>
#include <nlohmann/json.hpp>

class BranchEntry
{
public:
    BranchEntry(
        std::string date_value = "",
        std::string branch_value = "",
        std::string author_value = "",
        std::string subject_value = ""
    ) :
        date(std::move(date_value)),
        branch(std::move(branch_value)),
        author(std::move(author_value)),
        subject(std::move(subject_value))
    {
    }

    std::string date;
    std::string branch;
    std::string author;
    std::string subject;
};

BranchEntry map_branch_entry(const nlohmann::json& value);
