#pragma once

//*****************************************************************************
// cAlign
//*****************************************************************************
struct cAlign {
	enum Flags {
		// Horizontal alignment
		Left = 0, Center = 1, Right = 2,
		// Vertical alignment
		Top = 0, Middle = 4, Bottom = 8,

		// Predefined combinations
		TopLeft		= Top | Left,			TopCenter		= Top | Center,			TopRight		= Top | Right,
		MiddleLeft	= Middle | Left,		MiddleCenter	= Middle | Center,		MiddleRight		= Middle | Right,
		BottomLeft	= Bottom | Left,		BottomCenter	= Bottom | Center,		BottomRight		= Bottom | Right
	};
};


//*****************************************************************************
// cRect
//*****************************************************************************
/*
		�������� �������, ����� �������������� "cRect" �������� ��� ����� -
	���������� ������� ������ ����, �� - ���� ���������� ����������, � ����������
	������� �������� ����, �� - ���� ���������� ���������� (���� ���������� �
	�������� ���). �������������, ����� "cRect" �������� ������������ �����
	������������� "Transform" �������� "cMat4", ����������� �� ����� ���� � �������
	"TransformCoordinate" ������� "cVec2".
		����� "Transform" ��� ������� "cMat3" ��������� � ������� "Transform"
	������ "cVec2" (��. "cVec2.h").

	cRect::Align... - Translate rectangle to align selected reference point of this rectangle
	with the specified coordinates. Original rectangle width / height retains.
*/

class cRect {
protected:
	friend class cFile;
	cVec2 m_Min, m_Max;
public:
	enum ESetCtor { SetCtor };
	enum ESizeCtor { SizeCtor };
	
	cRect() {}

    cRect(const ESetCtor, const float MinX, const float MinY, const float MaxX, const float MaxY);
	cRect(const ESetCtor, const cVec2 &Min, const cVec2 &Max);
	cRect(const ESizeCtor, const float MinX, const float MinY, const float Width, const float Height);
	cRect(const ESizeCtor, const cVec2 &Min, const cVec2 &Size);

	bool operator == (const cRect &) const;
	bool operator != (const cRect &) const;
	static bool Equals(const cRect &, const cRect &, const float Eps = cMath::Epsilon);

	void Set(const float MinX, const float MinY, const float MaxX, const float MaxY);
	void Set(const cVec2 &Min, const cVec2 &Max);

	void SetLeft(const float Left) { m_Min.x = Left; }
	void AlignLeft(const float X);
	
	void SetTop(const float Top) { m_Max.y = Top; }
	void AlignTop(const float Y);

	void SetRight(const float Right) { m_Max.x = Right; }
	void AlignRight(const float X);
	
	void SetBottom(const float Bottom) { m_Min.y = Bottom; }
	void AlignBottom(const float Y);

	void AlignInside(const cRect &Parent); // Successively aligns right, bottom, left, and top edges to keep this rectangle inside the parent

	// TopLeft
	const cVec2 GetTopLeft() const { return cVec2(m_Min.x, m_Max.y); }
	void SetTopLeft(const float X, const float Y) { m_Min.x = X; m_Max.y = Y; }
	void SetTopLeft(const cVec2 &TopLeft) { SetTopLeft(TopLeft.x, TopLeft.y); }
	void AlignTopLeft(const float X, const float Y);
	void AlignTopLeft(const cVec2 &TopLeft) { AlignTopLeft(TopLeft.x, TopLeft.y); }
	
	// TopCenter
	const cVec2 GetTopCenter() const { return cVec2(0.5f * (m_Min.x + m_Max.x), m_Max.y); }
	void AlignTopCenter(const float X, const float Y);
	void AlignTopCenter(const cVec2 &TopCenter) { AlignTopCenter(TopCenter.x, TopCenter.y); }

	// TopRight
	const cVec2 GetTopRight() const { return cVec2(m_Max.x, m_Max.y); }
	void SetTopRight(const float X, const float Y) { m_Max.x = X; m_Max.y = Y; }
	void SetTopRight(const cVec2 &TopRight) { SetTopRight(TopRight.x, TopRight.y); }
	void AlignTopRight(const float X, const float Y);
	void AlignTopRight(const cVec2 &TopRight) { AlignTopRight(TopRight.x, TopRight.y); }

