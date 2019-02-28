#ifndef CANVAS_H_
#define CANVAS_H_
#include "Headers.h"

class CanvasView;

class Canvas : public wxWindow
{
	wxPoint m_TR;
	wxPoint m_BL;

	CanvasView *m_View;
	wxRect m_selection;
	static wxSize ScrollingIncrement;

	void Init();
public:
	Canvas();
	Canvas(wxWindow *Parent, wxWindowID id = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = wxBORDER_SUNKEN | wxHSCROLL | wxVSCROLL, const wxString &name = _("If this comes up, I'll be surprised"));
	bool Create(wxWindow *Parent, wxWindowID id = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = wxBORDER_SUNKEN | wxHSCROLL | wxVSCROLL, const wxString &name = _("If this comes up, I'll be surprised"));

	CanvasView* GetView();
	void SetView(CanvasView* value);

	const wxRect& GetSelection();

	wxSize GetCurrentSize();
	wxPoint GetScrollPosition();

	void Scroll(wxPoint pt);
	void Scroll(int x, int y);

	void FixViewOffset();
	void AdjustScrollBars();

	wxRect GetImageDisplayRect(const wxPoint &scrollPos);
	wxPoint ClientToImage(const wxPoint &pos);

	bool AutoScroll(wxPoint currentPos, wxPoint scrollPos);

	void OnScrollLineUp(wxScrollWinEvent &event);
	void OnScrollLineDown(wxScrollWinEvent &event);
	void OnScrollPageUp(wxScrollWinEvent &event);
	void OnScrollPageDown(wxScrollWinEvent &event);
	void OnScrollThumbTrack(wxScrollWinEvent &event);
	void OnScrollThumbRelease(wxScrollWinEvent &event);
	void OnPaint(wxPaintEvent &event);
	void OnIdle(wxIdleEvent &event);
	void OnEraseBackground(wxEraseEvent &event);
	void OnLeftDown(wxMouseEvent &event);
	void OnLeftUp(wxMouseEvent &event);
	void OnMotion(wxMouseEvent &event);

};



#endif // !CANVAS_H_
