#pragma once

#define Uses_TKeys
#define Uses_TApplication
#define Uses_TEvent
#define Uses_TRect
#define Uses_TDialog
#define Uses_TStaticText
#define Uses_TButton
#define Uses_TMenuBar
#define Uses_TSubMenu
#define Uses_TMenuItem
#define Uses_TStatusLine
#define Uses_TStatusItem
#define Uses_TStatusDef
#define Uses_TDeskTop
#include <tvision/tv.h>

#include "branches_dlg.hpp"
#include "commits_dlg.hpp"
#include "app_model.hpp"
#include "data_access_factory.hpp"

// Libgit
const int GreetThemCmd = 100;
const int RepoCommand = 102;

class TVGitApp : public TApplication, 
    public BranchesDlgDelegate
{

public:

    TVGitApp();

    virtual void handleEvent( TEvent& event ) override;
    static TMenuBar *initMenuBar( TRect );
    static TStatusLine *initStatusLine( TRect );

    void onBranchSelected(BranchesDlg *sender, const BranchEntry &branch) override;

private:
    AppModel model;

    void greetingBox();
    static TSubMenu *repos_menu();
    void showBranches();
};