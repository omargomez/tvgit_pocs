#pragma once

#define Uses_TDialog
#define Uses_TRect
#define Uses_TListBox
#include <tvision/tv.h>
#include <memory>
#include <vector>
#include "branch.hpp"
#include "commit_data_access.hpp"
#include "commit_item.hpp"
#include "root_repo.hpp"

class CommitsDlg : public TDialog
{
public:
    CommitsDlg( const TRect& bounds, const char *aTitle );

    CommitsDlg(const RootRepo &repo, const BranchEntry &parent_branch);

    const RootRepo& repo() const { return _repo; }

    void loadData() {
        auto commits = _commitDataAccess->get_commits();
        setCommits(commits);
    }

private:

    std::vector<CommitItem> _commitVector;
    TListBox *commitListBox;
    RootRepo _repo;
    BranchEntry _parentBranch;
    std::unique_ptr<CommitDataAccess> _commitDataAccess;

    void setCommits(const std::vector<CommitItem> commits);
    void addChildren();

};
