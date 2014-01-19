
///
/// @file
/// @brief The class CWxConsolePanel.
///
/// This is the header file of the class CWxConsolePanel.
///
/// @b Interesting @b Bookmarks:
///
/// Please search for the following key word on the code to locate some interesting places on the code:
///
/// -# @b BMK_TODO - We need to finish code this part.
///
/// @b Script @b Information:
///

#ifndef H_CLS_CONSOLE_PANEL_HEAD
#define H_CLS_CONSOLE_PANEL_HEAD

//
// Header files needed to be include with this class:
//

#include "wx/wx.h"
#include "wx/dc.h"

//
// Some public definess:
//

//
// Public prototypes:
//

//
// The CWxConsolePanel class declaration:
//

///
/// @brief Console panel.
///
/// This class is a console panel which can be used on your wxWidgets based 
/// application. The user can enter commands on the input bar at the bottom 
/// of the panel and your console's handler can display response messages on 
/// the text area of the console. The user can search for text on the text 
/// area using the find bar on the top area of the console panel.
///
/// @b Features:
///
/// - Console input with history.
/// - Log panel with search options.
///
/// @b Example:
///
/// You need to include:
///
/// @code
/// #include "wx_console_panel.h"
/// @endcode
///
/// Create the panel:
///
/// @code
/// CWxConsolePanel *pPanel; // Pointer to the new panel.
///
/// // Create a new console panel:
/// pPanel = new CWxConsolePanel ( this, wxID_ANY );
/// if ( pPanel == NULL )
/// {
/// 	// Error:
/// 	return false;
/// } // Endif.
/// @endcode
///
/// @see CWxLogPanel
///
class CWxConsolePanel : public wxPanel
{
	//
	// Some definess for this class:
	//
public:

	///
	/// @brief List of output event types.
	///
	/// This enum declaring all the possible events that can be sent from 
	/// this panel.
	///
	enum EOutEvent
	{
		E_OE_CLEAR_LIST = 0, ///< The events list been cleared.
		E_OE_FILL_LIST,      ///< There's at last one event on the list.
		E_OE_SEND_CMD        ///< A new console command.
	};

	///
	/// @brief Search types list.
	///
	/// This enum declaring all the possible search types.
	///
	enum ESearchType
	{
		E_ST_MATCH_PART = 0, ///< Find string.
		E_ST_MATCH_ALL,      ///< Find all the text.
		E_ST_WC_PART,        ///< Wildcard search.
		E_ST_WC_ALL,         ///< Wildcard on all the text.
		E_ST_REGEX           ///< Regular expression.
	};

	//
	// Constructors / destructors:
	//
public:

	///
	/// @brief CWxConsolePanel default constructor.
	///
	/// This is the default constructor of the CWxConsolePanel class.
	///
	/// @see Create
	/// @see Init
	///
	CWxConsolePanel () : wxPanel ()
	{
		// Initialize all the data members of CWxConsolePanel:
		Init ();
	}

	///
	/// @brief CWxConsolePanel constructor.
	///
	/// This is another constructor of the CWxConsolePanel class.
	///
	/// @param[in] pParent Pointer to the parent window.
	/// @param[in] iId Window identifier. If wxID_ANY, will automatically create an identifier.
	/// @param[in] pEventsWin Optional window to receive events.
	/// @param[in] pEventType The type of event to send.
	/// @param[in] bShowInput Is true to display the command input bar.
	/// @param[in] bFixedFind Is true to always display the find bar.
	/// @param[in] oPosition panel position. wxDefaultPosition indicates that wxWidgets should generate a default position for this panel.
	/// @param[in] oSize The panel size. wxDefaultSize indicates that wxWidgets should generate a default size for this panel is visible but obviously not correctly sized.
	/// @param[in] lStyle Window style for this panel.
	/// @param[in] strWindowName Window name.
	/// @see Init
	///
	CWxConsolePanel (
		wxWindow* pParent,
		wxWindowID iId,
		wxWindow* pEventsWin = NULL,
		const wxEventType* pEventType = NULL,
		bool bShowInput = true,
		bool bFixedFind = false,
		const wxPoint& oPosition = wxDefaultPosition,
		const wxSize& oSize = wxDefaultSize,
		long lStyle = 0,
		const wxString& strWindowName = wxT("wxConsolePanel")
		)
	{
		// Initialize all the data members of CWxConsolePanel:
		Init ();
		
		// Create the panel:
		Create ( pParent, iId, pEventsWin, pEventType, bShowInput, bFixedFind, oPosition, oSize, lStyle, strWindowName );
	}

