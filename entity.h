#ifndef ENTITY_H
#define ENTITY_H
#include <QString>

class entity
{
public:
    entity(), entity(const char *name, const char *graphic_file_name);
    QString *get_name();
    QString *get_graphic_dir();
    void set_name(const char *name), set_name(QString name);
    void set_graphic_dir(const char *graphic_directory), set_graphic_dir(QString graphic_directory);
private:
    QString name_, graphic_directory_;
};

#endif // ENTITY_H
