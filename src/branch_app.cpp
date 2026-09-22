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
#define Uses_TWindow
#define Uses_TView
#define Uses_TDrawBuffer
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
#define Uses_TListBox
#define Uses_TListDialog
#define Uses_TSortedListBox
#define Uses_TStringCollection
#include <tvision/tv.h>
#include <iostream>
#include "common/util.hpp"
#include "model/branch.hpp"
#include "model/commit.hpp"

// Libgit
#include <git2.h>
#include <git2pp.h>

const int GreetThemCmd = 100;
const int myEntryCommand = 101;
const int RepoCommand = 102;

class HelloView : public TView
{
public:
    HelloView( const TRect& bounds ) :
        TView( bounds )
    {
        growMode = gfGrowHiX | gfGrowHiY; // make size follow window's
        options = options | ofFramed;
    }

    virtual void draw()
    {
        const char *hstr = "Hello World!";
        ushort color = getColor (0x0301);
        TView::draw ();
        TDrawBuffer b;
        b.moveStr ( 0, hstr, color );
        writeLine ( 4, 2, 12, 1, b) ;
    }
};

class HelloWin : public TWindow
{
public:
    HelloWin( const TRect& bounds, const char *aTitle, short aNumber ) :
        TWindowInit( TWindow::initFrame ),
        TWindow( bounds, aTitle, aNumber )
    {
        addChildren();
    }

    HelloWin() :
        TWindowInit( TWindow::initFrame ),
        TWindow( TRect( 5, 3, 75, 20 ), "Commits", 0 )
    {
        addChildren();
    }
    
private:
    
    void addChildren() {
        TRect viewBounds = getClipRect();
        viewBounds.grow( -1, -1 );
        insert( new HelloView( viewBounds ) );
    }
};

#define _cpBlueWindow \
    "\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f"\
    "\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f"
#define _cpCyanWindow \
    "\x10\x11\x12\x13\x14\x15\x16\x17\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f"\
    "\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f"
#define _cpGrayWindow \
    "\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F"\
    "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F"

class ListDemoWin : public TWindow
{
public:
    ListDemoWin( const TRect& bounds, const char *aTitle, short aNumber ) :
    TWindowInit( &TWindow::initFrame ),
    TWindow( bounds, aTitle, aNumber )
    {
        addChildren();
    }
    
    ListDemoWin() :
    TWindowInit( TWindow::initFrame ),
    TWindow( TRect( 5, 3, 75, 20 ), "Commits", 0 )
    {
        addChildren();
    }
    virtual TPalette& getPalette() const {
        static TPalette blue( _cpBlueWindow, sizeof( _cpBlueWindow )-1 );
        static TPalette cyan( _cpCyanWindow, sizeof( _cpCyanWindow )-1 );
        static TPalette gray( _cpGrayWindow, sizeof( _cpGrayWindow )-1 );
        static TPalette *palettes[] =
            {
            &blue,
            &cyan,
            &gray
            };
        return *(palettes[palette]);

    }

private:
    
    void addChildren() {
        TRect viewBounds = getClipRect();
        viewBounds.grow( -1, -1 );
        auto listBox = new TSortedListBox(viewBounds, 1, 0);
        listBox->growMode = gfGrowHiX | gfGrowHiY; // make size follow window's
        listBox->options = listBox->options | ofFramed;
        auto list = new TStringCollection(100, 20);
        list->insert( newStr("One") );
        list->insert( newStr("Two") );
        list->insert( newStr("3") );
        list->insert( newStr("1️⃣") );
        list->insert( newStr("🤗") );
        listBox->newList(list);
        insert( listBox );
    }
    
};

class ListDemoDlg : public TDialog
{
public:
    ListDemoDlg( const TRect& bounds, const char *aTitle, short aNumber ) :
        TWindowInit(&TDialog::initFrame),
        TDialog( bounds, aTitle)
    {
        addChildren();
    }

    ListDemoDlg() :
    TWindowInit(&TDialog::initFrame),
    TDialog( TRect( 5, 3, 75, 20 ), "Branches")
    {
        addChildren();
    }
    
    static ListDemoDlg* fromBranchRepository() {
        auto branches = get_branch_list();
        auto result = new ListDemoDlg();
        result->setBranches(branches);
        return result;
    }
    
private:
    
    std::vector<BranchEntry> _branchVector;
    TSortedListBox *branchListBox;
    
    void setBranches(const std::vector<BranchEntry> branches) {
        _branchVector = std::move(branches);
        auto list = new TStringCollection(100, 20);
        for (auto &item : _branchVector) {
            list->insert( newStr(item.branch) );
        }
        branchListBox->newList(list);
    }
    
    void addChildren() {
        TRect viewBounds = getClipRect();
        viewBounds.grow( -1, -1 );
        branchListBox = new TSortedListBox(viewBounds, 1, 0);
        branchListBox->growMode = gfGrowHiX | gfGrowHiY; // make size follow window's
        branchListBox->options = branchListBox->options | ofFramed;
        insert( branchListBox );
    }
};


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
    void showCommits();
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

void THelloApp::showCommits()
{
    TView *win = validView( ListDemoDlg::fromBranchRepository() );
    if( win != 0 )
        deskTop->insert( win );
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
            case RepoCommand:
                showCommits();
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

int main()
{
#if 0
    auto branches = get_branch_list();
    for (const auto& item : branches) {
        std::cout << item.branch << "\n";
    }
    
    return 0;
#endif
    
    
    THelloApp helloWorld;
    
    helloWorld.run();
    
    
    return 0;
}
