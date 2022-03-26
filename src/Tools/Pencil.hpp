#ifndef PENCIL_HPP
#define PENCIL_HPP

// #include "../sfml_drawing/colors.hpp"
#include "Tools.hpp"

extern const size_t DEFAULT_PENCIL_SIZE;

class Pencil : public Tool
{
private:

public:
	Pencil();

	~Pencil() = default;
	
	void apply(Full_texture *texture, const Vector_ll &parameters, const Vector_ll &position) override;
};

#endif // PENCIL_HPP
