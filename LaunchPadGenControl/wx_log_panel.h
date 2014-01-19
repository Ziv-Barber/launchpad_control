
///
/// @file
/// @brief The class CWxLogPanel.
///
/// This is the header file of the class CWxLogPanel.
///
/// @b Interesting @b Bookmarks:
///
/// Please search for the following key word on the code to locate some interesting places on the code:
///
/// -# @b BMK_TODO - We need to finish code this part.
///
/// @b Script @b Information:
///

#ifndef H_CLS_LOG_PANEL_HEAD
#define H_CLS_LOG_PANEL_HEAD

//
// Header files needed to be include with this class:
//

#include "wx_console_panel.h"

//
// Some public definess:
//

//
// Public prototypes:
//

//
// The CWxLogPanel class declaration:
//

///
/// @brief Log panel.
///
/// This class is a log panel with search features.
///
/// @b Features:
///
/// - Log panel with search options.
/// - Two progress bars.
/// - Title to the log panel.
///
/// @b Example:
///
/// You need to include:
///
/// @code
/// #include "wx_log_panel.h"
/// @endcode
///
/// Create the panel:
///
/// @code
/// CWxLogPanel *pLogPanel; // Pointer to the new log panel.
///
/// // Create the log panel:
/// pLogPanel = new CWxLogPanel ( this, wxID_ANY );
/// if ( pLogPanel == NULL )
/// {
/// 	// Error:
/// 	return false;
/// } // Endif.
///
/// // Configure the panel:
/// pLogPanel->SetMaxLines ( 10000 );
/// pLogPanel->FireSetTitle ( "My Log:" );
/// pLogPanel->FireProgressMainEvent ( (unsigned int) -1 );
///
/// // --- Add pLogPanel to the right sizer ---
/// @endcode
///
/// @see CWxConsolePanel
///
class CWxLogPanel : public wxPanel
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
	/// @brief CWxLogPanel default constructor.
	///
	/// This is the default constructor of the CWxLogPanel class.
	///
	/// @see Create
	/// @see Init
	///
	CWxLogPanel () : wxPanel ()
	{
		// Initialize all the data members of CWxLogPanel:
		Init ();
	}

	///
	/// @brief CWxLogPanel constructor.
	///
	/// This is another constructor of the CWxLogPanel class.
	///
	/// @param[in] pParent Pointer to the parent window.
	/// @param[in] iId Window identifier. If wxID_ANY, will automatically create an identifier.
	/// @param[in] pEventsWin Optional window to receive events.
	/// @param[in] pEventType The type of event to send.
	/// @param[in] bFixedFind Is true to always display the find bar.
	/// @param[in] oPosition panel position. wxDefaultPosition indicates that wxWidgets should generate a default position for this panel.
	/// @param[in] oSize The panel size. wxDefaultSize indicates that wxWidgets should generate a default size for this panel is visible but obviously not correctly sized.
	/// @param[in] lStyle Window style for this panel.
	/// @param[in] strWindowName Window name.
	/// @see Init
	///
	CWxLogPanel (
		wxWindow* pParent,
		wxWindowID iId,
		wxWindow* pEventsWin = NULL,
		const wxEventType* pEventType = NULL,
		bool bFixedFind = false,
		const wxPoint& oPosition = wxDefaultPosition,
		const wxSize& oSize = wxDefaultSize,
		long lStyle = 0,
		const wxString& strWindowName = wxT("wxLogPanel")
		)
	{
		// Initialize all the data members of CWxLogPanel:
		Init ();
		
		// Create the panel:
		Create ( pParent, iId, pEventsWin, pEventType, bFixedFind, oPosition, oSize, lStyle, strWindowName );
	}

	///
	/// @brief CWxLogPanel destructor.
	///
	/// This is the destructor of the CWxLogPanel class.
	///
	virtual ~CWxLogPanel ();

	//
	// Public interface:
	//
