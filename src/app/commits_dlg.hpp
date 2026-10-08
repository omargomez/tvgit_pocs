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

class CommitsDlg : public TDialog
{
public:
    CommitsDlg( const TRect& bounds, const char *aTitle );

    CommitsDlg(const BranchEntry &parent_branch);

    void loadData() {
        auto commits = _commitDataAccess->get_commits();
        setCommits(commits);
    }

private:

    std::vector<CommitItem> _commitVector;
    TListBox *commitListBox;
    BranchEntry _parentBranch;
    std::unique_ptr<CommitDataAccess> _commitDataAccess;

    void setCommits(const std::vector<CommitItem> commits);
    void addChildren();

};
