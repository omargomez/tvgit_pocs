#pragma once

#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>

#include <git2.h>

struct GitRepositoryDeleter {
    void operator()(git_repository * repo) const {
        git_repository_free(repo);
    }
};

using GitRepositoryPtr = std::unique_ptr<git_repository, GitRepositoryDeleter>;

struct GitConfigDeleter {
    void operator()(git_config * config) const {
        git_config_free(config);
    }
};

using GitConfigPtr = std::unique_ptr<git_config, GitConfigDeleter>;

struct GitReferenceDeleter {
    void operator()(git_reference * ref) const {
        git_reference_free(ref);
    }
};

using GitReferencePtr = std::unique_ptr<git_reference, GitReferenceDeleter>;

class GitRepository {
public:
    static GitRepositoryPtr open_ext(const std::string& path,
                                     unsigned flags = 0,
                                     const char * ceiling_dirs = nullptr) {
        git_repository * repo = nullptr;
        int rc = git_repository_open_ext(&repo, path.c_str(), flags, ceiling_dirs);
        if (rc < 0) {
            throw std::runtime_error{"failed to open repository at '" + path + "': " +
                                     git_error_last()->message};
        }
        return GitRepositoryPtr{repo};
    }

    static GitConfigPtr git_repository_config(const GitRepositoryPtr& repo) {
        git_config * config = nullptr;
        int rc = ::git_repository_config(&config, repo.get());
        if (rc < 0) {
            throw std::runtime_error{std::string{"failed to get repository config: "} +
                                     git_error_last()->message};
        }
        return GitConfigPtr{config};
    }

    static GitReferencePtr git_repository_head(const GitRepositoryPtr& repo) {
        git_reference * ref = nullptr;
        int rc = ::git_repository_head(&ref, repo.get());
        if (rc < 0) {
            throw std::runtime_error{std::string{"failed to get repository HEAD: "} +
                                     git_error_last()->message};
        }
        return GitReferencePtr{ref};
    }
};

class GitReference {
public:
    static std::string git_reference_name(const GitReferencePtr& ref) {
        return ::git_reference_name(ref.get());
    }
};

class GitConfig {
public:
    static GitConfigPtr git_config_open_default() {
        git_config * config = nullptr;
        int rc = ::git_config_open_default(&config);
        if (rc < 0) {
            throw std::runtime_error{std::string{"failed to open default config: "} +
                                     git_error_last()->message};
        }
        return GitConfigPtr{config};
    }

    static GitConfigPtr git_config_open_ondisk(const std::string& path) {
        git_config * config = nullptr;
        int rc = ::git_config_open_ondisk(&config, path.c_str());
        if (rc < 0) {
            throw std::runtime_error{"failed to open config file '" + path + "': " +
                                     git_error_last()->message};
        }
        return GitConfigPtr{config};
    }

    static GitConfigPtr git_config_open_level(const GitConfigPtr& parent, git_config_level_t level) {
        git_config * config = nullptr;
        int rc = ::git_config_open_level(&config, parent.get(), level);
        if (rc < 0) {
            throw std::runtime_error{std::string{"failed to open config level: "} +
                                     git_error_last()->message};
        }
        return GitConfigPtr{config};
    }

    static GitConfigPtr git_config_open_global(const GitConfigPtr& config) {
        git_config * global = nullptr;
        int rc = ::git_config_open_global(&global, config.get());
        if (rc < 0) {
            throw std::runtime_error{std::string{"failed to open global config: "} +
                                     git_error_last()->message};
        }
        return GitConfigPtr{global};
    }

    static std::string git_config_get_string(const GitConfigPtr& config, const std::string& name) {
        const char * value = nullptr;
        int rc = ::git_config_get_string(&value, config.get(), name.c_str());
        if (rc < 0) {
            throw std::runtime_error{"failed to get config entry '" + name + "': " +
                                     git_error_last()->message};
        }
        return value;
    }
};

