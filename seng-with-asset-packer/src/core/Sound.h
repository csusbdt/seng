#ifndef SENG_THING_H
#define SENG_THING_H

#include "stdafx.h"
#include "Core.h"

/**
 * \class Thing
 *
 * \brief Basic scriptable object.
 *
 * Thing instances are recycled; they are never destroyed.
 */
class Thing
{
public:
	static Thing * create(const std::string & name);
	static Thing * find(const std::string & name);
	static void destroy(const std::string & name);
	static bool drawAll();

    double x;
    double y;
    double z;

    /**
     * Because name is used as a map key, user code should not be able to modify it.
     */
    const std::string & getName() { return name; }

    bool draw() const;
		
private:
    static std::map<const std::string, Thing *> things;
    static std::list<Thing *> retiredThings;

    std::string name;
    std::list<Component *> components;

    Thing(const std::string & name) : name(name), x(0), y(0), z(0) { }
    ~Thing() { if (Core::run) assert(false); }
};
d
#endif