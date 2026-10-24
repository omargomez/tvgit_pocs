#pragma once

#include <utility>
#include <vector>

#include "branch.hpp"
#include "commit_item.hpp"
#include "root_repo.hpp"

class CommitDataAccess
{
public:
    CommitDataAccess(RootRepo root_repo_value = RootRepo{}, BranchEntry parent_branch_value = {}) :
        root_repo(std::move(root_repo_value)),
        parent_branch(std::move(parent_branch_value))
    {
    }

    virtual ~CommitDataAccess() = 0;

    virtual std::vector<CommitItem> get_commits() const = 0;

    RootRepo root_repo;
    BranchEntry parent_branch;
};
