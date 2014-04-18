#include "entitledseparator.h"

EntitledSeparator::EntitledSeparator(const QString &title, QFrame::Shape shape, QFrame::Shadow shadow, int lineWidth, int midLineWidth, QWidget *parent) :
    QWidget(parent)
{
    QLabel *label = new QLabel(title);
    label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    QFrame *frame_l = new QFrame;
    frame_l->setFrameShape(shape);
    frame_l->setFrameShadow(shadow);
    frame_l->setLineWidth(lineWidth);
    frame_l->setMidLineWidth(midLineWidth);
    frame_l->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
    QFrame *frame_r = new QFrame;
    frame_r->setFrameShape(shape);
    frame_r->setFrameShadow(shadow);
    frame_r->setLineWidth(lineWidth);
    frame_r->setMidLineWidth(midLineWidth);
    frame_r->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setSizeConstraint(QLayout::SetMaximumSize);
    layout->setContentsMargins(0, 1, 0, 1);
    layout->setSpacing(15);
    layout->addWidget(frame_l);
    layout->addWidget(label);
    layout->addWidget(frame_r);
    setLayout(layout);
}
