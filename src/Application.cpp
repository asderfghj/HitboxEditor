#include "Application.h"
#include "Frame.h"
#include <wx/wx.h>
#include "icon/icon.xpm"

bool Application::OnInit()
{
	Frame* mainFrame = NULL;

	wxInitAllImageHandlers();
	mainFrame = new Frame();
	mainFrame->Show(true);
	SetTopWindow(mainFrame);

	return true;
}