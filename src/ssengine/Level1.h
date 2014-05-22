#ifndef LEVEL1_H
#define LEVEL1_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFGUI/SFGUI.hpp>
#include <Box2D/Box2D.h>
#include <Thor/Shapes/ConcaveShape.hpp>
#include <Thor/Shapes/Shapes.hpp>
#include <Thor/Input/Action.hpp>
#include <Thor/Input/ActionMap.hpp>
#include "debugrender.h"
#include "ssengine.h"
#include "Screen.h"
#include "GameContext.h"
#include "Player.h"
#include "Bullet.h"
#include "AICharacter.h"
#include "tween/TweenManager.h"
#include "ContactListener.h"

enum MyAction
{
	Debug
};

class Level1 : public Screen
{
public:
    Level1(sf::RenderWindow* rw, thor::MultiResourceCache* incache);
    virtual ~Level1();
    virtual int Run();
    bool Prepare();
protected:
private:
    sse::GameContext* context;
    sse::ContactListener* GameCL;
    sf::Sprite groundS;
    sf::Sprite targetS;
    sf::Sprite pointerS;
    sf::Sprite* CurrentTargetS;
    float playerHP;
    sse::Player* player;
    sf::ConvexShape roundedRecthp;
    sf::ConvexShape roundedRect;
    sf::Clock stepClock;
    sf::Clock frameClock;

    sfg::SFGUI m_sfgui;
    sfg::Label::Ptr m_label;
    sfg::Window::Ptr window = sfg::Window::Create();
    sfg::Desktop desktop;

    std::vector<sse::drawableentity*> DrawList;
    std::vector<sse::AICharacter*> EnemmyList;
    std::vector<sse::Character*> CharacterList;
    std::vector<b2Body*> RemoveList;
    std::vector<sse::Bullet*> BulletList;

    bool isFocused = true;
    bool hasclickplayer = true;
    bool debugflag = false;
    void ExitClick();
    void GotoMenu();
    int gotoWin = -2;
    static bool compareByY(const sse::drawableentity* a,const sse::drawableentity* b);
    thor::ActionMap<MyAction> map;
};

#endif // LEVEL1_H
