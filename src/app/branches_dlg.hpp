#pragma once

#define Uses_TDialog
#define Uses_TRect
#define Uses_TSortedListBox
#define Uses_TEvent
#include <tvision/tv.h>
#include <vector>
#include "branch.hpp"

class BranchesDlg : public TDialog
{
public:
    BranchesDlg( const TRect& bounds, const char *aTitle, short aNumber );

    BranchesDlg();
    
    virtual void handleEvent( TEvent& event ) {
        if (event.what == evKeyDown && event.keyDown.keyCode == kbEnter) {
            // Open commit info
        }
        TDialog::handleEvent(event);
    }
    
    static BranchesDlg* fromBranchRepository();

private:
    
    std::vector<BranchEntry> _branchVector;
    TSortedListBox *branchListBox;
    
    void setBranches(const std::vector<BranchEntry> branches);
    void addChildren();

};
