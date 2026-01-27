#pragma once
#include <QColor>
#include <span>
struct Theme{
public:
	QColor Background,
		   Background2,
		   Background3,
		   Primary,
		   Secondary,
		   Trinary,
		   Neutral,
		   Red1,
		   Red2,
		   Green1,
		   Green2,
		   DisabledPrimary,
		   DisabledSecondary,
		   DisabledTrinary,
		   DisabledNeutral,
		   DisabledRed1,
		   DisabledRed2,
		   DisabledGreen1,
		   DisabledGreen2,
		   Text1,
		   Text2,
		   TextInverted1,
		   TextInverted2;
	static Theme Default(){
		Theme t;
        t.Background =			QColor::fromRgb(0x41,0x46,0x4A);
        t.Background2 =			QColor::fromRgb(0x31,0x33,0x35);
        t.Background3 =			QColor::fromRgb(0x22,0x20,0x22);
        t.Primary =				QColor::fromRgb(0x09,0x89,0xD4);
        t.Secondary =			QColor::fromRgb(0x16,0x3C,0xBB);
        t.Trinary =				QColor::fromRgb(0x3F,0x4C,0xD9);
        t.Neutral =				QColor::fromRgb(0x72,0x78,0x82);
        t.Red1 =				QColor::fromRgb(0xFF,0x16,0x16);
        t.Red2 =				QColor::fromRgb(0xFB,0x3E,0x3E);
        t.Green1 =				QColor::fromRgb(0x16,0xFF,0x16);
        t.Green2 =				QColor::fromRgb(0x3E,0xFB,0x3E);
        t.DisabledPrimary =		QColor::fromRgb(0x68,0xA7,0xCC);
        t.DisabledSecondary =	QColor::fromRgb(0x2E,0x3F,0x73);
        t.DisabledTrinary =		QColor::fromRgb(0x66,0x70,0xCC);
        t.DisabledNeutral =		QColor::fromRgb(0x59,0x59,0x59);
        t.DisabledRed1 =		QColor::fromRgb(0xCC,0x52,0x52);
        t.DisabledRed2 =		QColor::fromRgb(0xCC,0x7A,0x7A);
        t.DisabledGreen1 =		QColor::fromRgb(0x59,0xCC,0x59);
        t.DisabledGreen2 =		QColor::fromRgb(0x7A,0xCC,0x7A);
        t.Text1 =				QColor::fromRgb(0xFF,0xFF,0xFF);
        t.Text2 =				QColor::fromRgb(0xD1,0xD3,0xD6);
        t.TextInverted1 =		QColor::fromRgb(0x00,0x00,0x00);
        t.TextInverted2 =		QColor::fromRgb(0x27,0x28,0x29);
		return t;
	}
};

union ArrayTheme{
    Theme t;
    QColor colors[23];
};
