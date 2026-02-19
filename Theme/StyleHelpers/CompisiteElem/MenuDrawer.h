#ifndef MENUBARDRAWER_H
#define MENUBARDRAWER_H
#include "Theme/Theme.h"
#include "Theme/PaletteThemeMapper.h"
#include <QStyle>
#include <QStyleOption>
#include <QRect>
#include <QColor>
#include <QPainter>
#include <QRadialGradient>

#include <QMenuBar>

using qsPElem  = QStyle::PrimitiveElement;
using qsCElem  = QStyle::ControlElement;
using ptm = PaletteThemeMapper;
using remap = ColorRemap;
class MenuDrawer{
private:
    static int drawPanelMenuBar(const QStyleOption *opt, QPainter *p, const QWidget *w){
        const ArrayTheme& theme = {Theme::m_currentTheme};
        QBrush bgColor ,strokeColor;

        if(w != nullptr){
            QPalette palette = w->palette();

            bgColor = ptm::getBrush(palette, remap::Background);
            strokeColor = ptm::getBrush(palette, remap::Background2);
        }
        else{
            bgColor = theme.t.Background;
            strokeColor =  theme.t.Background2;
        }
        p->save();
        p->setRenderHint(QPainter::Antialiasing,true);
        p->setPen(strokeColor.color());
        p->setBrush(bgColor);
        p->drawRect(opt->rect);
        p->restore();
        return 0;
    }

    inline static QRadialGradient gradFactory(const QPoint &mousePos, const QColor &clr){
        QRadialGradient res = QRadialGradient(mousePos,160);

        res.setSpread(QRadialGradient::PadSpread);
        res.setColorAt(0,clr);
        QColor trans = QColor(clr);
        trans.setAlpha(64); //half transparent
        res.setColorAt(1,trans);
        return res;
    }

    static int drawPanelMenu(const QStyleOption *opt, QPainter *p, const QWidget *w){
        if(w == nullptr) return -1;
        QPalette pal = w->palette();
        QPoint cursorPos = w->mapFromGlobal(QCursor::pos());
        QRadialGradient cursorGradient = gradFactory(cursorPos,ptm::getColor(pal,remap::Trinary));

        p->save();
        p->fillRect(opt->rect,ptm::getBrush(pal,remap::Background)); //background
        {
            QPen gradPen;
            gradPen.setWidth(2);
            gradPen.setBrush(cursorGradient);
            gradPen.setCapStyle(Qt::SquareCap);
            gradPen.setJoinStyle(Qt::MiterJoin);
            p->setPen(gradPen);
        }
        p->setBrush(Qt::NoBrush);
        QRect inner = opt->rect.adjusted(3,3,-3,-3);
        p->drawRect(inner);

        p->restore();
        return 0;
    }
    static int drawMenuBarItem(const QStyleOption *opt, QPainter *p, const QWidget *w){
        const QStyleOptionMenuItem* itemOpt = qstyleoption_cast<const QStyleOptionMenuItem*>(opt);
        const ArrayTheme& theme = {Theme::Default()};
        const bool enabled = itemOpt->state & QStyle::State_Enabled;
        const bool selected = itemOpt->state & QStyle::State_Sunken && enabled;
        const bool hovered = enabled && itemOpt->state & QStyle::State_Selected;
        QBrush bgColor , textColor;
        if(w != nullptr){
            QPalette palette = w->palette();
            bgColor = ptm::getBrush(palette, selected? remap::Background3 : (hovered? remap::Background : remap::Background2));
            textColor = ptm::getBrush(palette, hovered? remap::Primary : (enabled? remap::Text1 : remap::Text2));
        }
        else{
            bgColor = hovered? theme.t.Background3 : theme.t.Background2;
            textColor = enabled? (hovered? theme.t.Primary : theme.t.Text1) : theme.t.Text2;
        }
        p->save();
        p->setRenderHint(QPainter::Antialiasing,true);

        QRect box = itemOpt->rect.adjusted(2,2,-2,-2);
        p->fillRect(box,bgColor);
        p->setPen(textColor.color());
        p->drawText(box,Qt::AlignCenter,itemOpt->text);

        p->restore();
        return 0;
    }
    static int drawMenuItem(const QStyleOption *opt, QPainter *p, const QWidget *w){

        if(w == nullptr) return -1;
        QPalette pal = w->palette();
        const QStyleOptionMenuItem* itemOpt = qstyleoption_cast<const QStyleOptionMenuItem*>(opt);
        if(itemOpt->menuItemType == QStyleOptionMenuItem::Separator){
            QPoint cursorPos = w->mapFromGlobal(QCursor::pos());
            QRadialGradient cursorGradient = gradFactory(cursorPos,ptm::getColor(pal,remap::Trinary));
            QPen gradPen;
            gradPen.setWidth(2);
            gradPen.setBrush(cursorGradient);
            gradPen.setCapStyle(Qt::SquareCap);
            gradPen.setJoinStyle(Qt::MiterJoin);
            p->save();
            p->setPen(gradPen);
            QLine sep(itemOpt->rect.left() + 4,itemOpt->rect.center().y(),itemOpt->rect.right() - 4,itemOpt->rect.center().y());
            p->drawLine(sep);
            p->restore();
            return 0;
        } //separator
        const bool enabled = opt->state & QStyle::State_Enabled;
        const bool hovered = opt->state & QStyle::State_Selected && enabled;

        QBrush bgColor = ptm::getBrush(pal,hovered? remap::Background2 : remap::Transparent);
        QColor txtColor = ptm::getColor(pal,enabled? remap::Text1 : remap::Text2);

        QRect padded = opt->rect.adjusted(3,3,-3,-3);

        p->fillRect(padded,bgColor); //background


        QRect inner = padded.adjusted(4,1,-4,-1);
        p->save();
        p->setPen(txtColor);
        if (!itemOpt->icon.isNull()) {
            QIcon icon = itemOpt->icon;
            QSize iconSize(16,16);
            QRect iconRect(inner.topLeft(),iconSize);
            iconRect.translate(2,(inner.height() - iconSize.height()) / 2);
            itemOpt->icon.paint(p, iconRect, Qt::AlignVCenter | Qt::AlignLeft);
        }

        QStringList full = itemOpt->text.split('\t');

        if(full.length() > 0){
            inner.setLeft(32);
            p->setFont(itemOpt->font);
            p->drawText(inner, Qt::AlignVCenter | Qt::AlignLeft, full[0]);
        }

        if (full.length() > 1) {
            p->setPen(ptm::getColor(pal,remap::Text2)); //shortcut always gray
            p->drawText(inner, Qt::AlignVCenter | Qt::AlignRight, full[1]);
        }

        p->restore();
        return 0;
    }

public:
    static int draw(qsPElem elem, const QStyleOption *opt, QPainter *p, const QWidget *w){
        switch(elem){
        case qsPElem::PE_PanelMenuBar: return drawPanelMenuBar(opt,p,w);
        case qsPElem::PE_PanelMenu: return drawPanelMenu(opt,p,w);
        default: return -1;
        }
    }
    static int draw(qsCElem elem, const QStyleOption *opt, QPainter *p, const QWidget *w){
        switch(elem){
        default: return -1;
        case qsCElem::CE_MenuBarItem: return drawMenuBarItem(opt,p,w);
        case qsCElem::CE_MenuItem: return drawMenuItem(opt,p,w);
        }
    }
};

#endif // MENUBARDRAWER_H
