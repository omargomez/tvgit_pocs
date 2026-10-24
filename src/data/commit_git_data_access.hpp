#pragma once

#include <vector>

#include "commit_data_access.hpp"
#include "root_repo.hpp"

class CommitGitDataAccess final : public CommitDataAccess
{
public:
    CommitGitDataAccess(const RootRepo &repo, const BranchEntry &parent_branch) :
        CommitDataAccess(repo, parent_branch)
    {
    }

    std::vector<CommitItem> get_commits() const override;
};
