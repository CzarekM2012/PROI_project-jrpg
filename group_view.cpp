#include "group_view.h"

group_view::group_view(switchable_frame *parent):switchable_frame()
{
    connect(this, SIGNAL(target_info(entity *)), parent, SLOT(update_target(entity *)));
    for(int r=0; r<2; r++)
    {
        for(int p=0; p<2; p++)
        {
            formation_[r][p] = new character_frame();
            connect(this, SIGNAL(target_info(entity *)), formation_[r][p], SLOT(is_target(entity *)));
            connect(formation_[r][p], SIGNAL(target_acquired(entity *)), this, SLOT(pass_target_info(entity *)));
        }
    }
}

character_frame *group_view::get_character_frame(short int r, short int p){return formation_[r][p];}

void group_view::set_graphics()
{
    formation_[0][0]->set_standard_graphic();
    formation_[0][1]->set_standard_graphic();
    formation_[1][0]->set_standard_graphic();
    formation_[1][1]->set_standard_graphic();
}

void group_view::prepare_status_panels_highlight(group_status_panel *group_status_panel)
{
    for(int r=0; r<2; r++)
    {
        for(int p=0; p<2; p++)
        {
            if(formation_[r][p]->state()!=0)
            {
                character_status_panel *character_status_panel = group_status_panel->get_character_status_panel(r, p);
                connect(formation_[r][p], SIGNAL(hover_in()), character_status_panel, SLOT(highlight_on()));
                connect(formation_[r][p], SIGNAL(hover_out()), character_status_panel, SLOT(highlight_off()));
            }
        }
    }
}

void group_view::reset_states()
{
    for(int r=0; r<2; r++)
    {
        for(int p=0; p<2; p++)
        {
            formation_[r][p]->update(1);
        }
    }
}

void group_view::pass_target_info(entity *entity)
{
    target_info(entity);
}
