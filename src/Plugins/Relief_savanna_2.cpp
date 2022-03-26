#include "../Plugin_support2/plugin_std_2.hpp"

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <filesystem>

#include <cstdio>

// ============================================================================ How to compile

// clang++ -std=c++20 -fPIC -shared Plugins/Relief_savanna_2.cpp -o relief2.so

// ============================================================================ Info

const auto PTYPE = PUPPY::EFFECT;

const char *PNAME    = "Relief";
const char *PVERSION = "1.0";
const char *PAUTHOR  = "Savanna";
const char *PDESCR   = "Yes";

// ============================================================================ Resources

const long long DEFAULT_OFFSET = 20;
const long long DEFAULT_AMOUNT = 2;

// void *offset_setting = nullptr;
// void *amount_setting = nullptr;

// =====================================================================

struct Relief_plugin : public PUPPY::PluginInterface {
    bool  ext_enable        (const char */*name*/)                            const override;
    void *ext_get_func      (const char */*extension*/, const char */*func*/) const override;
    void *ext_get_interface (const char */*extension*/, const char */*name*/) const override;

    const PUPPY::PluginInfo *get_info() const override;

    PUPPY::Status init   (const PUPPY::AppInterface*, const std::filesystem::path& path = std::filesystem::path("./")) override;
    PUPPY::Status deinit ()                                                                                            override;
    
    void dump() const override;

    void on_tick(double dt)   const override;

    void effect_apply() const override;

    void tool_on_press  (const PUPPY::Vec2f &position)                 const override;
    void tool_on_release(const PUPPY::Vec2f &position)                 const override;
    void tool_on_move   (const PUPPY::Vec2f &from, const PUPPY::Vec2f &to) const override;

// settings
    void show_settings() const override;

//additional
    void draw(const PUPPY::Vec2f &position) const;

    PUPPY::Extensioner exts;
};

bool  Relief_plugin::ext_enable        (const char */*name*/)                        const { return false;   }
void *Relief_plugin::ext_get_func      (const char */*extension*/, const char *func) const { return exts.get(func); }
void *Relief_plugin::ext_get_interface (const char */*extension*/, const char *name) const { return exts.get(name); }

Relief_plugin Savanna_interface = {};

const PUPPY::PluginInfo PINFO =
{
    PUPPY::STD_VERSION, // std_version
    nullptr,            // reserved

    &Savanna_interface,

    PNAME,
    PVERSION,
    PAUTHOR,
    PDESCR,

    #ifdef ICON // icon
    ICON,
    #else
    nullptr,
    #endif

    PTYPE
};

const PUPPY::AppInterface *APPI = nullptr;

extern "C" PUPPY::PluginInterface *get_plugin_interface() 
{
    return &Savanna_interface;
}

// =====================================================================

struct 
{
    PUPPY::Window *window;
    PUPPY::TextField *offset_field;
    PUPPY::TextField *amount_field;
} settings;

PUPPY::Status Relief_plugin::init(const PUPPY::AppInterface *app_interface, const std::filesystem::path&) 
{
    srand(time(NULL));

    APPI = app_interface;

    if (APPI->factory.widget) 
    {
        settings.window = APPI->factory.widget->window("Relief", {{100, 100}, {200, 200}});
        settings.offset_field = APPI->factory.widget->text_field({{20, 20}, {150, 50}}, settings.window);
        settings.amount_field = APPI->factory.widget->text_field({{20, 80}, {150, 50}}, settings.window);
        
        APPI->log("<Relief effect> knows you support setting, that's great.");
    } 
    else 
    {
        APPI->log("<Relief effect> knows you don't support setting, default offset is %lld, default amount is %lld.", DEFAULT_OFFSET, DEFAULT_AMOUNT);
    }

    APPI->log("<Relief effect> was successfully inited.");
    
    return PUPPY::OK;
}

PUPPY::Status Relief_plugin::deinit() 
{
    if (settings.window) 
    {
        settings.window->set_to_delete();
    }

    APPI->log("<Relief effect> was successfully deinited.");
    return PUPPY::OK;
}

void Relief_plugin::dump() const
{
    APPI->log("<Relief effect> is active.", PINFO.name);
}

const PUPPY::PluginInfo *Relief_plugin::get_info() const
{
    return &PINFO;
}

void Relief_plugin::on_tick(double /*dt*/) const {}


void Relief_plugin::show_settings() const 
{
    settings.window->show();
}

void Relief_plugin::tool_on_release(const PUPPY::Vec2f &position) const 
{
    draw(position);
}

