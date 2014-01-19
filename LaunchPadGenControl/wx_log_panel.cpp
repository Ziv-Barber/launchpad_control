
///
/// @file
/// @brief The class CWxLogPanel.
///
/// This is the implementation of the class CWxLogPanel.
///
/// @b Interesting @b Bookmarks:
///
/// Please search for the following key word on the code to locate some interesting places on the code:
///
/// -# @b BMK_TODO - We need to finish code this part.
///

#include "wx_log_panel.h"
#include "wx_ext_common.h"

//
// Some internal definess:
//

///
/// @brief All the IDs of the controls of CWxLogPanel.
///
/// This enumerator declaring all the IDs of all the child controls of the 
/// CWxLogPanel class.
///
/// @see CWxLogPanel
///
typedef enum ELogPanelCntIds
{
	E_LOG_PANEL_CNT_UNKNOWN ///< No controls.
};

//
// Private prototypes:
//

//
// Global variables:
//

// Custom events:
const wxEventType g_oTitleEvent = wxNewEventType ();
const wxEventType g_oLogMessageEvent = wxNewEventType ();
const wxEventType g_oMainProgressEvent = wxNewEventType ();
const wxEventType g_oSubProgressEvent = wxNewEventType ();

//
// Constructors / destructors:
//

CWxLogPanel::~CWxLogPanel ()
{
	// Destroy any allocated resource by this instance of CWxLogPanel:
}

//
// Public methods:
//

