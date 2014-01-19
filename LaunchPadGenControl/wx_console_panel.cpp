
///
/// @file
/// @brief The class CWxConsolePanel.
///
/// This is the implementation of the class CWxConsolePanel.
///
/// @b Interesting @b Bookmarks:
///
/// Please search for the following key word on the code to locate some interesting places on the code:
///
/// -# @b BMK_TODO - We need to finish code this part.
///

#define D_NO_STRING_CODE

#include "wx_console_panel.h"
#include "wx_ext_common.h"

#include "wx/file.h"
#include "wx/regex.h"
#include "wx/msw/registry.h"

#include "string_parser.h"

//
// Some internal definess:
//

///
/// @brief All the IDs of the controls of CWxConsolePanel.
///
/// This enumerator declaring all the IDs of all the child controls of the 
/// CWxConsolePanel class.
///
/// @see CWxConsolePanel
///
typedef enum EConsolePanelCntIds
{
	E_CONSOLE_PANEL_CNT_IN_FIND,    ///< Input box for find.
	E_CONSOLE_PANEL_CNT_FIND,       ///< Find button.
	E_CONSOLE_PANEL_CNT_EVENTS,     ///< Events container.
	E_CONSOLE_PANEL_CNT_IN_SEND,    ///< Input box for send.
	E_CONSOLE_PANEL_CNT_SEND,       ///< Send button.
	E_CONSOLE_PANEL_MENU_SEL_ALL,   ///< Select all.
	E_CONSOLE_PANEL_MENU_DESEL_ALL, ///< Deselect all.
	E_CONSOLE_PANEL_MENU_INV_SEL,   ///< Invert selection.
	E_CONSOLE_PANEL_MENU_SAVE_ALL,  ///< Save all events.
	E_CONSOLE_PANEL_MENU_SEL_SV,    ///< Select events save.
	E_CONSOLE_PANEL_MENU_DESEL_SV,  ///< Deselect events save.
	E_CONSOLE_PANEL_MENU_CLR_ALL,   ///< Clear all events.
	E_CONSOLE_PANEL_MENU_SEL_CLR,   ///< Select events clear.
	E_CONSOLE_PANEL_MENU_DESEL_CLR, ///< Deselect events clear.
	E_CONSOLE_PANEL_MENU_SEARCH     ///< Show the find bar.
};

//
// Private prototypes:
//

//
// Global variables:
//

// Declare all the custom events:
//const wxEventType m_oConsoleMsgEvent = wxNewEventType ();

//
// Constructors / destructors:
//

CWxConsolePanel::~CWxConsolePanel ()
{
	// Destroy any allocated resource by this instance of CWxConsolePanel:
}

//
// Public methods:
//

