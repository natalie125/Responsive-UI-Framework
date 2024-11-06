//
// Created by twak on 07/10/2019.
//

#include "responsive_layout.h"
#include "responsive_label.h"
#include <iostream>

//using namespace std;

// you should probably make extensive changes to this function
void ResponsiveLayout::setGeometry(const QRect &r /* our layout should always fit inside r */ ) {

    QLayout::setGeometry(r);
    int count = 0;

//    QScrollArea *scrollArea = new QScrollArea;
//    scrollArea->setBackgroundRole(QPalette::Dark);
//    scrollArea->setGeometry(r.width()/3,90,r.width()/3*2,r.height()-90);

    // for all the Widgets added in ResponsiveWindow.cpp
    for (int i = 0; i < list_.size(); i++) {

        QLayoutItem *o = list_.at(i);

        try {
            // cast the widget to one of our responsive labels
            ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget());

            if (label == NULL) // null: cast failed on pointer
                std::cout << "warning, unknown widget class in layout" << std::endl;
            else if (label -> text() == kNavTabs ) // headers go at the top
                label -> setGeometry(0+r.x(),0+r.y(),r.width()-60, 40);
            else if (label -> text() == kSignIn )
                label -> setGeometry(r.width()-60,0,60,40);
            // only show a search button on small resolution, at the right of the window
            else if (label -> text() == kSearchText)
                label -> setGeometry(0,45,r.width()-160,40);
            else if (label -> text() == kSearchOptions)
                label -> setGeometry(r.width()-160,45,100,40);
            else if (label -> text() == kSearchButton)
                label -> setGeometry(r.width() - 60,45+r.y(),60,40);
            // fixme: focus group did not like this behaviour for the search result element.
            else if (label -> text() == kAdvert )
                label -> setGeometry(0,90,r.width()/3, r.height()-135);
            else if (label -> text() == kSearchResult ){
//                scrollArea->setWidget(label);
                if (count % 4 == 0)
                    label -> setGeometry(r.width()/3+5,90+count/4*65,r.width()/6-5,60);
                else if (count % 4 == 1)
                    label -> setGeometry(r.width()/2+5,90+count/4*65,r.width()/6-5,60);
                else if (count % 4 == 2)
                    label -> setGeometry(r.width()/3*2+5,90+count/4*65,r.width()/6-5,60);
                else if (count % 4 == 3)
                    label -> setGeometry(r.width()/6*5+5,90+count/4*65,r.width()/6-5,60);
                count += 1;
            }
            else if (label -> text() == kSearchBackward )
                label -> setGeometry(r.width()/2-10,r.height()-70,20,20);
            else if (label -> text() == kSearchForward )
                label -> setGeometry(r.width()/6*5-10,r.height()-70,20,20);
            else if (label -> text() == kHomeLink )
                label -> setGeometry(0,r.height()-40,r.width()/2, 40);
            else if (label -> text() == kShoppingBasket )
                label -> setGeometry(r.width()/2,r.height()-40,r.width()/2, 40);
            else // otherwise: disappear label by moving out of bounds
                label -> setGeometry (-1,-1,0,0);

        }
        catch (std::bad_cast) {
            // bad_case: cast failed on reference...
            std::cout << "warning, unknown widget class in layout" << std::endl;
        }
    }
}

// following methods provide a trivial list-based implementation of the QLayout class
int ResponsiveLayout::count() const {
    return list_.size();
}

QLayoutItem *ResponsiveLayout::itemAt(int idx) const {
    return list_.value(idx);
}

QLayoutItem *ResponsiveLayout::takeAt(int idx) {
    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ResponsiveLayout::addItem(QLayoutItem *item) {
    list_.append(item);
}

QSize ResponsiveLayout::sizeHint() const {
    return minimumSize();
}

QSize ResponsiveLayout::minimumSize() const {
    return QSize(320,320);
}

ResponsiveLayout::~ResponsiveLayout() {
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}