bool CWxLogPanel::Create (
	wxWindow* pParent,
	wxWindowID iId,
	wxWindow* pEventsWin,
	const wxEventType* pEventType,
	bool bFixedFind,
	const wxPoint& oPosition,
	const wxSize& oSize,
	long lStyle,
	const wxString& strWindowName
	)
{
	// Create the panel:
    if ( !wxPanel::Create ( pParent, iId, oPosition, oSize, lStyle | wxNO_BORDER | wxCLIP_CHILDREN | wxTAB_TRAVERSAL, strWindowName ) )
	{
		// Failed to create the new panel:
        return false;
	} // Endif.

	SetBackgroundColour ( wxSystemSettings::GetColour ( wxSYS_COLOUR_MENU ) );

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

	//
	// Create all the controls:
	//

	// Create the title control:
	m_pOprTitle = new wxStaticText ( this, wxID_ANY, wxT("   "), wxDefaultPosition, wxDefaultSize );
	if ( m_pOprTitle == NULL )
	{
		// Error:
		return false;
	} // Endif.

	// Create the main progress:
	m_pMainProgress = new wxGauge ( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	if ( m_pMainProgress == NULL )
	{
		// Error:
		return false;
	} // Endif.

	// Create the sub progress:
	m_pSubProgress = new wxGauge ( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	if ( m_pSubProgress == NULL )
	{
		// Error:
		return false;
	} // Endif.

	m_pMainProgress->SetValue ( 100 );
	m_pSubProgress->Show ( false );

	// Create the real log object:
	m_pLogPanel = new CWxConsolePanel ( this, wxID_ANY, pEventsWin, pEventType, false, bFixedFind );
	if ( m_pLogPanel == NULL )
	{
		// Error:
		return false;
	} // Endif.

	//
	// Connect all the controls to the sizers:
	//

	m_pMainSizer->Add ( m_pOprTitle, 0, wxEXPAND | wxALL, 3 );
	m_pMainSizer->Add ( m_pMainProgress, 0, wxEXPAND | wxALL, 0 );
	m_pMainSizer->Add ( m_pSubProgress, 0, wxEXPAND | wxALL, 0 );
	m_pMainSizer->Add ( m_pLogPanel, 1, wxEXPAND | wxALL, 2 );

	//
	// Add events:
	//

	// Connect all the control events:
	Connect ( wxID_ANY, g_oTitleEvent, wxCommandEventHandler ( CWxLogPanel::OnUpdateTitle ) );
	Connect ( wxID_ANY, g_oLogMessageEvent, wxCommandEventHandler ( CWxLogPanel::OnUpdateLog ) );
	Connect ( wxID_ANY, g_oMainProgressEvent, wxCommandEventHandler ( CWxLogPanel::OnUpdateMainProgress ) );
	Connect ( wxID_ANY, g_oSubProgressEvent, wxCommandEventHandler ( CWxLogPanel::OnUpdateSubProgress ) );
	// Connect ( D_MENU_MY_ITEM_ID, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler ( CWxLogPanel::OnMenuMyItem ) );
	// Connect ( E_MY_WINDOW_ID, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler ( CWxLogPanel::OnClickMyButton ) );

	// Connect the main sizer:
	SetSizer ( m_pMainSizer );

	// That's all:
	return true;
}

void CWxLogPanel::AddMsgString (
	wxString& oMessage,
	bool bForceBottom
	)
{
	// Pass it to the log object itself:
	m_pLogPanel->AddMsgString ( oMessage, bForceBottom );
}

void CWxLogPanel::AddMsgText (
	const char *szMessage,
	bool bForceBottom
	)
{
	// Pass it to the log object itself:
	m_pLogPanel->AddMsgText ( szMessage, bForceBottom );
}

void CWxLogPanel::AddBinDump (
	unsigned char *pBuffer,
	unsigned int uiSize,
	bool bForceBottom,
	char *szTitle
	)
{
	// Pass it to the log object itself:
	m_pLogPanel->AddBinDump ( pBuffer, uiSize, bForceBottom, szTitle );
}

void CWxLogPanel::AddMsgPartString (
	wxString& oMessage,
	bool bForceBottom
	)
{
	// Pass it to the log object itself:
	m_pLogPanel->AddMsgPartString ( oMessage, bForceBottom );
}

void CWxLogPanel::AddMsgPartText (
	const char *szMessage,
	bool bForceBottom
	)
{
	// Pass it to the log object itself:
	m_pLogPanel->AddMsgPartText ( szMessage, bForceBottom );
}

void CWxLogPanel::EndOfText (
	bool bForceBottom
	)
{
	// Pass it to the log object itself:
	m_pLogPanel->EndOfText ( bForceBottom );
}

wxListBox *CWxLogPanel::GetEventsList ()
{
	// Pass it to the log object itself:
	return m_pLogPanel->GetEventsList ();
}

void CWxLogPanel::SetMaxLines (
	unsigned int uiMaxLines
	)
{
	// Pass it to the log object itself:
	m_pLogPanel->SetMaxLines ( uiMaxLines );
}

void CWxLogPanel::SetMaxFindHistory (
	unsigned int uiMaxHistory
	)
{
	// Pass it to the log object itself:
	m_pLogPanel->SetMaxFindHistory ( uiMaxHistory );
}

bool CWxLogPanel::SaveMessages (
	const char *szFilename,
	bool bSaveMarked,
	bool bSaveUnmarked
	)
{
	// Pass it to the log object itself:
	return m_pLogPanel->SaveMessages ( szFilename, bSaveMarked, bSaveUnmarked );
}

void CWxLogPanel::ClearMessages (
	bool bClearMarked,
	bool bClearUnmarked
	)
{
	// Pass it to the log object itself:
	m_pLogPanel->ClearMessages ( bClearMarked, bClearUnmarked );
}

void CWxLogPanel::FireSetTitle (
	const char *szTitle
	)
{
	wxCommandEvent oEvent; // Event information.
	wxString oText;        // Text data.

	// Fire an event:
	oEvent.SetEventType ( g_oTitleEvent );
	oEvent.SetId ( 0 );
	oEvent.SetEventObject ( this );
	oText = M_STRING_CONVERT ( szTitle );
	oEvent.SetString ( oText );
	WXEXT_AddPendingEvent ( this, oEvent );
}

void CWxLogPanel::FireLogMessage (
	const char *szMessage
	)
{
	wxCommandEvent oEvent; // Event information.
	wxString oText;        // Text data.

	// Fire an event:
	oEvent.SetEventType ( g_oLogMessageEvent );
	oEvent.SetId ( 0 );
	oEvent.SetEventObject ( this );
	oText = M_STRING_CONVERT ( szMessage );
	oEvent.SetString ( oText );
	WXEXT_AddPendingEvent ( this, oEvent );
}

void CWxLogPanel::FireProgressMainEvent (
	unsigned int uiValue,
	unsigned int uiRange,
	int iState
	)
{
	wxCommandEvent oEvent; // Event information.

	// Fire an event:
	oEvent.SetEventType ( g_oMainProgressEvent );
	oEvent.SetId ( iState );
	oEvent.SetEventObject ( this );
	oEvent.SetInt ( uiValue );
	oEvent.SetExtraLong ( uiRange );
	AddPendingEvent ( oEvent );
}

void CWxLogPanel::FireProgressSubEvent (
	unsigned int uiValue,
	unsigned int uiRange,
	int iState
	)
{
	wxCommandEvent oEvent; // Event information.

	// Fire an event:
	oEvent.SetEventType ( g_oSubProgressEvent );
	oEvent.SetId ( iState );
	oEvent.SetEventObject ( this );
	oEvent.SetInt ( uiValue );
	oEvent.SetExtraLong ( uiRange );
	AddPendingEvent ( oEvent );
}

//
// Protected methods:
//

//
// Private methods:
//

void CWxLogPanel::OnUpdateMainProgress (
	wxCommandEvent& oEvent
	)
{
	// Check if we need to display this progress bar:
	if ( oEvent.GetInt () == -1 )
	{
		m_pMainProgress->Show ( false );
		Layout ();
		Refresh ();
		return;
	} // Endif.

	switch ( oEvent.GetId () )
	{
		case 1:
			// BMK_TODO:
			break;

		// Other:
		default:
			break;
	} // End of switch.

	// Check if we need to change the maximum value:
	m_pMainProgress->Show ( true );
	if ( oEvent.GetExtraLong () != -1 )
	{
		m_pMainProgress->SetRange ( oEvent.GetExtraLong () );
		m_pMainProgress->SetToolTip ( wxT("") );
	} // Endif.

	// Change the progress value:
	m_pMainProgress->SetValue ( oEvent.GetInt () );
	Layout ();
	Refresh ();
}

void CWxLogPanel::OnUpdateSubProgress (
	wxCommandEvent& oEvent
	)
{
	// Check if we need to display this progress bar:
	if ( oEvent.GetInt () == -1 )
	{
		m_pSubProgress->Show ( false );
		Layout ();
		Refresh ();
		return;
	} // Endif.

	switch ( oEvent.GetId () )
	{
		case 1:
			// BMK_TODO:
			break;

		// Other:
		default:
			break;
	} // End of switch.

	// Check if we need to change the maximum value:
	m_pSubProgress->Show ( true );
	if ( oEvent.GetExtraLong () != -1 )
	{
		m_pSubProgress->SetRange ( oEvent.GetExtraLong () );
		m_pSubProgress->SetToolTip ( wxT("") );
	} // Endif.

	// Change the progress value:
	m_pSubProgress->SetValue ( oEvent.GetInt () );
	Layout ();
	Refresh ();
}

void CWxLogPanel::OnUpdateTitle (
	wxCommandEvent& oEvent
	)
{
	wxString oText; // Text data.

	// Update the title:
	oText = oEvent.GetString ();
	m_pOprTitle->SetLabel ( oText );
	Layout ();
	Refresh ();
}

void CWxLogPanel::OnUpdateLog (
	wxCommandEvent& oEvent
	)
{
	wxString oText; // Text data.

	// Update the title:
	oText = oEvent.GetString ();
	AddMsgPartString ( oText, true );
	EndOfText ( true );
	Layout ();
	Refresh ();
}

void CWxLogPanel::Init ()
{
	// Initialize all the data members of CWxLogPanel:
	m_pMainSizer = NULL;
	m_pOprTitle = NULL;
	m_pMainProgress = NULL;
	m_pSubProgress = NULL;
	m_pLogPanel = NULL;
}

//
// End of the source file wx_log_panel.cpp
//

