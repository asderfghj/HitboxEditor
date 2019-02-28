#ifndef CANVASVIEW_H_
#define CANVASVIEW_H_

#include "Headers.h"

class Canvas;

class CanvasView : public wxView
{
	double m_Scale;
	wxBitmap m_ScaledBitmap;
	wxSize m_ViewOffset;
	Canvas* m_Canvas;
	HitboxTab* m_Parent;
	void ReCreateScaledBitmap();
public:
	CanvasView(Canvas *_canvas, HitboxTab *parent);

	wxBitmap& GetScaledBitmap();
	const wxSize& GetViewOffset();
	void SetViewOffset(const wxSize& value);

	virtual void OnDraw(wxDC* dc);
	virtual void OnUpdate(wxView *sender, wxObject *hint = (wxObject *)NULL);
	virtual bool OnClose(bool deleteWindow = true);

};





#endif // !CANVASVIEW_H_
