#include "scene.h"

Scene::Scene(QObject *parent):
    QGraphicsScene(parent)
{
    init();
}

Scene::Scene(const QRectF &sceneRect, QObject *parent):
    QGraphicsScene(sceneRect, parent)
{
    init();
}

Scene::Scene(qreal x, qreal y, qreal width, qreal height, QObject *parent):
    QGraphicsScene(x, y, width, height, parent)
{
    init();
}

void Scene::init()
{
    isPressing = false;
    clic = false;

    // Disable the scene size adaptation to items rect with a non null rect.
    setSceneRect(0, 0, 0, 1);
    addItem(&selection);
}

QString Scene::backgroundPath() const
{
    return path;
}

void Scene::addPolygonItem(QGraphicsItem *item)
{
    this->item = item;
    addItem(item);
}

void Scene::reset()
{
    if(item)
        removeItem(item);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && !isPressing)
    {
        isPressing = true;
        clic = true;

        pressPos = event->scenePos();
        selection.show();
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(isPressing)
    {
        clic = false;

        // Adapt if the selection rectangle has a negative size.
        if(pressPos.x() < event->scenePos().x())
            selection.setRect(pressPos.x(), 0, event->scenePos().x()-pressPos.x(), 0);
        else
            selection.setRect(event->scenePos().x(), 0, pressPos.x()-event->scenePos().x(), 0);

        if(pressPos.y() < event->scenePos().y())
            selection.setRect(selection.rect().x(), pressPos.y(), selection.rect().width(), event->scenePos().y()-pressPos.y());
        else
            selection.setRect(selection.rect().x(), event->scenePos().y(), selection.rect().width(), pressPos.y()-event->scenePos().y());
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
      {
          isPressing = false;

          // If no selection, store the click position in the selection rectangle.
          if(clic)
            selection.setRect(QRectF(QPointF(0, 0), event->scenePos()));

          emit repaintItem(selection.rect(), clic);

          selection.setRect(0, 0, 0, 0);
          selection.hide();
      }
}

void Scene::setBackground(const QString& filename, const QPixmap& pixmap)
{
    if(path != filename)
    {
        path = filename;

        setSceneRect(pixmap.rect());
        setBackgroundBrush(QBrush(pixmap));
    }
}
