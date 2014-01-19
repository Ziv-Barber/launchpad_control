
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
/// This is the implementation of the class CWxBorderPanel.
///
/// @b Interesting @b Bookmarks:
///
/// Please search for the following key word on the code to locate some interesting places on the code:
///
/// -# @b BMK_TODO - We need to finish code this part.
///

#include "wx_border_panel.h"

//
// Some internal definess:
//

///
/// @brief All the IDs of the controls of CWxBorderPanel.
///
/// This enumerator declaring all the IDs of all the child controls of the 
/// CWxBorderPanel class.
///
/// @see CWxBorderPanel
///
typedef enum EBorderPanelCntIds
{
	E_BORDER_PANEL_CNT_UNKNOWN ///< No controls.
};

//
// Private prototypes:
//

//
// Global variables:
//

//
// Constructors / destructors:
//

CWxBorderPanel::~CWxBorderPanel ()
{
	// Destroy any allocated resource by this instance of CWxBorderPanel:
}

//
// Public methods:
//

bool CWxBorderPanel::Create (
	wxWindow* pParent,
	wxWindowID iId,
	EBrdSizerType iSizerType,
	const wxString& strBorderTitle,
	int iRows,
	int iColumns,
	int iVerticalGap,
	int iHorizontalGap,
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

	m_iSizerType = iSizerType;
	SetBackgroundColour ( wxSystemSettings::GetColour ( wxSYS_COLOUR_MENU ) );

	//
	// Splitters and windows:
	//

	m_pBorderGroup = new wxStaticBox ( this, wxID_ANY, strBorderTitle );
	if ( m_pBorderGroup == NULL )
	{
		// Error:
		return false;
	} // Endif.

	m_pBorderPanel = new wxPanel ( m_pBorderGroup, wxID_ANY );
	if ( m_pBorderPanel == NULL )
	{
		// Error:
		return false;
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

	m_pBorderGSizer = new wxStaticBoxSizer ( m_pBorderGroup, wxVERTICAL );
	if ( m_pBorderGSizer == NULL )
	{
		// Error:
		return false;
	} // Endif.

	// Check what sizer to create:
	switch ( iSizerType )
	{
		// Horizontal sizer:
		case E_BRDSZ_TY_HORIZONTAL:
			m_pBorderSizer = new wxBoxSizer ( wxHORIZONTAL );
			if ( m_pBorderSizer == NULL )
			{
				// Error:
				return false;
			} // Endif.

			break;

		// Grid sizer:
		case E_BRDSZ_TY_GRID:
			m_pBorderSizer = new wxGridSizer ( iRows, iColumns, iVerticalGap, iHorizontalGap );
			if ( m_pBorderSizer == NULL )
			{
				// Error:
				return false;
			} // Endif.

			break;

		// Flex grid sizer:
		case E_BRDSZ_TY_FLEXGRID:
			m_pBorderSizer = new wxFlexGridSizer ( iRows, iColumns, iVerticalGap, iHorizontalGap );
			if ( m_pBorderSizer == NULL )
			{
				// Error:
				return false;
			} // Endif.

			break;

		// Vertical sizer:
		default:
			m_pBorderSizer = new wxBoxSizer ( wxVERTICAL );
			if ( m_pBorderSizer == NULL )
			{
				// Error:
				return false;
			} // Endif.

			break;
	} // End of switch.

	//
	// Create all the controls:
	//

	//
	// Connect all the controls to the sizers:
	//

	m_pBorderPanel->SetSizer ( m_pBorderSizer );

	m_pBorderGSizer->Add ( m_pBorderPanel, 1, wxEXPAND | wxALL, 3 );

	m_pMainSizer->Add ( m_pBorderGSizer, 1, wxEXPAND | wxALL, 0 );

	//
	// Tell the derived class to add it's controls:
	//

	if ( OnCreateControls ( m_pBorderPanel, m_pBorderSizer ) == false )
	{
		// Error:
		return false;
	} // Endif.

	//
	// Add events:
	//

	// Connect the main sizer:
	SetSizer ( m_pMainSizer );

	// That's all:
	return true;
}

//
// Protected methods:
//

bool CWxBorderPanel::OnCreateControls (
	wxPanel *pBorderPanel,
	wxSizer *pBorderSizer
	)
{
	// We don't have any additional controls:
	return true;
}

//
// Private methods:
//

void CWxBorderPanel::Init ()
{
	// Initialize all the data members of CWxBorderPanel:
	m_pMainSizer = NULL;
	m_pBorderGroup = NULL;
	m_pBorderPanel = NULL;
	m_pBorderGSizer = NULL;
	m_pBorderSizer = NULL;
	m_iSizerType = E_BRDSZ_TY_VERTICAL;
}

//
// End of the source file wx_border_panel.cpp
//

