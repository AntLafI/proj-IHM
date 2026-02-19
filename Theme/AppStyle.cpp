#include "AppStyle.h"
#include "StyleHelpers/PrimitiveElem/CheckboxDrawer.h"
#include "StyleHelpers/CompisiteElem/MenuDrawer.h"
#include <QMenu>


void AppStyle::drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p, const QWidget *w) const
{
    switch (pe) {

        //MenuBar
        case QStyle::PE_PanelMenuBar:
        case QStyle::PE_PanelMenu:
          if(MenuDrawer::draw(pe,opt,p,w) < 0)
                super::drawPrimitive(pe,opt,p,w);
            break;
        //Checkbox
        case PE_IndicatorCheckBox:
            if(CheckboxDrawer::draw(pe,opt,p,w) < 0) super::drawPrimitive(pe,opt,p,w);
            break;
        //Indicators Trivial
        case PE_IndicatorButtonDropDown:
        case PE_IndicatorRadioButton:

        //Indicator generic arrows (used for scoll bar)
        case PE_IndicatorArrowDown:
        case PE_IndicatorArrowLeft:
        case PE_IndicatorArrowRight:
        case PE_IndicatorArrowUp:
        case PE_IndicatorBranch: //used for file system

        //Indicator spinbox
        case PE_IndicatorSpinUp:   //up/down style
        case PE_IndicatorSpinDown:
        case PE_IndicatorSpinPlus: //+/- style
        case PE_IndicatorSpinMinus:

        //Misc Indicator
        case PE_IndicatorDockWidgetResizeHandle: //area resize handle
        case PE_IndicatorHeaderArrow: // sort btn for table
        case PE_IndicatorProgressChunk: //progressbar
        case PE_IndicatorTabTearLeft: //edge of cropped tab (out of scrollview)
        case PE_IndicatorTabTearRight:
        case PE_IndicatorItemViewItemDrop: //drop destination (drag n drop)
        case PE_IndicatorTabClose: //close btn on tabs
        case PE_IndicatorItemViewItemCheck: //item selected in list WITH A CHECKBOX
        case PE_IndicatorToolBarHandle: //dots area for draggable Toolbar
        case PE_IndicatorToolBarSeparator:
        case PE_IndicatorMenuCheckMark: //checkmark glyph in a menu

        //no clue what this is
        case PE_IndicatorColumnViewArrow: //arrow in QColumnView? (isn't the arrow in the scroll bar)


        case PE_PanelTipLabel:
        case PE_PanelScrollAreaCorner: //corner between vertical/horizontal scrollbars

        case PE_Widget: //plain widget
        default:
            super::drawPrimitive(pe,opt,p);
            break;
    }
}

void AppStyle::drawControl(ControlElement element, const QStyleOption *opt, QPainter *p, const QWidget *w) const{
    switch(element){
        case ControlElement::CE_MenuBarItem:
        case ControlElement::CE_MenuItem:
        MenuDrawer::draw(element,opt,p,w);
        break;
        default:
            super::drawControl(element,opt,p,w);
    }
}

QSize AppStyle::sizeFromContents(ContentsType type, const QStyleOption *option,const QSize &size, const QWidget *widget) const{
    QSize s = super::sizeFromContents(type, option, size, widget);

    if (type == CT_MenuBarItem) {
        s.rwidth() -= 8;
        s.rheight() -= 12;
    }

    return s;
}

void AppStyle::polish(QWidget *widget){
    super::polish(widget);
    if(QMenu *menu = static_cast<QMenu*>(widget)){

        QObject::connect(menu, &QMenu::hovered, menu, [menu](QAction*){
            menu->update(); // triggers a full repaint of the menu
        });
    }
}

