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
#include <iostream>
#include "common/util.hpp"

// Libgit
#include <git2.h>
#include <git2pp.h>

const int GreetThemCmd = 100;
const int myEntryCommand = 101;
const int RepoCommand = 102;

class THelloApp : public TApplication
{

public:

    THelloApp();

    virtual void handleEvent( TEvent& event );
    static TMenuBar *initMenuBar( TRect );
    static TStatusLine *initStatusLine( TRect );

private:

    void greetingBox();
    void myEntryBox();
    TSubMenu * hi();
    static TSubMenu *app_repos();
};

THelloApp::THelloApp() :
    TProgInit( &THelloApp::initStatusLine,
               &THelloApp::initMenuBar,
               &THelloApp::initDeskTop
             )
{
    
}

TSubMenu * THelloApp::hi() {
    return 0;
}

void THelloApp::greetingBox()
{
    TDialog *d = new TDialog(TRect( 25, 5, 55, 16 ), "Hello, World!" );

    d->insert( new TStaticText( TRect( 3, 5, 15, 6 ), "How are you?" ) );
    d->insert( new TButton( TRect( 16, 2, 28, 4 ), "Terrific", cmCancel, bfNormal ) );
    d->insert( new TButton( TRect( 16, 4, 28, 6 ), "Ok", cmCancel, bfNormal ) );
    d->insert( new TButton( TRect( 16, 6, 28, 8 ), "Lousy", cmCancel, bfNormal ) );
    d->insert( new TButton( TRect( 16, 8, 28, 10 ), "Cancel", cmCancel, bfNormal ) );

    deskTop->execView( d );
    destroy(d);
}

void THelloApp::myEntryBox()
{
    TDialog *d = new TDialog(TRect( 25, 7, 55, 16 ), "My Entry" );

    d->insert( new TStaticText( TRect( 3, 3, 20, 4 ), "My Message" ) );
    d->insert( new TButton( TRect( 10, 6, 20, 8 ), "Ok", cmOK, bfDefault ) );

    deskTop->execView( d );
    destroy(d);
}

void THelloApp::handleEvent( TEvent& event )
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
            case myEntryCommand:
                myEntryBox();
                clearEvent( event );
                break;
            default:
                break;
            }
        }
}

TMenuBar *THelloApp::initMenuBar( TRect r )
{
    r.b.y = r.a.y+1;

    auto repos_submenu = THelloApp::app_repos();
    return new TMenuBar( r,
      *new TSubMenu( "~F~ile", kbAltF ) +
        *new TMenuItem( "E~x~it", cmQuit, cmQuit, hcNoContext, "Alt-X" ) +
    *repos_submenu
        );

}

TSubMenu *THelloApp::app_repos() {
    TSubMenu* result = new TSubMenu( "~R~epositories", kbAltR );
    
    auto repos = get_repo_list();
    for (const auto& r : repos) {
        *result + *new TMenuItem( r, RepoCommand, kbNoKey );
    }
    
    return result;
}

TStatusLine *THelloApp::initStatusLine( TRect r )
{
    r.a.y = r.b.y-1;
    return new TStatusLine( r,
        *new TStatusDef( 0, 0xFFFF ) +
            *new TStatusItem( "~Alt-X~ Exit", kbAltX, cmQuit ) +
            *new TStatusItem( 0, kbF10, cmMenu )
            );
}

void show_commit(char const * shorthand) {
    git2pp::Session git2;

    auto repo = git2[git_repository_open_ext](".", 0, nullptr);
    auto master = repo[git_reference_dwim](shorthand);
    auto commit = master[git_reference_peel](GIT_OBJ_COMMIT).as<git_commit>();

    auto parent0 = commit[git_commit_parent](0);
    std::cout << shorthand << "^ = " << parent0[git_commit_id]() << "\n";
    std::cout << "author = " << parent0[git_commit_author]()->name << "\n";
    std::cout << "message = " << parent0[git_commit_message]() << "\n";

    auto revwalk = repo[git_revwalk_new]();
    revwalk[git_revwalk_sorting](GIT_SORT_TIME);
    revwalk[git_revwalk_push](commit[git_commit_id]());

    std::cout << "revs:\n";
    for (auto && oid : revwalk) {
        std::cout << "  " << &oid << "\n";
    }

    std::cout << "refs:\n";
    for (auto && ref : repo[git_reference_iterator_new]()) {
        std::cout << "  " << ref[git_reference_name]() << "\n";
    }

    std::cout << "branches:\n";
    for (auto && branch : repo[git_branch_iterator_new](GIT_BRANCH_ALL)) {
        std::cout << "  " << branch.ref[git_reference_name]() << (branch.type == GIT_BRANCH_LOCAL ? "" : " (remote)") << "\n";
    }

    std::cout << "config:\n";
    for (auto && config : repo[git_repository_config]()[git_config_iterator_new]()) {
        std::cout << "  " << config->name << " = " << config->value << "\n";
    }

    auto index = repo[git_repository_index]();

#if LIBGIT2PP_HAVE_INDEX_ITERATOR
    std::cout << "index:\n";
    for (auto && entry : index[git_index_iterator_new]()) {
        std::cout << "  " << entry->path << "\n";
    }
#endif

    std::cout << "index conflicts:\n";
    for (auto && conflict : index[git_index_conflict_iterator_new]()) {
        std::cout << "  " << conflict.ancestor << "\n";
    }

    char const * notes = "refs/notes/commits";
    try {
        std::cout << "notes:\n";
        for (auto && note : repo[git_note_iterator_new](notes)) {
            std::cout << "  " << &note.note_id << "\n";
        }
    } catch (std::exception const & e) {
        std::cerr << "  Error accessing " << notes << ": " << e.what() << "\n";
    }

    try {
        std::cout << "rebase:\n";
        auto upstream = repo[git_annotated_commit_from_ref](&*parent0.as<git_reference>());
        for (auto && op : repo[git_rebase_init](nullptr, &*upstream, nullptr, nullptr)) {
            std::cout << "  " << &op->id << "\n";
        }
    } catch (std::exception const & e) {
        // Too lazy to test this properly.
        std::cout << "  failure not unexpected: " << e.what() << "\n";
    }
}

int main()
{
    auto repos = get_repo_list();
    for (const auto& r : repos) {
            std::cout << r << '\n';
        }

//    return 0;
    
    
    THelloApp helloWorld;
    
    git2pp::Session git2;
    
    // show_commit("HEAD"); // Will fail
    helloWorld.run();
    return 0;
}
