
///
/// @file
/// @brief The class CLaunchPadGenMainFrame.
///
/// This is the header file of the class CLaunchPadGenMainFrame.
///
/// @b Interesting @b Bookmarks:
///
/// Please search for the following key word on the code to locate some interesting places on the code:
///
/// -# @b BMK_TODO - We need to finish code this part.
///

#ifndef H_CLS_LAUNCH_PAD_GEN_MF_HEAD
#define H_CLS_LAUNCH_PAD_GEN_MF_HEAD

//
// Header files needed to be include with this class:
//

#include "wx/wx.h"
#include "wx/image.h"
#include "wx/bitmap.h"
#include "wx/dc.h"
#include "wx/rawbmp.h"
#include "wx/mediactrl.h"
#include "wx/wxhtml.h"
#include "wx/wfstream.h"
#include "wx/splitter.h"

#include "wx_log_panel.h"
#include "wx_border_panel.h"

#include "launch_pad_gen_conf.h"

#include "RtMidi.h"

#include <map>

//
// Some public definess:
//

//
// Public prototypes:
//

//
// The CLaunchPadGenMainFrame class declaration:
//

///
/// @brief The main frame of the LaunchPadGen application.
///
/// This is the main frame of the LaunchPadGen application.
///
class CLaunchPadGenMainFrame : public wxFrame
{
	//
	// Some definess for this class:
	//
private:

	//
	// Constructors / destructors:
	//
public:

	///
	/// @brief CLaunchPadGenMainFrame constructor.
	///
	/// This is the constructor of the CLaunchPadGenMainFrame class.
	///
	/// @param[in] pParent Pointer to the parent window.
	/// @param[in] szTitle The title of this frame.
	/// @param[in] oPosition Position on the screen.
	/// @param[in] oSize Size of this frame.
	/// @see CLaunchPadGenMainFrame::~CLaunchPadGenMainFrame
	///
	CLaunchPadGenMainFrame (
		wxWindow* pParent,
		const wxString& szTitle,
		const wxPoint& oPosition,
		const wxSize& oSize
		);

	///
	/// @brief CLaunchPadGenMainFrame destructor.
	///
	/// This is the destructor of the CLaunchPadGenMainFrame class.
	///
	/// @see CLaunchPadGenMainFrame::CLaunchPadGenMainFrame
	///
	virtual ~CLaunchPadGenMainFrame ();

	//
	// Public interface:
	//
public:

	///
	/// @brief Check if the initialization operation passed.
	///
	/// This method check that we have all the controls.
	///
	/// @retval true Operation succeeded.
	/// @retval false Operation failed.
	///
	bool IsInitOK ()
	{
		// Return the initialization flag:
		return m_bIsInitOk;
	}

	//
	// Callbacks for derived classes to extend CLaunchPadGenMainFrame:
	//
protected:

	//
	// API for derived classes only:
	//
protected:

	//
	// Private interface of the CLaunchPadGenMainFrame class:
	//
private:

	///
	/// @brief Start the application.
	///
	/// This method been called after the application started and also all 
	/// the controls been created.
	///
	/// @param[in] oEvent Event information.
	///
	void OnRunningStart (
		wxCommandEvent& oEvent
		);

	///
	/// @brief Close event callback.
	///
	/// This method been called when the main window of the application is 
	/// going to be closed.
	///
	/// @param[in] oEvent Event information.
	///
	void OnClose (
		wxCloseEvent& oEvent
		);

	///
	/// @brief Handle events sent by the log panel.
	///
	/// This method been called to handle the events of the log panel.
	///
	/// @param[in] oEvent Event information.
	///
	void OnLogEvent(
		wxCommandEvent& oEvent
		);

	///
	/// @brief Button click event - "Start Using Launchpad".
	///
	/// This method been called when the user click on the "Start Using Launchpad" button.
	///
	/// @param[in] oEvent Event information.
	///
	void OnClickBtnStart(
		wxCommandEvent& oEvent
		);

