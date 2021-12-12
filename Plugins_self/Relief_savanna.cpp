#include "../Plugin/plugin_std.hpp"

#include <cstdlib>
#include <ctime>
#include <cmath>

#include <cstdio>

// ============================================================================ Info

const uint32_t PSTDVERSION = 0;

const char *PNAME    = "Relief";
const char *PVERSION = "0.1";
const char *PAUTHOR  = "Savanna";
const char *PDESCR   = "Yes";

// ============================================================================ Flush policy

const PPreviewLayerPolicy FLUSH_POLICY = PPLP_BLEND;

// ============================================================================ Resources

// ============================================================================


static PPluginStatus init(const PAppInterface* appInterface);
static PPluginStatus deinit();

static void dump();
static void on_tick(double dt);
static void on_update();

static const PPluginInfo  *get_info();
static PPreviewLayerPolicy get_flush_policy();

static void on_mouse_down(PVec2f pos);
static void on_mouse_move(PVec2f from, PVec2f to);
static void on_mouse_up  (PVec2f pos);
static void apply();

static bool  enable_extension  (const char *name);
static void *get_extension_func(const char *extension, const char *func);

static void draw(PVec2f pos);


const PPluginInterface PINTERFACE =
{
    PSTDVERSION, // std_version
    nullptr,     // reserved
    
    {
        enable_extension,
        get_extension_func
    },

    // general
    {
        get_info,
        init,
        deinit,
        dump,
        on_tick,
        on_update,
        get_flush_policy,
    },

    // effect
    {
        apply,
    },

    // tool
    {
        on_mouse_down,
        on_mouse_up  ,
        on_mouse_move,
    },
};

const PPluginInfo PINFO =
{
    PSTDVERSION, // std_version
    nullptr,     // reserved

    &PINTERFACE,

    PNAME,
    PVERSION,
    PAUTHOR,
    PDESCR,
    
    PPT_EFFECT
};

const PAppInterface *APPI = nullptr;


extern "C" const PPluginInterface *get_plugin_interface() 
{
    return &PINTERFACE;
}

static PPluginStatus init(const PAppInterface *app_interface) 
{
    srand(time(NULL));

    APPI = app_interface;

    APPI->general.log("<Relief effect> was successfully inited", PINFO.name);
    return PPS_OK;
}

static PPluginStatus deinit() 
{
    APPI->general.log("<Relief effect> was successfully deinited", PINFO.name, PINFO.author);
    return PPS_OK;
}

static void dump() 
{
    APPI->general.log("<Relief effect> is active", PINFO.name);
}

static const PPluginInfo *get_info() 
{
    return &PINFO;
}

static void on_tick(double /*dt*/) {}

static void on_update() {}

static PPreviewLayerPolicy get_flush_policy() 
{
    return FLUSH_POLICY;
}

static void on_mouse_down(PVec2f pos) 
{
    draw(pos);
}

static void on_mouse_move(PVec2f /*from*/, PVec2f to) 
{
    draw(to);
}

static void on_mouse_up(PVec2f /*pos*/) {}

void negative(PRGBA *to, long long width, long long height)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            PRGBA color = to[width * y + x];
            color.r = 255 - color.r;
            color.g = 255 - color.g;
            color.b = 255 - color.b;

            to[width * y + x] = color;
        }
    }
}

void multiply(PRGBA *to, PRGBA *from, long long width, long long height, long long offset)
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
            PRGBA color = from[width * y_0 + x_0];
            PRGBA positive_color = to[width * y + in_x];
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
    // if (offset > 0)
    // {
    //     x_begin = 0;
    //     y_begin = 0;
    // }
    // else
    // {
    //     x_begin = width + offset;
    //     y_begin = height + offset;
    // }

    for (int y_0 = 0; y_0 < height; y_0++)
    {
        for (int x_0 = x_begin; x_0 < offset; x_0++)
        {
            PRGBA color = to[width * y_0 + (x_0 + offset)];  
            to[width * y_0 + x_0] = color;
        }
    }

    for (int x_0 = 0; x_0 < width; x_0++)
    {
        for (int y_0 = y_begin; y_0 < offset; y_0++)
        {
            PRGBA color = to[width * (y_0 + offset) + x_0];  
            to[width * y_0 + x_0] = color;
        }
    }
}



static void apply() 
{
    PRenderMode render_mode = { PPBM_COPY, PPDP_ACTIVE, nullptr };

    size_t width = 0;
    size_t height = 0;
    APPI->target.get_size(&width, &height);

    PRGBA *positive_pixels = APPI->target.get_pixels();
    PRGBA *negative_pixels = new PRGBA[width * height];

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            PRGBA color = positive_pixels[width * y + x];
            color.r = 255 - color.r;
            color.g = 255 - color.g;
            color.b = 255 - color.b;
            
            negative_pixels[width * y + x] = color;
        }
    }

    long long offset = 20;
    multiply(positive_pixels, negative_pixels, width, height, offset);
    negative(positive_pixels, width, height);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            PRGBA color = positive_pixels[width * y + x];
            color.r = 255 - color.r;
            color.g = 255 - color.g;
            color.b = 255 - color.b;

            negative_pixels[width * y + x] = color;
        }
    }
    multiply(positive_pixels, negative_pixels, width, height, offset);
    negative(positive_pixels, width, height);

    APPI->render.pixels(PVec2f(0, 0), positive_pixels, width, height, &render_mode);
    delete [] negative_pixels;
    APPI->general.release_pixels(positive_pixels);
}

static bool enable_extension(const char * /*name*/) 
{
    return false;
}

static void *get_extension_func(const char * /*extension*/, const char * /*func*/) 
{
    return nullptr;
}
// 
static void draw(PVec2f pos) 
{
    float size  = APPI->general.get_size() ;
    PRGBA color = APPI->general.get_color();

    PRenderMode render_mode = { PPBM_COPY, PPDP_PREVIEW, nullptr }; 
    APPI->render.circle(pos, size, color, &render_mode);
}