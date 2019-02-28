#include "Headers.h"

CanvasView::CanvasView(Canvas *_canvas, HitboxTab *_parent) : m_Scale(1.0)
{
	m_Canvas = _canvas;
	m_Parent = _parent;
	m_Canvas->SetView(this);
}

void CanvasView::OnDraw(wxDC* dc)
{
	if (m_ScaledBitmap.IsOk())
	{
		dc->DrawBitmap(m_ScaledBitmap, m_ViewOffset.GetWidth(), m_ViewOffset.GetHeight());
	}
}

void CanvasView::OnUpdate(wxView *sender, wxObject *hint)
{
	ReCreateScaledBitmap();
	if (m_Canvas)
	{
		m_Canvas->AdjustScrollBars();
		m_Canvas->Refresh();
	}
}

void CanvasView::ReCreateScaledBitmap()
{
	Image* img = m_Parent->getCurrentlySelectedImage();
	if (img)
	{
		wxSize scaledSize(img->image.GetWidth() * m_Scale, img->image.GetHeight() * m_Scale);
		m_ScaledBitmap = wxBitmap(img->image.Scale(scaledSize.GetWidth(), scaledSize.GetHeight()));
	}
	else
	{
		m_ScaledBitmap = wxNullBitmap;
	}
}

bool CanvasView::OnClose(bool deleteWindow)
{
	if (m_Canvas)
	{
		m_Canvas->ClearBackground();
		m_Canvas->SetView(NULL);
		m_Canvas = NULL;
	}

	SetFrame(NULL);
	Activate(false);
	return true;
}

wxBitmap& CanvasView::GetScaledBitmap()
{
	return m_ScaledBitmap;
}

const wxSize& CanvasView::GetViewOffset()
{
	return m_ViewOffset;
}

void CanvasView::SetViewOffset(const wxSize& value)
{
	m_ViewOffset = value;
}