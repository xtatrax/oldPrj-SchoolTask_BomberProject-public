#pragma once

#include <windows.h>

namespace wiz {
namespace yamanoit{
#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))
#endif


/////////////////////////////////////////////////////////////////////////////
class Size;
class Point;
class Rect;

/////////////////////////////////////////////////////////////////////////////
class Size : public tagSIZE
{
public:
	Size() throw();
	Size(int initCX, int initCY) throw();
	Size(SIZE initSize) throw();
	Size(POINT initPt) throw();
	Size(DWORD dwSize) throw();
	BOOL operator==(SIZE size) const throw();
	BOOL operator!=(SIZE size) const throw();
	void operator+=(SIZE size) throw();
	void operator-=(SIZE size) throw();
	void SetSize(int CX, int CY) throw();
	Size operator+(SIZE size) const throw();
	Size operator-(SIZE size) const throw();
	Size operator-() const throw();
	Point operator+(POINT point) const throw();
	Point operator-(POINT point) const throw();
	Rect operator+(const RECT* lpRect) const throw();
	Rect operator-(const RECT* lpRect) const throw();
};

/////////////////////////////////////////////////////////////////////////////
class Point : public tagPOINT
{
public:
	Point() throw();
	Point(int initX, int initY) throw();
	Point(POINT initPt) throw();
	Point(SIZE initSize) throw();
	Point(LPARAM dwPoint) throw();
	void Offset(int xOffset, int yOffset) throw();
	void Offset(POINT point) throw();
	void Offset(SIZE size) throw();
	void SetPoint(int X, int Y) throw();
	BOOL operator==(POINT point) const throw();
	BOOL operator!=(POINT point) const throw();
	void operator+=(SIZE size) throw();
	void operator-=(SIZE size) throw();
	void operator+=(POINT point) throw();
	void operator-=(POINT point) throw();
	Point operator+(SIZE size) const throw();
	Point operator-(SIZE size) const throw();
	Point operator-() const throw();
	Point operator+(POINT point) const throw();
	Size operator-(POINT point) const throw();
	Rect operator+(const RECT* lpRect) const throw();
	Rect operator-(const RECT* lpRect) const throw();
};

/////////////////////////////////////////////////////////////////////////////

class Rect : public tagRECT
{
public:
	Rect() throw();
	Rect(int l, int t, int r, int b) throw();
	Rect(const RECT& srcRect) throw();
	Rect(LPCRECT lpSrcRect) throw();
	Rect(POINT point, SIZE size) throw();
	Rect(POINT topLeft, POINT bottomRight) throw();
	int Width() const throw();
	int Height() const throw();
	Size Size() const throw();
	Point& TopLeft() throw();
	Point& BottomRight() throw();
	const Point& TopLeft() const throw();
	const Point& BottomRight() const throw();
	Point CenterPoint() const throw();
	void SwapLeftRight() throw();
	static void WINAPI SwapLeftRight(LPRECT lpRect) throw();
	operator LPRECT() throw();
	operator LPCRECT() const throw();
	BOOL IsRectEmpty() const throw();
	BOOL IsRectNull() const throw();
	BOOL PtInRect(POINT point) const throw();
	void SetRect(int x1, int y1, int x2, int y2) throw();
	void SetRect(POINT topLeft, POINT bottomRight) throw();
	void SetRectEmpty() throw();
	void CopyRect(LPCRECT lpSrcRect) throw();
	BOOL EqualRect(LPCRECT lpRect) const throw();
	void InflateRect(int x, int y) throw();
	void InflateRect(SIZE size) throw();
	void InflateRect(LPCRECT lpRect) throw();
	void InflateRect(int l, int t, int r, int b) throw();
	void DeflateRect(int x, int y) throw();
	void DeflateRect(SIZE size) throw();
	void DeflateRect(LPCRECT lpRect) throw();
	void DeflateRect(int l, int t, int r, int b) throw();
	void OffsetRect(int x, int y) throw();
	void OffsetRect(SIZE size) throw();
	void OffsetRect(POINT point) throw();
	void NormalizeRect() throw();
	void MoveToY(int y) throw();
	void MoveToX(int x) throw();
	void MoveToXY(int x, int y) throw();
	void MoveToXY(POINT point) throw();
	BOOL IntersectRect(LPCRECT lpRect1, LPCRECT lpRect2) throw();
	BOOL UnionRect(LPCRECT lpRect1, LPCRECT lpRect2) throw();
	BOOL SubtractRect(LPCRECT lpRectSrc1, LPCRECT lpRectSrc2) throw();
	void operator=(const RECT& srcRect) throw();
	BOOL operator==(const RECT& rect) const throw();
	BOOL operator!=(const RECT& rect) const throw();
	void operator+=(POINT point) throw();
	void operator+=(SIZE size) throw();
	void operator+=(LPCRECT lpRect) throw();
	void operator-=(POINT point) throw();
	void operator-=(SIZE size) throw();
	void operator-=(LPCRECT lpRect) throw();
	void operator&=(const RECT& rect) throw();
	void operator|=(const RECT& rect) throw();

