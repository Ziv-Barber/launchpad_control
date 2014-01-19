
///
/// @file
/// @brief Common wxWidgets stuff.
///
/// This is the implementation of some common wxWidgets utilities.
///
/// @b Interesting @b Bookmarks:
///
/// Please search for the following key word on the code to locate some interesting places on the code:
///
/// -# @b BMK_TODO - We need to finish code this part.
///

#include "wx_ext_common.h"

#include "wx/image.h"
#include "wx/mstream.h"

//
// Some internal definess:
//

//
// Private prototypes:
//

//
// Global variables:
//

//
// Public code:
//

const char *WXEXT_GetAsAscii (
	wxString& oString
	)
{
	// Convert into ASCII:
#if wxCHECK_VERSION(2,9,0)
	return oString.utf8_str ();
#else
	return oString.c_str ();
#endif
}

void WXEXT_AddPendingEvent (
	wxWindow *pWindow,
	wxEvent& oEvent
	)
{
	// Post this event:
#if wxCHECK_VERSION(2,9,0)
	pWindow->GetEventHandler ()->AddPendingEvent ( oEvent );
#else
	pWindow->AddPendingEvent ( oEvent );
#endif
}

wxBitmap *WXEXT_MemoryFileToBitmap (
	void *pImageBuffer,
	unsigned int uiSizeOfImage
	)
{
	wxMemoryInputStream *pMemStream; // Memory stream.
	wxImage *pImage;                 // Image object.
	wxBitmap *pBitmap;               // The bitmap object.

	// Create a memory stream:
	pMemStream = new wxMemoryInputStream ( (const char *) pImageBuffer, uiSizeOfImage );
	if ( pMemStream == NULL )
	{
		// Error:
		return NULL;
	} // Endif.

	// Create an image:
	pImage = new wxImage ( *pMemStream, wxBITMAP_TYPE_ANY );
	if ( pImage == NULL )
	{
		// Error:
		delete pMemStream;
		return NULL;
	} // Endif.

	// The last step - create the bitmap itself:
	pBitmap = new wxBitmap ( *pImage );
	if ( pBitmap == NULL )
	{
		// Error:
		delete pImage;
		delete pMemStream;
		return NULL;
	} // Endif.

	// Clean after us:
	delete pImage;
	delete pMemStream;
	return pBitmap;
}

wxComboBox *WXEXT_CreateComboBox (
	wxWindow *pParent,
	wxWindowID iId,
	const wxString& strLabel,
	const wxPoint& oPos,
	const wxSize& oSize,
	long lStyle,
	const wxValidator& oValidator,
	const wxString& strClassName
	)
{
	// Allocate a new object:
#if wxCHECK_VERSION(2,9,1)
	return new wxComboBox ( pParent, iId, strLabel, oPos, oSize, 0, NULL, lStyle, oValidator, strClassName );
#else
	return new wxComboBox ( pParent, iId, strLabel, oPos, oSize, NULL, lStyle, oValidator, strClassName );
#endif
}

wxListBox *WXEXT_CreateListBox (
	wxWindow *pParent,
	wxWindowID iId,
	const wxPoint& oPos,
	const wxSize& oSize,
	long lStyle,
	const wxValidator& oValidator,
	const wxString& strClassName
	)
{
	// Allocate a new object:
#if wxCHECK_VERSION(2,9,1)
	return new wxListBox ( pParent, iId, oPos, oSize, 0, NULL, lStyle, oValidator, strClassName );
#else
	return new wxListBox ( pParent, iId, oPos, oSize, NULL, lStyle, oValidator, strClassName );
#endif
}

//
// Private code:
//

//
// End of the source file wx_ext_common.cpp
//