	// MiddleLeft
	const cVec2 GetMiddleLeft() const { return cVec2(m_Min.x, 0.5f * (m_Max.y + m_Min.y)); }
	void AlignMiddleLeft(const float X, const float Y);
	void AlignMiddleLeft(const cVec2 &MiddleLeft) { AlignMiddleLeft(MiddleLeft.x, MiddleLeft.y); }

	// MiddleCenter
	const cVec2 GetMiddleCenter() const { return cVec2(0.5f * (m_Min.x + m_Max.x), 0.5f * (m_Max.y + m_Min.y)); }
	void AlignMiddleCenter(const float X, const float Y);
	void AlignMiddleCenter(const cVec2 &MiddleCenter) { AlignMiddleCenter(MiddleCenter.x, MiddleCenter.y); }

	// MiddleRight
	const cVec2 GetMiddleRight() const { return cVec2(m_Max.x, 0.5f * (m_Max.y + m_Min.y)); }
	void AlignMiddleRight(const float X, const float Y);
	void AlignMiddleRight(const cVec2 &MiddleRight) { AlignMiddleRight(MiddleRight.x, MiddleRight.y); }

	// BottomLeft
	const cVec2 GetBottomLeft() const { return cVec2(m_Min.x, m_Min.y); }
	void SetBottomLeft(const float X, const float Y) { m_Min.x = X; m_Min.y = Y; }
	void SetBottomLeft(const cVec2 &BottomLeft) { SetBottomLeft(BottomLeft.x, BottomLeft.y); }
	void AlignBottomLeft(const float X, const float Y);
	void AlignBottomLeft(const cVec2 &BottomLeft) { AlignBottomLeft(BottomLeft.x, BottomLeft.y); }

	// BottomCenter
	const cVec2 GetBottomCenter() const { return cVec2(0.5f * (m_Min.x + m_Max.x), m_Min.y); }
	void AlignBottomCenter(const float X, const float Y);
	void AlignBottomCenter(const cVec2 &BottomCenter) { AlignBottomCenter(BottomCenter.x, BottomCenter.y); }

	// BottomRight
	const cVec2 GetBottomRight() const { return cVec2(m_Max.x, m_Min.y); }
	void SetBottomRight(const float X, const float Y) { m_Max.x = X; m_Min.y = Y; }
	void SetBottomRight(const cVec2 &BottomRight) { SetBottomRight(BottomRight.x, BottomRight.y); }
	void AlignBottomRight(const float X, const float Y);
	void AlignBottomRight(const cVec2 &BottomRight) { AlignBottomRight(BottomRight.x, BottomRight.y); }

	// Returns the specified point position
	const cVec2 GetPoint(const int Align) const;
	void AlignPoint(const int Align, const float X, const float Y);
	void AlignPoint(const int Align, const cVec2 &With) { AlignPoint(Align, With.x, With.y); }
	// Aligns the specified point of this rectangle with similar point on the parent rectangle
	void AlignPoint(const int Align, const cRect &Parent);
	
	// GetDocking { Align, CRegion }
	int GetDockingAlign(const cRect &Child, cRect *DockingRegion = NULL, cVec2 *RelPos = NULL) const;
	const cRect GetDockingRegion(const cRect &Child, const int Align) const;
	int GetDockingAlign(const cVec2 &Child, cRect *DockingRegion = NULL, cVec2 *RelPos = NULL) const;
	const cRect GetDockingRegion(const cVec2 &Child, const int Align) const;
	
	float GetLeft() const { return m_Min.x; }
	float GetTop() const { return m_Max.y; }
	float GetRight() const { return m_Max.x; }
	float GetBottom() const { return m_Min.y; }
	
	float GetWidth() const { return m_Max.x - m_Min.x; }
	float GetHeight() const { return m_Max.y - m_Min.y; }
	
	void SetWidth(const int HoldPoint, const float Width);
	void SetHeight(const int HoldPoint, const float Height);

