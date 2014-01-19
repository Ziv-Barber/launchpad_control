
///
/// @file
/// @brief The class CLaunchPadGenMainFrame.
///
/// This is the implementation of the class CLaunchPadGenMainFrame.
///
/// @b Interesting @b Bookmarks:
///
/// Please search for the following key word on the code to locate some interesting places on the code:
///
/// -# @b BMK_TODO - We need to finish code this part.
///

#include "launch_pad_gen_app.h"

#include "wx_ext_common.h"

#include "wx/mstream.h"

// Include this only if you need access to Expat:
// #include "expat.h"

//
// Some internal definess:
//

///
/// @brief All the controls of the main window.
///
/// This enum declaring all the controls of the main window.
///
enum ELauchPadGenControls
{
	E_CNT_BTN_START, ///< Start button.
	E_CNT_BTN_STOP,  ///< Stop button.
	E_CNT_BTN_SAVE,  ///< Save log button.
	E_CNT_BTN_CLEAR  ///< Clear log button.
};

//
// Private prototypes:
//

//
// Global variables:
//

CLaunchPadGenMainFrame *g_pThis; ///< Global save of our this.

// Declare a new event for sending start event:
const wxEventType m_oLaunchPadGenStartEvent = wxNewEventType ();
const wxEventType m_oLaunchPadGenLogEvent = wxNewEventType();

//
// Constructors / destructors:
//

CLaunchPadGenMainFrame::CLaunchPadGenMainFrame (
		wxWindow* pParent,
		const wxString& szTitle,
		const wxPoint& oPosition,
		const wxSize& oSize
		) : wxFrame ( (wxFrame *) NULL, -1, szTitle, oPosition, oSize )
{
	// Initialize all the data members of CLaunchPadGen:
	m_pSplit = NULL;
	m_pControlWin = NULL;
	m_pLogWin = NULL;
	m_pPortsInListPanel = NULL;
	m_pPortsOutListPanel = NULL;
	m_pAppListPanel = NULL;
	m_pMainSizer = NULL;
	m_pMnCtlSizer = NULL;
	m_pMnLogSizer = NULL;
	m_pControlsBar = NULL;
	m_pButtons = NULL;
	m_pPortsInList = NULL;
	m_pPortsOutList = NULL;
	m_pAppList = NULL;
	m_pStartPad = NULL;
	m_pStopPad = NULL;
	m_pSaveLog = NULL;
	m_pClearLog = NULL;
	m_pLogPanel = NULL;
	m_pMidiDev = NULL;
	m_pMidiOutDev = NULL;
	m_bIsInitOk = false;
	m_bIsShutDown = false;
	m_bIsAnimation = true;

	g_pThis = this;
	m_pCntWin = NULL;
	g_pThis->m_uiVisID = wxNOT_FOUND;

	// Create the MIDI input device:
	m_pMidiDev = new RtMidiIn();
	if (m_pMidiDev == NULL)
	{
		// Error:
		return;
	} // Endif.

	// Create the MIDI input device:
	m_pMidiOutDev = new RtMidiOut();
	if (m_pMidiOutDev == NULL)
	{
		// Error:
		return;
	} // Endif.

	// Set the small icon on the window itself:
	SetIcon(wxICON( IDR_MAINFRAME ));

	// Create all the controls:
	m_bIsInitOk = CreateControls ();
}

CLaunchPadGenMainFrame::~CLaunchPadGenMainFrame ()
{
	// Destroy any allocated resource by this instance of CLaunchPadGen:
}

//
// Public methods:
//

//
// Protected methods:
//

//
// Private methods:
//

