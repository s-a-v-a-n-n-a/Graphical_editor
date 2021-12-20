#ifndef VIDGET_FACTORY_HPP
#define VIDGET_FACTORY_HPP

#include <vector>

#include "plugin_std_2.hpp"
#include "Render.hpp"

#include "Vidget.hpp"
#include "Vidget_button.hpp"
#include "Vidget_color_picker.hpp"
#include "Vidget_label.hpp"
#include "Vidget_slider.hpp"
#include "Vidget_text_field.hpp"
#include "Vidget_window.hpp"

class Vidget_factory : public PUPPY::WidgetFactory
{
private:
	Vidget *root;
	mutable std::vector<PUPPY::WBody> windows;

public:
	Vidget_factory(Visual_object *par_root);

	// create_root();

	Vidget *get_root() { return root; }
	std::vector<PUPPY::WBody> get_windows() { return windows; }

	Visual_object *cast_parent(PUPPY::Widget *parent) const;

	PUPPY::Button      *button       (const PUPPY::WBody &body, PUPPY::Widget *parent = nullptr) const override;
    PUPPY::Button      *button       (const PUPPY::Vec2f &pos, const char *caption, PUPPY::Widget *parent = nullptr) const override; // button fit to contain caption
    PUPPY::Slider      *slider       (PUPPY::Slider::Type type, const PUPPY::WBody &body, PUPPY::Widget *parent = nullptr) const override;
    PUPPY::TextField   *text_field   (const PUPPY::WBody &body, PUPPY::Widget *parent = nullptr) const override;
    PUPPY::Window      *window       (const char *name, const PUPPY::WBody &body, PUPPY::Widget *parent = nullptr) const override;
    PUPPY::ColorPicker *color_picker (const PUPPY::WBody &body, PUPPY::Widget *parent = nullptr) const override;
    PUPPY::Label       *label        (const PUPPY::Vec2f &pos, const char *text, PUPPY::Widget *parent = nullptr) const override;
    PUPPY::Widget      *abstract     (const PUPPY::WBody &body, PUPPY::Widget *parent = nullptr) const override;
};

#endif // VIDGET_FACTORE_HPP
