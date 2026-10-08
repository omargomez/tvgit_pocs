#pragma once

#include <memory>
#include <vector>

#include "commit_data_access.hpp"
#include "commit_item.hpp"
#include "branch.hpp"

class CommitsViewModelDelegate
{
public:
    virtual ~CommitsViewModelDelegate() = 0;
};

class CommitsViewModel final
{
public:
    explicit CommitsViewModel(
        BranchEntry parent_branch_value,
        CommitsViewModelDelegate* delegate_value = nullptr
    );

    std::vector<CommitItem> get_commits() const;

    std::unique_ptr<CommitDataAccess> commit_data_access;
    CommitsViewModelDelegate* delegate;

private:
    BranchEntry parent_branch;
};
