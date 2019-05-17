#include <wx/dcbuffer.h>
class CanvasView;
class HitboxTab;

class Canvas : public wxWindow
{
	wxPoint m_TR;//Top right point, used for creating a new box in the canvas
	wxPoint m_BL;//Bottom right point, used for creating a new box in the canvas

	CanvasView *m_View;//Used for displaying the image (see canvas view class)
	wxRect m_selection;//Rect that is displayed when the canvas is clicked on, created using the top right and bottom left variables (see above)
	static wxSize ScrollingIncrement;//How much the canvas scrolls by
	HitboxTab *tabParent;//The hitbox tab that this class is assigned to. Used as an intermediary to access the ImagesContainer class on the frame class, to add hitboxes. Also used to get images.
	bool m_leftMouseDown, m_rightMouseDown;//Used to make sure that both mouse buttons do not activate functions at the same time.

	void Init();//Initialises events and sets some variables to default values.
public:
	Canvas();//Default constructor, calls the init function.
	Canvas(wxWindow *Parent, HitboxTab *tabParent, wxWindowID id = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = wxBORDER_SUNKEN | wxHSCROLL | wxVSCROLL, const wxString &name = _("If this comes up, I'll be surprised"));//Better constructor, assigns the tab parent, calls create
	bool Create(wxWindow *Parent, wxWindowID id = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = wxBORDER_SUNKEN | wxHSCROLL | wxVSCROLL, const wxString &name = _("If this comes up, I'll be surprised"));//creates an instance of the parent class 

	CanvasView* GetView();
	void SetView(CanvasView* value);

	const wxRect& GetSelection();//returns the rect created by a mouse drag in the window 

	wxSize GetCurrentSize();//returns the size of the currently selected image
	wxPoint GetScrollPosition();//returns the scroll postion

	void Scroll(wxPoint pt);
	void Scroll(int x, int y);

	void FixViewOffset();//centerises the image
	void AdjustScrollBars();//updates the scrollbars

	wxRect GetImageDisplayRect(const wxPoint &scrollPos);
	wxPoint ClientToImage(const wxPoint &pos);//translates a point from wxWidget space to image space

	bool AutoScroll(wxPoint currentPos, wxPoint scrollPos);

	//Event callbacks
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
	void OnRightDown(wxMouseEvent &event);
	void OnRightUp(wxMouseEvent &event);
	void OnMotion(wxMouseEvent &event);

	void DrawHitboxes(wxBufferedPaintDC* dc);

};


