#include "stdafx.h"
#include "Platform.h"
#include "Thing.h"
#include "Graphics.h"

std::map<const std::string, Thing *> Thing::things;
std::list<Thing *> Thing::retiredThings;

/**
 * If named thing already exists, a pointer to it is returned.
 */
Thing * Thing::create(const std::string & name)
{
    Thing * thing = find(name);
    if (thing != 0)
    {
        return thing;
    }
    if (retiredThings.empty())
    {
        thing = new Thing(name);
    }
    else
    {
        thing = retiredThings.back();
        retiredThings.pop_back();
    }
    things[name] = thing;
    return thing;
}

Thing * Thing::find(const std::string & name)
{
    if (things.count(name) == 0)
    {
        return NULL;
    }
    else
    {
        return things[name];
    }
}

void Thing::destroy(const std::string & name)
{
    Thing * thing = find(name);
    if (thing != NULL)
    {
        things.erase(name);
        retiredThings.push_back(thing);
    }
}

bool Thing::draw() const
{
    GLfloat vVertices[] = { (GLfloat)x +  0.0f, (GLfloat)y +  0.5f, (GLfloat)z + 0.0f, 
                            (GLfloat)x + -0.5f, (GLfloat)y + -0.5f, (GLfloat)z + 0.0f,
                            (GLfloat)x +  0.5f, (GLfloat)y + -0.5f, (GLfloat)z + 0.0f };

    glUseProgram(Graphics::programObject);
    if (!Graphics::checkGlError())
    {
        Platform::error << "glUseProgram failed.";
        return false;
    }

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    if (!Graphics::checkGlError())
    {
        Platform::error << "glVertexAttribPointer failed.";
        return false;
    }

    glEnableVertexAttribArray(0);
    if (!Graphics::checkGlError())
    {
        Platform::error << "glEnableVertexAttribArray failed.";
        return false;
    }

    glDrawArrays(GL_TRIANGLES, 0, 3);
    if (!Graphics::checkGlError())
    {
        Platform::error << "glDrawArrays failed.";
        return false;
    }

    return true;
}

bool Thing::drawAll()
{
    std::map<const std::string, Thing *>::iterator it = things.begin();
    std::map<const std::string, Thing *>::iterator end = things.end();
    while (it != end)
    {
        Thing * thing = (*it).second;
        if (!thing->draw())
        {
            return false;
        }
        ++it;
    }
    return true;
}
