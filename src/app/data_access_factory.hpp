#pragma once

#include <memory>

class RootRepoDataAccess;
class RootRepoJsonDataAccess;
class BranchDataAccess;
class BranchJsonDataAccess;
class CommitDataAccess;
class CommitJsonDataAccess;

class RootRepo;
class BranchEntry;

class DataAccessFactory
{
public:
    static RootRepoDataAccess& create_root_repo_data_access();
    static RootRepoJsonDataAccess& create_root_repo_json_data_access();
    static std::unique_ptr<BranchDataAccess> create_branch_data_access(const RootRepo &repo);
    static std::unique_ptr<BranchDataAccess> create_branch_json_data_access(const RootRepo &repo);
    static std::unique_ptr<CommitDataAccess> create_commit_data_access(const BranchEntry &parent_branch);
    static std::unique_ptr<CommitDataAccess> create_commit_json_data_access(const BranchEntry &parent_branch);
};
