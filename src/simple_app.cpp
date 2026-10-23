/*---------------------------------------------------------*/
/*                                                         */
/*   Turbo Vision Hello World Demo Source File             */
/*                                                         */
/*---------------------------------------------------------*/
/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 */

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

class SimpleApp : public TApplication, 
    public BranchesDlgDelegate
{

public:

    SimpleApp();

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

SimpleApp::SimpleApp() :
    TProgInit( &SimpleApp::initStatusLine,
               &SimpleApp::initMenuBar,
               &SimpleApp::initDeskTop
                         ),
    model(DataAccessFactory::create_root_repo_data_access())
{
}

void SimpleApp::greetingBox()
{
    TDialog *d = new TDialog(TRect( 25, 5, 55, 16 ), "Hello, World!!" );

    d->insert( new TStaticText( TRect( 3, 5, 15, 6 ), "How are you?" ) );
    d->insert( new TButton( TRect( 16, 2, 28, 4 ), "Terrific", cmCancel, bfNormal ) );
    d->insert( new TButton( TRect( 16, 4, 28, 6 ), "Ok", cmCancel, bfNormal ) );
    d->insert( new TButton( TRect( 16, 6, 28, 8 ), "Lousy", cmCancel, bfNormal ) );
    d->insert( new TButton( TRect( 16, 8, 28, 10 ), "Cancel", cmCancel, bfNormal ) );

    deskTop->execView( d );
    destroy(d);
}

void SimpleApp::handleEvent( TEvent& event )
{
    TApplication::handleEvent( event );
    if( event.what == evCommand )
        {
        switch( event.message.command )
            {
            case GreetThemCmd:
                greetingBox();
                clearEvent( event );
                break;
            case RepoCommand:
                showBranches();
                clearEvent( event );
                break;
            default:
                break;
            }
        }
}

void SimpleApp::showBranches()
{
    auto anyRepo = model.root_repo_data_access.get_root_repos().front();
    auto win = (BranchesDlg *) validView( BranchesDlg::fromBranchRepository( anyRepo ) );
    if( win != 0 )
        {
        win->setDelegate( this );
        deskTop->insert( win );
        }
}

void SimpleApp::onBranchSelected(BranchesDlg *sender, const BranchEntry &branch)
{
    auto win = (CommitsDlg *) validView(new CommitsDlg(branch));
    // win->delegate = nullptr; // TODO: implement delegate for commits
    win->loadData();
    if( win != 0 )
        {
        // win->setDelegate( this );
        deskTop->insert( win );
        }
}

TMenuBar *SimpleApp::initMenuBar( TRect r )
{
    r.b.y = r.a.y+1;

    auto repos_submenu = SimpleApp::repos_menu();
    return new TMenuBar( r,
      *new TSubMenu( "~F~ile", kbAltF ) +
        *new TMenuItem( "E~x~it", cmQuit, cmQuit, hcNoContext, "Alt-X" ) +
    *repos_submenu
        );
}

TStatusLine *SimpleApp::initStatusLine( TRect r )
{
    r.a.y = r.b.y-1;
    return new TStatusLine( r,
        *new TStatusDef( 0, 0xFFFF ) +
            *new TStatusItem( "~Alt-X~ Exit", kbAltX, cmQuit ) +
            *new TStatusItem( 0, kbF10, cmMenu )
            );
}

TSubMenu *SimpleApp::repos_menu() {
    TSubMenu* result = new TSubMenu( "~R~epositories", kbAltR );
    
    auto repos = DataAccessFactory::create_root_repo_data_access().get_root_repos();
    for (const auto& r : repos) {
        *result + *new TMenuItem( r.name.c_str(), RepoCommand, kbNoKey );
    }
    
    return result;
}

int main()
{
    SimpleApp helloWorld;
    
    helloWorld.run();
    return 0;
}