bool CWxConsolePanel::Create (
	wxWindow* pParent,
	wxWindowID iId,
	wxWindow* pEventsWin,
	const wxEventType* pEventType,
	bool bShowInput,
	bool bFixedFind,
	const wxPoint& oPosition,
	const wxSize& oSize,
	long lStyle,
	const wxString& strWindowName
	)
{
	//wxFont oFontInfo; // Font information.

	// Create the panel:
    if ( !wxPanel::Create ( pParent, iId, oPosition, oSize, lStyle | wxNO_BORDER | wxCLIP_CHILDREN | wxTAB_TRAVERSAL, strWindowName ) )
	{
		// Failed to create the new panel:
        return false;
	} // Endif.

	SetBackgroundColour ( wxSystemSettings::GetColour ( wxSYS_COLOUR_MENU ) );

	m_uiIntFlags = 0;
	m_pEventsWin = pEventsWin;
	m_pEventType = pEventType;

	if ( bShowInput != false )
	{
		m_uiIntFlags |= 4;
	} // Endif.

	if ( bFixedFind != false )
	{
		m_uiIntFlags |= 3;
	} // Endif.

	//
	// Create all the sizers:
	//

	// Create the main sizer:
	m_pMainSizer = new wxBoxSizer ( wxVERTICAL );
	if ( m_pMainSizer == NULL )
	{
		// Error:
		return false;
	} // Endif.

	// Create the find bar sizer:
	m_pFindSizer = new wxBoxSizer ( wxHORIZONTAL );
	if ( m_pFindSizer == NULL )
	{
		// Error:
		return false;
	} // Endif.

	// Create the input bar sizer:
	m_pInputSizer = new wxBoxSizer ( wxHORIZONTAL );
	if ( m_pInputSizer == NULL )
	{
		// Error:
		return false;
	} // Endif.

	//
	// Create all the controls:
	//

	// Create the "Find" text:
	m_pFindText = new wxStaticText ( this, wxID_ANY, wxT("Search for") );
	if ( m_pFindText == NULL )
	{
		// Error:
		return false;
	} // Endif.

	// Input control for find:
	m_pInFind = WXEXT_CreateComboBox ( this, E_CONSOLE_PANEL_CNT_IN_FIND, wxT(""), wxDefaultPosition, wxDefaultSize, wxCB_DROPDOWN | wxTE_PROCESS_ENTER );
	if ( m_pInFind == NULL )
	{
		// Error:
		return false;
	} // Endif.

	// Find method:
	wxString oFindTypes[] = { wxT("Match text"), wxT("Match all text"), wxT("Wildcards search"), wxT("Wildcards search (all text)"), wxT("Regular expression") };
	m_pFindType = new wxComboBox ( this, wxID_ANY, wxT("Match text"), wxDefaultPosition, wxDefaultSize, 5, oFindTypes, wxCB_READONLY );
	if ( m_pFindType == NULL )
	{
		// Error:
		return false;
	} // Endif.

	// Create the "Find" button:
	m_pFind = new wxButton ( this, E_CONSOLE_PANEL_CNT_FIND, wxT("Find") );
	if ( m_pFind == NULL )
	{
		// Error:
		return false;
	} // Endif.

	// Create the events list box:
	m_pEventsBox = WXEXT_CreateListBox ( this, E_CONSOLE_PANEL_CNT_EVENTS, wxDefaultPosition, wxDefaultSize, wxLB_MULTIPLE | wxLB_ALWAYS_SB | wxLB_HSCROLL );
	if ( m_pEventsBox == NULL )
	{
		// Error:
		return false;
	} // Endif.

	// Change the font:
	//oFontInfo = m_pEventsBox->GetFont ();
	//oFontInfo.SetFamily ( wxFONTFAMILY_MODERN );
	//m_pEventsBox->SetFont ( oFontInfo );

	// Selection list:
	m_pSelectList = WXEXT_CreateComboBox ( this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxCB_DROPDOWN | wxCB_READONLY );
	if ( m_pSelectList == NULL )
	{
		// Error:
		return false;
	} // Endif.

	// Input control for send:
	m_pInSend = WXEXT_CreateComboBox ( this, E_CONSOLE_PANEL_CNT_IN_SEND, wxT(""), wxDefaultPosition, wxDefaultSize, wxCB_DROPDOWN | wxTE_PROCESS_ENTER );
	if ( m_pInSend == NULL )
	{
		// Error:
		return false;
	} // Endif.

	// Create the "Send" button:
	m_pSend = new wxButton ( this, E_CONSOLE_PANEL_CNT_SEND, wxT("Send") );
	if ( m_pSend == NULL )
	{
		// Error:
		return false;
	} // Endif.

	//
	// Connect all the controls to the sizers:
	//

	m_pFindSizer->Add ( m_pFindText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2 );
	m_pFindSizer->Add ( m_pInFind, 1, wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALL, 2 );
	m_pFindSizer->Add ( m_pFindType, 0, wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALL, 2 );
	m_pFindSizer->Add ( m_pFind, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2 );
	m_pInputSizer->Add ( m_pSelectList, 0, wxEXPAND | wxALL, 2 );
	m_pInputSizer->Add ( m_pInSend, 1, wxEXPAND | wxALL, 2 );
	m_pInputSizer->Add ( m_pSend, 0, wxALIGN_CENTER_VERTICAL | wxALL, 2 );
	m_pMainSizer->Add ( m_pFindSizer, 0, wxEXPAND | wxALL, 0 );
	m_pMainSizer->Add ( m_pEventsBox, 1, wxEXPAND | wxALL, 0 );
	m_pMainSizer->Add ( m_pInputSizer, 0, wxEXPAND | wxALL, 0 );

	//
	// Add events:
	//

	// Connect all the control events:
	Connect ( E_CONSOLE_PANEL_CNT_IN_FIND, wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler ( CWxConsolePanel::OnClickFind ) );
	Connect ( E_CONSOLE_PANEL_CNT_IN_FIND, wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler ( CWxConsolePanel::OnClickFind ) );
	Connect ( E_CONSOLE_PANEL_CNT_EVENTS, wxEVT_CONTEXT_MENU, wxCommandEventHandler ( CWxConsolePanel::OnEventsRightClick ) );
	Connect ( E_CONSOLE_PANEL_CNT_IN_SEND, wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler ( CWxConsolePanel::OnClickSend ) );
	Connect ( E_CONSOLE_PANEL_CNT_IN_SEND, wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler ( CWxConsolePanel::OnClickSend ) );
	Connect ( E_CONSOLE_PANEL_CNT_FIND, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler ( CWxConsolePanel::OnClickFind ) );
	Connect ( E_CONSOLE_PANEL_CNT_SEND, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler ( CWxConsolePanel::OnClickSend ) );
	Connect ( E_CONSOLE_PANEL_MENU_SEL_ALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler ( CWxConsolePanel::OnMenuSelAll ) );
	Connect ( E_CONSOLE_PANEL_MENU_DESEL_ALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler ( CWxConsolePanel::OnMenuDeselAll ) );
	Connect ( E_CONSOLE_PANEL_MENU_INV_SEL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler ( CWxConsolePanel::OnMenuInvertAll ) );
	Connect ( E_CONSOLE_PANEL_MENU_SAVE_ALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler ( CWxConsolePanel::OnMenuSaveAll ) );
	Connect ( E_CONSOLE_PANEL_MENU_SEL_SV, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler ( CWxConsolePanel::OnMenuSelSave ) );
	Connect ( E_CONSOLE_PANEL_MENU_DESEL_SV, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler ( CWxConsolePanel::OnMenuDeselSave ) );
	Connect ( E_CONSOLE_PANEL_MENU_CLR_ALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler ( CWxConsolePanel::OnMenuClearAll ) );
	Connect ( E_CONSOLE_PANEL_MENU_SEL_CLR, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler ( CWxConsolePanel::OnMenuSelClear ) );
	Connect ( E_CONSOLE_PANEL_MENU_DESEL_CLR, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler ( CWxConsolePanel::OnMenuDeselClear ) );
	Connect ( E_CONSOLE_PANEL_MENU_SEARCH, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler ( CWxConsolePanel::OnMenuSearch ) );

	// Connect the main sizer:
	SetSizer ( m_pMainSizer );

	// Check if we need to display the find bar:
	if ( (m_uiIntFlags & 1) == 0 )
	{
		m_pFindSizer->Show ( false );
	} // Endif.

	// Check if we need to display the input bar:
	if ( (m_uiIntFlags & 4) == 0 )
	{
		m_pInputSizer->Show ( false );

	} else
	{
		// By default hide the selection control:
		m_pSelectList->Show ( false );
	} // Endif.

	// That's all:
	return true;
}

