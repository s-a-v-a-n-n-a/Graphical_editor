#include "redactor/plugin_std.h"
// #include "kctf_utils.h"

#include <cstdlib>
#include <ctime>
#include <cmath>

// ============================================================================ Info

const uint32_t PSTDVERSION = 0;

const char *PNAME    = "A name";
const char *PVERSION = "0.1";
const char *PAUTHOR  = "An author";
const char *PDESCR   = "A discription";

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
        get_extension_func,
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
    
    PPT_TOOL
};

const PAppInterface *APPI = nullptr;


extern "C" const PPluginInterface *get_plugin_interface() {
    return &PINTERFACE;
}

static PPluginStatus init(const PAppInterface *app_interface) {
    srand(time(NULL));

    APPI = app_interface;

    APPI->general.log("[plugin](%s) inited", PINFO.name);
    return PPS_OK;
}

static PPluginStatus deinit() {
    APPI->general.log("[plugin](%s) deinited | %s thanks you for using it", PINFO.name, PINFO.author);
    return PPS_OK;
}

static void dump() {
    APPI->general.log("[plugin](%s) is active", PINFO.name);
}

static const PPluginInfo *get_info() {
    return &PINFO;
}

static void on_tick(double /*dt*/) {
}

static void on_update() {
}

static PPreviewLayerPolicy get_flush_policy() {
    return FLUSH_POLICY;
}

static void on_mouse_down(PVec2f pos) {
    draw(pos);
}

static void on_mouse_move(PVec2f /*from*/, PVec2f to) {
    draw(to);
}

static void on_mouse_up(PVec2f /*pos*/) {}

static void apply() {}

static bool enable_extension(const char * /*name*/) {
    return false;
}

static void *get_extension_func(const char * /*extension*/, const char * /*func*/) {
    return nullptr;
}

static void draw(PVec2f pos) {
    float size  = APPI->general.get_size() ;
    PRGBA color = APPI->general.get_color();

    PRenderMode render_mode = { PPBM_COPY, PPDP_PREVIEW, nullptr }; 
    APPI->render.circle(pos, size, color, &render_mode);
}

