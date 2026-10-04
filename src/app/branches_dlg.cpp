#define Uses_TDialog
#define Uses_TRect
#define Uses_TKeys
#define Uses_TStringCollection
#include <tvision/tv.h>

#include "branches_dlg.hpp"
#include "util.hpp"

BranchesDlg::BranchesDlg( const TRect& bounds, const char *aTitle, short aNumber ) :
    TWindowInit(&TDialog::initFrame),
    TDialog( bounds, aTitle)
{
    addChildren();
}

BranchesDlg::BranchesDlg() :
    TWindowInit(&TDialog::initFrame),
    TDialog( TRect( 5, 3, 75, 20 ), "Branches")
{
    addChildren();
}

BranchesDlg* BranchesDlg::fromBranchRepository() {
    auto branches = get_branch_list();
    auto result = new BranchesDlg();
    result->setBranches(branches);
    return result;
}

void BranchesDlg::setBranches(const std::vector<BranchEntry> branches) {
    _branchVector = std::move(branches);
    auto list = new TStringCollection(100, 20);
    for (auto &item : _branchVector) {
        list->insert( newStr(item.branch) );
    }
    branchListBox->newList(list);
}

void BranchesDlg::addChildren() {
    TRect viewBounds = getClipRect();
    viewBounds.grow( -1, -1 );
    branchListBox = new TSortedListBox(viewBounds, 1, 0);
    branchListBox->growMode = gfGrowHiX | gfGrowHiY; // make size follow window's
    branchListBox->options = branchListBox->options | ofFramed;
    insert( branchListBox );
}