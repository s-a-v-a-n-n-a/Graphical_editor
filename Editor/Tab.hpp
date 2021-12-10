#ifndef TAB_VIDGET_H
#define TAB_VIDGET_H

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"

class Tab;

#include "Graphical_delegates.hpp"
#include "Editor_delegates.hpp"

extern const size_t DEFAULT_TAB_WIDTH;
extern const size_t DEFAULT_TAB_HEIGHT;

class Tab : public Visual_object
{
private:
	Visual_object *parent;

public:
	Tab(const Visual_object::Config &par_base, Visual_object *par_parent);
	~Tab() = default;

	void draw(Screen_information *screen) override;
};

#endif // TAB_VIDGET_H
