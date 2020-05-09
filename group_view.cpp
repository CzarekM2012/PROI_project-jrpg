#include "group_view.h"

group_view::group_view()
{
    layout_ = new QGridLayout();
    this->setLayout(layout_);
    for(int r=0; r<2; r++)
    {
        for(int p=0; p<2; p++)
        {
            formation_[r][p] = new character_frame();
        }
    }
}

character_frame *group_view::get_character_frame(short int r, short int p){return formation_[r][p];}

void group_view::place_frame(character_frame *frame, int row, int column, int rowspan, int columnspan)
{
    layout_->addWidget(frame, row, column, rowspan, columnspan);
}

void group_view::set_graphic(character_frame *frame, QString *new_graphic_file_name)
{
    QString stylesheet("border-image:url(:/images/"), end(")");
    stylesheet = stylesheet + *new_graphic_file_name + end;
    frame->setStyleSheet(stylesheet);
}

void group_view::set_graphics(party *party)
{
    for(int r=0; r<2; r++)
    {
        for(int p=0; p<2; p++)
        {
            pc *pc_to_set_graphic = party->get_pc_address(r, p);
            QString *graphic_file_name = pc_to_set_graphic->get_graphic_dir();
            QVector<QString> array_of_traits{"border-color:blue", "border-width:4px", "border-style:inset", QString("border-image:url(:/images/")+*graphic_file_name+QString(")")};
            formation_[r][p]->set_compound_style_sheet(array_of_traits);
        }
    }
}
void group_view::set_graphics(enemy_group *enemy_group)
{
    for(int r=0; r<2; r++)
    {
        for(int p=0; p<2; p++)
        {
            npc *npc_to_set_graphic = enemy_group->get_npc_adress(r, p);
            QString *graphic_file_name = npc_to_set_graphic->get_graphic_dir();
            QVector<QString> array_of_traits{"border-color:blue", "border-width:4px", "border-style:inset", QString("border-image:url(:/images/")+*graphic_file_name+QString(")")};
            formation_[r][p]->set_compound_style_sheet(array_of_traits);
        }
    }
}
void group_view::prepare_status_panels_highlight(group_status_panel *group_status_panel)
{
    for(int r=0; r<2; r++)
    {
        for(int p=0; p<2; p++)
        {
            character_status_panel *character_status_panel = group_status_panel->get_character_status_panel(r, p);
            connect(formation_[r][p], SIGNAL(hover_in()), character_status_panel, SLOT(highlight_on()));
            connect(formation_[r][p], SIGNAL(hover_out()), character_status_panel, SLOT(highlight_off()));
        }
    }
}
void group_view::prepare_action_target_acquisition()
{
    for(int r=0; r<2; r++)
    {
        for(int p=0; p<2; p++)
        {
            connect(formation_[r][p], SIGNAL(target_acquired(character *)), parent(), SLOT(update_target(character *)));
        }
    }
}
void group_view::set_party(bool is_party){party_ = is_party;}
