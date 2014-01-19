
//
// Code license:
//
// Copyright (C) Ziv Barber.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//

///
/// @file
/// @brief The class CWxBorderPanel.
///
/// This is the header file of the class CWxBorderPanel.
///
/// @b Interesting @b Bookmarks:
///
/// Please search for the following key word on the code to locate some interesting places on the code:
///
/// -# @b BMK_TODO - We need to finish code this part.
///
/// @b Script @b Information:
///

#ifndef H_CLS_BORDER_PANEL_HEAD
#define H_CLS_BORDER_PANEL_HEAD

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
// The CWxBorderPanel class declaration:
//

///
/// @brief Border panel.
///
/// This class hide all the process of creating a group box (group of controls 
/// with border around them). You can use this class either as is or you can 
/// use it as a base class for controls that need a border around them. In the 
/// 2nd case, overide OnCreateControls() to create your controls.
///
/// @b Example:
///
/// You need to include:
///
/// @code
/// #include "wx_border_panel.h"
/// @endcode
///
/// Create the panel:
///
/// @code
/// CWxBorderPanel *pPanel; // Pointer to the new panel.
///
/// // Create a new border with flex grid inside it of 4 rows and 3 columns:
/// pPanel = new CWxBorderPanel ( this, wxID_ANY, CWxBorderPanel::E_BRDSZ_TY_FLEXGRID, wxT(""), 4, 3, 2, 2 );
/// if ( pPanel == NULL )
/// {
/// 	// Error:
/// 	return false;
/// } // Endif.
///
/// // pPanel->GetBorderPanel () - the border's panel for controls
/// // pPanel->GetBorderSizer () - the border's sizer for controls
///
/// // --- Add pPanel to the right sizer ---
/// @endcode
///
class CWxBorderPanel : public wxPanel
{
	//
	// Some definess for this class:
	//
public:

	///
	/// @brief Internal border sizer type.
	///
	/// This enum declaring all the types of sizers that can be used.
	///
	enum EBrdSizerType
	{
		E_BRDSZ_TY_VERTICAL,   ///< Vertical sizer.
		E_BRDSZ_TY_HORIZONTAL, ///< Horizontal sizer.
		E_BRDSZ_TY_GRID,       ///< Grid sizer.
		E_BRDSZ_TY_FLEXGRID    ///< Flex grid sizer.
	};

	//
	// Constructors / destructors:
	//
public:

	///
	/// @brief CWxBorderPanel default constructor.
	///
	/// This is the default constructor of the CWxBorderPanel class.
	///
	/// @see Create
	/// @see Init
	///
	CWxBorderPanel () : wxPanel ()
	{
		// Initialize all the data members of CWxBorderPanel:
		Init ();
	}

	///
	/// @brief CWxBorderPanel constructor.
	///
	/// This is another constructor of the CWxBorderPanel class.
	///
	/// @param[in] pParent Pointer to the parent window.
	/// @param[in] iId Window identifier. If wxID_ANY, will automatically create an identifier.
	/// @param[in] iSizerType The type of sizer to create inside the border.
	/// @param[in] strBorderTitle Border title.
	/// @param[in] iRows Number of rows for any grid based sizer only.
	/// @param[in] iColumns Number of columns for any grid based sizer only.
	/// @param[in] iVerticalGap Vertical gap for any grid based sizer only.
	/// @param[in] iHorizontalGap Horizontal gap for any grid based sizer only.
	/// @param[in] oPosition panel position. wxDefaultPosition indicates that wxWidgets should generate a default position for this panel.
	/// @param[in] oSize The panel size. wxDefaultSize indicates that wxWidgets should generate a default size for this panel is visible but obviously not correctly sized.
	/// @param[in] lStyle Window style for this panel.
	/// @param[in] strWindowName Window name.
	/// @see Init
	///
	CWxBorderPanel (
		wxWindow* pParent,
		wxWindowID iId,
		EBrdSizerType iSizerType = E_BRDSZ_TY_VERTICAL,
		const wxString& strBorderTitle = wxT(""),
		int iRows = 2,
		int iColumns = 2,
		int iVerticalGap = 2,
		int iHorizontalGap = 2,
		const wxPoint& oPosition = wxDefaultPosition,
		const wxSize& oSize = wxDefaultSize,
		long lStyle = 0,
		const wxString& strWindowName = wxT("wxBorderPanel")
		)
	{
		// Initialize all the data members of CWxBorderPanel:
		Init ();
		
		// Create the panel:
		Create ( pParent, iId, iSizerType, strBorderTitle, iRows, iColumns, iVerticalGap, iHorizontalGap, oPosition, oSize, lStyle, strWindowName );
	}

