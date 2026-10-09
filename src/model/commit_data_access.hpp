#pragma once

#include <utility>
#include <vector>

#include "branch.hpp"
#include "commit_item.hpp"

class CommitDataAccess
{
public:
    CommitDataAccess(BranchEntry parent_branch_value = {}) :
        parent_branch(std::move(parent_branch_value))
    {
    }

    virtual ~CommitDataAccess() = 0;

    virtual std::vector<CommitItem> get_commits() const = 0;

    BranchEntry parent_branch;
};
