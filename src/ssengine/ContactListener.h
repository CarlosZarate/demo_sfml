#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <Box2D/Box2D.h>
#include "GameContext.h"

namespace sse
{
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
        else if(userdataB->tipo == 3 && userdataA->tipo == 2 && userdataB->estado==0)
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
        else if(userdataB->tipo == 4)
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
        else if(userdataB->tipo == 4)
        {
            b2Body* bodyB = FixtB->GetBody();
            sse::Character* collCharacter = static_cast<sse::Character*>(bodyB->GetUserData());
            collCharacter->removeCollisionList(FixtA);
        }
    }

public:
    ContactListener(sse::GameContext* incontext):context(incontext) {}
private:
    sse::GameContext* context;
};
}
#endif // CONTACTLISTENER_H
