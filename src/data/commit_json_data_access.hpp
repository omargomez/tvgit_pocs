#pragma once

#include <vector>

#include "branch.hpp"
#include "commit_data_access.hpp"
#include "root_repo.hpp"

class CommitJsonDataAccess final : public CommitDataAccess
{
public:
    CommitJsonDataAccess(const RootRepo &repo, const BranchEntry &parent_branch) :
        CommitDataAccess(repo, parent_branch)
    {
    }

    std::vector<CommitItem> get_commits() const override;
};
