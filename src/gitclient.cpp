#include <filesystem>
#include <iostream>
#include <string>

#include "libgit_util.hpp"

std::string get_repository_name(git_repository * repo) {
    const char * workdir = git_repository_workdir(repo);
    if (!workdir) {
        return std::filesystem::path{git_repository_path(repo)}.filename();
    }
    return std::filesystem::path{workdir}.filename();
}

void print_head_name(const GitRepositoryPtr& repo) {
    GitReferencePtr head = GitRepository::git_repository_head(repo);
    std::cout << "HEAD: " << GitReference::git_reference_name(head) << "\n";
}

void list_commits_from_head(const GitRepositoryPtr& repo) {
    GitRevwalkPtr walk = GitRevwalk::git_revwalk_new(repo);
    GitRevwalk::git_revwalk_sorting(walk, GIT_SORT_TIME);
    GitRevwalk::git_revwalk_push_head(walk);

    while (auto id = GitRevwalk::git_revwalk_next(walk)) {
        GitCommitPtr commit = GitCommit::git_commit_lookup(repo, &*id);
        std::string message = GitCommit::git_commit_message(commit);
        std::cout << git_oid_tostr_s(&*id) << " "
                  << message.substr(0, message.find('\n')) << "\n";
    }
}

void branches(const GitRepositoryPtr& repo) {
    GitReferencePtr head = GitRepository::git_repository_head(repo);
    const std::string current = GitBranch::git_branch_name(head);

    GitBranchIteratorPtr iter = GitBranch::git_branch_iterator_new(repo, GIT_BRANCH_LOCAL);
    while (auto entry = GitBranch::git_branch_next(iter)) {
        const std::string name = GitBranch::git_branch_name(entry->first);
        std::cout << (name == current ? "* " : "  ") << name << "\n";
    }
}

int main(int argc, char * argv[]) {
    const char * path = argc > 1 ? argv[1] : ".";

    git_libgit2_init();

    try {
        GitRepositoryPtr repo = GitRepository::open_ext(path, GIT_REPOSITORY_OPEN_FROM_ENV);
        std::cout << "opened repository: " << get_repository_name(repo.get()) << "\n";
        // GitConfigPtr config = GitConfig::git_config_open_default();
        // std::cout << "user.name: " << GitConfig::git_config_get_string(config, "user.name") << "\n";
        // print_head_name(repo);
        // list_commits_from_head(repo);
        branches(repo);

    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
        git_libgit2_shutdown();
        return 1;
    }

    git_libgit2_shutdown();
    return 0;
}
