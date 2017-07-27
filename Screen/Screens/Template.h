#ifndef TEMPLATE_H
#define TEMPLATE_H

#include "../ScreenEngine.h"

namespace pong { namespace screen {

class Template : public Screen
{


public:
    Template(ScreenConstructionParameters parameters);

    void update(ScreenUpdateParameters parameters) override;

    void draw(sf::RenderTarget & target, const TransitionInfo & transition) override;
};

}}

#endif