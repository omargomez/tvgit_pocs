#pragma once

#include <vector>

#include "branch.hpp"
#include "commit_data_access.hpp"

class CommitJsonDataAccess final : public CommitDataAccess
{
public:
    CommitJsonDataAccess(const BranchEntry &parent_branch) :
        CommitDataAccess(parent_branch)
    {
    }

    std::vector<CommitItem> get_commits() const override;
};
