#include "Gradient_bar.hpp"

const size_t PICKER_SIZE = 5;

Gradient_bar::Gradient_bar(const Visual_object::Config &par_base, Color_picker *par_to_control, const HSV &position_hsv)
: Visual_object(par_base), current_position(0), to_control(par_to_control)
{
	Full_texture *rect = Resources::get_instance()->create_texture(PICKING_RECT_TEXTURE, PICKER_SIZE, get_height());// new Full_texture(WINDOW_BACKGROUND, DEFAULT_COLOR_VIDGET_WIDTH, DEFAULT_COLOR_VIDGET_HEIGHT);
	
	size_t width = get_width();
	current_position = (size_t)((double)(255 - position_hsv.h) / 255.0 * (double)width);

	Visual_object::Config buttton_base = { (size_t)Vidget_type::BUTTON, get_position() + Vector_ll(current_position, 0) - Vector_ll(5, 0), rect, TRANSPARENT, PICKER_SIZE, get_height() };
	picker = new Magnetic(buttton_base, this, get_position(), get_position() + Vector_ll(get_width() - PICKER_SIZE, 0), get_height());

	add_visual_object(picker);
}

Color Gradient_bar::get_color()
{
	int gap = current_position / ((int)MAX_COLOR_VALUE / ((int)DEFAULT_COLORS_AMOUNT - 1));
	gap++;
	int res = current_position % ((int)MAX_COLOR_VALUE / ((int)DEFAULT_COLORS_AMOUNT - 1));
	
	Color first_color = COLOR_SEQUENCE[gap];
	gap %= (DEFAULT_COLORS_AMOUNT - 1);
	Color second_color = COLOR_SEQUENCE[gap + 1];

	if (first_color.get_r() != second_color.get_r())
	{
		int r_1 = (int)first_color.get_r();
		int r_2 = (int)second_color.get_r();

		first_color.set_r(r_1 + (r_2 - r_1) * res / ((int)MAX_COLOR_VALUE / ((int)DEFAULT_COLORS_AMOUNT - 1)));
	}
	else if (first_color.get_g() != second_color.get_g())
	{
		int g_1 = (int)first_color.get_g();
		int g_2 = (int)second_color.get_g();

		first_color.set_g(g_1 + (g_2 - g_1) * res / ((int)MAX_COLOR_VALUE / ((int)DEFAULT_COLORS_AMOUNT - 1)));
	}
	else if (first_color.get_b() != second_color.get_b())
	{
		int b_1 = (int)first_color.get_b();
		int b_2 = (int)second_color.get_b();

		first_color.set_b(b_1 + (b_2 - b_1) * res / ((int)MAX_COLOR_VALUE / ((int)DEFAULT_COLORS_AMOUNT - 1)));
	}
	else
		printf("This code is wrong\n");
	
	return first_color;
}

void Gradient_bar::set_current_position(const Color &main_color)
{
	unsigned char red = main_color.get_r();
	unsigned char green = main_color.get_g();
	unsigned char blue = main_color.get_b();

	size_t width = get_width();
	
	Vector_ll position = picker->get_position();

	size_t gap = width / (DEFAULT_COLORS_AMOUNT - 1);
	
	if (green == 0)
	{
		if (red == MAX_COLOR_VALUE)
		{
			position.set_x((long long)((double)gap * ((double)blue / (double)MAX_COLOR_VALUE)));
			picker->set_position(position);

			return;
		}
		position.set_x(2 * gap - (long long)((double)gap * ((double)blue / (double)MAX_COLOR_VALUE)));
		picker->set_position(position);

		return;
	}

	if (red == 0)
	{
		if (blue == MAX_COLOR_VALUE)
		{
			position.set_x(2 * gap + (long long)((double)(gap) * ((double)blue / (double)MAX_COLOR_VALUE)));
			picker->set_position(position);

			return;
		}
		position.set_x(3 * gap - (long long)((double)(gap) * ((double)blue / (double)MAX_COLOR_VALUE)));
		picker->set_position(position);

		return;
	}

	if (green == MAX_COLOR_VALUE)
	{
		position.set_x(4 * gap + (long long)((double)(gap) * ((double)blue / (double)MAX_COLOR_VALUE)));
		picker->set_position(position);

		return;
	}

	position.set_x(5 * gap - (long long)((double)(gap) * ((double)blue / (double)MAX_COLOR_VALUE)));
	picker->set_position(position);

	to_control->set_main_color(main_color);
	to_control->set_color();
}

