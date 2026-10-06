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

class BranchesDlg : public TDialog
{
public:
    BranchesDlg( const TRect& bounds, const char *aTitle, short aNumber );

    BranchesDlg(const RootRepo &repo);
    
    virtual void handleEvent( TEvent& event ) {
        if (event.what == evKeyDown && event.keyDown.keyCode == kbEnter) {
            // Open commit info
        }
        TDialog::handleEvent(event);
    }
    
    static BranchesDlg* fromBranchRepository(const RootRepo &repo);
    void loadDataFromRepository() {
        auto branches = _branchDataAccess->get_branches();
        setBranches(branches);
    }

private:
    
    std::vector<BranchEntry> _branchVector;
    TListBox *branchListBox;
    RootRepo _repo;
    std::unique_ptr<BranchDataAccess> _branchDataAccess;
    
    void setBranches(const std::vector<BranchEntry> branches);
    void addChildren();

};
