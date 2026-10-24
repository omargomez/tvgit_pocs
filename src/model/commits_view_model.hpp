#pragma once

#include <memory>
#include <vector>

#include "commit_data_access.hpp"
#include "commit_item.hpp"
#include "branch.hpp"
#include "root_repo.hpp"

class CommitsViewModelDelegate
{
public:
    virtual ~CommitsViewModelDelegate() = 0;
};

class CommitsViewModel final
{
public:
    explicit CommitsViewModel(
        RootRepo root_repo_value,
        BranchEntry parent_branch_value,
        CommitsViewModelDelegate* delegate_value = nullptr
    );

    std::vector<CommitItem> get_commits() const;

    std::unique_ptr<CommitDataAccess> commit_data_access;
    CommitsViewModelDelegate* delegate;

private:
    RootRepo root_repo;
    BranchEntry parent_branch;
};