	const cVec2 GetSize() const { return cVec2(m_Max.x - m_Min.x, m_Max.y - m_Min.y); }
	
	void SetSize(const float MinX, const float MinY, const float Width, const float Height);
	void SetSize(const cVec2 &Min, const cVec2 &Size);
	void SetSize(const int HoldPoint, const float Width, const float Height) { SetWidth(HoldPoint, Width); SetHeight(HoldPoint, Height); }
	void SetSize(const int HoldPoint, const cVec2 &Size) { SetWidth(HoldPoint, Size.x); SetHeight(HoldPoint, Size.y); }
	void SetSize(const int HoldPoint, const float Side) { SetWidth(HoldPoint, Side); SetHeight(HoldPoint, Side); }
	
	float GetCenterX() const { return (m_Min.x + m_Max.x) / 2.0f; }
	float GetCenterY() const { return (m_Min.y + m_Max.y) / 2.0f; }

	void AlignCenterX(const float X);
	void AlignCenterY(const float Y);

	void Inflate(const float DeltaXY);
	void Inflate(const float DeltaX, const float DeltaY);
	void Inflate(const cVec2 &Delta) { Inflate(Delta.x, Delta.y); }

	void SetToPoint(const float X, const float Y);
	void SetToPoint(const cVec2 &P) { SetToPoint(P.x, P.y); }

	const cVec2 ProjectPoint(const cVec2 &) const; // Returns closest point within rectangle

	bool AddPoint(const float X, const float Y);
	bool AddPoint(const cVec2 &P) { return AddPoint(P.x, P.y); }
	
	bool AddRect(const cRect &Rc); // Returns "true" if this rectangle is expanded

	void Translate(const float DeltaX, const float DeltaY);
	void Translate(const cVec2 &Delta) { Translate(Delta.x, Delta.y); }

	bool Contains(const float X, const float Y) const;
	bool Contains(const cVec2 &P) const { return Contains(P.x, P.y); }
	bool Contains(const cRect &Rc) const;
	
	static const cRect Union(const cRect &l, const cRect &r);
	static const cRect Intersect(const cRect &l, const cRect &r);
	bool IntersectsWith(const cRect &Rc) const {
		return !Intersect(*this, Rc).IsEmpty();
	}
	static bool IntersectsWith(const cRect *L, const cRect *R) {
		return !Intersect(*L, *R).IsEmpty();
	}
	
	void Transform(const cMat3 &R); // (x, y, 0)
	void operator *= (const cMat3 &R);

	void Transform(const cMat4 &T); // (x, y, 0, 1), projects the result back into w = 1
	void operator *= (const cMat4 &T);
	
	static const cRect Transform(const cRect &Rc, const cMat3 &R); // (x, y, 0)
	const cRect operator * (const cMat3 &R) const;
	
	static const cRect Transform(const cRect &Rc, const cMat4 &T); // (x, y, 0, 1)
	const cRect operator * (const cMat4 &T) const;

	const cRect ToRound() const;
	void Round();

	static const cRect Zero;
	static const cRect Empty;
	static const cRect Unit;

	bool IsEmpty() const { return m_Min.x > m_Max.x || m_Min.y > m_Max.y; }
	void SetEmpty() { Set(cMath::FloatMaxValue, cMath::FloatMaxValue, -cMath::FloatMaxValue, -cMath::FloatMaxValue); }
	void SetZero() { Set(0.0f, 0.0f, 0.0f, 0.0f); }

	// Returns inscribed and centered rectangle with preserved proportions
	static const cRect Inscribe(const cRect &What, const cRect &Where);
};

// cRect.ctor : (const ESetCtor, const float, ...)
inline cRect::cRect(const ESetCtor, const float MinX, const float MinY, const float MaxX, const float MaxY)
: m_Min(MinX, MinY), m_Max(MaxX, MaxY) {}

// cRect.ctor : (const ESetCtor, const cVec2 &, ...)
inline cRect::cRect(const ESetCtor, const cVec2 &Min, const cVec2 &Max)
: m_Min(Min), m_Max(Max) {}

