#pragma once

#include <memory>

class RootRepoDataAccess;
class RootRepoJsonDataAccess;
class BranchDataAccess;
class BranchJsonDataAccess;

class RootRepo;

class DataAccessFactory
{
public:
    static RootRepoDataAccess& create_root_repo_data_access();
    static RootRepoJsonDataAccess& create_root_repo_json_data_access();
    static std::unique_ptr<BranchDataAccess> create_branch_data_access(const RootRepo &repo);
    static std::unique_ptr<BranchDataAccess> create_branch_json_data_access(const RootRepo &repo);
};