void CWxConsolePanel::AddMsgString (
	wxString& oMessage,
	bool bForceBottom
	)
{
	int iPos;      // Current schroll position.
	int iRange;    // Used for changing the schrollbar.
	int iThumb;    // Used for changing the schrollbar.
	bool bIsFirst; // Is true if this is the first event.

	// Close any waiting part of message:
	EndOfText ( bForceBottom );

	// Check if we passed the limit:
	if ( m_pEventsBox->GetCount () >= m_uiMaxLines )
	{
		m_pEventsBox->Delete ( 0 );
	} // Endif.

	bIsFirst = m_pEventsBox->GetCount () == 0 ? true : false;

	// Add the message to the console messages:
	m_pEventsBox->Append ( oMessage );
	if ( bForceBottom != false )
	{
		iPos = m_pEventsBox->GetScrollPos ( wxVERTICAL );
		iRange = m_pEventsBox->GetScrollRange ( wxVERTICAL );
		iThumb = m_pEventsBox->GetScrollThumb ( wxVERTICAL );
		if ( iRange > 1 )
		{
			m_pEventsBox->ScrollLines ( 10000 );
		} // Endif.
	} // Endif.

	// Allow saving messages:
	if ( bIsFirst != false )
	{
		FireOutEvent ( E_OE_FILL_LIST, NULL );
	} // Endif.
}

void CWxConsolePanel::AddMsgText (
	const char *szMessage,
	bool bForceBottom
	)
{
	wxString oText; ///< The text message.

	// Convert to string:
	oText = M_STRING_CONVERT ( szMessage );
	AddMsgString ( oText, bForceBottom );
}

void CWxConsolePanel::AddBinDump (
	unsigned char *pBuffer,
	unsigned int uiSize,
	bool bForceBottom,
	char *szTitle
	)
{
	char szOut[80];          // Working buffer.
	unsigned char *pCur;     // Current position.
	unsigned int uiLeftSize; // Bytes left to display.
	unsigned int uiSubSize;  // The number of bytes been displayed.

	// Create the header:
	if ( szTitle != NULL )
	{
		uiSubSize = strlen ( szTitle );
		if ( uiSubSize > 71 )
		{
			uiSubSize = 71;
		} // Endif.

		if ( uiSubSize > 0 )
		{
			szOut[0] = '-';
			szOut[1] = '-';
			szOut[2] = '-';
			szOut[3] = ' ';
			memcpy ( szOut + 4, szTitle, uiSubSize );
			szOut[uiSubSize + 4] = ' ';
			szOut[uiSubSize + 5] = '-';
			szOut[uiSubSize + 6] = '-';
			szOut[uiSubSize + 7] = '-';
			szOut[uiSubSize + 8] = 0;
			AddMsgText ( szOut, bForceBottom );
		} // Endif.
	} // Endif.

	// Loop on all the data to display:
	pCur = pBuffer;
	uiLeftSize = uiSize;
	while ( uiLeftSize > 0 )
	{
		BinToHexLine ( pCur, szOut, uiLeftSize );
		AddMsgText ( szOut, bForceBottom );
		uiSubSize = uiLeftSize > 16 ? 16 : uiLeftSize;
		pCur += uiSubSize;
		uiLeftSize -= uiSubSize;
	} // End of while loop.

	// Write the end line:
	if ( szTitle != NULL )
	{
		uiSubSize = strlen ( szTitle );
		if ( uiSubSize > 71 )
		{
			uiSubSize = 71;
		} // Endif.

		if ( uiSubSize > 0 )
		{
			uiSubSize += 8;
			memset ( szOut, '-', uiSubSize );
			szOut[uiSubSize] = 0;
			AddMsgText ( szOut, bForceBottom );
		} // Endif.
	} // Endif.
}

