#ifndef CHECKBOXDRAWER_H
#define CHECKBOXDRAWER_H
#include "Theme/Theme.h"
#include "Theme/PaletteThemeMapper.h"
#include <QStyle>
#include <QStyleOption>
#include <QRect>
#include <QPainter>
using qsPElem  = QStyle::PrimitiveElement;
using ptm = PaletteThemeMapper;
using remap = ColorRemap;

class CheckboxDrawer{
private:
    static int drawBox(const QStyleOption *opt, QPainter *p, const QWidget *w){
        QMargins margins;

        const bool enabled = opt->state & QStyle::State_Enabled;
        const bool hovered = opt->state & QStyle::State_MouseOver && enabled;
        const bool pressed = opt->state & QStyle::State_Sunken && enabled;
        const bool checked = opt->state & QStyle::State_On;
        const ArrayTheme& theme = {Theme::m_currentTheme};
        QBrush bgColor, strokeColor , markColor;

        if(w != nullptr){
            margins = w->contentsMargins();

            QPalette palette = w->palette();
            bgColor = ptm::getBrush(palette,enabled? remap::Background : remap::Background3);
            strokeColor = ptm::getBrush(palette,hovered? remap::DisabledTrinary : remap::Primary);
            markColor = ptm::getBrush(palette, pressed? remap::Green2 : (enabled? remap::Green1 : remap::DisabledGreen1));
        }
        else{
            bgColor = enabled? (pressed? theme.t.Background2 : theme.t.Background) : theme.t.Background3;
            strokeColor = hovered? theme.t.Primary : theme.t.Trinary;
            markColor = pressed? theme.t.Green2 : (enabled? theme.t.Green1 : theme.t.DisabledGreen1);
            margins = QMargins(1,1,1,1);
        }
        QRect box = opt->rect.adjusted(margins.left(),margins.top(),-margins.right(),-margins.bottom());

        p->save();
        p->setRenderHint(QPainter::Antialiasing,true);

        p->setPen(strokeColor.color());
        p->setBrush(bgColor);
        p->drawRoundedRect(box,3,3);
        p->restore();
        if(checked || pressed){
            p->save();
            p->setPen(theme.t.Transparent);
            p->setBrush(markColor);

            int circleMargin = checked? (pressed? 5 : 3) : 2;

            p->drawEllipse(box.adjusted(circleMargin,circleMargin,-circleMargin,-circleMargin));
            p->restore();

        }

        return 0;
    }

public:
    static int draw(qsPElem elem, const QStyleOption *opt, QPainter *p, const QWidget *w){
        if(elem == qsPElem::PE_IndicatorCheckBox) return drawBox(opt,p,w);
        return -1;
    }
};

#endif // CHECKBOXDRAWER_H