// cRect.ctor : (const ESizeCtor, const float, ...)
inline cRect::cRect(const ESizeCtor, const float MinX, const float MinY, const float Width, const float Height)
: m_Min(MinX, MinY), m_Max(MinX + Width, MinY + Height) {}

// cRect.ctor : (const ESizeCtor, const cVec2 &, ...)
inline cRect::cRect(const ESizeCtor, const cVec2 &Min, const cVec2 &Size)
: m_Min(Min), m_Max(Min + Size) {}

// cRect::operator ==
inline bool cRect::operator == (const cRect &r) const {
	return m_Min == r.m_Min && m_Max == r.m_Max;
}

// cRect::operator !=
inline bool cRect::operator != (const cRect &r) const {
	return m_Min != r.m_Min || m_Max != r.m_Max;
}

// cRect::Equals
inline bool cRect::Equals(const cRect &l, const cRect &r, const float Eps) {
	return cVec2::Equals(l.m_Min, r.m_Min, Eps) && cVec2::Equals(l.m_Max, r.m_Max, Eps);
}

// cRect::Set : (const float, ...)
inline void cRect::Set(const float MinX, const float MinY, const float MaxX, const float MaxY) {
	m_Min.Set(MinX, MinY);
	m_Max.Set(MaxX, MaxY);
}

// cRect::Set : (const cVec2 &, ...)
inline void cRect::Set(const cVec2 &Min, const cVec2 &Max) {
	m_Min = Min;
	m_Max = Max;
}

// cRect::SetSize : (const float, ...)
inline void cRect::SetSize(const float MinX, const float MinY, const float Width, const float Height) {
	m_Min.Set(MinX, MinY);
	m_Max.Set(MinX + Width, MinY + Height);
}

// cRect::SetSize : (const cVec2 &, ...)
inline void cRect::SetSize(const cVec2 &Min, const cVec2 &Size) {
	m_Min = Min;
	m_Max = Min + Size;
}

// cRect::AlignLeft
inline void cRect::AlignLeft(const float X) {
	const float W = m_Max.x - m_Min.x;
	m_Min.x = X;
	m_Max.x = m_Min.x + W;
}

// cRect::AlignTop
inline void cRect::AlignTop(const float Y) {
	const float H = m_Max.y - m_Min.y;
	m_Max.y = Y;
	m_Min.y = m_Max.y - H;
}

// cRect::AlignTopLeft : (const float, ...)
inline void cRect::AlignTopLeft(const float X, const float Y) {
	const float W = m_Max.x - m_Min.x;
	const float H = m_Max.y - m_Min.y;
	m_Min.x = X;
	m_Max.y = Y;
	m_Max.x = m_Min.x + W;
	m_Min.y = m_Max.y - H;
}

// cRect::AlignTopCenter : (const float, ...)
inline void cRect::AlignTopCenter(const float X, const float Y) {
	const float W = m_Max.x - m_Min.x;
	const float H = m_Max.y - m_Min.y;
	m_Min.x = X - 0.5f * W;
	m_Max.y = Y;
	m_Max.x = m_Min.x + W;
	m_Min.y = m_Max.y - H;
}

// cRect::AlignTopRight : (const float, ...)
inline void cRect::AlignTopRight(const float X, const float Y) {
	const float W = m_Max.x - m_Min.x;
	const float H = m_Max.y - m_Min.y;
	m_Min.x = X - W;
	m_Max.y = Y;
	m_Max.x = X;
	m_Min.y = m_Max.y - H;
}

// cRect::AlignMiddleLeft : (const float, ...)
inline void cRect::AlignMiddleLeft(const float X, const float Y) {
	const float W = m_Max.x - m_Min.x;
	const float H = m_Max.y - m_Min.y;
	m_Min.x = X;
	m_Max.y = Y + 0.5f * H;
	m_Max.x = m_Min.x + W;
	m_Min.y = m_Max.y - H;
}

// cRect::AlignCenterX
inline void cRect::AlignCenterX(const float X) {
	const float W = m_Max.x - m_Min.x;
	m_Min.x = X - 0.5f * W;
	m_Max.x = m_Min.x + W;
}