	///
	/// @brief CWxConsolePanel destructor.
	///
	/// This is the destructor of the CWxConsolePanel class.
	///
	virtual ~CWxConsolePanel ();

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
	/// @param[in] bShowInput Is true to display the command input bar.
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
		bool bShowInput = true,
		bool bFixedFind = false,
		const wxPoint& oPosition = wxDefaultPosition,
		const wxSize& oSize = wxDefaultSize,
		long lStyle = 0,
		const wxString& strWindowName = wxT("wxConsolePanel")
		);

	///
	/// @brief Add a line message line into the log.
	///
	/// This method add a new message line into the log.
	///
	/// @param[in] oMessage The message to add.
	/// @param[in] bForceBottom Is true to force the scrollbar to be at the bottom.
	/// @see AddMsgText
	/// @see AddBinDump
	/// @see AddMsgPartString
	///
	void AddMsgString (
		wxString& oMessage,
		bool bForceBottom = true
		);

	///
	/// @brief Add a line message line into the log.
	///
	/// This method add a new message line into the log.
	///
	/// @param[in] szMessage The message to add.
	/// @param[in] bForceBottom Is true to force the scrollbar to be at the bottom.
	/// @see AddMsgString
	/// @see AddBinDump
	///
	void AddMsgText (
		const char *szMessage,
		bool bForceBottom = true
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
	/// @see AddMsgPartText
	///
	void AddMsgPartString (
		wxString& oMessage,
		bool bForceBottom = true
		);

	///
	/// @brief Add a text into the log.
	///
	/// This method will count any '\n' character inside the given message 
	/// as line break.
	///
	/// @param[in] szMessage The message to add.
	/// @param[in] bForceBottom Is true to force the scrollbar to be at the bottom.
	/// @see AddMsgPartString
	///
	void AddMsgPartText (
		const char *szMessage,
		bool bForceBottom = true
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
		bool bForceBottom = true
		);

	///
	/// @brief Get access to the internal listbox.
	///
	/// Using this method you can do advance operations on the stored events.
	///
	/// @return Pointer to the internal events list.
	///
	wxListBox *GetEventsList ()
	{
		// Get access to the internal events listbox:
		return m_pEventsBox;
	}

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
	/// @brief Change the maximum items on the history list.
	///
	/// This method changing the maximum number of items that can be stored on 
	/// the history list.
	///
	/// @param[in] uiMaxHistory The new history size.
	///
	void SetMaxHistory (
		unsigned int uiMaxHistory
		);

	///
	/// @brief Get the selection list control.
	///
	/// Using this control you can add a selection list on the right of the 
	/// console input control.
	///
	/// @b Note:
	///
	/// the enable() method can also show or hide this control depending if 
	/// it has items.
	///
	/// @return Pointer to the selection list control.
	///
	wxComboBox *GetSelControl ()
	{
		// Get the selection list control:
		return m_pSelectList;
	}

	///
	/// @brief Get the current input command.
	///
	/// This method get the current input command.
	///
	/// @param[out] oCommand Will be filled with the current input command.
	///
	void GetCurrentCommand (
		wxString& oCommand
		);

	///
	/// @brief Set the current command to send.
	///
	/// This method set the current input command.
	///
	/// @param[in] oCommand The command to place on the input combo box.
	/// @param[in] bSelect Is true to select the input text.
	///
	void SetCommandString (
		wxString& oCommand,
		bool bSelect = false
		);

	///
	/// @brief Set the current command to send.
	///
	/// This method set the current input command.
	///
	/// @param[in] szCommand The command to place on the input combo box.
	/// @param[in] bSelect Is true to select the input text.
	///
	void SetCommandText (
		const char *szCommand,
		bool bSelect = false
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
	///
	void ClearMessages (
		bool bClearMarked = true,
		bool bClearUnmarked = true
		);

	///
	/// @brief Either show or hide the console.
	///
	/// This method either show or hide the console.
	///
	/// @param[in] bShow Is true to show the console.
	/// @param[in] bEnable Is true to enable the console (only if bShow is true).
	///
	void ShowConsole (
		bool bShow = true,
		bool bEnable = true
		);

	///
	/// @brief Either enable or disable the console.
	///
	/// If the control is disabled then you'll not be able to enter console 
	/// commands. This method has any effect only if the console is enabled.
	///
	/// @param[in] bEnable Is true to enable this button.
	///
	virtual bool Enable (
		bool bEnable = true
		);

	///
	/// @brief Check if the control is enabled.
	///
	/// This method always returning false if the console is not shown.
	///
	/// @retval true The control is enabled.
	/// @retval false The control is disabled.
	///
	virtual bool IsEnabled () const;

	//
	// Callbacks for derived classes to extend CWxConsolePanel:
	//
protected:

	///
	/// @brief Button click event - "Find".
	///
	/// This method been called when the user click on the "Find" button.
	///
	/// @param[in] oEvent Event information.
	///
	void OnClickFind (
		wxCommandEvent& oEvent
		);

	///
	/// @brief Right click event on the events list.
	///
	/// This method been called when the user right click on the events list.
	///
	/// @param[in] oEvent Event information.
	///
	void OnEventsRightClick (
		wxCommandEvent& oEvent
		);

	///
	/// @brief Button click event - "Send".
	///
	/// This method been called when the user click on the "Send" button.
	///
	/// @param[in] oEvent Event information.
	///
	void OnClickSend (
		wxCommandEvent& oEvent
		);

	///
	/// @brief Right menu event - "Sellect All".
	///
	/// This method been called when the user click on the "Sellect All" right menu option.
	///
	/// @param[in] oEvent Event information.
	///
	void OnMenuSelAll (
		wxCommandEvent& oEvent
		);

	///
	/// @brief Right menu event - "Desellect All".
	///
	/// This method been called when the user click on the "Desellect All" right menu option.
	///
	/// @param[in] oEvent Event information.
	///
	void OnMenuDeselAll (
		wxCommandEvent& oEvent
		);

	///
	/// @brief Right menu event - "Invert All".
	///
	/// This method been called when the user click on the "Invert All" right menu option.
	///
	/// @param[in] oEvent Event information.
	///
	void OnMenuInvertAll (
		wxCommandEvent& oEvent
		);

	///
	/// @brief Right menu event - "Save All".
	///
	/// This method been called when the user click on the "Save All" right menu option.
	///
	/// @param[in] oEvent Event information.
	///
	void OnMenuSaveAll (
		wxCommandEvent& oEvent
		);

	///
	/// @brief Right menu event - "Save All Selection".
	///
	/// This method been called when the user click on the "Save All Selection" right menu option.
	///
	/// @param[in] oEvent Event information.
	///
	void OnMenuSelSave (
		wxCommandEvent& oEvent
		);

	///
	/// @brief Right menu event - "Save All Non Selected".
	///
	/// This method been called when the user click on the "Save All Non Selected" right menu option.
	///
	/// @param[in] oEvent Event information.
	///
	void OnMenuDeselSave (
		wxCommandEvent& oEvent
		);

	///
	/// @brief Right menu event - "Clear All".
	///
	/// This method been called when the user click on the "Clear All" right menu option.
	///
	/// @param[in] oEvent Event information.
	///
	void OnMenuClearAll (
		wxCommandEvent& oEvent
		);

	///
	/// @brief Right menu event - "Clear All Selection".
	///
	/// This method been called when the user click on the "Clear All Selection" right menu option.
	///
	/// @param[in] oEvent Event information.
	///
	void OnMenuSelClear (
		wxCommandEvent& oEvent
		);

	///
	/// @brief Right menu event - "Clear All Non Selected".
	///
	/// This method been called when the user click on the "Clear All Non Selected" right menu option.
	///
	/// @param[in] oEvent Event information.
	///
	void OnMenuDeselClear (
		wxCommandEvent& oEvent
		);

	///
	/// @brief Right menu event - "Search".
	///
	/// This method been called when the user click on the "Search" right menu option.
	///
	/// @param[in] oEvent Event information.
	///
	void OnMenuSearch (
		wxCommandEvent& oEvent
		);

	//
	// API for derived classes only:
	//
protected:

	///
	/// @brief Fire an output event.
	///
	/// This method fire an output event.
	///
	/// @param[in] iEventType The type of the event to send.
	/// @param[in] pText Optional text parameter.
	///
	void FireOutEvent (
		EOutEvent iEventType,
		wxString *pText = NULL
		);

	///
	/// @brief Find the next match line on the events list.
	///
	/// This method find the next match line.
	///
	/// @param[in] oText The text to search.
	/// @param[in] iSearchType The type of search to do.
	/// @param[in] lPrevMatch Previous match item or -1 to start a new search.
	/// @retval -1 Not found.
	/// @retval else Item's ID.
	///
	unsigned int FindNext (
		wxString& oText,
		ESearchType iSearchType,
		unsigned int lPrevMatch = (unsigned int) -1
		);

	//
	// Private interface of the CWxConsolePanel class:
	//
private:

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

	wxString m_oPart;                ///< Part of a text to write.
	wxBoxSizer *m_pMainSizer;        ///< Pointer to the main sizer.
	wxBoxSizer *m_pFindSizer;        ///< Find bar sizer.
	wxBoxSizer *m_pInputSizer;       ///< Input sizer.
	wxStaticText *m_pFindText;       ///< The "Find" text.
	wxComboBox *m_pInFind;           ///< Input box for find.
	wxComboBox *m_pFindType;         ///< Find method.
	wxButton *m_pFind;               ///< The "Find" button control.
	wxListBox *m_pEventsBox;         ///< Events box.
	wxComboBox *m_pSelectList;       ///< Selection list.
	wxComboBox *m_pInSend;           ///< Input box for send.
	wxButton *m_pSend;               ///< The "Send" button control.
	wxWindow *m_pEventsWin;          ///< Window to receive events.
	const wxEventType *m_pEventType; ///< Event type.
	unsigned int m_uiMaxLines;       ///< Maximum number of lines to display.
	unsigned int m_uiMaxFind;        ///< Maximum find history items.
	unsigned int m_uiMaxHistory;     ///< Maximum history items.
	unsigned int m_uiIntFlags;       ///< Internal working flags.
};

#endif // H_CLS_CONSOLE_PANEL_HEAD

//
// End of the header file wx_console_panel.h
//