void CWxConsolePanel::AddMsgPartString (
	wxString& oMessage,
	bool bForceBottom
	)
{
	wxString oTemp; // Temporary string.
	wxString oText; // The text left to work on it.
	int iPos;       // Position of the next new line character.

	// Loop on all the complate lines:
	oText = oMessage;
	iPos = oText.Find ( '\n' );
	while ( iPos != wxNOT_FOUND )
	{
		if ( iPos > 0 )
		{
			m_oPart.Append ( oText.Mid ( 0, iPos ) );
		} // Endif.

		oTemp = m_oPart;
		m_oPart = wxT("");
		AddMsgString ( oTemp, bForceBottom );
		oTemp = oText.Mid ( iPos + 1 );
		oText = oTemp;
		iPos = oText.Find ( '\n' );
	} // End of while loop.

	// Save the rest:
	m_oPart.Append ( oText );
}

void CWxConsolePanel::AddMsgPartText (
	const char *szMessage,
	bool bForceBottom
	)
{
	wxString oText; ///< The text message.

	// Convert to string:
	oText = M_STRING_CONVERT ( szMessage );
	AddMsgPartString ( oText, bForceBottom );
}

void CWxConsolePanel::EndOfText (
	bool bForceBottom
	)
{
	wxString oText; // The text to display.

	// Check if we have a text to add:
	if ( m_oPart.IsEmpty () == false )
	{
		oText = m_oPart;
		m_oPart = wxT("");
		AddMsgString ( oText, bForceBottom );
	} // Endif.
}

void CWxConsolePanel::SetMaxLines (
	unsigned int uiMaxLines
	)
{
	// Check if we passed the limit:
	m_uiMaxLines = uiMaxLines;
	if ( m_pEventsBox->GetCount () >= m_uiMaxLines )
	{
		m_pEventsBox->Delete ( 0 );
	} // Endif.
}

void CWxConsolePanel::SetMaxFindHistory (
	unsigned int uiMaxHistory
	)
{
	// Check if we passed the limit:
	m_uiMaxFind = uiMaxHistory;
	while ( m_pInFind->GetCount () >= m_uiMaxFind )
	{
		m_pInFind->Delete ( 0 );
	} // Endif.
}

void CWxConsolePanel::SetMaxHistory (
	unsigned int uiMaxHistory
	)
{
	// Check if we passed the limit:
	m_uiMaxHistory = uiMaxHistory;
	while ( m_pInSend->GetCount () >= m_uiMaxHistory )
	{
		m_pInSend->Delete ( 0 );
	} // Endif.
}

void CWxConsolePanel::GetCurrentCommand (
	wxString& oCommand
	)
{
	// Get the current input command:
	oCommand = m_pInSend->GetValue ();
}

void CWxConsolePanel::SetCommandString (
	wxString& oCommand,
	bool bSelect
	)
{
	// Set the given text as the command:
	m_pInSend->SetValue ( oCommand );
	if ( bSelect == false )
	{
		m_pInSend->SetSelection ( 0, oCommand.Len () );
	} // Endif.
}

void CWxConsolePanel::SetCommandText (
	const char *szCommand,
	bool bSelect
	)
{
	wxString oText; ///< The text message.

	// Convert to string:
	oText = M_STRING_CONVERT ( szCommand );
	SetCommandString ( oText, bSelect );
}

