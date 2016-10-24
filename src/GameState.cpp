#include "../include/GameState.h"

GameState::GameState()
{

}

void GameState::onLoad()
{
   s_renderer = new Renderer();
   Font::loadFont("mailrays", 12);
   s_renderer->setDrawFont("main", 12);
   if (getGraphicsContext())
        s_renderer->setContext(getGraphicsContext());

   Tilesheet *wind_border = new Tilesheet();
   wind_border->createTilesheet(Image::getImage("border.png"), 3, 3, 16, 16);

   getWindowManager()->setDefaultBorder(wind_border);
   /*Frame *wind = getWindowManager()->createWindow(100, 100, 208, 80);
   wind->setBGColor(0, 0, 128);
   wind->setFGColor(255, 255, 255);
   wind->setName("My_First_Window");
   wind->setCaption("This Window ;)");

   Button *but1 = new Button();
   but1->X(10);
   but1->Y(20);
   but1->Width(200);
   but1->Height(30);
   but1->setAction("a1");
   but1->setCaption("My_First_Button");
   but1->setName("Button01");
   but1->setBGColor(125, 0, 0);
   but1->setFGColor(255, 255, 255);
   getWindowManager()->addComponent(wind->getUID(), but1);*/

   Sprite::loadSprite("place_holder");
   Sprite::loadSprite("char");

   SpriteSet::loadSpriteSet("basic_char");

   MapGenerator mg;
   test_map = mg.generateMap(100);

   clog << "Start X: "  << test_map->getStartX() << " : Start Y: " << test_map->getStartY() << endl;

   cam.setLimit(test_map->mapWidth(), test_map->mapHeight());

   player_obj = game_objects.createNewObject();
   game_objects.addModule(player_obj->getUID(), new PositionModule(test_map->getStartX()*test_map->tileWidth(), test_map->getStartY()*test_map->tileHeight()));
   game_objects.addModule(player_obj->getUID(), new VelocityModule(100.f, 20.f));
   game_objects.addModule(player_obj->getUID(), new BoundsModule(6, 8, 16, 24));
   game_objects.addModule(player_obj->getUID(), new SpriteModule(Sprite::getSprite("w_l"), SpriteSet::getSpriteSet("BasicChar")));
   game_objects.addModule(player_obj->getUID(), new WaypointModule());
   game_objects.addModule(player_obj->getUID(), new MapModule(test_map));
   game_objects.addModule(player_obj->getUID(), new SkillSetModule());

   Object *other_obj = game_objects.createNewObject();
   //game_objects.addModule(other_obj->getUID(), new PositionModule(200, 100));
   game_objects.addModule(other_obj->getUID(), new VelocityModule(0.f, 10.f));
   game_objects.addModule(other_obj->getUID(), new BoundsModule(32, 32, 16, 30));
   game_objects.addModule(other_obj->getUID(), new LifetimeModule(500));
   game_objects.addModule(other_obj->getUID(), new SpriteModule(Sprite::getSprite("sprite_1")));
   game_objects.addModule(other_obj->getUID(), new MapModule(test_map));

   SkillSetModule *sk_m = player_obj->getModule<SkillSetModule>();
   sk_m->mapSkill(0, SDLK_a, new Skill());

   other_obj = NULL;

    cam.setLimit(test_map->mapWidth(), test_map->mapHeight());
    cam.setOffset(0, 0);
    cam.setSize(800, 600);


    renderer.setRenderer(s_renderer);
    renderer.setCamera(&cam);
}

void GameState::onUnload()
{
    clog << "Lool Im unloading" << endl;
}

void GameState::onUpdate(unsigned int d_t)
{
    PositionModule *p_m = player_obj->getModule<PositionModule>();
    if (p_m)
    {
        cam.setOffset((int)p_m->X() - (cam.getWidth()/2), (int)p_m->Y() - (cam.getHeight()/2));
    }

    vector<Object*> obj_list = game_objects.getObjectList();
    for (int i = 0; i < obj_list.size(); i++)
    {
        way_p_system.Update(obj_list[i], d_t);
        move_system.Update(obj_list[i], d_t);
        spr_system.Update(obj_list[i], d_t);
        life_system.Update(obj_list[i], d_t);
    }


    game_objects.sweep();
}

