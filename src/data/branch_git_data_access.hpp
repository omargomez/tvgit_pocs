#pragma once

#include <vector>

#include "branch_data_access.hpp"
#include "root_repo.hpp"

class BranchGitDataAccess final : public BranchDataAccess
{
public:
    BranchGitDataAccess(const RootRepo &repo) : _repo(repo) {}

    std::vector<BranchEntry> get_branches() const override;

private:
    RootRepo _repo;
};
