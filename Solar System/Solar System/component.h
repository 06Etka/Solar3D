#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
public:
	Component();
	virtual ~Component() = default;

	virtual void update(float deltaTime);
};

#endif // !COMPONENT_H
