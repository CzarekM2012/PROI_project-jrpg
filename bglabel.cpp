#include "bglabel.h"
#include <QApplication>
#include <QPushButton>
#include <QLabel>

BgLabel::BgLabel(int part, QWidget *parent) : QWidget(parent)
{
  steps_counter = 0;
  setSteps(part);
  bg_pic = choose_bg(part);
  face_set = choose_face_set(part);
  texts_set = choose_texts(part);

  QPixmap bg(bg_pic);
  background = new QLabel(this);
  background->setGeometry(10, 10, 1300, 650);
  bg = bg.scaled(1300, 650);
  background->setPixmap(bg);

  QString dialog0;
  dialog0 = texts_set[steps_counter];
  QFont font ("Courier", 12);

  next = new QPushButton("Dalej", this);
  next->setGeometry(1000, 550, 80, 50);
  next->setFont(font);
  connect(next, SIGNAL (clicked(bool)), this, SLOT (slotButtonClicked()));

  text_bg = new QLabel(this);
  text_bg->setGeometry(400, 400, 550, 150);
  QPixmap for_dialog(550, 150);
  for_dialog.fill();
  text_bg->setPixmap(for_dialog);
  text_bg->setFrameStyle(3);
  text_bg->setFrameShadow(QFrame::Sunken);

  dialog = new QLabel(this);
  dialog->setGeometry(450, 400, 550, 150);
  dialog->setText(dialog0);
  dialog->setFont(font);

  face = new QLabel(this);
  face->setGeometry(190, 350, 300, 250);
  QPixmap for_face(face_set[steps_counter]);
  for_face = for_face.scaled(280, 230);
  face->setPixmap(for_face);
}

void BgLabel::setSteps(int part)
{
  int dsteps[] = {5, 4, 4};
  steps = dsteps[part];
  return;
}


QString BgLabel::choose_bg(int part)
{
  std::vector<QString> bgs = {":/images/living_room.png", ":/images/path.png", ":/images/lake1.png", ":/images/mountains.png", ":/images/sand_forest.png"
                             ":/images/sand_forest1.png", ":/images/castle.png", ":/images/ruins1.png", ":/images/ruins2.png"};
  return bgs[part];

}

std::vector<QString> BgLabel::choose_face_set(int part)
{
  std::vector<std::vector<QString>> faces_sets = {{":/images/face5.png", ":/images/face2.png", ":/images/face1.png", ":/images/face4.png", ":/images/face6.png"},
                                               {":/images/face6.png", ":/images/face1.png", ":/images/face3.png", ":/images/face2.png"},
                                                  {":/images/face5.png", ":/images/face4.png", ":/images/face3.png", ":/images/face2.png"}};
  return faces_sets[part];

}

std::vector<QString> BgLabel::choose_texts(int part)
{
  std::vector<std::vector<QString>> texts_sets = {{"Lena:\nBardzo ładny dzień dzisiaj mamy, a tak poza tym\nto ten pokój jest całkiem przytulny,\nmożemy kiedyś zrobić noc filmową!",
                                                   "Sara:\nMoże pójdziemy na spacer? Jest\nbardzo ładna pogoda.", "Oskar:\nNo dobra", "Jacek:\nTo ja wezmę wędkę!", "Alek:\nO nie, tylko nie wychodzenie na dwór!"},
                                                  {"Alek:\nDaleko jeszczeee? Nogi zaczynają\nmnie boleć!", "Oskar:\nPrzypomnijcie, dlaczego w ogóle\nzabraliśmy go ze sobą na tę wyprawę?",
                                                   "Tina:\nBo ma dużą wiedzę o potworach z gier.\nLena uznała, że to nam się przyda.", "Sara:\nWłaśnie, gdzie jest Lena?"},
                                                   {"Lena:\nPiękny widok na jezioro!", "Jacek:\nMoże zatrzymamy się, żeby złapać\njakiegoś leszczyka?",
                                                    "Tina:\nNie mamy teraz czasu, musimy iść dalej\nżeby odkryć, dlaczego wioskę atakują\nkolorowe gluty.", "Sara:\nWrócimy tu później, Jacku."}};
  return texts_sets[part];

}

void BgLabel::slotButtonClicked()
{
  steps_counter++;
  if(steps_counter >= steps)
    {
    this->BgLabel::~BgLabel();
//    steps_counter--;
    return;
    }
  QString new_dialog;
  new_dialog = texts_set[steps_counter];
  dialog->setText(new_dialog);

  QString new_face;
  new_face = face_set[steps_counter];
  QPixmap f(new_face);
  f = f.scaled(280, 230);
  face->setPixmap(f);

  return;
}

int BgLabel::getSteps()
{
  return steps;
}

int BgLabel::getStepsCounter()
{
  return steps_counter;
}
