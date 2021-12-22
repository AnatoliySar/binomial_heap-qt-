#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QObject>
#include <QWidget>
#include <QPainter>

class Node : public QGraphicsItem
{
public:
    Node(int t);
    QRectF boundingRect() const;

    bool pressed;
    int data;
    int degree;
    Node* child;
    Node* sibling;
    Node* parent;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // NODE_H