void Relief_plugin::tool_on_move(const PUPPY::Vec2f &from, const PUPPY::Vec2f &to) const
{
    draw(to);
}

void Relief_plugin::tool_on_press(const PUPPY::Vec2f &position) const {}

void make_negative(PUPPY::RGBA *to, long long width, long long height)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            PUPPY::RGBA color = to[width * y + x];
            color.r = 255 - color.r;
            color.g = 255 - color.g;
            color.b = 255 - color.b;

            to[width * y + x] = color;
        }
    }
}

void multiply(PUPPY::RGBA *to, PUPPY::RGBA *from, long long width, long long height, long long offset)
{
    if (offset < 0)
        offset *= -1;

    int y = offset < 0 ? 0 : offset;
    int x = offset < 0 ? 0 : offset;

    int width_limit = width + offset < width ? width + offset : width;
    int height_limit = height + offset < height ? height + offset : height;
    for (int y_0 = 0; y < height_limit; y++, y_0++)
    {
        for (int in_x = x, x_0 = 0; in_x < width_limit; in_x++, x_0++)
        {
            PUPPY::RGBA color = from[width * y_0 + x_0];
            PUPPY::RGBA positive_color = to[width * y + in_x];
            long long r = (long long)positive_color.r;
            r = (r * 3) / 4;
            long long g = (long long)positive_color.g;
            g = (g * 3) / 4;
            long long b = (long long)positive_color.b;
            b = (b * 3) / 4;
            long long a = (long long)positive_color.a;
            a = (a * 3) / 4;

            r += color.r / 4;
            g += color.g / 4;
            b += color.b / 4;
            a += color.a / 4;
            
            positive_color.r = r;
            positive_color.g = g;
            positive_color.b = b;

            to[width * y + in_x] = positive_color;
        }
    }

    int x_begin = 0;
    int y_begin = 0;
    
    for (int y_0 = 0; y_0 < height; y_0++)
    {
        for (int x_0 = x_begin; x_0 < offset; x_0++)
        {
            PUPPY::RGBA color = to[width * y_0 + (x_0 + offset)];  
            to[width * y_0 + x_0] = color;
        }
    }

    for (int x_0 = 0; x_0 < width; x_0++)
    {
        for (int y_0 = y_begin; y_0 < offset; y_0++)
        {
            PUPPY::RGBA color = to[width * (y_0 + offset) + x_0];  
            to[width * y_0 + x_0] = color;
        }
    }
}

static void initialize_negative(PUPPY::RGBA *positive, PUPPY::RGBA *negative, long long width, long long height)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            PUPPY::RGBA color = positive[width * y + x];
            color.r = 255 - color.r;
            color.g = 255 - color.g;
            color.b = 255 - color.b;
            
            negative[width * y + x] = color;
        }
    }
}

static void make_relief(PUPPY::RGBA *positive, PUPPY::RGBA *negative, long long width, long long height, long long offset)
{
    initialize_negative(positive, negative, width, height);

    multiply(positive, negative, width, height, offset);
    make_negative(positive, width, height);
}

void Relief_plugin::effect_apply() const
{
    long long offset = DEFAULT_OFFSET;
    if (settings.offset_field) 
    {
        auto text = settings.offset_field->get_text().begin();
        long long wanted_offset = atoi(text);
        if (wanted_offset) 
        {
            offset = wanted_offset;
        }
    }
    long long amount = DEFAULT_AMOUNT;
    if (settings.amount_field) 
    {
        auto text = settings.amount_field->get_text().begin();
        long long wanted_amount = atoi(text);
        if (wanted_amount) 
        {
            amount = wanted_amount;
        }
    }

    PUPPY::Vec2s size = APPI->get_size();

    auto target = APPI->get_target();
    PUPPY::RGBA *positive_pixels = target->get_pixels();
    PUPPY::RGBA *negative_pixels = new PUPPY::RGBA[size.x * size.y];

    for (long long i = 0; i < amount; ++i)
        make_relief(positive_pixels, negative_pixels, size.x, size.y, offset);

    target->render_pixels(PUPPY::Vec2f(0, 0), size, positive_pixels, PUPPY::COPY);
    delete [] negative_pixels;
    delete target;
}

static bool enable_extension(const char * /*name*/) 
{
    return false;
}

static void *get_extension_func(const char * /*extension*/, const char * /*func*/) 
{
    return nullptr;
}

void Relief_plugin::draw(const PUPPY::Vec2f &pos) const 
{
    float size  = APPI->get_size() ;
    PUPPY::RGBA color = APPI->get_color();

    auto target = APPI->get_target();
    target->render_circle(pos, size, color, PUPPY::COPY);
    delete target;
}