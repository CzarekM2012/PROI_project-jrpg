#include "data_processing.h"
void int_to_char_array(int value, char* destination)
{
    int i=0;
    if(value == 0)
    {
        destination[i++]='0';
        destination[i]=0;
        return;
    }

    while(value != 0)
    {
        int temp = value % 10;
        destination[i++] = temp + '0';
        value /= 10;
    }
    destination[i] = 0;
    int start = 0;
    i--;
    while(start < i)
    {
        char temp = *(destination+start);
        *(destination + start) = *(destination + i);
        *(destination + i) = temp;
        start++;
        i--;
    }
}

std::string remove_floors(std::string dline)
{
        for(unsigned int i = 0; i < dline.length(); i++)
        {
            if(dline[i] == '_')
            {
                 dline[i] = ' ';
            }

        }

    return dline;
}

skill *read_skill(std::string name, std::vector<skill*> *skills_vector)
{
    std::string dir = "texts/" + name + ".txt";
    std::ifstream readfile(dir);
    std::string strname;
    std::string strdesc;
    int parameters[5];
    QString qname;
    QString qdescription;

    readfile >> strname;
    readfile >> strdesc;
    for(int i = 0; i<5; i++)
      readfile >> parameters[i];
    readfile.close();

    //strname = remove_floors(strname);
    strdesc = remove_floors(strdesc);
    qname = QString::fromStdString(strname);
    qdescription = QString::fromStdString(strname);

    skill *generated = new skill(qname, qdescription, parameters[0], parameters[1], parameters[2], parameters[3], parameters[4]);
    unsigned int j=0;
    skill **array = &(*skills_vector)[0];
    bool match = false;
    while(j<skills_vector->size())
    {
        if(*array[j] == *generated)
        {
            delete generated;
            match = true;
            generated = array[j];
        }
        j++;
    }
    if(!match){skills_vector->push_back(generated);}
    return generated;
}

pc read_pc(std::string name, std::vector<skill*> *skills_vector, std::vector<equipment*> *equipment_vector)
{
    std::string dir = "texts/" + name + ".txt";
    std::ifstream readfile(dir);
    int i;

    std::string strname;
    int stats[9];
    skill *skills[8];
    equipment *gear_array[7];
    std::string strdesc;
    QString qname;
    QString qdescription;

    readfile >> strname;
    for(i = 0; i<9; i++)
      readfile >> stats[i];
    for(i = 0; i<8; i++)
      {
        std::string skillname;
        readfile >> skillname;
        if(skillname != "empty")
          {
          skill *skill = read_skill(skillname, skills_vector);
          skills[i] = skill;
          }
        else
          skills[i] = nullptr;
      }
    for(i = 0; i<7; i++)
      {
        std::string eqname;
        readfile >> eqname;
        if(eqname != "empty")
          {
          equipment *eq = read_equipment(eqname, equipment_vector);
          gear_array[i] = eq;
          }
        else
          gear_array[i] = nullptr;
      }
    readfile >> strdesc;
    readfile.close();

    //strname = remove_floors(strname);
    strdesc = remove_floors(strdesc);
    qname = QString::fromStdString(strname);
    qdescription = QString::fromStdString(strname);

    pc generated(qname, stats, skills, gear_array, qdescription);
    return generated;
}

void read_npc(std::string name, std::vector<npc*> *enemies_vector, std::vector<skill*> *skills_vector)
{
  std::string dir = "texts/" + name + ".txt";
  std::ifstream readfile(dir);
  int i;

  std::string strname;
  int stats[9];
  skill *skills[8];
  std::string strdesc;
  QString qname;
  QString qdescription;

  readfile >> strname;
  for(i = 0; i<9; i++)
    readfile >> stats[i];
  for(i = 0; i<8; i++)
    {
      std::string skillname;
      readfile >> skillname;
      if(skillname != "empty")
        {
        skill *nskill = read_skill(skillname, skills_vector);
        skills[i] = nskill;
        }
      else
        skills[i] = nullptr;
    }
  readfile >> strdesc;
  readfile.close();

  //strname = remove_floors(strname);
  strdesc = remove_floors(strdesc);
  qname = QString::fromStdString(strname);
  qdescription = QString::fromStdString(strname);

  npc *generated = new npc(qname, stats, skills, qdescription);
  unsigned int j=0;
  npc **array = &(*enemies_vector)[0];
  while(j<skills_vector->size())
  {
      if(array[j]->get_name() == generated->get_name())
      {
          delete generated;
          generated = nullptr;
      }
      j++;
  }
  if(generated != nullptr){enemies_vector->push_back(generated);}
}

void read_consumable(std::string name, std::vector<consumable*> *consumables_vector)
{
    std::string dir = "texts/" + name + ".txt";
    std::ifstream readfile(dir);

    std::string strname;
    int stats[9];
    short id;
    bool battle_item;
    int counter;
    std::string strdesc;
    QString qname;
    QString qdescription;

    readfile >> strname;
    for(int i = 0; i<9; i++)
      readfile >> stats[i];
    readfile >> id;
    readfile >> battle_item;
    readfile >> counter;
    readfile >> strdesc;
    readfile.close();

    //strname = remove_floors(strname);
    strdesc = remove_floors(strdesc);
    qname = QString::fromStdString(strname);
    qdescription = QString::fromStdString(strname);

    consumable *generated = new consumable(qname, stats, id, battle_item, counter, qdescription);
    unsigned int j=0;
    consumable **array = &(*consumables_vector)[0];
    while(j<consumables_vector->size())
    {
        if(array[j]->get_id() == generated->get_id())
        {
            delete generated;
            generated = nullptr;
        }
        j++;
    }
    if(generated != nullptr){consumables_vector->push_back(generated);}
}

equipment *read_equipment(std::string name, std::vector<equipment*> *equipment_vector)
{
    std::string dir = "texts/" + name + ".txt";
    std::ifstream readfile(dir);

    std::string strname;
    int stats[9];
    short id;
    short eqtype;
    std::string strdesc;
    QString qname;
    QString qdescription;

    readfile >> strname;
    for(int i = 0; i<9; i++)
      readfile >> stats[i];
    readfile >> id;
    readfile >> eqtype;
    readfile >> strdesc;
    readfile.close();

    //strname = remove_floors(strname);
    strdesc = remove_floors(strdesc);
    qname = QString::fromStdString(strname);
    qdescription = QString::fromStdString(strname);

    equipment *generated = new equipment(qname, stats, id, eqtype, qdescription);
    unsigned int j=0;
    equipment **array = &(*equipment_vector)[0];
    bool match = false;
    while(j<equipment_vector->size())
    {
        if(array[j]->get_id() == generated->get_id())
        {
            delete generated;
            match = true;
            generated=array[j];
        }
        j++;
    }
    if(!match){equipment_vector->push_back(generated);}
    return generated;
}
