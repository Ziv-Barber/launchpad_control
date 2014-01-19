
///
/// @file
/// @brief Common additional code for wxWidgets.
///
/// This header file declaring some common code to help you working with different versions of wxWidgets.
///
/// @b Interesting @b Bookmarks:
///
/// Please search for the following key word on the code to locate some interesting places on the code:
///
/// -# @b BMK_TODO - We need to finish code this part.
///
/// @b Script @b Information:
///

#ifndef H_WX_EXT_COMMON_HEAD
#define H_WX_EXT_COMMON_HEAD

//
// Header files needed to be include with this class:
//

#include "wx/wx.h"
#include "wx/dc.h"
#include "wx/bitmap.h"

//
// Some public definess:
//

#if wxCHECK_VERSION(2,9,0)
#define M_STRING_CONVERT wxString::FromUTF8
#else
#define M_STRING_CONVERT wxString::FromAscii
#endif

//
// Public prototypes:
//

///
/// @brief Smart convert from wxString into normal characters.
///
/// On wxWidgets version 2.9.0 and later the convertion will be into UTF8.
///
/// @param[in] oString The string object to work on it.
/// @return The string on ASCII version.
///
const char *WXEXT_GetAsAscii (
	wxString& oString
	);

///
/// @brief Add a pending event.
///
/// This operation is posting an event.
///
/// @param[in] pWindow The window that will receive this event.
/// @param[in] oEvent The event to send.
///
void WXEXT_AddPendingEvent (
	wxWindow *pWindow,
	wxEvent& oEvent
	);

///
/// @brief Convert a memory based image file into a bitmap object.
///
/// This function create a bitmap object from a memory dump of an image file.
///
/// @param[in] pImageBuffer Pointer to the image file data loaded into memory.
/// @param[in] uiSizeOfImage Size of the given buffer.
/// @retval NULL Operation failed.
/// @retval else Pointer to the generated bitmap.
///
wxBitmap *WXEXT_MemoryFileToBitmap (
	void *pImageBuffer,
	unsigned int uiSizeOfImage
	);

///
/// @brief Create a new combobox control.
///
/// Use this function instead of just creating a wxComboBox object with new 
/// to enable your code to be compiled on multi wxWidgets versions.
///
/// @param[in] pParent Parent window. Must not be NULL.
/// @param[in] iId Control's identifier. The value wxID_ANY indicates a default value.
/// @param[in] strLabel Initial selection string. An empty string indicates no selection. Notice that for the controls with wxCB_READONLY style this string must be one of the valid choices if it is not empty.
/// @param[in] oPos Checkbox position. If wxDefaultPosition is specified then a default position is chosen.
/// @param[in] oSize Checkbox size. If wxDefaultSize is specified then a default size is chosen.
/// @param[in] lStyle Window style.
/// @param[in] oValidator Window validator.
/// @param[in] strWinName Window name.
/// @retval NULL Operation failed.
/// @retval else Pointer to the new object.
///
wxComboBox *WXEXT_CreateComboBox (
	wxWindow *pParent,
	wxWindowID iId,
	const wxString& strLabel,
	const wxPoint& oPos = wxDefaultPosition,
	const wxSize& oSize = wxDefaultSize,
	long lStyle = 0,
	const wxValidator& oValidator = wxDefaultValidator,
	const wxString& strClassName = wxCheckBoxNameStr
	);

///
/// @brief Create a new listbox control.
///
/// Use this function instead of just creating a wxListBox object with new 
/// to enable your code to be compiled on multi wxWidgets versions.
///
/// @param[in] pParent Parent window. Must not be NULL.
/// @param[in] iId Control's identifier. The value wxID_ANY indicates a default value.
/// @param[in] oPos Checkbox position. If wxDefaultPosition is specified then a default position is chosen.
/// @param[in] oSize Checkbox size. If wxDefaultSize is specified then a default size is chosen.
/// @param[in] lStyle Window style.
/// @param[in] oValidator Window validator.
/// @param[in] strWinName Window name.
/// @retval NULL Operation failed.
/// @retval else Pointer to the new object.
///
wxListBox *WXEXT_CreateListBox (
	wxWindow *pParent,
	wxWindowID iId,
	const wxPoint& oPos = wxDefaultPosition,
	const wxSize& oSize = wxDefaultSize,
	long lStyle = 0,
	const wxValidator& oValidator = wxDefaultValidator,
	const wxString& strClassName = wxListBoxNameStr
	);

#endif // H_WX_EXT_COMMON_HEAD

//
// End of the header file wx_ext_common.h
//

