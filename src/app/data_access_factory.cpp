#include "data_access_factory.hpp"

#include "branch_data_access.hpp"
#include "branch_json_data_access.hpp"
#include "commit_data_access.hpp"
#include "commit_json_data_access.hpp"
#include "root_repo_data_access.hpp"
#include "root_repo_json_data_acces.hpp"
#include "root_repo.hpp"

std::unique_ptr<BranchDataAccess> DataAccessFactory::create_branch_json_data_access(const RootRepo &repo)
{
    return std::make_unique<BranchJsonDataAccess>(repo);
}

std::unique_ptr<BranchDataAccess>  DataAccessFactory::create_branch_data_access(const RootRepo &repo)
{
    return DataAccessFactory::create_branch_json_data_access(repo);
}

std::unique_ptr<CommitDataAccess> DataAccessFactory::create_commit_json_data_access(const BranchEntry &parent_branch)
{
    return std::make_unique<CommitJsonDataAccess>(parent_branch);
}

std::unique_ptr<CommitDataAccess> DataAccessFactory::create_commit_data_access(const BranchEntry &parent_branch)
{
    return DataAccessFactory::create_commit_json_data_access(parent_branch);
}

RootRepoJsonDataAccess& DataAccessFactory::create_root_repo_json_data_access()
{
    static RootRepoJsonDataAccess data_access;
    return data_access;
}

RootRepoDataAccess& DataAccessFactory::create_root_repo_data_access()
{
    return create_root_repo_json_data_access();
}
