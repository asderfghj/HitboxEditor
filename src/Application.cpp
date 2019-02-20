#include "Headers.h"

bool Application::OnInit()
{
	Frame* mainFrame = NULL;

	wxInitAllImageHandlers();
	mainFrame = new Frame();
	mainFrame->Show(true);
	SetTopWindow(mainFrame);

	return true;
}