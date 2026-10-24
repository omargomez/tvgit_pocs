#pragma once

#include <memory>

class RootRepoDataAccess;
class BranchDataAccess;
class CommitDataAccess;

class RootRepo;
class BranchEntry;

class DataAccessFactory
{
public:
    static std::unique_ptr<RootRepoDataAccess> create_root_repo_data_access();
    static std::unique_ptr<BranchDataAccess> create_branch_data_access(const RootRepo &repo);
    static std::unique_ptr<CommitDataAccess> create_commit_data_access(const RootRepo &repo, const BranchEntry &parent_branch);
};
