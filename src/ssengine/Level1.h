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
#include <Screen.h>
#include "../debugrender.h"
#include "ssengine.h"
#include "GameContext.h"

class ContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact)
    {
        b2Fixture* FixtA = contact->GetFixtureA();
        b2Fixture* FixtB = contact->GetFixtureB();
        sse::UserData* userdataA = static_cast<sse::UserData*>(FixtA->GetUserData());
        sse::UserData* userdataB = static_cast<sse::UserData*>(FixtB->GetUserData());
        if(userdataA->tipo == 3 && userdataA->tipo == 2 && userdataA->estado==0)
        {
            context->RemoveList.push_back(FixtA->GetBody());
            userdataA->estado=1;
        }
        else
            if(userdataB->tipo == 3 && userdataA->tipo == 2 && userdataB->estado==0)
            {
                context->RemoveList.push_back(FixtB->GetBody());
                userdataB->estado=1;
            }

        if(userdataA->tipo == 4)
        {
            b2Body* bodyA = FixtA->GetBody();
            sse::Character* collCharacter = static_cast<sse::Character*>(bodyA->GetUserData());
            collCharacter->addCollisionList(FixtB);
        }
        else
            if(userdataB->tipo == 4)
            {
                b2Body* bodyB = FixtB->GetBody();
                sse::Character* collCharacter = static_cast<sse::Character*>(bodyB->GetUserData());
                collCharacter->addCollisionList(FixtA);
            }
    }

    void EndContact(b2Contact* contact)
    {
        b2Fixture* FixtA = contact->GetFixtureA();
        b2Fixture* FixtB = contact->GetFixtureB();
        sse::UserData* userdataA = static_cast<sse::UserData*>(FixtA->GetUserData());
        sse::UserData* userdataB = static_cast<sse::UserData*>(FixtB->GetUserData());

        if(userdataA->tipo == 4)
        {
            b2Body* bodyA = FixtA->GetBody();
            sse::Character* collCharacter = static_cast<sse::Character*>(bodyA->GetUserData());
            collCharacter->removeCollisionList(FixtB);
        }
        else
            if(userdataB->tipo == 4)
            {
                b2Body* bodyB = FixtB->GetBody();
                sse::Character* collCharacter = static_cast<sse::Character*>(bodyB->GetUserData());
                collCharacter->removeCollisionList(FixtA);
            }
    }

    public:
        ContactListener(sse::GameContext* incontext):context(incontext){}
    private:
        sse::GameContext* context;
};

class Level1 : public Screen
{
    public:
        Level1(sf::RenderWindow* rw);
        virtual ~Level1();
        virtual int Run();
    protected:
    private:
        DebugDraw* debugDraw;
        sf::RenderWindow* renderWindow;
        sse::GameContext* context;
        ContactListener* GameCL;
        std::vector<sse::MyRayCastCallback*> RaycastList;
        sf::Texture groundT;
        sf::Sprite groundS;
        sf::Vector2i screnSize;
        sf::Texture texture;
        sf::Vector2f VURef;
        sf::Event event;
        sf::Vector2f centro;
        sf::Sprite targetS;
        sf::Texture targetT;
        float playerHP;
        sse::AICharacter* character;
        sse::Player* player;
        sf::Vector2f* impactview;
        sf::Clock frameClock;
        sf::ConvexShape roundedRecthp;
        sf::ConvexShape roundedRect;
        AnimatedAccessor* animaccess;
        sse::Tween tween;
        sse::tweenOptions* options;
        sf::Clock stepClock;

        sfg::SFGUI m_sfgui;
        sfg::Label::Ptr m_label;
        sfg::Window::Ptr window = sfg::Window::Create();
        sfg::Desktop desktop;

        std::vector<sse::drawableentity*> DrawList;

        bool isFocused = true;
        bool hasclickplayer = true;
        void OnButtonClick();
};

#endif // LEVEL1_H