struct GitCommitDeleter {
    void operator()(git_commit * commit) const {
        git_commit_free(commit);
    }
};

using GitCommitPtr = std::unique_ptr<git_commit, GitCommitDeleter>;

class GitCommit {
public:
    static GitCommitPtr git_commit_lookup(const GitRepositoryPtr& repo, const git_oid * id) {
        git_commit * commit = nullptr;
        int rc = ::git_commit_lookup(&commit, repo.get(), id);
        if (rc < 0) {
            throw std::runtime_error{std::string{"failed to lookup commit: "} +
                                     git_error_last()->message};
        }
        return GitCommitPtr{commit};
    }

    static std::string git_commit_message(const GitCommitPtr& commit) {
        return ::git_commit_message(commit.get());
    }
};

struct GitRevwalkDeleter {
    void operator()(git_revwalk * walk) const {
        git_revwalk_free(walk);
    }
};

using GitRevwalkPtr = std::unique_ptr<git_revwalk, GitRevwalkDeleter>;

class GitRevwalk {
public:
    static GitRevwalkPtr git_revwalk_new(const GitRepositoryPtr& repo) {
        git_revwalk * walk = nullptr;
        int rc = ::git_revwalk_new(&walk, repo.get());
        if (rc < 0) {
            throw std::runtime_error{std::string{"failed to create revwalk: "} +
                                     git_error_last()->message};
        }
        return GitRevwalkPtr{walk};
    }

    static void git_revwalk_push_head(const GitRevwalkPtr& walk) {
        int rc = ::git_revwalk_push_head(walk.get());
        if (rc < 0) {
            throw std::runtime_error{std::string{"failed to push HEAD to revwalk: "} +
                                     git_error_last()->message};
        }
    }

    static void git_revwalk_sorting(const GitRevwalkPtr& walk, unsigned int sort_mode) {
        ::git_revwalk_sorting(walk.get(), sort_mode);
    }

    static std::optional<git_oid> git_revwalk_next(const GitRevwalkPtr& walk) {
        git_oid id;
        int rc = ::git_revwalk_next(&id, walk.get());
        if (rc == GIT_ITEROVER) {
            return std::nullopt;
        }
        if (rc < 0) {
            throw std::runtime_error{std::string{"revwalk iteration failed: "} +
                                     git_error_last()->message};
        }
        return id;
    }
};

struct GitBranchIteratorDeleter {
    void operator()(git_branch_iterator * iter) const {
        git_branch_iterator_free(iter);
    }
};

using GitBranchIteratorPtr = std::unique_ptr<git_branch_iterator, GitBranchIteratorDeleter>;

class GitBranch {
public:
    static GitBranchIteratorPtr git_branch_iterator_new(const GitRepositoryPtr& repo,
                                                        git_branch_t list_flags) {
        git_branch_iterator * iter = nullptr;
        int rc = ::git_branch_iterator_new(&iter, repo.get(), list_flags);
        if (rc < 0) {
            throw std::runtime_error{std::string{"failed to create branch iterator: "} +
                                     git_error_last()->message};
        }
        return GitBranchIteratorPtr{iter};
    }

    static std::optional<std::pair<GitReferencePtr, git_branch_t>>
    git_branch_next(const GitBranchIteratorPtr& iter) {
        git_reference * ref = nullptr;
        git_branch_t type;
        int rc = ::git_branch_next(&ref, &type, iter.get());
        if (rc == GIT_ITEROVER) {
            return std::nullopt;
        }
        if (rc < 0) {
            throw std::runtime_error{std::string{"branch iteration failed: "} +
                                     git_error_last()->message};
        }
        return std::pair{GitReferencePtr{ref}, type};
    }

    static std::string git_branch_name(const GitReferencePtr& ref) {
        const char * name = nullptr;
        int rc = ::git_branch_name(&name, ref.get());
        if (rc < 0) {
            throw std::runtime_error{std::string{"failed to get branch name: "} +
                                     git_error_last()->message};
        }
        return name;
    }
};