public:

	///
	/// @brief Create the new panel.
	///
	/// This method is called by the user only for two-step construction.
	///
	/// @param[in] pParent Pointer to the parent window.
	/// @param[in] iId Window identifier. If wxID_ANY, will automatically create an identifier.
	/// @param[in] pEventsWin Optional window to receive events.
	/// @param[in] pEventType The type of event to send.
	/// @param[in] bFixedFind Is true to always display the find bar.
	/// @param[in] oPosition panel position. wxDefaultPosition indicates that wxWidgets should generate a default position for this panel.
	/// @param[in] oSize panel size. wxDefaultSize indicates that wxWidgets should generate a default size for this panel. If no suitable size can be found, the panel will be sized to 20x20 pixels so that the panel is visible but obviously not correctly sized.
	/// @param[in] lStyle Window style for this panel.
	/// @param[in] strWindowName Window name.
	/// @retval true Operation succeeded.
	/// @retval false Operation failed.
	///
	bool Create (
		wxWindow* pParent,
		wxWindowID iId,
		wxWindow* pEventsWin = NULL,
		const wxEventType* pEventType = NULL,
		bool bFixedFind = false,
		const wxPoint& oPosition = wxDefaultPosition,
		const wxSize& oSize = wxDefaultSize,
		long lStyle = 0,
		const wxString& strWindowName = wxT("wxLogPanel")
		);

	///
	/// @brief Add a line message line into the log.
	///
	/// This method add a new message line into the log.
	///
	/// @param[in] oMessage The message to add.
	/// @param[in] bForceBottom Is true to force the scrollbar to be at the bottom.
	///
	void AddMsgString (
		wxString& oMessage,
		bool bForceBottom
		);

	///
	/// @brief Add a line message line into the log.
	///
	/// This method add a new message line into the log.
	///
	/// @param[in] szMessage The message to add.
	/// @param[in] bForceBottom Is true to force the scrollbar to be at the bottom.
	///
	void AddMsgText (
		const char *szMessage,
		bool bForceBottom
		);

	///
	/// @brief Add a hex dump of a binary data into the log.
	///
	/// This method add a hex dump text of the given binary data into the log.
	///
	/// @param[in] pBuffer The binary data to dump.
	/// @param[in] uiSize The size of the binary data.
	/// @param[in] bForceBottom Is true to force the scrollbar to be at the bottom.
	/// @param[in] szTitle Optional name of this binary dump.
	/// @see AddMsgString
	/// @see AddMsgText
	///
	void AddBinDump (
		unsigned char *pBuffer,
		unsigned int uiSize,
		bool bForceBottom = true,
		char *szTitle = NULL
		);

	///
	/// @brief Add a text into the log.
	///
	/// This method will count any '\n' character inside the given message 
	/// as line break.
	///
	/// @param[in] oMessage The message to add.
	/// @param[in] bForceBottom Is true to force the scrollbar to be at the bottom.
	///
	void AddMsgPartString (
		wxString& oMessage,
		bool bForceBottom
		);

	///
	/// @brief Add a text into the log.
	///
	/// This method will count any '\n' character inside the given message 
	/// as line break.
	///
	/// @param[in] szMessage The message to add.
	/// @param[in] bForceBottom Is true to force the scrollbar to be at the bottom.
	///
	void AddMsgPartText (
		const char *szMessage,
		bool bForceBottom
		);

	///
	/// @brief Finish adding uncompleted message.
	///
	/// Finish to add any uncompleted message that been added by either 
	/// AddMsgPartString() or AddMsgPartText().
	///
	/// @param[in] bForceBottom Is true to force the scrollbar to be at the bottom.
	/// @see AddMsgPartString
	/// @see AddMsgPartText
	///
	void EndOfText (
		bool bForceBottom
		);

	///
	/// @brief Get access to the internal listbox.
	///
	/// Using this method you can do advance operations on the stored events.
	///
	/// @return Pointer to the internal events list.
	///
	wxListBox *GetEventsList ();

	///
	/// @brief Change the maximum lines to hold on the console.
	///
	/// This method control the maximum number of lines that can be hold on the 
	/// console's log.
	///
	/// @param[in] uiMaxLines The maximum lines to display.
	///
	void SetMaxLines (
		unsigned int uiMaxLines
		);

	///
	/// @brief Change the maximum items on the find history list.
	///
	/// This method changing the maximum number of items that can be stored on 
	/// the find history list.
	///
	/// @param[in] uiMaxHistory The new find history size.
	///
	void SetMaxFindHistory (
		unsigned int uiMaxHistory
		);

	///
	/// @brief Save the log messages into file.
	///
	/// This method save the log messages into a text file.
	///
	/// @param[in] szFilename The name of the file to use. If this parameter is equal 
	///            to NULL then the user will be able to select it from a dialog.
	/// @param[in] bSaveMarked Is true to save marked messages.
	/// @param[in] bSaveUnmarked Is true to save unmarked messages.
	/// @retval true Operation succeeded.
	/// @retval false Operation failed.
	/// @see ClearMessages
	///
	bool SaveMessages (
		const char *szFilename = NULL,
		bool bSaveMarked = true,
		bool bSaveUnmarked = true
		);

	///
	/// @brief Clear the log messages.
	///
	/// This method clear messages on the console log.
	///
	/// @param[in] bClearMarked Is true to clear the marked messages.
	/// @param[in] bClearUnmarked Is true to clear the unmarked messages.
	/// @see SaveMessages
	///
	void ClearMessages (
		bool bClearMarked = true,
		bool bClearUnmarked = true
		);

	///
	/// @brief Fire change title event.
	///
	/// This method changing the title of the control.
	///
	/// @param[in] szTitle The new title.
	///
	void FireSetTitle (
		const char *szTitle
		);

	///
	/// @brief Fire a log message.
	///
	/// This method add another log message.
	///
	/// @param[in] szMessage Message to add into the log.
	///
	void FireLogMessage (
		const char *szMessage
		);

	///
	/// @brief Fire event to change the main progress bar.
	///
	/// This method fire an event to update the main progress bar.
	///
	/// @param[in] uiValue The current progress value.
	/// @param[in] uiRange The maximum value.
	/// @param[in] iState Either 1 for normal, 2 for error or 0 to leave as is.
	///
	void FireProgressMainEvent (
		unsigned int uiValue,
		unsigned int uiRange = (unsigned int) -1,
		int iState = 0
		);

	///
	/// @brief Fire event to change the main progress bar.
	///
	/// This method fire an event to update the main progress bar.
	///
	/// @param[in] uiValue The current progress value.
	/// @param[in] uiRange The maximum value.
	/// @param[in] iState Either 1 for normal, 2 for error or 0 to leave as is.
	///
	void FireProgressSubEvent (
		unsigned int uiValue,
		unsigned int uiRange = (unsigned int) -1,
		int iState = 0
		);

	//
	// Callbacks for derived classes to extend CWxLogPanel:
	//