void CLaunchPadGenMainFrame::OnRunningStart (
	wxCommandEvent& oEvent
	)
{
	wxString strDefDev;                 // Default Launchpad device.
	unsigned int uiLoopCount;           // Loop counter.
	unsigned int uiDevices;             // Number of MIDI devices exists.
	size_t uiLaunchpadID = wxNOT_FOUND; // For auto-detection the Launchpad.

	// Get all the input MIDI devices:
	uiDevices = m_pMidiDev->getPortCount();
	for (uiLoopCount = 0; uiLoopCount < uiDevices; uiLoopCount++)
	{
		if ((uiLaunchpadID == wxNOT_FOUND) && (m_pMidiDev->getPortName(uiLoopCount).find_first_of("Launcgpad")))
		{
			strDefDev = m_pMidiDev->getPortName(uiLoopCount);
			uiLaunchpadID = m_pPortsInList->GetCount();
		} // Endif.

		m_pPortsInList->Append(m_pMidiDev->getPortName(uiLoopCount));
	} // End of for loop.

	// Get all the output MIDI devices:
	uiDevices = m_pMidiOutDev->getPortCount();
	for (uiLoopCount = 0; uiLoopCount < uiDevices; uiLoopCount++)
	{
		m_pPortsOutList->Append(m_pMidiOutDev->getPortName(uiLoopCount));
	} // End of for loop.

	if (uiLaunchpadID != wxNOT_FOUND)
	{
		size_t ulOutId;

		m_pPortsInList->Select ( uiLaunchpadID );
		ulOutId = m_pPortsOutList->FindString(strDefDev);
		if (ulOutId != wxNOT_FOUND)
		{
			m_pPortsOutList->Select(ulOutId);
		} // Endif.
	} // Endif.

	// Get the current windows:
	EnumWindows(CLaunchPadGenMainFrame::OnEnumWindows, 0);

	if (g_pThis->m_uiVisID != wxNOT_FOUND)
	{
		m_pAppList->Select(g_pThis->m_uiVisID);
	} // Endif.

	m_pStartPad->Enable(true);
}

void CLaunchPadGenMainFrame::OnClose (
	wxCloseEvent& oEvent
	)
{
	// Destroy the MIDI handlers:
	delete m_pMidiDev;
	delete m_pMidiOutDev;

	// This code close the application:
	oEvent.Skip ();
}

void CLaunchPadGenMainFrame::OnLogEvent(
	wxCommandEvent& oEvent
	)
{
	// Check what command to do:
	switch (oEvent.GetInt())
	{
		// The events messages is empty:
	case CWxConsolePanel::E_OE_CLEAR_LIST:
		m_pSaveLog->Enable(false);
		m_pClearLog->Enable(false);
		break;

		// The events messages is filled:
	case CWxConsolePanel::E_OE_FILL_LIST:
		m_pSaveLog->Enable(true);
		m_pClearLog->Enable(true);
		break;

		// The user entered a command:
	case CWxConsolePanel::E_OE_SEND_CMD:
		break;

		// Unknown:
	default:
		break;
	} // End of switch.
}

void CLaunchPadGenMainFrame::OnClickBtnStart(
	wxCommandEvent& oEvent
	)
{
	unsigned int uiInDev = (unsigned int)m_pPortsInList->GetSelection();
	unsigned int uiOutDev = (unsigned int)m_pPortsOutList->GetSelection();
	unsigned int uiAppId;

	if (uiInDev == wxNOT_FOUND)
	{
		m_pLogPanel->AddMsgText("ERROR: Please select an input MIDI device.", true);
		return;
	} // Endif.

	if (uiOutDev == wxNOT_FOUND)
	{
		m_pLogPanel->AddMsgText("WARNING: Without an output MIDI device you'll see no light feedback on your Launchpad.", true);
	} // Endif.

	try
	{
		m_pMidiDev->openPort(uiInDev);
		m_pMidiDev->ignoreTypes(false, false, false);
		m_pMidiDev->setCallback(CLaunchPadGenMainFrame::OnMidiInput, this);

		if (uiOutDev != wxNOT_FOUND)
		{
			m_pMidiOutDev->openPort(uiOutDev);
		} // Endif.

	} catch (RtError &error) {
		wxString strErr = error.getMessage();
		m_pLogPanel->AddMsgString(strErr, true);
		return;
	} // Enidif.

	m_pStartPad->Enable(false);
	m_pStopPad->Enable(true);

	m_pCntWin = NULL;
	uiAppId = m_pAppList->GetSelection();
	if (uiAppId != wxNOT_FOUND)
	{
		m_pCntWin = m_oAppsInfo[uiAppId];
		SetForegroundWindow(m_pCntWin);

	} else
	{
		m_pLogPanel->AddMsgText("WARNING: No application been selected.", false);
	} // Endif.

	std::vector< unsigned char > oMessage;

	oMessage.push_back(0xF0);
	oMessage.push_back(0);
	oMessage.push_back(0x20);
	oMessage.push_back(0x29);
	oMessage.push_back(0x9);
	oMessage.push_back(31);
	oMessage.push_back('H');
	oMessage.push_back('E');
	oMessage.push_back('L');
	oMessage.push_back('L');
	oMessage.push_back('O');
	oMessage.push_back(0xF7);
	m_bIsAnimation = true;
	m_pMidiOutDev->sendMessage(&oMessage);
}

