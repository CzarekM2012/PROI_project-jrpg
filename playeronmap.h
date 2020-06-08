#ifndef PLAYERONMAP_H
#define PLAYERONMAP_H

#include <QWidget>
#include "switchable_frame.h"

class QLabel;
class maptile;
class playeronmap : public switchable_frame
{
  Q_OBJECT
public:
  playeronmap(maptile *start, QWidget *parent = nullptr);
  maptile *curr_tile;
  int int_curr_tile;

};

#endif // PLAYERONMAP_H
