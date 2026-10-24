#include "commit_git_data_access.hpp"

#include <ctime>

#include <git2pp.h>

#include "libgit_util.hpp"

namespace {

std::string format_date(git_time_t time)
{
    const std::time_t value = static_cast<std::time_t>(time);
    std::tm tm{};
    localtime_r(&value, &tm);

    char buffer[20];
    std::strftime(buffer, sizeof buffer, "%Y-%m-%d %H:%M:%S", &tm);
    return buffer;
}

} // namespace

std::vector<CommitItem> CommitGitDataAccess::get_commits() const
{
    git2pp::Session session;
    const GitRepositoryPtr repo = GitRepository::open_ext(root_repo.path);
    const GitRevwalkPtr walk = GitRevwalk::git_revwalk_new(repo);
    GitRevwalk::git_revwalk_sorting(walk, GIT_SORT_TIME);
    GitRevwalk::git_revwalk_push_ref(walk, "refs/heads/" + parent_branch.branch);

    std::vector<CommitItem> commits;
    while (auto id = GitRevwalk::git_revwalk_next(walk)) {
        const GitCommitPtr commit = GitCommit::git_commit_lookup(repo, &*id);
        commits.emplace_back(
            git_oid_tostr_s(&*id),
            GitCommit::git_commit_author_name(commit),
            GitCommit::git_commit_author_email(commit),
            format_date(GitCommit::git_commit_author_time(commit)),
            GitCommit::git_commit_summary(commit));
    }

    return commits;
}