// cRect::AlignCenterY
inline void cRect::AlignCenterY(const float Y) {
	const float H = m_Max.y - m_Min.y;
	m_Max.y = Y + 0.5f * H;
	m_Min.y = m_Max.y - H;
}

// cRect::AlignMiddleCenter : (const float, ...)
inline void cRect::AlignMiddleCenter(const float X, const float Y) {
	const float W = m_Max.x - m_Min.x;
	const float H = m_Max.y - m_Min.y;
	m_Min.x = X - 0.5f * W;
	m_Max.y = Y + 0.5f * H;
	m_Max.x = m_Min.x + W;
	m_Min.y = m_Max.y - H;
}

// cRect::AlignMiddleRight : (const float, ...)
inline void cRect::AlignMiddleRight(const float X, const float Y) {
	const float W = m_Max.x - m_Min.x;
	const float H = m_Max.y - m_Min.y;
	m_Min.x = X - W;
	m_Max.y = Y + 0.5f * H;
	m_Max.x = X;
	m_Min.y = m_Max.y - H;
}

// cRect::AlignBottomLeft : (const float, ...)
inline void cRect::AlignBottomLeft(const float X, const float Y) {
	const float W = m_Max.x - m_Min.x;
	const float H = m_Max.y - m_Min.y;
	m_Min.x = X;
	m_Max.y = Y + H;
	m_Max.x = m_Min.x + W;
	m_Min.y = Y;
}

// cRect::AlignBottomCenter : (const float, ...)
inline void cRect::AlignBottomCenter(const float X, const float Y) {
	const float W = m_Max.x - m_Min.x;
	const float H = m_Max.y - m_Min.y;
	m_Min.x = X - 0.5f * W;
	m_Max.y = Y + H;
	m_Max.x = m_Min.x + W;
	m_Min.y = Y;
}

// cRect::AlignRight
inline void cRect::AlignRight(const float X) {
	const float W = m_Max.x - m_Min.x;
	m_Min.x = X - W;
	m_Max.x = X;
}

// cRect::AlignBottom
inline void cRect::AlignBottom(const float Y) {
	const float H = m_Max.y - m_Min.y;
	m_Max.y = Y + H;
	m_Min.y = Y;
}

// cRect::AlignBottomRight : (const float, ...)
inline void cRect::AlignBottomRight(const float X, const float Y) {
	const float W = m_Max.x - m_Min.x;
	const float H = m_Max.y - m_Min.y;
	m_Min.x = X - W;
	m_Max.y = Y + H;
	m_Max.x = X;
	m_Min.y = Y;
}

// cRect::SetToPoint : (const float, ...)
inline void cRect::SetToPoint(const float X, const float Y) {
	m_Min.x = m_Max.x = X;
	m_Max.y = m_Min.y = Y;
}

// cRect::ProjectPoint
inline const cVec2 cRect::ProjectPoint(const cVec2 &p) const {
	return cVec2(cMath::Clamp(p.x, m_Min.x, m_Max.x), cMath::Clamp(p.y, m_Min.y, m_Max.y));
}

//-----------------------------------------------------------------------------
// cRect::AddPoint : (const float, ...)
//-----------------------------------------------------------------------------
inline bool cRect::AddPoint(const float X, const float Y) {
	bool Expanded = false;
	if(X < m_Min.x) {
		m_Min.x = X;
		Expanded = true;
	}
	if(Y > m_Max.y) {
		m_Max.y = Y;
		Expanded = true;
	}
	if(X > m_Max.x) {
		m_Max.x = X;
		Expanded = true;
	}
	if(Y < m_Min.y) {
		m_Min.y = Y;
		Expanded = true;
	}
	return Expanded;
} // cRect::AddPoint

//-----------------------------------------------------------------------------
// cRect::AddRect
//-----------------------------------------------------------------------------
inline bool cRect::AddRect(const cRect &Rc) {
	bool Expanded = false;
	if(Rc.m_Min.x < m_Min.x) {
		m_Min.x = Rc.m_Min.x;
		Expanded = true;
	}
	if(Rc.m_Max.y > m_Max.y) {
		m_Max.y = Rc.m_Max.y;
		Expanded = true;
	}
	if(Rc.m_Max.x > m_Max.x) {
		m_Max.x = Rc.m_Max.x;
		Expanded = true;
	}
	if(Rc.m_Min.y < m_Min.y) {
		m_Min.y = Rc.m_Min.y;
		Expanded = true;
	}
	return Expanded;
} // cRect::AddRect

