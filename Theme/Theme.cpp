#include "Theme.h"
Theme Theme::Default(){
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
//declareing this in header causes link errors
Theme Theme::m_currentTheme = Theme::Default();
#include <iostream>
void Theme::Print(){
    std::cout
        << "[THEME] :\n"
        << "\tBackground : (" << Background.red() << ',' << Background.green() << ',' << Background.blue() << ',' << Background.alpha() << ")\n"
        << "\tBackground2 : (" << Background2.red() << ',' << Background2.green() << ',' << Background2.blue() << ',' << Background2.alpha() << ")\n"
        << "\tBackground3 : (" << Background3.red() << ',' << Background3.green() << ',' << Background3.blue() << ',' << Background3.alpha() << ")\n"
        << "\tPrimary : (" << Primary.red() << ',' << Primary.green() << ',' << Primary.blue() << ',' << Primary.alpha() << ")\n"
        << "\tSecondary : (" << Secondary.red() << ',' << Secondary.green() << ',' << Secondary.blue() << ',' << Secondary.alpha() << ")\n"
        << "\tTrinary : (" << Trinary.red() << ',' << Trinary.green() << ',' << Trinary.blue() << ',' << Trinary.alpha() << ")\n"
        << "\tNeutral : (" << Neutral.red() << ',' << Neutral.green() << ',' << Neutral.blue() << ',' << Neutral.alpha() << ")\n"
        << "\tRed1 : (" << Red1.red() << ',' << Red1.green() << ',' << Red1.blue() << ',' << Red1.alpha() << ")\n"
        << "\tRed2 : (" << Red2.red() << ',' << Red2.green() << ',' << Red2.blue() << ',' << Red2.alpha() << ")\n"
        << "\tGreen1 : (" << Green1.red() << ',' << Green1.green() << ',' << Green1.blue() << ',' << Green1.alpha() << ")\n"
        << "\tGreen2 : (" << Green2.red() << ',' << Green2.green() << ',' << Green2.blue() << ',' << Green2.alpha() << ")\n"
        << "\tDisabledPrimary : ("<< DisabledPrimary .red() << ',' << DisabledPrimary .green() << ',' << DisabledPrimary .blue() << ',' << DisabledPrimary .alpha() << ")\n"
        << "\tDisabledSecondary : ("<< DisabledSecondary .red() << ',' << DisabledSecondary .green() << ',' << DisabledSecondary .blue() << ',' << DisabledSecondary .alpha() << ")\n"
        << "\tDisabledTrinary : ("<< DisabledTrinary .red() << ',' << DisabledTrinary .green() << ',' << DisabledTrinary .blue() << ',' << DisabledTrinary .alpha() << ")\n"
        << "\tDisabledNeutral : ("<< DisabledNeutral .red() << ',' << DisabledNeutral .green() << ',' << DisabledNeutral .blue() << ',' << DisabledNeutral .alpha() << ")\n"
        << "\tDisabledRed1 : ("<< DisabledRed1 .red() << ',' << DisabledRed1 .green() << ',' << DisabledRed1 .blue() << ',' << DisabledRed1 .alpha() << ")\n"
        << "\tDisabledRed2 : ("<< DisabledRed2 .red() << ',' << DisabledRed2 .green() << ',' << DisabledRed2 .blue() << ',' << DisabledRed2 .alpha() << ")\n"
        << "\tDisabledGreen1 : ("<< DisabledGreen1 .red() << ',' << DisabledGreen1 .green() << ',' << DisabledGreen1 .blue() << ',' << DisabledGreen1 .alpha() << ")\n"
        << "\tDisabledGreen2 : ("<< DisabledGreen2.red() << ',' << DisabledGreen2.green() << ',' << DisabledGreen2.blue() << ',' << DisabledGreen2.alpha() << ")\n"
        << "\tText1 : (" << Text1.red() << ',' << Text1.green() << ',' << Text1.blue() << ',' << Text1.alpha() << ")\n"
        << "\tText2 : (" << Text2.red() << ',' << Text2.green() << ',' << Text2.blue() << ',' << Text2.alpha() << ")\n"
        << "\tTextInverted1 : (" << TextInverted1.red() << ',' << TextInverted1.green() << ',' << TextInverted1.blue() << ',' << TextInverted1.alpha() << ")\n"
        << "\tTextInverted2 : (" << TextInverted2.red() << ',' << TextInverted2.green() << ',' << TextInverted2.blue() << ',' << TextInverted2.alpha() << ")\n"
        << "\tTransparent : (" << Transparent.red() << ',' << Transparent.green() << ',' << Transparent.blue() << ',' << Transparent.alpha() <<  ")\n";
}
