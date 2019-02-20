#include "Headers.h"

Frame::Frame() : wxFrame(NULL, wxID_ANY, _("Hitbox Editor"), wxDefaultPosition, wxSize(800, 600))
{
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	filePath = _("");
	menuBar = new wxMenuBar();
	fileMenu = new wxMenu();

	menuBar->Append(fileMenu, _("File"));
	Connect(fileMenu->Append(wxID_ANY, _T("&New"))->GetId(), wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&Frame::OnNew);
	Connect(fileMenu->Append(wxID_ANY, _T("&Open"))->GetId(), wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&Frame::OnOpen);
	Connect(fileMenu->Append(wxID_ANY, _T("&Save"))->GetId(), wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&Frame::OnSave);
	Connect(fileMenu->Append(wxID_ANY, _T("Save &As"))->GetId(), wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&Frame::OnSaveAs);
	Connect(fileMenu->Append(wxID_ANY, _T("&Re-Open"))->GetId(), wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&Frame::OnReopen);
	fileMenu->AppendSeparator();
	Connect(fileMenu->Append(wxID_ANY, _T("&Quit"))->GetId(), wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&Frame::OnQuit);
	SetMenuBar(menuBar);


	SetSizerAndFit(sizer);
}

void Frame::OnNew(wxCommandEvent& event)
{
	SetTitle(_("Hitbox Editor - UNTITLED"));
	filePath = _("");

	Refresh();
}

void Frame::OnOpen(wxCommandEvent& event)
{
	wxString path;
	wxFileDialog* openDialog = NULL;

	openDialog = new wxFileDialog(this, _("Choose a file to open"), wxEmptyString, wxEmptyString, _("Hitbox files (*.hbox)|*.hbox"), wxFD_OPEN, wxDefaultPosition);

	if (openDialog->ShowModal() == wxID_OK)
	{
		path = openDialog->GetPath();
	}

	openDialog->Destroy();

	if (path == _(""))
	{
		return;
	}

	filePath = path;
	OnReopen(event);

}

void Frame::OnReopen(wxCommandEvent& event)
{
	//*TODO* Implement this after the main interface
}


void Frame::OnQuit(wxCommandEvent& event)
{
	Close();
}

void Frame::OnSaveAs(wxCommandEvent& event)
{
	wxFileDialog* saveDialog = NULL;

	saveDialog = new wxFileDialog(this, _(""), wxEmptyString, wxEmptyString, _("Hitbox Files (*.hbox)|*.hbox"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);

	if (saveDialog->ShowModal() != wxID_OK)
	{
		saveDialog->Destroy();
		return;
	}

	filePath = saveDialog->GetPath();
	saveDialog->Destroy();
	OnSave(event);
	SetTitle(_("Hitbox Editor - ") + filePath);
}

void Frame::OnSave(wxCommandEvent& event)
{
	//*TODO* Implement this after the main interface
}