#include "data_access_factory.hpp"

#include "branch_data_access.hpp"
#include "branch_json_data_access.hpp"
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

RootRepoJsonDataAccess& DataAccessFactory::create_root_repo_json_data_access()
{
    static RootRepoJsonDataAccess data_access;
    return data_access;
}

RootRepoDataAccess& DataAccessFactory::create_root_repo_data_access()
{
    return create_root_repo_json_data_access();
}
