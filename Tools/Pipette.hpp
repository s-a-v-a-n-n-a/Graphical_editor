#ifndef PIPETTE_H
#define PIPETTE_H

#include "Toolbar.hpp"

class Pipette : public Tool 
{
public:
	Pipette();
	~Pipette() = default;
	
	void apply(Full_texture *texture, const Vector_ll &parameters, const Vector_ll &position) override;

	// void set_color(const Color &par_color) override { ; }
};


#endif // PIPETTE_H