bool CWxConsolePanel::SaveMessages (
	const char *szFilename,
	bool bSaveMarked,
	bool bSaveUnmarked
	)
{
	wxFile oFileHandle;       // File handle.
	wxString oFile;           // The messages filename.
	wxString oMsg;            // Current message.
	wxMessageDialog *pDialog; // Message box.
	wxFileDialog *pFDialog;   // File selection dialog.
	int iLoopCount;           // Loop counter.
	int iTotalCount;          // Total number of messages.

	// Get the file name:
	pFDialog = NULL;
	if ( szFilename != NULL )
	{
		oFile = M_STRING_CONVERT ( szFilename );

	} else
	{
		// Display a save file dialog:
		pFDialog = new wxFileDialog ( this, wxT("Save events"), wxT(""), wxT(""), wxT("Log file (*.log)|*.log|Text file (*.txt)|*.txt|All files|*.*"), wxFD_SAVE );
		if ( pFDialog == NULL )
		{
			// Error:
			return false;
		} // Endif.

		// Show this dialog:
		if ( pFDialog->ShowModal () == wxID_OK )
		{
			oFile = pFDialog->GetPath ();

		} else
		{
			// Abort:
			delete pFDialog;
			return false;
		} // Endif.

		// Destroy the dialog object:
		delete pFDialog;
	} // Endif.

	// Create the events file:
	if ( oFileHandle.Open ( oFile, wxFile::write ) == false )
	{
		// Display error:
		pDialog = new wxMessageDialog ( this, wxT("Failed to create the dump file."), wxT("Error"), wxOK );
		if ( pDialog != NULL )
		{
			pDialog->ShowModal ();
			delete pDialog;
		} // Endif.

		// Clean after us:
		delete pFDialog;
		return false;
	} // Endif,

	// Write all the messages to the file:
	iTotalCount = m_pEventsBox->GetCount ();
	for ( iLoopCount = 0; iLoopCount < iTotalCount; iLoopCount++ )
	{
		oMsg = m_pEventsBox->GetString ( iLoopCount );
		if ( m_pEventsBox->IsSelected ( iLoopCount ) != false )
		{
			if ( bSaveMarked != false )
			{
				oFileHandle.Write ( oMsg );
				oFileHandle.Write ( wxT("\n") );
			} // Endif.

		} else
		{
			if ( bSaveUnmarked != false )
			{
				oFileHandle.Write ( oMsg );
				oFileHandle.Write ( wxT("\n") );
			} // Endif.
		} // Endif.
	} // End of for loop.

	// Close the messages file:
	oFileHandle.Close ();
	return true;
}

void CWxConsolePanel::ClearMessages (
	bool bClearMarked,
	bool bClearUnmarked
	)
{
	unsigned int uiCurPos; // Current tested string.

	// Check if we need to clear all the events:
	if ( (bClearMarked == true) && (bClearUnmarked == true) )
	{
		// Just clear everything:
		m_pEventsBox->Clear ();

	} else
	{
		// Loop on all the messages:
		uiCurPos = 0;
		while ( uiCurPos < m_pEventsBox->GetCount () )
		{
			if ( m_pEventsBox->IsSelected ( uiCurPos ) == false )
			{
				if ( bClearUnmarked != false )
				{
					m_pEventsBox->Delete ( uiCurPos );

				} else
				{
					uiCurPos++;
				} // Endif.

			} else
			{
				if ( bClearMarked != false )
				{
					m_pEventsBox->Delete ( uiCurPos );

				} else
				{
					uiCurPos++;
				} // Endif.
			} // Endif.
		} // End of while loop.
	} // Endif.

	// Check if there are no events:
	if ( m_pEventsBox->GetCount () == 0 )
	{
		FireOutEvent ( E_OE_CLEAR_LIST, NULL );
	} // Endif.
}

#ifdef REF_CODE
void CWxConsolePanel::SaveHistory ()
{
	char szNumber[32];       // Number string.
	wxString oText;          // Text string.
	const char *szText;      // The text to save on the registry.
	HKEY hBaseKey = NULL;    // Handle to the main registry key.
	HKEY hHistoryKey = NULL; // Handle to the history registry key.
	long lTotal;             // Total history items.
	long lCount;             // Current history item.

	// Create our registry key if it's not already exist:
	if ( RegCreateKeyEx ( HKEY_LOCAL_MACHINE, "SOFTWARE\\WinUsbGenClient", 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hBaseKey, NULL ) == ERROR_SUCCESS )
	{
		// Save all the history items:
		if ( RegCreateKeyEx ( hBaseKey, "History", 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hHistoryKey, NULL ) == ERROR_SUCCESS )
		{
			lTotal = m_pInSend->GetCount ();
			for ( lCount = 0; lCount < lTotal; lCount++ )
			{
				sprintf ( szNumber, "%lu", lCount );
				oText = m_pInSend->GetString ( lCount );
				szText = oText.c_str ();
				if ( RegSetValueEx ( hHistoryKey, szNumber, 0, REG_SZ, (BYTE *) szText, strlen ( szText ) ) == ERROR_SUCCESS )
				{
				} // Endif.
			} // End of for loop.

			// Close registry key:
			RegCloseKey ( hHistoryKey );
		} // Endif.

		oText = m_pInSend->GetValue ();
		szText = oText.c_str ();
		if ( RegSetValueEx ( hBaseKey, "DefCommand", 0, REG_SZ, (BYTE *) szText, strlen ( szText ) ) == ERROR_SUCCESS )
		{
		} // Endif.

		// Close registry key:
		RegCloseKey ( hBaseKey );
	} // Endif.
}
#endif // REF_CODE

