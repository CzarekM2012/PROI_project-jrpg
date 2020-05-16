#include "dialog_window.h"
#include "bglabel.h"
#include <QApplication>
#include <QPushButton>
#include <QLabel>

dialog_window::dialog_window(QWidget *parent) : QWidget(parent)
{
 background = new BgLabel(1, this);
 background = new BgLabel(0, this);

}

void dialog_window::check_state()
{
  while(background->getSteps() > background->getStepsCounter())
    {

    }
   background->~BgLabel();
   return;
}