	///
	/// @brief CWxBorderPanel destructor.
	///
	/// This is the destructor of the CWxBorderPanel class.
	///
	virtual ~CWxBorderPanel ();

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
	/// @param[in] iSizerType The type of sizer to create inside the border.
	/// @param[in] strBorderTitle Border title.
	/// @param[in] iRows Number of rows for any grid based sizer only.
	/// @param[in] iColumns Number of columns for any grid based sizer only.
	/// @param[in] iVerticalGap Vertical gap for any grid based sizer only.
	/// @param[in] iHorizontalGap Horizontal gap for any grid based sizer only.
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
		EBrdSizerType iSizerType = E_BRDSZ_TY_VERTICAL,
		const wxString& strBorderTitle = wxT(""),
		int iRows = 2,
		int iColumns = 2,
		int iVerticalGap = 2,
		int iHorizontalGap = 2,
		const wxPoint& oPosition = wxDefaultPosition,
		const wxSize& oSize = wxDefaultSize,
		long lStyle = 0,
		const wxString& strWindowName = wxT("wxBorderPanel")
		);

	///
	/// @brief Get the internal border panel.
	///
	/// This method returning the internal border panel which can be used 
	/// for creating controls inside the border.
	///
	/// @return Pointer to the internal border panel.
	/// @see GetBorderSizer
	/// @see GetSizerType
	///
	wxPanel *GetBorderPanel ()
	{
		// Return the internal border panel:
		return m_pBorderPanel;
	}

	///
	/// @brief Get the internal border sizer.
	///
	/// This method returning the internal border sizer which can be used for 
	/// creating controls inside the border.
	///
	/// @return Pointer to the internal border sizer.
	/// @see GetBorderPanel
	/// @see GetSizerType
	///
	wxSizer *GetBorderSizer ()
	{
		// Return the internal border sizer:
		return m_pBorderSizer;
	}

	///
	/// @brief Get the type of sizer on the internal border panel.
	///
	/// This method returning the type of sizer on the internal border panel.
	///
	/// @return The type of sizer been created (EBrdSizerType).
	/// @see GetBorderPanel
	/// @see GetBorderSizer
	///
	EBrdSizerType GetSizerType ()
	{
		// Get the type of sizer been created:
		return m_iSizerType;
	}

	//
	// Callbacks for derived classes to extend CWxBorderPanel:
	//
protected:

	///
	/// @brief Call the derived class to add it's controls.
	///
	/// This method allow the derived class to add it's controls.
	///
	/// @param[in] pBorderPanel Pointer to the internal border's panel.
	/// @param[in] pBorderSizer Pointer to the internal border's sizer.
	/// @retval true Operation succeeded.
	/// @retval false Operation failed.
	///
	virtual bool OnCreateControls (
		wxPanel *pBorderPanel,
		wxSizer *pBorderSizer
		);

	//
	// Callbacks for control based events:
	//

	//
	// API for derived classes only:
	//
protected:

	//
	// Private interface of the CWxBorderPanel class:
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

	// Splitters and windows:
	wxStaticBox *m_pBorderGroup;       ///< Main border group panel.
	wxPanel *m_pBorderPanel;           ///< Border internal panel.

	// Sizer based controls:
	wxBoxSizer *m_pMainSizer;          ///< Pointer to the main sizer.
	wxStaticBoxSizer *m_pBorderGSizer; ///< Pointer to the group sizer of the border.
	wxSizer *m_pBorderSizer;           ///< Pointer to the border internal sizer.

	// All the other controls:

	EBrdSizerType m_iSizerType; ///< The type of sizer been created.
};

#endif // H_CLS_BORDER_PANEL_HEAD

//
// End of the header file wx_border_panel.h
//

