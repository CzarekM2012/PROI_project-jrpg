#ifndef PLAYERONMAP_H
#define PLAYERONMAP_H

#include <QWidget>

class QLabel;
class maptile;
class playeronmap : public QWidget
{
  Q_OBJECT
public:
  playeronmap(maptile *start, QWidget *parent = nullptr);
  maptile *curr_tile;
  QLabel *face;

};

#endif // PLAYERONMAP_H
