#define Uses_TDialog
#define Uses_TRect
#define Uses_TKeys
#define Uses_TStringCollection
#include <tvision/tv.h>

#include "branches_dlg.hpp"
#include "util.hpp"
#include "data_access_factory.hpp"
#include "str_collection.hpp"

BranchesDlg* BranchesDlg::fromBranchRepository(const RootRepo &repo) {
    auto result = new BranchesDlg(repo);
    result->loadDataFromRepository();
    return result;
}

BranchesDlg::BranchesDlg( const TRect& bounds, const char *aTitle, short aNumber ) :
    TWindowInit(&TDialog::initFrame),
    TDialog( bounds, aTitle)
    // TODO _repo
{
    addChildren();
}

BranchesDlg::BranchesDlg(const RootRepo &repo) :
    TWindowInit(&TDialog::initFrame),
    TDialog( TRect( 5, 3, 75, 20 ), "Branches"),
    _repo(repo),
    _branchDataAccess(DataAccessFactory::create_branch_data_access(repo))
{
    addChildren();
}

void BranchesDlg::setBranches(const std::vector<BranchEntry> branches) {
    _branchVector = std::move(branches);
    auto list = new TStrCollection(100, 20);
    for (auto &item : _branchVector) {
        list->insert( newStr(item.branch) );
    }
    branchListBox->newList(list);
}

void BranchesDlg::addChildren() {
    TRect viewBounds = getClipRect();
    viewBounds.grow( -1, -1 );
    branchListBox = new TListBox(viewBounds, 1, 0);
    branchListBox->growMode = gfGrowHiX | gfGrowHiY; // make size follow window's
    branchListBox->options = branchListBox->options | ofFramed;
    insert( branchListBox );
}