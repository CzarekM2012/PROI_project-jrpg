#include "enemy_group_view.h"

enemy_group_view::enemy_group_view():group_view(){}

enemy_group_view::enemy_group_view(enemy_group *enemy_group):group_view()
{
    set_party(false);
    std::pair<int,int> frames_coordinates[2][2];
    frames_coordinates[0][0].first = 5, frames_coordinates[0][0].second = 5;
    frames_coordinates[0][1].first = 4, frames_coordinates[0][1].second = 0;
    frames_coordinates[1][0].first = 1, frames_coordinates[1][0].second = 9;
    frames_coordinates[1][1].first = 0, frames_coordinates[1][1].second = 4;
    for(int r=0; r<2; r++)
    {
        for(int p=0; p<2; p++)
        {
            character_frame *frame = get_character_frame(r, p);
            place_frame(frame, frames_coordinates[r][p].first, frames_coordinates[r][p].second, 4, 3);
            npc *npc = enemy_group->get_npc_adress(r, p);
            frame->set_represented_character(npc);
            QString *graphic_file_name = npc->get_graphic_dir();
            QVector<QString> array_of_traits{"border-color:transparent",
                                             "border-width:4px",
                                             "border-style:inset",
                                             QString("border-image:url(:/images/")+*graphic_file_name+QString(")")};
            frame->set_compound_style_sheet(array_of_traits);
        }
    }
}
