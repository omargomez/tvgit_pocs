#pragma once

#define Uses_TDialog
#define Uses_TRect
#define Uses_TSortedListBox
#define Uses_TEvent
#include <tvision/tv.h>
#include <vector>
#include <memory>
#include "branch.hpp"
#include "root_repo.hpp"
#include "branch_data_access.hpp"

class BranchesDlg;

class BranchesDlgDelegate
{
public:
    virtual ~BranchesDlgDelegate() = default;

    virtual void onBranchSelected(BranchesDlg *sender, const BranchEntry &branch) = 0;
};

class BranchesDlg : public TDialog
{
public:
    BranchesDlg( const TRect& bounds, const char *aTitle, short aNumber );

    BranchesDlg(const RootRepo &repo);
    
    virtual void handleEvent( TEvent& event ) {
        if (event.what == evKeyDown && event.keyDown.keyCode == kbEnter) {
            // Open commit info
            if (_delegate != nullptr && branchListBox->focused >= 0 &&
                branchListBox->focused < (short)_branchVector.size()) {
                _delegate->onBranchSelected(this, _branchVector[branchListBox->focused]);
            }
        }
        TDialog::handleEvent(event);
    }
    
    static BranchesDlg* fromBranchRepository(const RootRepo &repo);
    void setDelegate(BranchesDlgDelegate *delegate) { _delegate = delegate; }
    void loadDataFromRepository() {
        auto branches = _branchDataAccess->get_branches();
        setBranches(branches);
    }

private:
    
    std::vector<BranchEntry> _branchVector;
    TListBox *branchListBox;
    RootRepo _repo;
    std::unique_ptr<BranchDataAccess> _branchDataAccess;
    BranchesDlgDelegate *_delegate = nullptr;
    
    void setBranches(const std::vector<BranchEntry> branches);
    void addChildren();

};
