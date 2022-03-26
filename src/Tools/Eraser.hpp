#ifndef ERASER_H
#define ERASER_H

#include "Tools.hpp"

class Eraser : public Tool 
{
public:
	Eraser();
	~Eraser() = default;
	
	void apply(Full_texture *texture, const Vector_ll &parameters, const Vector_ll &position) override;

	// void set_color(const Color &par_color) override { ; }
};

#endif // ERASER_H
