
///
/// @file
/// @brief The class CLaunchPadGenApp.
///
/// This is the header file of the class CLaunchPadGenApp.
///
/// @b Interesting @b Bookmarks:
///
/// Please search for the following key word on the code to locate some interesting places on the code:
///
/// -# @b BMK_TODO - We need to finish code this part.
///

#ifndef H_CLS_LAUNCH_PAD_GEN_APP_HEAD
#define H_CLS_LAUNCH_PAD_GEN_APP_HEAD

//
// Header files needed to be include with this class:
//

#include "launch_pad_gen_dlg.h"

//
// Some public definess:
//

//
// Public prototypes:
//

//
// The CLaunchPadGenApp class declaration:
//

///
/// @brief The LaunchPadGen application.
///
/// This class is the main class of the LaunchPadGen application.
///
class CLaunchPadGenApp : public wxApp
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
	/// @brief CLaunchPadGenApp default constructor.
	///
	/// This is the default constructor of the CLaunchPadGenApp class.
	///
	/// @see CLaunchPadGenApp::~CLaunchPadGenApp
	///
	CLaunchPadGenApp ();

	///
	/// @brief CLaunchPadGenApp destructor.
	///
	/// This is the destructor of the CLaunchPadGenApp class.
	///
	/// @see CLaunchPadGenApp::CLaunchPadGenApp
	///
	virtual ~CLaunchPadGenApp ();

	//
	// Public interface:
	//
public:

	///
	/// @brief Called when the application starting to run.
	///
	/// This method been called when the application is starting to run.
	///
	/// @retval true Operation succeeded.
	/// @retval false Operation failed.
	///
	virtual bool OnInit ();

	//
	// Callbacks for derived classes to extend CLaunchPadGenApp:
	//
protected:

	//
	// API for derived classes only:
	//
protected:

	//
	// Private interface of the CLaunchPadGenApp class:
	//
private:

	//
	// Data members:
	//
private:

	CLaunchPadGenMainFrame *m_pFrame; // The main frame.
};

#endif // H_CLS_LAUNCH_PAD_GEN_APP_HEAD

//
// End of the header file launch_pad_gen_app.h
//