	///
	/// @brief Button click event - "Stop Using Launchpad".
	///
	/// This method been called when the user click on the "Stop Using Launchpad" button.
	///
	/// @param[in] oEvent Event information.
	///
	void OnClickBtnStop(
		wxCommandEvent& oEvent
		);

	///
	/// @brief Button click event - "Save Log".
	///
	/// This method been called when the user click on the "Save Log" button.
	///
	/// @param[in] oEvent Event information.
	///
	void OnClickBtnSave(
		wxCommandEvent& oEvent
		);

	///
	/// @brief Button click event - "Clear Log".
	///
	/// This method been called when the user click on the "Clear Log" button.
	///
	/// @param[in] oEvent Event information.
	///
	void OnClickBtnClear(
		wxCommandEvent& oEvent
		);

	///
	/// @brief Called when a new MIDI message arraived.
	///
	/// This function been called when we have a new MIDI message.
	///
	/// @param[in] deltatime Delta time.
	/// @param[in] message The MIDI message.
	/// @param[in] userData Pointer to our instance.
	///
	static void OnMidiInput(
		double deltatime,
		std::vector< unsigned char > *message,
		void *userData
		);

	///
	/// @brief Callback called by Windows for every window exist.
	///
	/// This function receive an handle to a window.
	///
	/// @param[in] hwnd Handle to a window.
	/// @param[in] lParam This parameter is unused.
	///
	static BOOL CALLBACK OnEnumWindows(
		HWND hwnd,
		LPARAM lParam
		);

	///
	/// @brief Create all the frame's controls.
	///
	/// This method creates all the controls of this frame.
	///
	/// @retval true Operation succeeded.
	/// @retval false Operation failed.
	///
	bool CreateControls ();

	//
	// Data members:
	//
private:

	// Splitters and windows:
	wxSplitterWindow *m_pSplit;           ///< Main splitter.
	wxWindow *m_pControlWin;              ///< Control window.
	wxWindow *m_pLogWin;                  ///< Log window.
	CWxBorderPanel *m_pPortsInListPanel;  ///< Ports list panel.
	CWxBorderPanel *m_pPortsOutListPanel; ///< Ports list panel.
	CWxBorderPanel *m_pAppListPanel;      ///< Applications list panel.

	// Sizer based controls:
	wxBoxSizer *m_pMainSizer;   ///< Pointer to the main sizer.
	wxBoxSizer *m_pMnCtlSizer;  ///< Pointer to the main control panel sizer.
	wxBoxSizer *m_pMnLogSizer;  ///< Pointer to the main log panel sizer.
	wxBoxSizer *m_pControlsBar; ///< Pointer to the controls area sizer.
	wxBoxSizer *m_pButtons;     ///< Pointer to the buttons bar sizer.

	// All the controls:
	wxListBox *m_pPortsInList;  ///< Listbox to display all the midi input ports.
	wxListBox *m_pPortsOutList; ///< Listbox to display all the midi output ports.
	wxListBox *m_pAppList;      ///< Listbox to display all the application to monitor.
	wxButton *m_pStartPad;      ///< The "Start Using Launchpad" button control.
	wxButton *m_pStopPad;       ///< The "Stop Using Launchpad" button control.
	wxButton *m_pSaveLog;       ///< The "Save Log" button control.
	wxButton *m_pClearLog;      ///< The "Clear Log" button control.
	CWxLogPanel *m_pLogPanel;   ///< The log messages panel.

	std::map<int, HWND> m_oAppsInfo; ///< Map to translate the application ID on the listbox to window handle.

	RtMidiIn *m_pMidiDev;     ///< Midi in device.
	RtMidiOut *m_pMidiOutDev; ///< Midi out device.
	HWND m_pCntWin;           ///< Controled window handle.
	unsigned int m_uiVisID;   ///< Visual Studio first window.
	bool m_bIsInitOk;         ///< This data member is true if everything been initialized without any errors.
	bool m_bIsShutDown;       ///< Is true to force shutdown.
	bool m_bIsAnimation;      ///< Is true if we are in animation mode.
};

#endif // H_CLS_LAUNCH_PAD_GEN_MF_HEAD

//
// End of the header file launch_pad_gen_dlg.h
//