protected:

	//
	// API for derived classes only:
	//
protected:

	//
	// Private interface of the CWxLogPanel class:
	//
private:

	///
	/// @brief Custom event - update progress (main).
	///
	/// This method been called for the update progress custom event.
	///
	/// @param[in] oEvent Event information.
	///
	void OnUpdateMainProgress (
		wxCommandEvent& oEvent
		);

	///
	/// @brief Custom event - update progress (sub).
	///
	/// This method been called for the update progress custom event.
	///
	/// @param[in] oEvent Event information.
	///
	void OnUpdateSubProgress (
		wxCommandEvent& oEvent
		);

	///
	/// @brief Custom event - update the title.
	///
	/// This method been called to update the control's title.
	///
	/// @param[in] oEvent Event information.
	///
	void OnUpdateTitle (
		wxCommandEvent& oEvent
		);

	///
	/// @brief Custom event - update the log.
	///
	/// This method been called to update the log.
	///
	/// @param[in] oEvent Event information.
	///
	void OnUpdateLog (
		wxCommandEvent& oEvent
		);

	///
	/// @brief Initialize this class.
	///
	/// This method been called by any of the constructors of this class to 
	/// initialize all the data members to the default state.
	///
	void Init ();

	//
	// Data members:
	//
private:

	wxBoxSizer *m_pMainSizer;     ///< Pointer to the main sizer.
	CWxConsolePanel *m_pLogPanel; ///< The log panel.
	wxStaticText *m_pOprTitle;    ///< The operation string area on the top of the list.
	wxGauge *m_pMainProgress;     ///< The main progress bar.
	wxGauge *m_pSubProgress;      ///< Sub-progress bar.
};

#endif // H_CLS_LOG_PANEL_HEAD

//
// End of the header file wx_log_panel.h
//

