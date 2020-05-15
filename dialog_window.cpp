#include "dialog_window.h"
#include "bglabel.h"
#include <QApplication>
#include <QPushButton>
#include <QLabel>

dialog_window::dialog_window(QWidget *parent) : QWidget(parent)
{
  QString dialog1;
  dialog1 = "Lena:\nBardzo ładny dzień dzisiaj mamy, a tak poza tym\nto ta gra jest dość brzydka, a ja tutaj\ntotalnie nie pasuję!";
  background = new QLabel(this);
  background->setGeometry(30, 30, 1300, 650);
  QPixmap test(":/images/path.png");
  test = test.scaled(1300, 650);
  background->setPixmap(test);

  QFont font ("Courier", 12);
  next = new QPushButton("Dalej", this);
  next->setGeometry(1000, 550, 80, 50);
  next->setFont(font);

  text_bg = new QLabel(this);
  text_bg->setGeometry(400, 400, 550, 150);
  QPixmap for_dialog(550, 150);
  for_dialog.fill();
  text_bg->setPixmap(for_dialog);
  text_bg->setFrameStyle(3);
  text_bg->setFrameShadow(QFrame::Sunken);

  dialog = new QLabel(this);
  dialog->setGeometry(450, 400, 550, 150);
  dialog->setText(dialog1);
  dialog->setFont(font);

  face = new QLabel(this);
  face->setGeometry(190, 350, 300, 250);
  QPixmap for_face(":/images/face5.png");
  for_face = for_face.scaled(300, 250);
  face->setPixmap(for_face);

}
