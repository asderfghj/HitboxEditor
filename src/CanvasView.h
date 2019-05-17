#include <wx/docview.h>
class Canvas;
class HitboxTab;

class CanvasView : public wxView
{
	double m_Scale;//defaultly set to 1.0
	wxBitmap m_ScaledBitmap;//the image that is displayed
	wxSize m_ViewOffset;//how much the image has offset from the original position, used for scrolling
	Canvas* m_Canvas;//canvas that this class is attached to
	HitboxTab* m_Parent;//The hitbox tab that this class is attached to, used for getting the image that will be displayed when an image listbox is changed
	void ReCreateScaledBitmap();//Gets the currently selected image from the hitbox tab and rescales it based on m_Scale. if the image is too large scrollbars will appear on the window.
public:
	CanvasView(Canvas *_canvas, HitboxTab *parent);//constructor, assigns the canvas and parent, also sets this as the view in the canvas as part of the constructor

	wxBitmap& GetScaledBitmap();
	const wxSize& GetViewOffset();
	void SetViewOffset(const wxSize& value);

	void ClearCanvas();//removes the current scaled bitmap from the class and makes the window blank. used when an image is deleted
	
	virtual void OnDraw(wxDC* dc);//draws the current scaled bitmap to the window
	virtual void OnUpdate(wxView *sender, wxObject *hint = (wxObject *)NULL);//called whenever the image is changed, calls ReCreateScaledBitmap and then refreshes scroll bars and then shows the image.
	virtual bool OnClose(bool deleteWindow = true);//cleanup

};

