#include "comms-Math.h"

namespace comms {

const cRect cRect::Zero(cRect::SetCtor, 0.0f, 0.0f, 0.0f, 0.0f);
const cRect cRect::Empty(cRect::SetCtor, cMath::FloatMaxValue, cMath::FloatMaxValue, -cMath::FloatMaxValue, -cMath::FloatMaxValue);
const cRect cRect::Unit(cRect::SetCtor, 0.0f, 0.0f, 1.0f, 1.0f);

//-----------------------------------------------------------------------------
// cRect::SetWidth
//-----------------------------------------------------------------------------
void cRect::SetWidth(const int HoldPoint, const float Width) {
	float X, H;
	
	switch(HoldPoint) {
		case cAlign::TopLeft: // == "Left"
		case cAlign::MiddleLeft:
		case cAlign::BottomLeft:
			m_Max.x = m_Min.x + Width;
			break;
		case cAlign::TopCenter: // == "Center"
		case cAlign::MiddleCenter:
		case cAlign::BottomCenter:
			X = (m_Min.x + m_Max.x) / 2.0f;
			H = Width / 2.0f;
			m_Min.x = X - H;
			m_Max.x = X + H;
			break;
		case cAlign::TopRight: // == "Right"
		case cAlign::MiddleRight:
		case cAlign::BottomRight:
			m_Min.x = m_Max.x - Width;
			break;
		default:
			cAssertM(0, "\"Align\" contains unacceptable flags combination");
	}
} // cRect::SetWidth

//-----------------------------------------------------------------------------
// cRect::SetHeight
//-----------------------------------------------------------------------------
void cRect::SetHeight(const int HoldPoint, const float Height) {
	float Y, H;

	switch(HoldPoint) {
		case cAlign::TopLeft: // == "Top"
		case cAlign::TopCenter:
		case cAlign::TopRight:
			m_Min.y = m_Max.y - Height;
			break;
		case cAlign::MiddleLeft: // == "Middle"
		case cAlign::MiddleCenter:
		case cAlign::MiddleRight:
			Y = (m_Min.y + m_Max.y) / 2.0f;
			H = Height / 2.0f;
			m_Min.y = Y - H;
			m_Max.y = Y + H;
			break;
		case cAlign::BottomLeft: // == "Bottom"
		case cAlign::BottomCenter:
		case cAlign::BottomRight:
			m_Max.y = m_Min.y + Height;
			break;
		default:
			cAssertM(0, "\"Align\" contains unacceptable flags combination");
	}
} // cRect::SetHeight

//-----------------------------------------------------------------------------
// cRect::GetPoint
//-----------------------------------------------------------------------------
const cVec2 cRect::GetPoint(const int Align) const {
	switch(Align) {
		case cAlign::TopLeft:
			return GetTopLeft();
		case cAlign::TopCenter:
			return GetTopCenter();
		case cAlign::TopRight:
			return GetTopRight();
		case cAlign::MiddleLeft:
			return GetMiddleLeft();
		case cAlign::MiddleCenter:
			return GetMiddleCenter();
		case cAlign::MiddleRight:
			return GetMiddleRight();
		case cAlign::BottomLeft:
			return GetBottomLeft();
		case cAlign::BottomCenter:
			return GetBottomCenter();
		case cAlign::BottomRight:
			return GetBottomRight();
		default:
			cAssert(0); // "Align" contains unacceptable flags combination
			return cVec2::Zero;
	}
} // cRect::GetPoint

//-----------------------------------------------------------------------------
// cRect::AlignPoint : (..., const float, ...)
//-----------------------------------------------------------------------------
void cRect::AlignPoint(const int Align, const float X, const float Y) {
	switch(Align) {
		case cAlign::TopLeft:
			AlignTopLeft(X, Y);
			break;
		case cAlign::TopCenter:
			AlignTopCenter(X, Y);
			break;
		case cAlign::TopRight:
			AlignTopRight(X, Y);
			break;
		case cAlign::MiddleLeft:
			AlignMiddleLeft(X, Y);
			break;
		case cAlign::MiddleCenter:
			AlignMiddleCenter(X, Y);
			break;
		case cAlign::MiddleRight:
			AlignMiddleRight(X, Y);
			break;
		case cAlign::BottomLeft:
			AlignBottomLeft(X, Y);
			break;
		case cAlign::BottomCenter:
			AlignBottomCenter(X, Y);
			break;
		case cAlign::BottomRight:
			AlignBottomRight(X, Y);
			break;
		default:
			cAssert(0); // "Align" contains unacceptable flags combination
	}
} // cRect::AlignPoint : (..., const float, ...)

//-----------------------------------------------------------------------------
// cRect::AlignPoint : (..., const cRect &)
//-----------------------------------------------------------------------------
void cRect::AlignPoint(const int Align, const cRect &Parent) {
	switch(Align) {
		case cAlign::TopLeft:
			AlignTopLeft(Parent.GetTopLeft());
			break;
		case cAlign::TopCenter:
			AlignTopCenter(Parent.GetTopCenter());
			break;
		case cAlign::TopRight:
			AlignTopRight(Parent.GetTopRight());
			break;
		case cAlign::MiddleLeft:
			AlignMiddleLeft(Parent.GetMiddleLeft());
			break;
		case cAlign::MiddleCenter:
			AlignMiddleCenter(Parent.GetMiddleCenter());
			break;
		case cAlign::MiddleRight:
			AlignMiddleRight(Parent.GetMiddleRight());
			break;
		case cAlign::BottomLeft:
			AlignBottomLeft(Parent.GetBottomLeft());
			break;
		case cAlign::BottomCenter:
			AlignBottomCenter(Parent.GetBottomCenter());
			break;
		case cAlign::BottomRight:
			AlignBottomRight(Parent.GetBottomRight());
			break;
		default:
			cAssert(0); // "Align" contains unacceptable flags combination
	}
} // cRect::AlignPoint : (..., const cRect &)

//-----------------------------------------------------------------------------------------
// cRect::GetDockingAlign : (const cRect &, ...)
//-----------------------------------------------------------------------------------------
int cRect::GetDockingAlign(const cRect &Child, cRect *DockingRegion, cVec2 *RelPos) const {
	int Align = 0;

	// Vertical alignment
	float VertDists[] = {
		GetTop() - Child.GetTop(),
		cMath::Abs(GetCenterY() - Child.GetCenterY()),
		Child.GetBottom() - GetBottom()
	};

	const int VertFlags[] = { cAlign::Top, cAlign::Middle, cAlign::Bottom };
	Align |= VertFlags[cMath::MinIndex(VertDists[0], VertDists[1], VertDists[2])];

	// Horizontal alignment
	const float HorDists[] = {
		Child.GetLeft() - GetLeft(),
		cMath::Abs(GetCenterX() - Child.GetCenterX()),
		GetRight() - Child.GetRight()
	};
	const int HorFlags[] = { cAlign::Left, cAlign::Center, cAlign::Right };
	Align |= HorFlags[cMath::MinIndex(HorDists[0], HorDists[1], HorDists[2])];

	if(DockingRegion != NULL) {
		*DockingRegion = GetDockingRegion(Child, Align);
	}

	if(RelPos != NULL) {
		*RelPos = Child.GetPoint(Align) - GetPoint(Align);
	}
	
	return Align;
} // cRect::GetDockingAlign

//------------------------------------------------------------------------------
// cRect::GetDockingRegion : (const cRect &, ...)
//------------------------------------------------------------------------------
const cRect cRect::GetDockingRegion(const cRect &Child, const int Align) const {
	cRect Dr;
	float GapY, GapX;
	const float MinVisCellY = 0.0f;
	const float MinVisCellX = 0.0f;
	const float CellY = GetHeight() / 4.0f;
	const float CellX = GetWidth() / 4.0f;

	// Calc docking region
	Dr.SetEmpty();
	
	GapY = Child.GetHeight() / 4.0f;
	GapX = Child.GetWidth() / 4.0f;
	if(CellX - GapX < MinVisCellX) {
		GapX = CellX - MinVisCellX;
	}
	if(CellY - GapY < MinVisCellY) {
		GapY = CellY - MinVisCellY;
	}
	
	if(Align & cAlign::Bottom) {
		Dr.SetBottom(GetBottom());
		Dr.SetTop(GetBottom() + CellY - GapY);
	} else if(Align & cAlign::Middle) {
		Dr.SetTop(GetCenterY() + CellY - GapY);
		Dr.SetBottom(GetCenterY() - CellY + GapY);
	} else {
		Dr.SetBottom(GetTop() - CellY + GapY);
		Dr.SetTop(GetTop());
	}
	
	if(Align & cAlign::Right) {
		Dr.SetRight(GetRight());
		Dr.SetLeft(GetRight() - CellX + GapX);
	} else if(Align & cAlign::Center) {
		Dr.SetRight(GetCenterX() + CellX - GapX);
		Dr.SetLeft(GetCenterX() - CellX + GapX);
	} else {
		Dr.SetLeft(GetLeft());
		Dr.SetRight(GetLeft() + CellX - GapX);
	}
	return Dr;
} // cRect::GetDockingRegion

// cRect::GetDockingAlign : (const cVec2 &, ...)
int cRect::GetDockingAlign(const cVec2 &Child, cRect *DockingRegion, cVec2 *RelPos) const {
	cRect Rc;
	Rc.SetToPoint(Child);
	return GetDockingAlign(Rc, DockingRegion, RelPos);
}

// cRect::GetDockingRegion : (const cVec2 &, ...)
const cRect cRect::GetDockingRegion(const cVec2 &Child, const int Align) const {
	cRect Rc;
	Rc.SetToPoint(Child);
	return GetDockingRegion(Rc, Align);
}

//-----------------------------------------------------------------------------
// cRect::Inscribe
//-----------------------------------------------------------------------------
const cRect cRect::Inscribe(const cRect &What, const cRect &Where) {
	float W = What.GetWidth();
	float H = What.GetHeight();
	if(W <= 0.0f || H <= 0.0f) {
		return cRect::Zero;
	}

	float S = Where.GetWidth();
	float T = Where.GetHeight();
	float Scale = cMath::Min(S / W, T / H);
	float X = Scale * W;
	float Y = Scale * H;
	float Dx = (S - X) / 2.0f;
	float Dy = (T - Y) / 2.0f;

	cRect R;
	R.SetTopLeft(Where.GetTopLeft() + cVec2(Dx, -Dy));
	R.SetBottomRight(Where.GetBottomRight() + cVec2(-Dx, Dy));
	return R;
} // cRect::Inscribe

// cRect::AlignInside
void cRect::AlignInside(const cRect &Parent) {
	if(GetRight() > Parent.GetRight()) {
		AlignRight(Parent.GetRight());
	}
	if(GetBottom() < Parent.GetBottom()) {
		AlignBottom(Parent.GetBottom());
	}
	if(GetLeft() < Parent.GetLeft()) {
		AlignLeft(Parent.GetLeft());
	}
	if(GetTop() > Parent.GetTop()) {
		AlignTop(Parent.GetTop());
	}
}

} // comms
