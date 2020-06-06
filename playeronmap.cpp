#include "playeronmap.h"
#include <QLabel>
#include "maptile.h"

playeronmap::playeronmap(maptile *start, QWidget *parent)
{
  curr_tile = start;

}