void GameState::onRender(unsigned int d_t)
{
    for (int i = ((cam.getXOffset() > 0) ? cam.getXOffset() / test_map->tileWidth() : 0); i < (((cam.getXOffset()+cam.getWidth())/test_map->tileWidth() < test_map->tilesWide()) ? (cam.getXOffset()+cam.getWidth())/test_map->tileWidth() + 1 : test_map->tilesWide()); i++)
    {
       for (int ii = ((cam.getYOffset() > 0) ? cam.getYOffset() / test_map->tileHeight() : 0); ii < (((cam.getYOffset()+cam.getHeight())/test_map->tileHeight() < test_map->tilesTall()) ? (cam.getYOffset()+cam.getWidth())/test_map->tileHeight() + 1 : test_map->tilesTall()); ii++)
       {
            Tile* tmp = test_map->getTile(i, ii);
            if (tmp)
            {
                if (tmp->Type() == TILE_BLANK)
                {
                    /*SDL_Rect tmp_r;
                    tmp_r.x = i * test_map->tileWidth() - cam.getXOffset();
                    tmp_r.y = ii * test_map->tileHeight() - cam.getYOffset();

                    */s_renderer->drawImage(test_map->tSheet()->baseImage(), i * test_map->tileWidth() - cam.getXOffset(), ii * test_map->tileHeight() - cam.getYOffset(), test_map->tSheet()->getTile(test_map->getTile(i, ii)->Id()));

                    //SDL_BlitSurface(test_map->tSheet()->baseImage()->getRaw(), test_map->tSheet()->getTile(test_map->getTile(i, ii)->Id()), getGraphicsContext(), &tmp_r);
                }
                else
                {
                    s_renderer->setDrawColor(128, 128, 0);
                    s_renderer->drawRect(i * test_map->tileWidth() - cam.getXOffset(), ii * test_map->tileHeight() - cam.getYOffset(), test_map->tileWidth(), test_map->tileHeight());
                }
            }
       }
    }

    vector<Object*> obj_list = game_objects.getObjectList();
    for (int i = 0; i < obj_list.size(); i++)
    {
        renderer.Update(obj_list[i], d_t);
    }

    getWindowManager()->renderGUI(s_renderer);
}

void GameState::handleMousePress(int m_x, int m_y, int m_button)
{
    if (m_button == 1)
    {
        player_obj->getModule<WaypointModule>()->pathTo(m_x + cam.getXOffset(), m_y + cam.getYOffset());
    }
    else if (m_button == 10)
    {
        Tile *t = test_map->getTileFromCoords(m_x + cam.getXOffset(), m_y + cam.getYOffset());
        if (t)
        {
            if (t->Type() == TILE_SOLID)
            {
                t->Type(TILE_BLANK);
            }
            else
            {
                t->Type(TILE_SOLID);
            }
        }
    }

}

void GameState::handleMouseRelease(int m_x, int m_y, int m_button)
{

}

void GameState::handleMouseMove(int m_x, int m_y)
{

}

void GameState::handleMouseDrag(int m_x, int m_y, int m_button)
{
    if (m_button == 1)
        player_obj->getModule<WaypointModule>()->pathTo(m_x + cam.getXOffset(), m_y + cam.getYOffset());
}

void GameState::handleKeyPress(SDLKey key)
{
    vector<Object*> obj_list = game_objects.getObjectList();
    for (int i = 0; i < obj_list.size(); i++)
    {
        SkillSetModule *sk_m = obj_list[i]->getModule<SkillSetModule>();

        if (sk_m)
        {
            int fnd = sk_m->isMapped(key);
            if (fnd >= 0)
            {
                clog << "Skill found" << endl;
                CmdSkillActivated *new_cmd = new CmdSkillActivated(sk_m->getSkill(fnd));
            }
        }
    }
}

void GameState::handleKeyRelease(SDLKey key)
{

}

void GameState::handleWindowEvent(GUIEvent &ev)
{
    switch(ev.gui_type)
    {
        case GUIEVENT_PRESSED:
        {
            if (ev.comp->getAction() == "a1")
            {
                clog << "Button01 Pressed" << endl;
                Object *new_o = game_objects.createNewObject();
                game_objects.addModule(new_o->getUID(), new PositionModule(100, 100));
                game_objects.addModule(new_o->getUID(), new VelocityModule(270, 100.f));
                game_objects.addModule(new_o->getUID(), new LifetimeModule(1000));
                game_objects.addModule(new_o->getUID(), new ImageModule(Image::getImage(1)));
            }
            break;
        }
        case GUIEVENT_RELEASED:
        {
            if (ev.comp->getAction() == "a1")
            {
                clog << "Button01 Released" << endl;
            }
            break;
        }
    }
}

void GameState::handleCmdObjectLifeExpired(CmdObjectLifeExpired *ev)
{
   game_objects.destroyObject(ev->getObject());
}

void GameState::handleCmdSkillActivated(CmdSkillActivated *sk)
{
    clog << "Skill Activated" << endl;
}

GameState::~GameState()
{
    //dtor
}
