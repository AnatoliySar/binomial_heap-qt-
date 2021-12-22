#include "node.h"

Node::Node(int t)
{
    pressed = false;
    data = t;
}

QRectF Node::boundingRect() const
{
    return QRectF(0, 0, 60, 60);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::TextAntialiasing);


    QRectF rec = boundingRect();
    QBrush brush(Qt::green);

    if(pressed)
    {
        brush.setColor(Qt::blue);
    }
    else
    {
        brush.setColor(Qt::cyan);
    }

    painter->setPen(QPen(QBrush(Qt::black), 4));
    painter->setBrush(brush);
    painter->drawEllipse(rec);

    painter->setPen(QPen(QBrush(Qt::red), 4));
    painter->setFont(QFont("fixed-width", 13, QFont::Bold));
    painter->drawText(rec, Qt::AlignCenter, QString::number(data));
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = !pressed;
    update();
    QGraphicsItem::mousePressEvent(event);
}
