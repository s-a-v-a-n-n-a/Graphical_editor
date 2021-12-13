#ifndef TEXTURE_H
#define TEXTURE_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <SFML/Graphics.hpp>

#include "../math_structures/Radius_vector.hpp"
#include "../simple_list/simple_list.hpp"
#include "colors.hpp"

#define Shelled_texture sf::Texture // sf::RenderTexture

class Texture
{
protected:
	char *texture_name;
	Vector_ll size;

public:
	Texture(const char *par_texture_name);

	~Texture();

	long long get_width() const { return size.get_x(); }
	long long get_height() const { return size.get_y(); }
	Vector_ll get_size() const { return size; }

	virtual void set_size(const Vector_ll par_size);

	char *get_name() { return texture_name; }
	virtual const Shelled_texture *get_texture() { return NULL; }
	virtual void set_texture(Color *array, const size_t width, const size_t height) { ; }
};

class Full_texture : public Texture
{
private:
	sf::RenderTexture texture;
	Shelled_texture tmp_texture; 

public:
	Full_texture(const char *par_texture_name);

	Full_texture(const char *par_texture_name, const size_t width, const size_t height);

	void set_size(const Vector_ll par_size) override;

	~Full_texture() = default;

	Color *get_pixels();

	const Shelled_texture *get_texture() override;

	sf::RenderTexture *get_current_texture();

	// Shelled_texture *getTexture()
	// {

	// }
	void set_texture(const sf::Texture *par_texture);

	void set_texture(Color *array, const size_t width, const size_t height) override;

	void add_picture(Color *other_array, const size_t width, const size_t height, const sf::BlendMode &mode);
};

#endif // TEXTURE_H
