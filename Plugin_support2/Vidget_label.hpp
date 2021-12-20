#ifndef VIDGET_LABEL_HPP
#define VIDGET_LABEL_HPP

#include "plugin_std_2.hpp"
#include "Vidget.hpp"
#include "Vidget_label_container.hpp"

class Vidget_label : public PUPPY::Label, public Vidget
{
private:
	Vidget_label_container *label;

public:
	Vidget_label(PUPPY::Vec2f position, const char *text = nullptr, PUPPY::Widget *parent = nullptr);
	~Vidget_label();

	std::string_view get_text() const override;
    void set_text(std::string_view text) override;
};

#endif // VIDGET_LABEL_HPP
