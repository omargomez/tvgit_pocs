#include "data_access_factory.hpp"

#include "branch_data_access.hpp"
#include "branch_json_data_access.hpp"
#include "commit_data_access.hpp"
#include "commit_json_data_access.hpp"
#include "commit_git_data_access.hpp"
#include "root_repo_data_access.hpp"
#include "root_repo_json_data_acces.hpp"
#include "root_repo.hpp"
#include <branch_git_data_access.hpp>

std::unique_ptr<BranchDataAccess>  DataAccessFactory::create_branch_data_access(const RootRepo &repo)
{
    return std::make_unique<BranchGitDataAccess>(repo);
}

std::unique_ptr<CommitDataAccess> DataAccessFactory::create_commit_data_access(const RootRepo &repo, const BranchEntry &parent_branch)
{
    return std::make_unique<CommitGitDataAccess>(repo, parent_branch);
}

std::unique_ptr<RootRepoDataAccess> DataAccessFactory::create_root_repo_data_access()
{
    return std::make_unique<RootRepoJsonDataAccess>();
}
