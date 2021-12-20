#ifndef VIDGET_LABEL_CONTAINER_HPP
#define VIDGET_LABEL_CONTAINER_HPP

#include "plugin_std_2.hpp"
#include "../GUI/Text.hpp"

class Vidget_label_container : public Text
{
private:
	PUPPY::Label *ward;

public:
	Vidget_label_container(Visual_object *parent, const size_t par_type, const char *par_text, const size_t par_font_size, const Vector_ll &par_position, const Color &par_color, PUPPY::Label *par_ward)
	: Text(parent, par_type, par_text, par_font_size, par_position, par_color), ward(par_ward) {}
	~Vidget_label_container() {}

	PUPPY::Label *get_ward() { return ward; }
};

#endif // VIDGET_LABEL_CONTAINER_HPP
