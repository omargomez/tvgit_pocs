#include "branch_git_data_access.hpp"

#include <git2pp.h>

#include "libgit_util.hpp"

std::vector<BranchEntry> BranchGitDataAccess::get_branches() const
{
    git2pp::Session session;
    const GitRepositoryPtr repo = GitRepository::open_ext(_repo.path);
    const GitBranchIteratorPtr iterator = GitBranch::git_branch_iterator_new(repo, GIT_BRANCH_LOCAL);

    std::vector<BranchEntry> branches;
    while (auto entry = GitBranch::git_branch_next(iterator)) {
        branches.emplace_back("", GitBranch::git_branch_name(entry->first));
    }

    return branches;
}
