#include "maplabel.h"
#include "maptile.h"

MapLabel::MapLabel(int tileset, QWidget *parent) : QWidget(parent)
{
  this->setGeometry(5, 5, 1000, 800);
  init_tiles(tileset);
}

void MapLabel::init_tiles(int tileset)
{
//int tileset: 0=plains, 1=sand forest, 2=ruins
  QString tf = ":/images/";
  std::vector<QString> tileset0 = {tf+"grass_bg.png", tf+"trees_bg.png", tf+"trees_bg.png",
                                  tf+"path_dirt_bg.png", tf+"grass_bg.png", tf+"grass_bg.png",
                                  tf+"grass_bg.png", tf+"grass_bg.png", tf+"grass_bg.png", tf+"path_dirt_bg.png",
                                  tf+"path_dirt_bg.png", tf+"trees_bg.png", tf+"grass_bg.png", tf+"trees_bg.png",
                                  tf+"stone_bg.png", tf+"stone_bg.png", tf+"path_dirt_bg.png", tf+"grass_bg.png",
                                  tf+"grass_bg.png", tf+"trees_bg.png", tf+"trees_bg.png", tf+"grass_bg.png",
                                  tf+"trees_bg.png", tf+"grass_bg.png", tf+"grass_bg.png", tf+"grass_bg.png",
                                  tf+"grass_bg.png", tf+"grass_bg.png", tf+"trees_bg.png", tf+"trees_bg.png",
                                  tf+"trees_bg.png", tf+"trees_bg.png", tf+"trees_bg.png", tf+"trees_bg.png",
                                  tf+"trees_bg.png", tf+"trees_bg.png", tf+"trees_bg.png", tf+"trees_bg.png"};

if(tileset == 0)
  {
    MapTile* new_tile;
    int pctr = 0;
    for(int j=10; j<500; j+=100)
      {
        for(int i=10; i<700; i+=100)
        {
        new_tile = new MapTile(i, j, tileset0[pctr], this);
        pctr++;
        tiles.push_back(new_tile);
        }
      }
  }
  return;

}

void MapLabel::set_all_neighbors()
{


}
