
///
/// @file
/// @brief The class CLaunchPadGenApp.
///
/// This is the implementation of the class CLaunchPadGenApp.
///
/// @b Interesting @b Bookmarks:
///
/// Please search for the following key word on the code to locate some interesting places on the code:
///
/// -# @b BMK_TODO - We need to finish code this part.
///

#include "launch_pad_gen_app.h"
#include "wx/fs_mem.h"
#include "wx/fs_inet.h"

//
// Some internal definess:
//

//
// Private prototypes:
//

//
// Global variables:
//

IMPLEMENT_APP(CLaunchPadGenApp)

//
// Constructors / destructors:
//

CLaunchPadGenApp::CLaunchPadGenApp ()
{
	// Initialize all the data members of CLaunchPadGen:
	m_pFrame = NULL;

	// Add support for common types of bitmaps:
	wxImage::AddHandler ( new wxPNGHandler );
	wxImage::AddHandler ( new wxJPEGHandler );
	wxImage::AddHandler ( new wxGIFHandler );
	wxImage::AddHandler ( new wxXPMHandler );

	// Allow using of real HTTP requests on the HTML control:
	//wxFileSystem::AddHandler ( new wxInternetFSHandler );
}

CLaunchPadGenApp::~CLaunchPadGenApp ()
{
	// Destroy any allocated resource by this instance of CLaunchPadGen:
}

//
// Public methods:
//

bool CLaunchPadGenApp::OnInit ()
{
	// Create the main frame:
	m_pFrame = new CLaunchPadGenMainFrame ( NULL, "Launchpad Applications Control", wxPoint ( 50,50 ), wxSize ( 500,400 ) );
	if ( m_pFrame == NULL )
	{
		// Error:
		return false;
	} // Endif.

	// Check for errors:
	if ( m_pFrame->IsInitOK () == false )
	{
		// Error:
		return false;
	} // Endif.

	// Show the main frame:
	m_pFrame->Show ( true );
	SetTopWindow ( m_pFrame );

	// That's all:
	return true;
}

//
// Protected methods:
//

//
// Private methods:
//

//
// End of the source file launch_pad_gen_app.cpp
//

