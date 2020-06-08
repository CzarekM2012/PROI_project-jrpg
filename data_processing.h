#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H
#include "skill.h"
#include "npc.h"
#include "pc.h"
#include "consumable.h"
#include "equipment.h"
#include <fstream>

void int_to_char_array(int, char*);
skill *read_skill(std::string, std::vector<skill*> *skills_vector);
pc read_pc(std::string, std::vector<skill*> *skills_vector, std::vector<equipment*> *equipment_vector);
void read_npc(std::string, std::vector<npc*> *enemies_vector, std::vector<skill*> *skills_vector);
void read_consumable(std::string, std::vector<consumable*> *consumables_vector);
equipment *read_equipment(std::string, std::vector<equipment*> *equipment_vector);
#endif // DATA_PROCESSING_H
