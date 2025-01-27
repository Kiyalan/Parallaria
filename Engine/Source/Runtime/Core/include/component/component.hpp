#ifndef ENGINE_COMPONENT_INCLUDED
#define ENGINE_COMPONENT_INCLUDED

#include <env.hpp>
#include <utility.hpp>

namespace Engine {

class ActorComponent {
public:
    virtual void Initialize() = 0;
    virtual void Destroy() = 0;
    virtual void Update() = 0;
};

class IntangibleActorComponent :public ActorComponent {

};

class TangibleActorComponent :public ActorComponent {
public:
    FRealVector2D _relativeLocation;
    // Ranged in [-Pi, Pi]
    FReal64 _relativeRotation;
public:
    virtual void Initialize() = 0;
    virtual void Destroy() = 0;
    virtual void Update() = 0;
};


class ImageComponent :public TangibleActorComponent {

};

}
#endif