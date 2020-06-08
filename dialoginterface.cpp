#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "dialoginterface.h"

dialoginterface::dialoginterface(int dnum)
{
  std::string a = "dg" + std::to_string(dnum) + ".txt";
  std::string b = "f" + std::to_string(dnum) + ".txt";
  dialog_data = load_dialog(a);
  face_set = load_faces(b);
  steps = dialog_data.size();
  QString pix = choose_background(dnum);
  init_children();
  background->setStyleSheet(QString("border-image:url(") + pix + QString(")"));
}

std::vector<std::string> dialoginterface::load_dialog(std::string path)
{
  /*
  Loads dialog from a file.
  */
  {
    std::ifstream readfile(path);
    std::string line;
    std::vector<std::string> data_vector;

while(getline(readfile, line))  //while there are lines to read in the file
   {
    std::string dline;

    std::istringstream iss(line);

    iss >> dline;
    for(unsigned int i = 0; i < dline.length(); i++)
    {
        if(dline[i] == '_')
        {
            dline[i] = ' ';
        }
    }
      data_vector.push_back(dline);
   }

    return data_vector;
  }
}

std::vector<char> dialoginterface::load_faces(std::string path)
{
  std::ifstream readfile(path);
  std::string line;
  std::vector<char> data_vector;
  for(unsigned int i = 0; i < dialog_data.size(); i++)
    {
      char f;
      readfile >> f;
      data_vector.push_back(f);
    }
  return data_vector;
}


QString dialoginterface::choose_background(int dnum)
{
  std::vector<QString> bgs = {":/images/living_room.png", ":/images/lake1.png", ":/images/path.png",
                              ":/images/path.png", ":/images/sand_forest.png", ":/images/sand_forest1.png",
                              ":/images/desert.png", ":/images/desert.png", ":/images/sand_forest1.png",
                              ":/images/castle.png", ":/images/ruins1.png", ":/images/ruins1.png",
                              ":/images/ruins2.png", ":/images/ruins2.png"};
  return bgs[dnum];
}

void dialoginterface::init_children()
{
  steps_counter = 0;
  background = new QFrame(this);
  layout_->addWidget(background, 0, 0, 10, 13);

  text_bg = new QFrame(this);
  layout_->addWidget(text_bg, 7, 3, 1, 7);
  text_bg->setStyleSheet(QString("border-image:url(:/images/text_bg.png)"));
  text_bg->setFrameStyle(3);
  text_bg->setFrameShadow(QFrame::Sunken);

  dialog = new QLabel(this);
  QString new_dialog;
  new_dialog = QString::fromStdString(dialog_data[steps_counter]);
  QFont font ("Courier", 14);
  dialog->setText(new_dialog);
  dialog->setFont(font);
  layout_->addWidget(dialog, 7, 4, 1, 5);

  face = new QFrame(this);
  layout_->addWidget(face, 5, 1, 3, 3);
  face->setStyleSheet(QString("border-image:url(:/images/face") + face_set[steps_counter] + QString(".png)"));

  next = new QPushButton("Dalej", this);
  layout_->addWidget(next, 7, 10, 1, 1);
  next->setFont(font);
  next->setMinimumSize(100, 70);
  connect(next, SIGNAL (clicked(bool)), this, SLOT (slotDialogButton()));
}

void dialoginterface::setSteps(int stp)
{
  steps = stp;
}

void dialoginterface::slotDialogButton()
{
  steps_counter++;
  if(steps_counter >= steps)
    {
//    emit dialog_end();
//    this->BgLabel::~BgLabel();
//    steps_counter--;
      delete this;
      return;
    }
  QString new_dialog;
  new_dialog = QString::fromStdString(dialog_data[steps_counter]);
  dialog->setText(new_dialog);
  face->setStyleSheet(QString("border-image:url(:/images/face") + face_set[steps_counter] + QString(".png)"));

  return;
}