void CWxConsolePanel::ShowConsole (
	bool bShow,
	bool bEnable
	)
{
	// Update the flags:
	m_uiIntFlags |= 4;
	if ( bShow == false )
	{
		m_uiIntFlags ^= 4;
	} // Endif.

	// Change the console bar:
	m_pInputSizer->Show ( bShow );
	if ( bShow != false )
	{
		Enable ( bEnable );
	} // Endif.

	// Refresh:
	Layout ();
	Refresh ();
}

bool CWxConsolePanel::Enable (
	bool bEnable
	)
{
	bool bPrevState; // Previous state.

	// You must have a console to use this method:
	if ( (m_uiIntFlags & 4) == 0 )
	{
		// We can't change the current state (which is always disabled):
		return false;
	} // Endif.

	// Enable or disable:
	bPrevState = m_pInSend->IsEnabled ();
	m_pInSend->Enable ( bEnable );
	m_pSend->Enable ( bEnable );
	if ( m_pSelectList->GetCount () > 0 )
	{
		m_pSelectList->Show ( true );
		m_pSelectList->Enable ( bEnable );

	} else
	{
		m_pSelectList->Show ( false );
	} // Endif.

	// Return true if we changed something:
	Layout ();
	Refresh ();
	return bPrevState != bEnable;
}

bool CWxConsolePanel::IsEnabled () const
{
	// You must have a console to use this method:
	if ( (m_uiIntFlags & 4) == 0 )
	{
		// The control is always disabled:
		return false;
	} // Endif.

	// Check the current console's controls state:
	return m_pInSend->IsEnabled ();
}

//
// Protected methods:
//

void CWxConsolePanel::OnClickFind (
	wxCommandEvent& oEvent
	)
{
	wxString oText;        // The command's text.
	wxString oToLog;       // The message as been posted to the log.
	ESearchType iType;     // Search type.
	unsigned int uiCurPos; // Current tested string.

	// Prepare the search type:
	iType = (ESearchType) (int) m_pFindType->GetSelection ();

	// Check if this string is also on the find histroy:
	oText = m_pInFind->GetValue ();
	if ( m_pInFind->FindString ( oText ) == wxNOT_FOUND )
	{
		while ( m_pInFind->GetCount () >= m_uiMaxFind )
		{
			m_pInFind->Delete ( 0 );
		} // Endif.

		m_pInFind->Append ( oText );
	} // Endif.

	// Select all the match items:
	uiCurPos = (unsigned int) -1;
	uiCurPos = FindNext ( oText, iType, uiCurPos );
	while ( uiCurPos != (unsigned int) -1 )
	{
		if ( m_pEventsBox->IsSelected ( uiCurPos ) == false )
		{
			m_pEventsBox->SetSelection ( uiCurPos );
		} // Endif.

		uiCurPos = FindNext ( oText, iType, uiCurPos );
	} // End of while loop.

	// Select all:
	m_pInFind->SetSelection ( 0, -1 );
	m_pInFind->SetFocus ();
}

void CWxConsolePanel::OnEventsRightClick (
	wxCommandEvent& oEvent
	)
{
	wxMenu *pMenu; // The right menu.

	// Create the right menu:
	pMenu = new wxMenu ();
	if ( pMenu == NULL )
	{
		// Error:
		return;
	} // Endif.

	// Append the menu items:
	pMenu->Append ( E_CONSOLE_PANEL_MENU_SEL_ALL, wxT("Select all") );
	pMenu->Append ( E_CONSOLE_PANEL_MENU_DESEL_ALL, wxT("Deselect all") );
	pMenu->Append ( E_CONSOLE_PANEL_MENU_INV_SEL, wxT("Invert selection") );
	pMenu->AppendSeparator ();
	pMenu->Append ( E_CONSOLE_PANEL_MENU_SAVE_ALL, wxT("Save all") );
	pMenu->Append ( E_CONSOLE_PANEL_MENU_SEL_SV, wxT("Save selected text") );
	pMenu->Append ( E_CONSOLE_PANEL_MENU_DESEL_SV, wxT("Save not selected text") );
	pMenu->AppendSeparator ();
	pMenu->Append ( E_CONSOLE_PANEL_MENU_CLR_ALL, wxT("Clear all") );
	pMenu->Append ( E_CONSOLE_PANEL_MENU_SEL_CLR, wxT("Clear selected") );
	pMenu->Append ( E_CONSOLE_PANEL_MENU_DESEL_CLR, wxT("Clear not selected") );
	if ( (m_uiIntFlags & 2) == 0 )
	{
		pMenu->AppendSeparator ();
		pMenu->Append ( E_CONSOLE_PANEL_MENU_SEARCH, (m_uiIntFlags & 1) == 0 ? wxT("Show the search bar") : wxT("Hide the search bar") );
	} // Endif.

	// Show the popup menu:
	PopupMenu ( pMenu );
	delete pMenu;
}