void CLaunchPadGenMainFrame::OnClickBtnStop(
	wxCommandEvent& oEvent
	)
{
	std::vector< unsigned char > oMessage;

	// Stop the animation if running:
	if (m_bIsAnimation)
	{
		oMessage.push_back(0xF0);
		oMessage.push_back(0);
		oMessage.push_back(0x20);
		oMessage.push_back(0x29);
		oMessage.push_back(0x9);
		oMessage.push_back(0);
		oMessage.push_back(0xF7);
		m_bIsAnimation = false;
		m_pMidiOutDev->sendMessage(&oMessage);
		Sleep(200);
	} // Endif.

	// Clean after us:
	m_pCntWin = NULL;
	m_pMidiDev->cancelCallback();
	m_pMidiDev->closePort();
	m_pMidiOutDev->closePort();
	m_pStartPad->Enable(true);
	m_pStopPad->Enable(false);
}

void CLaunchPadGenMainFrame::OnClickBtnSave(
	wxCommandEvent& oEvent
	)
{
	// Save the log:
	m_pLogPanel->SaveMessages();
}

void CLaunchPadGenMainFrame::OnClickBtnClear(
	wxCommandEvent& oEvent
	)
{
	// Clear the log:
	m_pLogPanel->ClearMessages();
}

void CLaunchPadGenMainFrame::OnMidiInput(
	double deltatime,
	std::vector< unsigned char > *pMessage,
	void *userData
	)
{
	char szMessage[128];           // The message to send.
	CLaunchPadGenMainFrame *pThis; // Pointer to our this.

	// Get access to the main frame:
	pThis = (CLaunchPadGenMainFrame *)userData;
	if (pThis == NULL)
	{
		// Error:
		return;
	} // Endif.

	// Message dump:
	if (pMessage->size() == 0)
	{
		pThis->m_pLogPanel->FireLogMessage("MIDI empty message");

	}
	else if (pMessage->size() == 1)
	{
		sprintf_s(szMessage, 127, "%d = %d", pMessage->size(), pMessage->at(0));
		pThis->m_pLogPanel->FireLogMessage(szMessage);

	} else if (pMessage->size() == 2)
	{
		sprintf_s(szMessage, 127, "%d = %d %d", pMessage->size(), pMessage->at(0), pMessage->at(1));
		pThis->m_pLogPanel->FireLogMessage(szMessage);

	} else
	{
		sprintf_s(szMessage, 127, "%d = %d %d %d", pMessage->size(), pMessage->at(0), pMessage->at(1), pMessage->at(2));
		pThis->m_pLogPanel->FireLogMessage(szMessage);
	} // Endif.

	if (pMessage->size() == 3)
	{
		if ((pMessage->at(0) == 176) && (pMessage->at(1) == 0) && (pMessage->at(2) == 3) && (pThis->m_bIsAnimation == true))
		{
			std::vector< unsigned char > oMessage;

			// Stop the last animation:
			oMessage.push_back(0xF0);
			oMessage.push_back(0);
			oMessage.push_back(0x20);
			oMessage.push_back(0x29);
			oMessage.push_back(0x9);
			oMessage.push_back(0);
			oMessage.push_back(0xF7);
			pThis->m_bIsAnimation = false;
			pThis->m_pMidiOutDev->sendMessage(&oMessage);

		} else
		{
			pThis->m_pMidiOutDev->sendMessage(pMessage);

			if (pThis->m_pCntWin != NULL)
			{
				INPUT oKeyData;
				unsigned int ucLaunchpadKey = pMessage->at(1);

				oKeyData.type = INPUT_KEYBOARD;
				oKeyData.ki.wScan = 0; // hardware scan code for key
				oKeyData.ki.time = 0;
				oKeyData.ki.dwExtraInfo = 0;
				oKeyData.ki.dwFlags = pMessage->at(2) > 0 ? 0 : KEYEVENTF_KEYUP;

				// Ugly but for this hack it'll be OK:
				if ((pMessage->at(0) == 176) && (pMessage->at(1) > 103))
				{
					if (ucLaunchpadKey == 104)
					{
						oKeyData.ki.wVk = VK_F1;
						SendInput(1, &oKeyData, sizeof(INPUT));

					} else if (ucLaunchpadKey == 105)
					{
						oKeyData.ki.wVk = VK_F2;
						SendInput(1, &oKeyData, sizeof(INPUT));

					} else if (ucLaunchpadKey == 106)
					{
						oKeyData.ki.wVk = VK_F3;
						SendInput(1, &oKeyData, sizeof(INPUT));

					} else if (ucLaunchpadKey == 107)
					{
						oKeyData.ki.wVk = VK_F4;
						SendInput(1, &oKeyData, sizeof(INPUT));

					} else if (ucLaunchpadKey == 108)
					{
						oKeyData.ki.wVk = VK_F5;
						SendInput(1, &oKeyData, sizeof(INPUT));

					} else if (ucLaunchpadKey == 109)
					{
						oKeyData.ki.wVk = VK_F6;
						SendInput(1, &oKeyData, sizeof(INPUT));

					} else if (ucLaunchpadKey == 110)
					{
						oKeyData.ki.wVk = VK_F7;
						SendInput(1, &oKeyData, sizeof(INPUT));

					} else if (ucLaunchpadKey == 111)
					{
						oKeyData.ki.wVk = VK_F8;
						SendInput(1, &oKeyData, sizeof(INPUT));
					} // Endif.

				} else if (pMessage->at(0) == 144)
				{
					if (ucLaunchpadKey == 8)
					{
						oKeyData.ki.wVk = VK_F5;
						SendInput(1, &oKeyData, sizeof(INPUT));

					} else if (ucLaunchpadKey == 24)
					{
						oKeyData.ki.wVk = VK_F6;
						SendInput(1, &oKeyData, sizeof(INPUT));

					} else if (ucLaunchpadKey == 40)
					{
						oKeyData.ki.wVk = VK_F7;
						SendInput(1, &oKeyData, sizeof(INPUT));

					} else if (ucLaunchpadKey == 56)
					{
						oKeyData.ki.wVk = VK_F8;
						SendInput(1, &oKeyData, sizeof(INPUT));

					} else if (ucLaunchpadKey == 72)
					{
						oKeyData.ki.wVk = VK_F9;
						SendInput(1, &oKeyData, sizeof(INPUT));

					} else if (ucLaunchpadKey == 88)
					{
						oKeyData.ki.wVk = VK_F10;
						SendInput(1, &oKeyData, sizeof(INPUT));

					} else if (ucLaunchpadKey == 104)
					{
						oKeyData.ki.wVk = VK_F11;
						SendInput(1, &oKeyData, sizeof(INPUT));

					} else if (ucLaunchpadKey == 120)
					{
						oKeyData.ki.wVk = VK_F12;
						SendInput(1, &oKeyData, sizeof(INPUT));
					} // Endif.
				} // Endif.
			} // Endif.
		} // Endif.
	} // Endif.
}

