#define Uses_TDialog
#define Uses_TRect
#include <tvision/tv.h>

#include "commits_dlg.hpp"
#include "data_access_factory.hpp"
#include "str_collection.hpp"

CommitsDlg::CommitsDlg( const TRect& bounds, const char *aTitle ) :
    TWindowInit(&TDialog::initFrame),
    TDialog( bounds, aTitle ),
    _parentBranch(),
    _commitDataAccess(DataAccessFactory::create_commit_data_access(_parentBranch))
{
    addChildren();
}

CommitsDlg::CommitsDlg(const BranchEntry &parent_branch) :
    TWindowInit(&TDialog::initFrame),
    TDialog( TRect( 5, 3, 75, 20 ), "Commits" ),
    _parentBranch(parent_branch),
    _commitDataAccess(DataAccessFactory::create_commit_data_access(parent_branch))
{
    addChildren();
}

void CommitsDlg::setCommits(const std::vector<CommitItem> commits) {
    _commitVector = std::move(commits);
    auto list = new TStrCollection(100, 20);
    for (auto &item : _commitVector) {
        list->insert( newStr(item.messageLine()) );
    }
    commitListBox->newList(list);
}

void CommitsDlg::addChildren() {
    TRect viewBounds = getClipRect();
    viewBounds.grow( -1, -1 );
    commitListBox = new TListBox(viewBounds, 1, 0);
    commitListBox->growMode = gfGrowHiX | gfGrowHiY; // make size follow window's
    commitListBox->options = commitListBox->options | ofFramed;
    insert( commitListBox );
}
