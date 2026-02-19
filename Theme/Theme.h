#ifndef THEME_H
#define THEME_H
#include <QColor>
struct Theme{
    Theme(){
        Transparent = QColor::fromRgb(0,0,0,0);
    }

    QColor
        Background,
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
        TextInverted2,
        Transparent
        ;
    static Theme Default();
    static Theme m_currentTheme;
    void Print();
};

union ArrayTheme{
    Theme t;
    QColor colors[24];
};
#endif