HSV Gradient_bar::get_hsv(const Color &rgb)
{
	double red = (double)rgb.get_r() / 255.0;
	double green = (double)rgb.get_g() / 255.0;
	double blue = (double)rgb.get_b() / 255.0;

	HSV hsv = { 0, 0, 0 };
    unsigned char rgbMin = 0;
    unsigned char rgbMax = 0;

    rgbMin = rgb.get_r() < rgb.get_g() ? (rgb.get_r() < rgb.get_b() ? rgb.get_r() : rgb.get_b()) : (rgb.get_g() < rgb.get_b() ? rgb.get_g() : rgb.get_b());
    rgbMax = rgb.get_r() > rgb.get_g() ? (rgb.get_r() > rgb.get_b() ? rgb.get_r() : rgb.get_b()) : (rgb.get_g() > rgb.get_b() ? rgb.get_g() : rgb.get_b());

    double MIN = red < green ? (red < blue ? red : blue) : (green < blue ? green : blue);
    double MAX = red > green ? (red > blue ? red : blue) : (green > blue ? green : blue); 

    hsv.set_v(rgbMax);
    // if (rgbMax == rgb.get_r())
    // 	if (rgb.get_g() >= rgb.get_b())
    // 		hsv.set_h((unsigned)(60.0 * ((green - blue)/(MAX - MIN))));
    // 	else 
    // 		hsv.set_h((unsigned)(360.0 + 60.0 * ((green - blue)/(MAX - MIN))));



    if (hsv.get_v() == 0)
    {
        hsv.set_h(0);
        hsv.set_s(0);
        return hsv;
    }

    hsv.set_s((unsigned)(255.0 * (1.0 - (double)rgbMin / (double)rgbMax)));
    if (hsv.get_s() == 0)
    {
        hsv.set_h(0);
        return hsv;
    }

    if (rgbMax == rgb.get_r())
        if (rgb.get_g() >= rgb.get_b())
        	hsv.set_h(0 + 43 * ((double)(rgb.get_g()) - (double)(rgb.get_b())) / ((double)rgbMax - (double)rgbMin));
        else
        {
        	hsv.set_h(255 + 43 * ((double)rgb.get_g() - (double)rgb.get_b()) / ((double)rgbMax - (double)rgbMin));
        	// printf("%u\n", hsv.h);
        }
    else if (rgbMax == rgb.get_g())
        hsv.set_h((unsigned)(85 + 43 * ((double)rgb.get_b() - (double)rgb.get_r()) / ((double)rgbMax - (double)rgbMin)));
    else
        hsv.set_h((unsigned)(171 + 43 * ((double)rgb.get_r() - (double)rgb.get_g()) / ((double)rgbMax - (double)rgbMin)));

    return hsv;
}

// HSV_d Gradient_bar::get_hsv(const Color &rgb)
// {
// 	double red = (double)rgb.r / 255.0;
// 	double green = (double)rgb.g / 255.0;
// 	double blue = (double)rgb.b / 255.0;

// 	HSV_d hsv = { 0.0, 0.0, 0.0 };

//     double MIN = red < green ? (red < blue ? red : blue) : (green < blue ? green : blue);
//     double MAX = red > green ? (red > blue ? red : blue) : (green > blue ? green : blue); 

