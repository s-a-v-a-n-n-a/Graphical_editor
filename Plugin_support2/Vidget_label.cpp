#include "Vidget_label.hpp"
#include "Render.hpp"

Vidget_label::Vidget_label(PUPPY::Vec2f position, const char *text, PUPPY::Widget *parent)
: PUPPY::Label(), Vidget(position, {0, 0}, parent)
{
	Vector_ll app_position = app_translate_vector(position);
	
	Vidget *par_parent = dynamic_cast<Vidget*>(parent);
	Visual_object *visual_parent = nullptr;
	if (par_parent)
		visual_parent = par_parent->get_analog();

	label = new Vidget_label_container(visual_parent, (size_t)Vidget_type::TEXT, text, 20, app_position, BLACK, this);
}

Vidget_label::~Vidget_label()
{
	delete label;
}

std::string_view Vidget_label::get_text() const
{
	return std::string_view{ label->get_text() };
}

void Vidget_label::set_text(std::string_view text)
{
	label->set_text(text.cbegin());
}

