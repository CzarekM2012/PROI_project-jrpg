#include "entity.h"
#include <iostream>

entity::entity()
{
    name_ = QString("");
    graphic_directory_ = QString("");
}
entity::entity(const char *name, const char *graphic_file_name)
{
    name_ = QString(name);
    graphic_directory_ = QString(graphic_file_name);
}

QString *entity::get_name(){return &name_;}

QString *entity::get_graphic_dir(){return &graphic_directory_;}


void entity::set_name(const char *name)
{
    name_ = QString(name);
}
void entity::set_name(QString name)
{
    name_ = name;
}

void entity::set_graphic_dir(const char *graphic_directory)
{
    graphic_directory_ = QString(graphic_directory);
}
void entity::set_graphic_dir(QString graphic_directory)
{
    graphic_directory_ = graphic_directory;
}
