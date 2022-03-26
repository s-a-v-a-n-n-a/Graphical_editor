#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "plugin_std_2.hpp"
#include "Render.hpp"
#include "Vidget_factory.hpp"

struct Interface : public PUPPY::AppInterface
{
private:
	// Vidget_factory *this_factory;

public:
	// Render *render;

	Interface();
	~Interface();

	Vidget_factory *get_factory() { return dynamic_cast<Vidget_factory*>(factory.widget); } 

	bool ext_enable(const char *name) const override { return false; } 
	void *ext_get_func(const char *extension, const char *func) const override { return nullptr; } 
	void *ext_get_interface(const char *extension, const char *name) const override { return nullptr; }
	void ext_register_as(const char *extension) const override {}

	void log(const char *fmt, ...) const override;
	double get_absolute_time()     const override;

	PUPPY::RGBA get_color() const override;
	float get_size() const override;

	void set_color(const PUPPY::RGBA &color) const override;
	void set_size(float size) const override;

	const std::vector<PUPPY::WBody> get_windows() const override; //no realization
	PUPPY::Widget *get_root_widget() const override; // no realization

	PUPPY::RenderTarget *get_target()  const override; // no realization
	PUPPY::RenderTarget *get_preview() const override; // no realization
	void flush_preview() const override; // no realization
};

#endif // INTERFACE_HPP