/*
#include <cmath>

template <typename T, int neutral, int T_EPS>
struct Vec2 {
    static constexpr T EPS = T_EPS / 1000000;

    union {
        struct {
            T x;
            T y;
        };

        T data[2];
    };

    Vec2() : x(neutral), y(neutral) {}
    Vec2(const T &x, const T &y) : x(x), y(y) {}
    Vec2(const T &fill) : x(fill), y(fill) {}

    inline T len() const {
        return hypot(x, y);
    }

    inline T len_squared() const {
        return x * x + y * y;
    }

    inline Vec2 normal() const {
        T l = len();
        if(l < EPS) {
            return {neutral, neutral};
        } else {
            return {x / l, y / l};
        }
    }

    inline void normalize() {
        T l = len();
        if (l < EPS) { x = neutral; y = neutral; }
        else { x /= l; y /= l; }
    }

    inline bool is_zero() const {
        return len() < EPS;
    }

    inline T dot(const Vec2 &other) const {
        return x * other.x + y * other.y;
    }

    inline T cross(const Vec2 &other) const {
        return x * other.y - y * other.x;
    }

    double operator[](const int i) const {
        return data[i];
    }

    inline Vec2 rot90(int dir = 1) const {
        return {(-1 * dir) * x, (1 * dir) * y};
    }
};


template <typename T, int neutral, int eps>
inline Vec2<T, neutral, eps> operator+(const Vec2<T, neutral, eps> &first) {
    return first;
}

template <typename T, int neutral, int eps>
inline Vec2<T, neutral, eps> operator-(const Vec2<T, neutral, eps> &first) {
    return {-1 * first.x, -1 * first.y};
}

template <typename T, int neutral, int eps>
inline Vec2<T, neutral, eps> operator+(const Vec2<T, neutral, eps> &first, const Vec2<T, neutral, eps> &second) {
    return {first.x + second.x, first.y + second.y};
}

template <typename T, int neutral, int eps>
inline Vec2<T, neutral, eps> operator-(const Vec2<T, neutral, eps> &first, const Vec2<T, neutral, eps> &second) {
    return {first.x - second.x, first.y - second.y};
}

template <typename T, int neutral, int eps>
inline Vec2<T, neutral, eps> operator*(const Vec2<T, neutral, eps> &first, const Vec2<T, neutral, eps> &second) {
    return {first.x * second.x, first.y * second.y};
}

template <typename T, int neutral, int eps>
inline Vec2<T, neutral, eps> operator/(const Vec2<T, neutral, eps> &first, const Vec2<T, neutral, eps> &second) {
    return {first.x / second.x, first.y / second.y};
}

template <typename T, int neutral, int eps>
inline Vec2<T, neutral, eps> operator*(const Vec2<T, neutral, eps> &first, const double k) {
    return {static_cast<T>(k * first.x), static_cast<T>(k * first.y)};
}

template <typename T, int neutral, int eps>
inline Vec2<T, neutral, eps> operator*(const double k, const Vec2<T, neutral, eps> &first) {
    return {static_cast<T>(k * first.x), static_cast<T>(k * first.y)};
}

template <typename T, int neutral, int eps>
inline Vec2<T, neutral, eps> operator/(const Vec2<T, neutral, eps> &first, const double k) {
    return {static_cast<T>(first.x / k), static_cast<T>(first.y / k)};
}

template <typename T, int neutral, int eps>
inline Vec2<T, neutral, eps> &operator+=(Vec2<T, neutral, eps> &first, const Vec2<T, neutral, eps> &second) {
    first.x += second.x;
    first.y += second.y;
    return first;
}

template <typename T, int neutral, int eps>
inline Vec2<T, neutral, eps> &operator-=(Vec2<T, neutral, eps> &first, const Vec2<T, neutral, eps> &second) {
    first.x -= second.x;
    first.y -= second.y;
    return first;
}

template <typename T, int neutral, int eps>
inline Vec2<T, neutral, eps> &operator*=(Vec2<T, neutral, eps> &first, const Vec2<T, neutral, eps> &second) {
    first.x *= second.x;
    first.y *= second.y;
    return first;
}

template <typename T, int neutral, int eps>
inline Vec2<T, neutral, eps> &operator/=(Vec2<T, neutral, eps> &first, const Vec2<T, neutral, eps> &second) {
    first.x /= second.x;
    first.y /= second.y;
    return first;
}

template <typename T, int neutral, int eps>
inline Vec2<T, neutral, eps> &operator*=(Vec2<T, neutral, eps> &first, const double k) {
    first.x *= k;
    first.y *= k;
    return first;
}

template <typename T, int neutral, int eps>
inline Vec2<T, neutral, eps> &operator/=(Vec2<T, neutral, eps> &first, const double k) {
    first.x /= k;
    first.y /= k;
    return first;
}

template <typename T, int neutral, int eps>
inline bool operator==(const Vec2<T, neutral, eps> &first, const Vec2<T, neutral, eps> &second) {
    return abs(first.x - second.x) < first.EPS && abs(first.y - second.y) < first.EPS;
}

template <typename T, int neutral, int eps>
inline bool operator<(const Vec2<T, neutral, eps> &first, const Vec2<T, neutral, eps> &second) {
    return first.x - second.x < first.EPS && first.y - second.y < first.EPS;
}

template <typename T, int neutral, int eps>
inline Vec2<T, neutral, eps> sqrt(const Vec2<T, neutral, eps> &first) {
    return {sqrt(first.x),
            sqrt(first.y)};
}

template <typename T, int neutral, int eps>
inline Vec2<T, neutral, eps> pow(const Vec2<T, neutral, eps> &first, const double power) {
    return {pow(first.x, power),
            pow(first.y, power)};
}

using Vec2i = Vec2<int,    0, 0>;
using Vec2f = Vec2<float,  0, 1>;
using Vec2d = Vec2<double, 0, 1>;
*/