// cRect::Inflate : (const float)
inline void cRect::Inflate(const float Delta) {
	m_Min.x -= Delta;
	m_Max.y += Delta;
	m_Max.x += Delta;
	m_Min.y -= Delta;
}

// cRect::Inflate : (const float, const float)
inline void cRect::Inflate(const float DeltaX, const float DeltaY) {
	m_Min.x -= DeltaX;
	m_Max.y += DeltaY;
	m_Max.x += DeltaX;
	m_Min.y -= DeltaY;
}

// cRect::Contains : (const float, ...)
inline bool cRect::Contains(const float X, const float Y) const {
	return m_Min.x <= X && m_Max.y >= Y && m_Max.x >= X && m_Min.y <= Y;
}

// cRect::Contains : (const cRect &)
inline bool cRect::Contains(const cRect &Rc) const {
	return m_Min.x <= Rc.m_Min.x && m_Max.y >= Rc.m_Max.y && m_Max.x >= Rc.m_Max.x && m_Min.y <= Rc.m_Min.y;
}

//-----------------------------------------------------------------------------
// cRect::Union
//-----------------------------------------------------------------------------
inline const cRect cRect::Union(const cRect &l, const cRect &r) {
	cRect u;
	u.m_Min = cVec2::Min(l.m_Min, r.m_Min);
	u.m_Max = cVec2::Max(l.m_Max, r.m_Max);
	return u;
} // cRect::Union

//-----------------------------------------------------------------------------
// cRect::Intersect
//-----------------------------------------------------------------------------
inline const cRect cRect::Intersect(const cRect &l, const cRect &r) {
	cRect i;
	i.m_Min = cVec2::Max(l.m_Min, r.m_Min);
	i.m_Max = cVec2::Min(l.m_Max, r.m_Max);
	return i;
} // cRect::Intersect

// cRect::Translate : (const float, ...)
inline void cRect::Translate(const float DeltaX, const float DeltaY) {
	m_Min.x += DeltaX;
	m_Max.y += DeltaY;
	m_Max.x += DeltaX;
	m_Min.y += DeltaY;
}

// cRect::Transform : (const cMat3 &)
inline void cRect::Transform(const cMat3 &R) {
	m_Min.Transform(R);
	m_Max.Transform(R);
}

// cRect::operator *= : (const cMat3 &)
inline void cRect::operator *= (const cMat3 &R) {
	Transform(R);
}

// cRect::Transform
inline void cRect::Transform(const cMat4 &T) {
	m_Min.TransformCoordinate(T);
	m_Max.TransformCoordinate(T);
}

// cRect::operator *= : (const cMat4 &)
inline void cRect::operator *= (const cMat4 &T) {
	Transform(T);
}

// cRect::Transform : (const cRect &, const cMat3 &)
inline const cRect cRect::Transform(const cRect &Rc, const cMat3 &R) {
	cRect r = Rc;
	r.Transform(R);
	return r;
}

// cRect::operator * : (const cMat3 &)
inline const cRect cRect::operator * (const cMat3 &R) const {
	return Transform(*this, R);
}

// cRect::Transform : (const cRect &, const cMat4 &)
inline const cRect cRect::Transform(const cRect &Rc, const cMat4 &T) {
	cRect r = Rc;
	r.Transform(T);
	return r;
}

// cRect::operator * : (const cMat4 &)
inline const cRect cRect::operator * (const cMat4 &T) const {
	return Transform(*this, T);
}

// cRect::ToRound
inline const cRect cRect::ToRound() const {
	return cRect(cRect::SetCtor, m_Min.ToRound(), m_Max.ToRound());
}

// cRect::Round
inline void cRect::Round() {
	m_Min.Round();
	m_Max.Round();
}
