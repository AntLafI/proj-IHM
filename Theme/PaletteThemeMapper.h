#ifndef PALLETTETHEMEMAPPER_H
#define PALLETTETHEMEMAPPER_H
#include <QPalette>
#include <QColor>
#include <QBrush>
#include "Theme/Theme.h"

enum ColorRemap{
    Background = 0,
    Background2 = 1,
    Background3 = 2,
    Primary = 3,
    Secondary = 4,
    Trinary = 5,
    Neutral = 6,
    Red1 = 7,
    Red2 = 8,
    Green1 = 9,
    Green2 = 10,
    DisabledPrimary = 11,
    DisabledSecondary = 12,
    DisabledTrinary = 13,
    DisabledNeutral = 14,
    DisabledRed1 = 15,
    DisabledRed2 = 16,
    DisabledGreen1 = 17,
    DisabledGreen2 = 18,
    Text1 = 19,
    Text2 = 20,
    TextInverted1 = 21,
    TextInverted2 = 22,
    Transparent = 23
};
using cr = QPalette::ColorRole;
using cg = QPalette::ColorGroup;
class PaletteThemeMapper{
private:
    inline static const QColor _Transparent = QColor::fromRgb(0,0,0,0);
    inline static const QBrush _TransparentBrush = QBrush(_Transparent);
public:
    static QBrush getBrush(QPalette source,ColorRemap requested){
        switch (requested){
            default:
            case Transparent: return _Transparent;

            case Background: return source.brush(cg::Active,cr::Base);
            case Background2: return source.brush(cg::Active,cr::Window);
            case Background3: return source.brush(cg::Active,cr::AlternateBase);
            case Primary: return source.brush(cg::Active,cr::Accent);
            case Secondary: return source.brush(cg::Active,cr::BrightText);
            case Trinary: return source.brush(cg::Active,cr::Highlight);
            case Neutral: return source.brush(cg::Active,cr::Shadow);
            case Red1:   return source.brush(cg::Active, cr::Link);
            case Red2:   return source.brush(cg::Active, cr::LinkVisited);
            case Green1: return source.brush(cg::Active, cr::ToolTipBase);
            case Green2: return source.brush(cg::Active, cr::ToolTipText);
            case DisabledPrimary: return source.brush(cg::Disabled,cr::Accent);
            case DisabledSecondary: return source.brush(cg::Disabled,cr::BrightText);
            case DisabledTrinary: return source.brush(cg::Disabled,cr::Highlight);
            case DisabledNeutral: return source.brush(cg::Disabled,cr::Shadow);
            case DisabledRed1:   return source.brush(cg::Disabled, cr::Link);
            case DisabledRed2:   return source.brush(cg::Disabled, cr::LinkVisited);
            case DisabledGreen1: return source.brush(cg::Disabled, cr::ToolTipBase);
            case DisabledGreen2: return source.brush(cg::Disabled, cr::ToolTipText);
            case Text1: return source.brush(cg::Active,cr::Text);
            case Text2: return source.brush(cg::Disabled,cr::Text);
            case TextInverted1: return source.brush(cg::Active,cr::HighlightedText);
            case TextInverted2: return source.brush(cg::Disabled,cr::HighlightedText);
        }
    }
    inline static QColor getColor(QPalette source,ColorRemap requested){
        return getBrush(source,requested).color();
    }

    static QPalette paletteFromTheme(const Theme& t) //AI generated from the funtion above
    {
        QPalette res{};
    
        // ===== Backgrounds =====
        res.setColor(cg::All, cr::Base,          t.Background);
        res.setColor(cg::All, cr::Window,        t.Background2);
        res.setColor(cg::All, cr::AlternateBase, t.Background3);

        res.setColor(cg::All, cr::Light, t.Background);
        res.setColor(cg::All, cr::Midlight, t.Background);
        res.setColor(cg::All, cr::Mid, t.Background3);
        res.setColor(cg::All, cr::Dark, t.Background3);
    
        // ===== Primary Accent =====
        res.setColor(cg::Active,   cr::Accent, t.Primary);
        res.setColor(cg::Inactive, cr::Accent, t.Primary);
        res.setColor(cg::Disabled, cr::Accent, t.DisabledPrimary);
    
        // ===== Secondary =====
        res.setColor(cg::Active,   cr::BrightText, t.Secondary);
        res.setColor(cg::Inactive, cr::BrightText, t.Secondary);
        res.setColor(cg::Disabled, cr::BrightText, t.DisabledSecondary);
    
        // ===== Highlight / Trinary =====
        res.setColor(cg::Active,   cr::Highlight, t.Trinary);
        res.setColor(cg::Inactive, cr::Highlight, t.Trinary);
        res.setColor(cg::Disabled, cr::Highlight, t.DisabledTrinary);
    
        // ===== Neutral / Shadow =====
        res.setColor(cg::Active,   cr::Shadow, t.Neutral);
        res.setColor(cg::Inactive, cr::Shadow, t.Neutral);
        res.setColor(cg::Disabled, cr::Shadow, t.DisabledNeutral);
    
        // ===== Red =====
        res.setColor(cg::Active,   cr::Link,    t.Red1);
        res.setColor(cg::Inactive, cr::Link,    t.Red1);
        res.setColor(cg::Disabled, cr::Link,    t.DisabledRed1);
    
        res.setColor(cg::Active,   cr::LinkVisited, t.Red2);
        res.setColor(cg::Inactive, cr::LinkVisited, t.Red2);
        res.setColor(cg::Disabled, cr::LinkVisited, t.DisabledRed2);
    
        // ===== Green =====
        res.setColor(cg::Active,   cr::ToolTipBase,  t.Green1);
        res.setColor(cg::Inactive, cr::ToolTipBase,  t.Green1);
        res.setColor(cg::Disabled, cr::ToolTipBase,  t.DisabledGreen1);
    
        res.setColor(cg::Active,   cr::ToolTipText, t.Green2);
        res.setColor(cg::Inactive, cr::ToolTipText, t.Green2);
        res.setColor(cg::Disabled, cr::ToolTipText, t.DisabledGreen2);
    
        // ===== Text =====
        res.setColor(cg::Active,   cr::Text, t.Text1);
        res.setColor(cg::Inactive, cr::Text, t.Text1);
        res.setColor(cg::Disabled, cr::Text, t.Text2);
    
        // ===== WindowText =====
        res.setColor(cg::Active,   cr::WindowText, t.Text1);
        res.setColor(cg::Inactive, cr::WindowText, t.Text1);
        res.setColor(cg::Disabled, cr::WindowText, t.Text2);
    
        // ===== Highlighted Text =====
        res.setColor(cg::Active,   cr::HighlightedText, t.TextInverted1);
        res.setColor(cg::Inactive, cr::HighlightedText, t.TextInverted1);
        res.setColor(cg::Disabled, cr::HighlightedText, t.TextInverted2);
    
        // ===== Button roles =====
        
        res.setColor(cg::Active,   cr::Button, t.Background2);
        res.setColor(cg::Inactive, cr::Button, t.Background2);
        res.setColor(cg::Disabled, cr::Button, t.Background3);
    
        res.setColor(cg::Active,   cr::ButtonText, t.Text1);
        res.setColor(cg::Inactive, cr::ButtonText, t.Text1);
        res.setColor(cg::Disabled, cr::ButtonText, t.Text2);
    
        return res;
    }

};

#endif // PALLETTETHEMEMAPPER_H
