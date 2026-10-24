#include <iostream>
#include <vector>

#include "branch_git_data_access.hpp"
#include "root_repo.hpp"
#include "root_repo_json_data_acces.hpp"

std::vector<RootRepo> test_repos()
{
    RootRepoJsonDataAccess data_access;
    const auto repos = data_access.get_root_repos();

    for (const auto& repo : repos) {
        std::cout << "name: " << repo.name << ", path: " << repo.path << '\n';
    }

    return repos;
}

void test_branches(const RootRepo &repo)
{
    BranchGitDataAccess data_access(repo);
    const auto branches = data_access.get_branches();

    for (const auto& branch : branches) {
        std::cout << branch.branch << '\n';
    }
}

int main()
{
    const auto repos = test_repos();
    test_branches(repos.front());
    return 0;
}