void CWxConsolePanel::OnClickSend (
	wxCommandEvent& oEvent
	)
{
	wxString oText;  // The command's text.
	wxString oToLog; // The message as been posted to the log.

	// Check if this string is also on the histroy:
	oText = m_pInSend->GetValue ();
	if ( m_pInSend->FindString ( oText ) == wxNOT_FOUND )
	{
		while ( m_pInSend->GetCount () >= m_uiMaxHistory )
		{
			m_pInSend->Delete ( 0 );
		} // Endif.

		m_pInSend->Append ( oText );
	} // Endif.

	// Add the command itself to the log:
	oToLog = wxT("-> ");
	oToLog.Append ( oText );
	AddMsgString ( oToLog, true );

	// Fire event:
	FireOutEvent ( E_OE_SEND_CMD, &oText );

	// Select all:
	m_pInSend->SetSelection ( 0, -1 );
	m_pInSend->SetFocus ();
}

void CWxConsolePanel::OnMenuSelAll (
	wxCommandEvent& oEvent
	)
{
	unsigned int uiMaxItems; // Number of events messages.
	unsigned int uiCurPos;   // Current tested string.

	// Loop on all the messages:
	uiCurPos = 0;
	uiMaxItems = m_pEventsBox->GetCount ();
	while ( uiMaxItems > uiCurPos )
	{
		if ( m_pEventsBox->IsSelected ( uiCurPos ) == false )
		{
			m_pEventsBox->SetSelection ( uiCurPos );
		} // Endif.

		uiCurPos++;
	} // End of while loop.
}

void CWxConsolePanel::OnMenuDeselAll (
	wxCommandEvent& oEvent
	)
{
	unsigned int uiMaxItems; // Number of events messages.
	unsigned int uiCurPos;   // Current tested string.

	// Loop on all the messages:
	uiCurPos = 0;
	uiMaxItems = m_pEventsBox->GetCount ();
	while ( uiMaxItems > uiCurPos )
	{
		m_pEventsBox->Deselect ( uiCurPos );

		uiCurPos++;
	} // End of while loop.
}

void CWxConsolePanel::OnMenuInvertAll (
	wxCommandEvent& oEvent
	)
{
	unsigned int uiMaxItems; // Number of events messages.
	unsigned int uiCurPos;   // Current tested string.

	// Loop on all the messages:
	uiCurPos = 0;
	uiMaxItems = m_pEventsBox->GetCount ();
	while ( uiMaxItems > uiCurPos )
	{
		if ( m_pEventsBox->IsSelected ( uiCurPos ) == false )
		{
			m_pEventsBox->SetSelection ( uiCurPos );

		} else
		{
			m_pEventsBox->Deselect ( uiCurPos );
		} // Endif.

		uiCurPos++;
	} // End of while loop.
}

void CWxConsolePanel::OnMenuSaveAll (
	wxCommandEvent& oEvent
	)
{
	// Save all events:
	SaveMessages ( NULL, true, true );
}

void CWxConsolePanel::OnMenuSelSave (
	wxCommandEvent& oEvent
	)
{
	// Save only the marked events:
	SaveMessages ( NULL, true, false );
}

void CWxConsolePanel::OnMenuDeselSave (
	wxCommandEvent& oEvent
	)
{
	// Save only the unmarked events:
	SaveMessages ( NULL, false, true );
}

void CWxConsolePanel::OnMenuClearAll (
	wxCommandEvent& oEvent
	)
{
	// Clear all the events:
	ClearMessages ( true, true );
}

void CWxConsolePanel::OnMenuSelClear (
	wxCommandEvent& oEvent
	)
{
	// Clear only all the selected events:
	ClearMessages ( true, false );
}

void CWxConsolePanel::OnMenuDeselClear (
	wxCommandEvent& oEvent
	)
{
	// Clear only all the non selected events:
	ClearMessages ( false, true );
}