//     hsv.v = (MAX);
//     // if (rgbMax == rgb.get_r())
//     // 	if (rgb.get_g() >= rgb.get_b())
//     // 		hsv.set_h((unsigned)(60.0 * ((green - blue)/(MAX - MIN))));
//     // 	else 
//     // 		hsv.set_h((unsigned)(360.0 + 60.0 * ((green - blue)/(MAX - MIN))));

// 	if (MAX == 0)
// 		hsv.s = 0;
// 	else
// 		hsv.s = 1 - MIN/MAX;	

//     if (MAX == red)
//     {
//         printf("red\n");
//         if (green >= blue)
//         {
//         	hsv.h = (0 + 60 * (green - blue) / (MAX - MIN));
//         }
//         else
//         {
//         	hsv.h = (360 + 60 * (green - blue) / (MAX - MIN));
//         	printf("%lg\n", hsv.h);
//         }
//     }
//     else if (MAX == green)
//     {
//         printf("green\n");
//         hsv.h = (120 + 60 * (blue - red) / (MAX - MIN));
//     }
//     else
//     {
//         printf("blue\n");
//         hsv.h = (240 + 60 * (red - green) / (MAX - MIN));
//     }

//     return hsv;
// }

Color Gradient_bar::get_rgb(const HSV &hsv)
{
	Color rgb = { 0, 0, 0, 255 };
    unsigned char region = 0; 
    unsigned char remainder = 0;
    unsigned char p = 0;
    unsigned char q = 0;
    unsigned char t = 0;

    if (hsv.get_s() == 0)
    {
        rgb.set_r(hsv.get_v());
        rgb.set_g(hsv.get_v());
        rgb.set_b(hsv.get_v());
        
        return rgb;
    }

    double region_d = ((double)hsv.get_h() / 43);
    region = (unsigned char)region_d;
    // printf("region %u\n", region);
    remainder = (unsigned char)(((double)hsv.get_h() - ((double)region * 43)) * 6); 

    p = (hsv.get_v() * (255 - hsv.get_s())) >> 8;
    q = (hsv.get_v() * (255 - ((hsv.get_s() * remainder) >> 8))) >> 8;
    t = (hsv.get_v() * (255 - ((hsv.get_s() * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:
            rgb.set_r(hsv.get_v()); 
            rgb.set_g(t); 
            rgb.set_b(p);
            
            break;
		case 1:
            
            rgb.set_r(q); 
            rgb.set_g(hsv.get_v()); 
            rgb.set_b(p);
            
            break;
        case 2:
            
            rgb.set_r(p); 
            rgb.set_g(hsv.get_v()); 
            rgb.set_b(t);
            
            break;
        case 3:
            
            rgb.set_r(p); 
            rgb.set_g(q); 
            rgb.set_b(hsv.get_v());
            
            break;
        case 4:
            
            rgb.set_r(t); 
            rgb.set_g(p); 
            rgb.set_b(hsv.get_v());
            
            break;
        default:
            
            rgb.set_r(hsv.get_v()); 
            rgb.set_g(p); 
            rgb.set_b(q);
            
            break;
    }

    return rgb;
}

// Color Gradient_bar::get_rgb(HSV_d &hsv)
// {
// 	Color rgb = {};

// 	hsv.s = hsv.s * 100;
// 	hsv.v = hsv.v * 100;

// 	int H_i = ((int)hsv.h / 60) % 6;

// 	double V_min = (((100 - hsv.s) * hsv.v) / 100.0);
// 	// int remainder = (int)hsv.h - ((int)hsv.h / 60) * 60;
// 	double relation = (hsv.h / 60.0) - ((int)hsv.h / 60);
// 	double a = ((((hsv.v - V_min)) * relation)); 

// 	double V_inc = V_min + a;
// 	double V_dec = hsv.v - a;

// 	double red = 0;
// 	double green = 0;
// 	double blue = 0;

// 	switch(H_i)
// 	{
// 	case 0:
// 		red = hsv.v;
// 		green = V_inc;
// 		blue = V_min;
// 		break;

// 	case 1:
// 		red = V_dec;
// 		green = hsv.v;
// 		blue = V_min;
// 		break;

// 	case 2:
// 		red = V_min;
// 		green = hsv.h;
// 		blue = V_inc;
// 		break;

// 	case 3:
// 		red = V_min;
// 		green = V_dec;
// 		blue = hsv.v;
// 		break;

// 	case 4:
// 		red = V_inc; 
// 		green = V_min; 
// 		blue = hsv.v;
// 		break;

// 	case 5:
// 		red = hsv.v;
// 		green = V_min;
// 		blue = V_dec;
// 		break;

// 	default:
// 		break;
// 	}

// 	// printf("%d %d %d\n", red, green, blue);
// 	rgb = { (unsigned char)((red * 255.0) / 100.0), (unsigned char)(green * 255.0 / 100.0), (unsigned char)(blue * 255.0 / 100.0), 255 };

// 	return rgb;
// }

bool Gradient_bar::on_mouse_click(const bool state, const size_t par_x, const size_t par_y)
{
	if (point_inside(par_x, par_y) && state)
	{
		size_t width = get_width();

		current_position = par_x - get_position().get_x();

		double value = (double)current_position;
		// Color color = get_color();
		// HSV_d hsv = { (360.0 * (255.0 - value)) / 255.0, 1.0, 1.0 };
		HSV hsv = { (int)(((double)(width - current_position) / (double)width) * 255.0), 255, 255 };
		Color main_color = get_rgb(hsv);
		
		to_control->set_main_color(main_color);
		to_control->set_color();

		picker->on_mouse_click(state, par_x, par_y);
		
		return true;
	}
	
	picker->on_mouse_click(state, par_x, par_y);

	return false;
}

bool Gradient_bar::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	bool change = picker->on_mouse_move(from, to);

	if (change)
	{
		size_t width = get_width();

		current_position = to.get_x() - get_position().get_x();
		// Color color = get_color();
		// HSV_d hsv = { (360.0 * (1.0 - ((double)current_position/255.0))), 1.0, 1.0 };
		HSV hsv = { (int)(((double)(width - current_position) / (double)width) * 255.0), 255, 255 };
		Color main_color = get_rgb(hsv);

		to_control->set_main_color(main_color);
		to_control->set_color();

		return true;
	}

	return false;
}

void Gradient_bar::draw(Screen_information *screen)
{
	Visual_object::draw(screen);

	Vector_ll position(get_position());

	// screen->draw_rectangle(position + Vector_ll(current_position, 0), BLACK, 5, get_height());
	picker->draw(screen);
}

void Gradient_bar::tick(Screen_information *screen, const double delta_time)
{
	// Tool *current_tool = Toolbar::get_instance()->get_active_tool();
	// Color tool_color = current_tool->get_color();

	// // Color main_color = get_rgb(get_hsv(tool_color));
	// // set_current_position(main_color);

	// HSV_d hsv = get_hsv(tool_color);

	// Vector_ll position = picker->get_position();
	// size_t width = get_width();
	
	// // printf("%u %u \n", hsv.get_h());
	// current_position = (long long)((360.0 - (hsv.h)) * 255.0 / 360.0);
	// picker->set_position(get_position() + Vector_ll(current_position, 0));
	
	// // Color main_color = get_color();
	// HSV_d tmp = { hsv.h, 1.0, 1.0 };
	// Color main_color = get_rgb(tmp);
	// // printf("%u %u %u vs %u %u %u\n", tool_color.get_r(), tool_color.get_g(), tool_color.get_b(), main_color.get_r(), main_color.get_g(), main_color.get_b());

	// to_control->set_main_color(main_color);
	// to_control->set_pencil_color();
}