	Rect operator+(POINT point) const throw();
	Rect operator-(POINT point) const throw();
	Rect operator+(LPCRECT lpRect) const throw();
	Rect operator+(SIZE size) const throw();
	Rect operator-(SIZE size) const throw();
	Rect operator-(LPCRECT lpRect) const throw();
	Rect operator&(const RECT& rect2) const throw();
	Rect operator|(const RECT& rect2) const throw();
	Rect MulDiv(int nMultiplier, int nDivisor) const throw();
};

// Size
inline Size::Size() throw()
	{ /* random filled */ }
inline Size::Size(int initCX, int initCY) throw()
	{ cx = initCX; cy = initCY; }
inline Size::Size(SIZE initSize) throw()
	{ *(SIZE*)this = initSize; }
inline Size::Size(POINT initPt) throw()
	{ *(POINT*)this = initPt; }
inline Size::Size(DWORD dwSize) throw()
	{
		cx = (short)LOWORD(dwSize);
		cy = (short)HIWORD(dwSize);
	}
inline BOOL Size::operator==(SIZE size) const throw()
	{ return (cx == size.cx && cy == size.cy); }
inline BOOL Size::operator!=(SIZE size) const throw()
	{ return (cx != size.cx || cy != size.cy); }
inline void Size::operator+=(SIZE size) throw()
	{ cx += size.cx; cy += size.cy; }
inline void Size::operator-=(SIZE size) throw()
	{ cx -= size.cx; cy -= size.cy; }
inline void Size::SetSize(int CX, int CY) throw()
	{ cx = CX; cy = CY; }	
inline Size Size::operator+(SIZE size) const throw()
	{ return Size(cx + size.cx, cy + size.cy); }
inline Size Size::operator-(SIZE size) const throw()
	{ return Size(cx - size.cx, cy - size.cy); }
inline Size Size::operator-() const throw()
	{ return Size(-cx, -cy); }
inline Point Size::operator+(POINT point) const throw()
	{ return Point(cx + point.x, cy + point.y); }
inline Point Size::operator-(POINT point) const throw()
	{ return Point(cx - point.x, cy - point.y); }
inline Rect Size::operator+(const RECT* lpRect) const throw()
	{ return Rect(lpRect) + *this; }
inline Rect Size::operator-(const RECT* lpRect) const throw()
	{ return Rect(lpRect) - *this; }

// Point
inline Point::Point() throw()
	{ /* random filled */ }
inline Point::Point(int initX, int initY) throw()
	{ x = initX; y = initY; }
inline Point::Point(POINT initPt) throw()
	{ *(POINT*)this = initPt; }
inline Point::Point(SIZE initSize) throw()
	{ *(SIZE*)this = initSize; }
inline Point::Point(LPARAM dwPoint) throw()
	{
		x = (short)GET_X_LPARAM(dwPoint);
		y = (short)GET_Y_LPARAM(dwPoint);
	}
inline void Point::Offset(int xOffset, int yOffset) throw()
	{ x += xOffset; y += yOffset; }
inline void Point::Offset(POINT point) throw()
	{ x += point.x; y += point.y; }
inline void Point::Offset(SIZE size) throw()
	{ x += size.cx; y += size.cy; }
inline void Point::SetPoint(int X, int Y) throw()
	{ x = X; y = Y; }
inline BOOL Point::operator==(POINT point) const throw()
	{ return (x == point.x && y == point.y); }
inline BOOL Point::operator!=(POINT point) const throw()
	{ return (x != point.x || y != point.y); }
inline void Point::operator+=(SIZE size) throw()
	{ x += size.cx; y += size.cy; }
inline void Point::operator-=(SIZE size) throw()
	{ x -= size.cx; y -= size.cy; }
inline void Point::operator+=(POINT point) throw()
	{ x += point.x; y += point.y; }
inline void Point::operator-=(POINT point) throw()
	{ x -= point.x; y -= point.y; }
inline Point Point::operator+(SIZE size) const throw()
	{ return Point(x + size.cx, y + size.cy); }
inline Point Point::operator-(SIZE size) const throw()
	{ return Point(x - size.cx, y - size.cy); }
inline Point Point::operator-() const throw()
	{ return Point(-x, -y); }
inline Point Point::operator+(POINT point) const throw()
	{ return Point(x + point.x, y + point.y); }
inline Size Point::operator-(POINT point) const throw()
	{ return Size(x - point.x, y - point.y); }
inline Rect Point::operator+(const RECT* lpRect) const throw()
	{ return Rect(lpRect) + *this; }
inline Rect Point::operator-(const RECT* lpRect) const throw()
	{ return Rect(lpRect) - *this; }

// Rect
inline Rect::Rect() throw()
	{ /* random filled */ }
inline Rect::Rect(int l, int t, int r, int b) throw()
	{ left = l; top = t; right = r; bottom = b; }
inline Rect::Rect(const RECT& srcRect) throw()
	{ ::CopyRect(this, &srcRect); }
inline Rect::Rect(LPCRECT lpSrcRect) throw()
	{ ::CopyRect(this, lpSrcRect); }
inline Rect::Rect(POINT point, SIZE size) throw()
	{ right = (left = point.x) + size.cx; bottom = (top = point.y) + size.cy; }
inline Rect::Rect(POINT topLeft, POINT bottomRight) throw()
	{ left = topLeft.x; top = topLeft.y;
		right = bottomRight.x; bottom = bottomRight.y; }
inline int Rect::Width() const throw()
	{ return right - left; }
inline int Rect::Height() const throw()
	{ return bottom - top; }
inline Size Rect::Size() const throw()
{ return yamanoit::Size(right - left, bottom - top); }
inline Point& Rect::TopLeft() throw()
	{ return *((Point*)this); }
inline Point& Rect::BottomRight() throw()
	{ return *((Point*)this+1); }
inline const Point& Rect::TopLeft() const throw()
	{ return *((Point*)this); }
inline const Point& Rect::BottomRight() const throw()
	{ return *((Point*)this+1); }
inline Point Rect::CenterPoint() const throw()
	{ return Point((left+right)/2, (top+bottom)/2); }
inline void Rect::SwapLeftRight() throw()
	{ SwapLeftRight(LPRECT(this)); }
inline void WINAPI Rect::SwapLeftRight(LPRECT lpRect) throw()
	{ LONG temp = lpRect->left; lpRect->left = lpRect->right; lpRect->right = temp; }
inline Rect::operator LPRECT() throw()
	{ return this; }
inline Rect::operator LPCRECT() const throw()
	{ return this; }
inline BOOL Rect::IsRectEmpty() const throw()
	{ return ::IsRectEmpty(this); }
inline BOOL Rect::IsRectNull() const throw()
	{ return (left == 0 && right == 0 && top == 0 && bottom == 0); }
inline BOOL Rect::PtInRect(POINT point) const throw()
	{ return ::PtInRect(this, point); }
inline void Rect::SetRect(int x1, int y1, int x2, int y2) throw()
	{ ::SetRect(this, x1, y1, x2, y2); }
inline void Rect::SetRect(POINT topLeft, POINT bottomRight) throw()
	{ ::SetRect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y); }
inline void Rect::SetRectEmpty() throw()
	{ ::SetRectEmpty(this); }
inline void Rect::CopyRect(LPCRECT lpSrcRect) throw()
	{ ::CopyRect(this, lpSrcRect); }
inline BOOL Rect::EqualRect(LPCRECT lpRect) const throw()
	{ return ::EqualRect(this, lpRect); }
inline void Rect::InflateRect(int x, int y) throw()
	{ ::InflateRect(this, x, y); }
inline void Rect::InflateRect(SIZE size) throw()
	{ ::InflateRect(this, size.cx, size.cy); }
inline void Rect::DeflateRect(int x, int y) throw()
	{ ::InflateRect(this, -x, -y); }
inline void Rect::DeflateRect(SIZE size) throw()
	{ ::InflateRect(this, -size.cx, -size.cy); }
inline void Rect::OffsetRect(int x, int y) throw()
	{ ::OffsetRect(this, x, y); }
inline void Rect::OffsetRect(POINT point) throw()
	{ ::OffsetRect(this, point.x, point.y); }
inline void Rect::OffsetRect(SIZE size) throw()
	{ ::OffsetRect(this, size.cx, size.cy); }
inline void Rect::MoveToY(int y) throw()
	{ bottom = Height() + y; top = y; }
inline void Rect::MoveToX(int x) throw()
	{ right = Width() + x; left = x; }
inline void Rect::MoveToXY(int x, int y) throw()
	{ MoveToX(x); MoveToY(y); }
inline void Rect::MoveToXY(POINT pt) throw()
	{ MoveToX(pt.x); MoveToY(pt.y); }
inline BOOL Rect::IntersectRect(LPCRECT lpRect1, LPCRECT lpRect2) throw()
	{ return ::IntersectRect(this, lpRect1, lpRect2);}
inline BOOL Rect::UnionRect(LPCRECT lpRect1, LPCRECT lpRect2) throw()
	{ return ::UnionRect(this, lpRect1, lpRect2); }
inline void Rect::operator=(const RECT& srcRect) throw()
	{ ::CopyRect(this, &srcRect); }
inline BOOL Rect::operator==(const RECT& rect) const throw()
	{ return ::EqualRect(this, &rect); }
inline BOOL Rect::operator!=(const RECT& rect) const throw()
	{ return !::EqualRect(this, &rect); }
inline void Rect::operator+=(POINT point) throw()
	{ ::OffsetRect(this, point.x, point.y); }
inline void Rect::operator+=(SIZE size) throw()
	{ ::OffsetRect(this, size.cx, size.cy); }
inline void Rect::operator+=(LPCRECT lpRect) throw()
	{ InflateRect(lpRect); }
inline void Rect::operator-=(POINT point) throw()
	{ ::OffsetRect(this, -point.x, -point.y); }
inline void Rect::operator-=(SIZE size) throw()
	{ ::OffsetRect(this, -size.cx, -size.cy); }
inline void Rect::operator-=(LPCRECT lpRect) throw()
	{ DeflateRect(lpRect); }
inline void Rect::operator&=(const RECT& rect) throw()
	{ ::IntersectRect(this, this, &rect); }
inline void Rect::operator|=(const RECT& rect) throw()
	{ ::UnionRect(this, this, &rect); }
inline Rect Rect::operator+(POINT pt) const throw()
	{ Rect rect(*this); ::OffsetRect(&rect, pt.x, pt.y); return rect; }
inline Rect Rect::operator-(POINT pt) const throw()
	{ Rect rect(*this); ::OffsetRect(&rect, -pt.x, -pt.y); return rect; }
inline Rect Rect::operator+(SIZE size) const throw()
	{ Rect rect(*this); ::OffsetRect(&rect, size.cx, size.cy); return rect; }
inline Rect Rect::operator-(SIZE size) const throw()
	{ Rect rect(*this); ::OffsetRect(&rect, -size.cx, -size.cy); return rect; }
inline Rect Rect::operator+(LPCRECT lpRect) const throw()
	{ Rect rect(this); rect.InflateRect(lpRect); return rect; }
inline Rect Rect::operator-(LPCRECT lpRect) const throw()
	{ Rect rect(this); rect.DeflateRect(lpRect); return rect; }
inline Rect Rect::operator&(const RECT& rect2) const throw()
	{ Rect rect; ::IntersectRect(&rect, this, &rect2);
		return rect; }
inline Rect Rect::operator|(const RECT& rect2) const throw()
	{ Rect rect; ::UnionRect(&rect, this, &rect2);
		return rect; }
inline BOOL Rect::SubtractRect(LPCRECT lpRectSrc1, LPCRECT lpRectSrc2) throw()
	{ return ::SubtractRect(this, lpRectSrc1, lpRectSrc2); }

inline void Rect::NormalizeRect() throw()
	{
		int nTemp;
		if (left > right)
		{
			nTemp = left;
			left = right;
			right = nTemp;
		}
		if (top > bottom)
		{
			nTemp = top;
			top = bottom;
			bottom = nTemp;
		}
	}

inline void Rect::InflateRect(LPCRECT lpRect) throw()
	{
		left -= lpRect->left;		top -= lpRect->top;
		right += lpRect->right;		bottom += lpRect->bottom;
	}

inline void Rect::InflateRect(int l, int t, int r, int b) throw()
	{
		left -= l;			top -= t;
		right += r;			bottom += b;
	}

inline void Rect::DeflateRect(LPCRECT lpRect) throw()
	{
		left += lpRect->left;	top += lpRect->top;
		right -= lpRect->right;	bottom -= lpRect->bottom;
	}

inline void Rect::DeflateRect(int l, int t, int r, int b) throw()
	{
		left += l;		top += t;
		right -= r;		bottom -= b;
	}

inline Rect Rect::MulDiv(int nMultiplier, int nDivisor) const throw()
	{
		return Rect(
			::MulDiv(left, nMultiplier, nDivisor),
			::MulDiv(top, nMultiplier, nDivisor),
			::MulDiv(right, nMultiplier, nDivisor),
			::MulDiv(bottom, nMultiplier, nDivisor));
	}

}//end of namespace yamanoit.
using namespace yamanoit ;
}//end of namespace wiz.

