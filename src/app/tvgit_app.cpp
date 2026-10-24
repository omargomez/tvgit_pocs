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

#include "tvgit_app.hpp"

TVGitApp::TVGitApp() :
    TProgInit( &TVGitApp::initStatusLine,
               &TVGitApp::initMenuBar,
               &TVGitApp::initDeskTop
                         ),
    model(DataAccessFactory::create_root_repo_data_access())
{
}

void TVGitApp::greetingBox()
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

void TVGitApp::handleEvent( TEvent& event )
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
            default:
                if( event.message.command >= RepoCommand )
                    {
                    auto repos = model.root_repo_data_access->get_root_repos();
                    size_t index = event.message.command - RepoCommand;
                    if( index < repos.size() )
                        {
                        showBranches( repos[index] );
                        clearEvent( event );
                        }
                    }
                break;
            }
        }
}

void TVGitApp::showBranches(const RootRepo &repo)
{
    auto win = (BranchesDlg *) validView( BranchesDlg::fromBranchRepository( repo ) );
    if( win != 0 )
        {
        win->setDelegate( this );
        deskTop->insert( win );
        }
}

void TVGitApp::onBranchSelected(BranchesDlg *sender, const BranchEntry &branch)
{
    auto win = (CommitsDlg *) validView(new CommitsDlg(sender->repo(), branch));
    // win->delegate = nullptr; // TODO: implement delegate for commits
    win->loadData();
    if( win != 0 )
        {
        // win->setDelegate( this );
        deskTop->insert( win );
        }
}

TMenuBar *TVGitApp::initMenuBar( TRect r )
{
    r.b.y = r.a.y+1;

    auto repos_submenu = TVGitApp::repos_menu();
    return new TMenuBar( r,
      *new TSubMenu( "~F~ile", kbAltF ) +
        *new TMenuItem( "E~x~it", cmQuit, cmQuit, hcNoContext, "Alt-X" ) +
    *repos_submenu
        );
}

TStatusLine *TVGitApp::initStatusLine( TRect r )
{
    r.a.y = r.b.y-1;
    return new TStatusLine( r,
        *new TStatusDef( 0, 0xFFFF ) +
            *new TStatusItem( "~Alt-X~ Exit", kbAltX, cmQuit ) +
            *new TStatusItem( 0, kbF10, cmMenu )
            );
}

TSubMenu *TVGitApp::repos_menu() {
    TSubMenu* result = new TSubMenu( "~R~epositories", kbAltR );
    
    auto repos = DataAccessFactory::create_root_repo_data_access()->get_root_repos();
    auto count = 0;
    for (const auto& r : repos) {
        *result + *new TMenuItem( r.name.c_str(), RepoCommand + count, kbNoKey );
        count++;
    }
    
    return result;
}