BOOL CALLBACK CLaunchPadGenMainFrame::OnEnumWindows(
	HWND hwnd,
	LPARAM lParam
	)
{
	wchar_t oTitle[256]; // Window's title.

	// Crash protection:
	if (hwnd == NULL)
	{
		// Error:
		return FALSE;
	} // Endif.

	// Get the title of this window:
	if (GetWindowText(hwnd, oTitle, 255))
	{
		if ((g_pThis->m_uiVisID == wxNOT_FOUND) && (wcsstr(oTitle, L"Visual Studio") != NULL))
		{
			g_pThis->m_pCntWin = hwnd;
			g_pThis->m_uiVisID = g_pThis->m_pAppList->GetCount();
		} // Endif.

		g_pThis->m_oAppsInfo[g_pThis->m_pAppList->GetCount()] = hwnd;
		g_pThis->m_pAppList->Append(oTitle);
	} // Endif.

	// Get more:
	return TRUE;
}

bool CLaunchPadGenMainFrame::CreateControls()
{
	// General configurations:
	CreateStatusBar ();
	SetStatusText ( D_LAUNCH_PAD_GEN_PROJECT_NAME " version " D_LAUNCH_PAD_GEN_CNF_VERSION_A );
	SetBackgroundColour ( *wxLIGHT_GREY );

	//
	// Splitters and windows:
	//

	// Create the main splitter:
	m_pSplit = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE | wxSP_3D);
	if (m_pSplit == NULL)
	{
		// Error:
		return false;
	} // Endif.

	// Create the top window:
	m_pControlWin = new wxWindow(m_pSplit, wxID_ANY);
	if (m_pControlWin == NULL)
	{
		// Error:
		return false;
	} // Endif.

	// Create the bottom window:
	m_pLogWin = new wxWindow(m_pSplit, wxID_ANY);
	if (m_pLogWin == NULL)
	{
		// Error:
		return false;
	} // Endif.

	m_pPortsInListPanel = new CWxBorderPanel(m_pControlWin, wxID_ANY, CWxBorderPanel::E_BRDSZ_TY_VERTICAL, wxT("Midi Input Ports:"));
	if (m_pPortsInListPanel == NULL)
	{
		// Error:
		return false;
	} // Endif.

	m_pPortsOutListPanel = new CWxBorderPanel(m_pControlWin, wxID_ANY, CWxBorderPanel::E_BRDSZ_TY_VERTICAL, wxT("Midi Output Ports:"));
	if (m_pPortsOutListPanel == NULL)
	{
		// Error:
		return false;
	} // Endif.

	m_pAppListPanel = new CWxBorderPanel(m_pControlWin, wxID_ANY, CWxBorderPanel::E_BRDSZ_TY_VERTICAL, wxT("Applications:"));
	if (m_pAppListPanel == NULL)
	{
		// Error:
		return false;
	} // Endif.

	//
	// Create all the sizers:
	//

	// Create the main sizer:
	m_pMainSizer = new wxBoxSizer(wxVERTICAL);
	if (m_pMainSizer == NULL)
	{
		// Error:
		return false;
	} // Endif.

	// Create the main sizer of the top window:
	m_pMnCtlSizer = new wxBoxSizer(wxVERTICAL);
	if (m_pMnCtlSizer == NULL)
	{
		// Error:
		return false;
	} // Endif.

	// Create the main sizer of the bottom window:
	m_pMnLogSizer = new wxBoxSizer(wxVERTICAL);
	if (m_pMnLogSizer == NULL)
	{
		// Error:
		return false;
	} // Endif.

	// Create the controls area sizer:
	m_pControlsBar = new wxBoxSizer(wxHORIZONTAL);
	if (m_pControlsBar == NULL)
	{
		// Error:
		return false;
	} // Endif.

	// Create the buttons bar sizer:
	m_pButtons = new wxBoxSizer(wxHORIZONTAL);
	if (m_pButtons == NULL)
	{
		// Error:
		return false;
	} // Endif.

	//
	// Create all the controls:
	//

	// Create a listbox to place all the midi input ports:
	m_pPortsInList = WXEXT_CreateListBox(m_pPortsInListPanel->GetBorderPanel(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLB_SINGLE | wxLB_HSCROLL);
	if (m_pPortsInList == NULL )
	{
		// Error:
		return false;
	} // Endif.

	// Create a listbox to place all the midi output ports:
	m_pPortsOutList = WXEXT_CreateListBox(m_pPortsOutListPanel->GetBorderPanel(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLB_SINGLE | wxLB_HSCROLL);
	if (m_pPortsOutList == NULL)
	{
		// Error:
		return false;
	} // Endif.

	// Create a listbox to place all the applications:
	m_pAppList = WXEXT_CreateListBox(m_pAppListPanel->GetBorderPanel(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLB_SINGLE | wxLB_HSCROLL);
	if (m_pAppList == NULL)
	{
		// Error:
		return false;
	} // Endif.

	// Create the start button:
	m_pStartPad = new wxButton(m_pControlWin, E_CNT_BTN_START, wxT("Start Using Launchpad"));
	if (m_pStartPad == NULL)
	{
		// Error:
		return false;
	} // Endif.

	// Create the stop button:
	m_pStopPad = new wxButton(m_pControlWin, E_CNT_BTN_STOP, wxT("Stop Using Launchpad"));
	if (m_pStopPad == NULL)
	{
		// Error:
		return false;
	} // Endif.

	// Create the save log button:
	m_pSaveLog = new wxButton(m_pControlWin, E_CNT_BTN_SAVE, wxT("Save Log..."));
	if (m_pSaveLog == NULL)
	{
		// Error:
		return false;
	} // Endif.

	// Create the clear log button:
	m_pClearLog = new wxButton(m_pControlWin, E_CNT_BTN_CLEAR, wxT("Clear Log..."));
	if (m_pClearLog == NULL)
	{
		// Error:
		return false;
	} // Endif.

	// Disable all the buttons:
	m_pStartPad->Enable(false);
	m_pStopPad->Enable(false);
	m_pSaveLog->Enable(false);
	m_pClearLog->Enable(false);

	// Create the log panel:
	m_pLogPanel = new CWxLogPanel(m_pLogWin, wxID_ANY, m_pLogWin, &m_oLaunchPadGenLogEvent, true);
	if (m_pLogPanel == NULL)
	{
		// Error:
		return false;
	} // Endif.

	// Configure the log panel:
	m_pLogPanel->FireProgressMainEvent(-1);
	m_pLogPanel->FireSetTitle("Not connected to any application");

	//
	// Connect all the sizers to the main sizer:
	//

	// The controls area:
	m_pPortsInListPanel->GetBorderSizer()->Add(m_pPortsInList, 1, wxEXPAND | wxALL, 2);
	m_pPortsOutListPanel->GetBorderSizer()->Add(m_pPortsOutList, 1, wxEXPAND | wxALL, 2);
	m_pAppListPanel->GetBorderSizer()->Add(m_pAppList, 1, wxEXPAND | wxALL, 2);
	m_pControlsBar->Add(m_pPortsInListPanel, 1, wxEXPAND | wxALL, 5);
	m_pControlsBar->Add(m_pPortsOutListPanel, 1, wxEXPAND | wxALL, 5);
	m_pControlsBar->Add(m_pAppListPanel, 1, wxEXPAND | wxALL, 5);
	m_pMnCtlSizer->Add(m_pControlsBar, 1, wxEXPAND | wxALL, 2);

	// The buttons area:
	m_pButtons->Add(m_pStartPad, 0, wxALL, 2);
	m_pButtons->Add(m_pStopPad, 0, wxALL, 2);
	m_pButtons->AddSpacer(20);
	m_pButtons->Add(m_pSaveLog, 0, wxALL, 2);
	m_pButtons->Add(m_pClearLog, 0, wxALL, 2);
	m_pMnCtlSizer->Add(m_pButtons, 0, wxALIGN_CENTER, 0);

	m_pControlWin->SetSizer(m_pMnCtlSizer);

	// Log window:
	m_pMnLogSizer->Add(m_pLogPanel, 1, wxEXPAND | wxALL, 2);
	m_pLogWin->SetSizer(m_pMnLogSizer);

	m_pMainSizer->Add(m_pSplit, 1, wxEXPAND | wxALL, 5);

	// Connect these windows to the splitter:
	m_pSplit->SplitHorizontally(m_pControlWin, m_pLogWin, 200);
	m_pSplit->SetMinimumPaneSize(50);

	//
	// Add events:
	//

	// Buttons events:
	Connect(E_CNT_BTN_START, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CLaunchPadGenMainFrame::OnClickBtnStart), NULL, this);
	Connect(E_CNT_BTN_STOP, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CLaunchPadGenMainFrame::OnClickBtnStop), NULL, this);
	Connect(E_CNT_BTN_SAVE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CLaunchPadGenMainFrame::OnClickBtnSave), NULL, this);
	Connect(E_CNT_BTN_CLEAR, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CLaunchPadGenMainFrame::OnClickBtnClear), NULL, this);

	// Close event:
	Connect ( wxID_ANY, wxEVT_CLOSE_WINDOW, wxCloseEventHandler ( CLaunchPadGenMainFrame::OnClose ) );

	// Custom events:
	Connect ( wxID_ANY, m_oLaunchPadGenStartEvent, wxCommandEventHandler ( CLaunchPadGenMainFrame::OnRunningStart ) );
	Connect(wxID_ANY, m_oLaunchPadGenLogEvent, wxCommandEventHandler(CLaunchPadGenMainFrame::OnLogEvent));

	// Connect the main sizer with our frame:
	m_pMainSizer->SetMinSize ( 600,480 );
	m_pMainSizer->SetSizeHints ( this ); // This code MUST be placed AFTER all the calls to SetMinSize().
	SetSizer ( m_pMainSizer );
	SetAutoLayout ( TRUE );
	Centre (); // Put the window on the center of the screen.

	//
	// Send custom event to start the logic:
	//

    wxCommandEvent oEvent ( m_oLaunchPadGenStartEvent, 0 );
    oEvent.SetEventObject ( this );
    AddPendingEvent ( oEvent );

	// That's all:
	return true;
}

//
// End of the source file launch_pad_gen_dlg.cpp
//