void CWxConsolePanel::OnMenuSearch (
	wxCommandEvent& oEvent
	)
{
	// Check what we should do:
	if ( m_uiIntFlags & 1 )
	{
		// Hide the search menu:
		m_pFindSizer->Show ( false );
		m_uiIntFlags ^= 1;
		Layout ();
		Refresh ();

	} else
	{
		// Show the search menu:
		m_pFindSizer->Show ( true );
		m_uiIntFlags |= 1;
		Layout ();
		Refresh ();
	} // Endif.
}

void CWxConsolePanel::FireOutEvent (
	EOutEvent iEventType,
	wxString *pText
	)
{
	wxCommandEvent oEvent; // Event information.

	// Check if we can fire an event:
	if ( (m_pEventType == NULL) || (m_pEventsWin == NULL) )
	{
		// Error:
		return;
	} // Endif.

	// Fire an event:
	oEvent.SetEventType ( *m_pEventType );
	oEvent.SetId ( 0 );
	oEvent.SetEventObject ( this );
	if ( pText != NULL )
	{
		oEvent.SetString ( *pText );
	} // Endif.
	oEvent.SetInt ( (int) iEventType );
	oEvent.SetClientData ( this );
	WXEXT_AddPendingEvent ( m_pEventsWin, oEvent );
}

unsigned int CWxConsolePanel::FindNext (
	wxString& oText,
	CWxConsolePanel::ESearchType iSearchType,
	unsigned int lPrevMatch
	)
{
	wxRegEx oRegEx;          // RegEx object.
	wxString oItemText;      // The current text to search.
	const char *szFindUtf8;  // The string to search.
	unsigned int uiMaxItems; // Number of events messages.
	unsigned int uiCurPos;   // Current tested string.
	bool bIsMatch;           // Is true if the string match.

	// Special case for regex search:
	szFindUtf8 = NULL;
	if ( iSearchType == E_ST_REGEX )
	{
		if ( oRegEx.Compile ( oText ) == false )
		{
			// Error:
			return (unsigned int) -1;
		} // Endif.
	} // Endif.

	// Loop on all the messages:
	uiCurPos = lPrevMatch + 1;
	uiMaxItems = m_pEventsBox->GetCount ();
	while ( uiMaxItems > uiCurPos )
	{
		// Get the string to work on it:
		oItemText = m_pEventsBox->GetString ( uiCurPos );

		// Check if match:
		bIsMatch = false;
		switch ( iSearchType )
		{
			case E_ST_MATCH_PART:
				if ( oItemText.Find ( oText ) != wxNOT_FOUND )
				{
					bIsMatch = true;
				} // Endif.
				break;

			case E_ST_MATCH_ALL:
				if ( oItemText.CmpNoCase ( oText ) == 0 )
				{
					bIsMatch = true;
				} // Endif.
				break;

			case E_ST_WC_PART:
				if ( szFindUtf8 == NULL )
				{
					szFindUtf8 = WXEXT_GetAsAscii ( oText );
				} // Endif.

				if ( ExtendedCompare ( (char *) (const char *) WXEXT_GetAsAscii ( oItemText ), (char *) (const char *) szFindUtf8, -1, -1, true, true, true, true, true ) != -1 )
				{
					bIsMatch = true;
				} // Endif.
				break;

			case E_ST_WC_ALL:
				if ( szFindUtf8 == NULL )
				{
					szFindUtf8 = WXEXT_GetAsAscii ( oText );
				} // Endif.

				if ( ExtendedCompare ( (char *) (const char *) WXEXT_GetAsAscii ( oItemText ), (char *) (const char *) szFindUtf8, -1, -1, false, true, true, true, true ) != -1 )
				{
					bIsMatch = true;
				} // Endif.
				break;

			case E_ST_REGEX:
				if ( oRegEx.Matches ( oItemText ) != false )
				{
					bIsMatch = true;
				} // Endif.
				break;

			default:
				// Error:
				return (unsigned int) -1;
		} // End of switch.

		// Check if match:
		if ( bIsMatch != false )
		{
			// Another match:
			return uiCurPos;
		} // Endif.

		uiCurPos++;
	} // End of while loop.

	// No more match messages:
	return (unsigned int) -1;
}

//
// Private methods:
//

void CWxConsolePanel::Init ()
{
	// Initialize all the data members of CWxConsolePanel:
	m_oPart = wxT("");
	m_pMainSizer = NULL;
	m_pFindSizer = NULL;
	m_pInputSizer = NULL;
	m_pFindText = NULL;
	m_pInFind = NULL;
	m_pFindType = NULL;
	m_pFind = NULL;
	m_pEventsBox = NULL;
	m_pInSend = NULL;
	m_pSend = NULL;
	m_uiMaxLines = 10000;
	m_uiMaxFind = 20;
	m_uiMaxHistory = 20;
	m_uiIntFlags = 0;
}

//
// End of the source file wx_console_panel.cpp
//

