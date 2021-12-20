#include "../Plugin_support2/plugin_std_2.hpp"

#include <vector>

class WindowTest : public PUPPY::PluginInterface
{
public:
    WindowTest() : PUPPY::PluginInterface() {};

    virtual bool ext_enable(const char *name) const override;

    virtual void *ext_get_func(const char *extension, const char *func) const override;

    virtual void *ext_get_interface(const char *extension, const char *name) const override;

    virtual const PUPPY::PluginInfo *get_info() const override;
    virtual PUPPY::Status init(const PUPPY::AppInterface*, const std::filesystem::path& path) override;
    virtual PUPPY::Status deinit() override;
    virtual void dump() const override;

    virtual void on_tick(double dt) const override;

    virtual void effect_apply() const override;

    virtual void tool_on_press(const PUPPY::Vec2f &position) const override;
    virtual void tool_on_release(const PUPPY::Vec2f &position) const override;
    virtual void tool_on_move(const PUPPY::Vec2f &from, const PUPPY::Vec2f &to) const override;

    virtual void show_settings() const override;
};

//===================================================================

const PUPPY::AppInterface* gAppInterface = nullptr;

struct {
    PUPPY::Window *window;
} gWidgets;

const PUPPY::WBody WINDOW_BODY(PUPPY::Vec2f(400, 400), PUPPY::Vec2f(1000, 1000));

//===================================================================

const WindowTest gPluginInterface;

const PUPPY::PluginInfo gPluginInfo =
{
    PUPPY::STD_VERSION,     // std_version
    0,                      // reserved

    &gPluginInterface,      // plugin interface

    "Window test",
    "2.0",
    "loochek",
    "kekw",

    nullptr,                // icon
    
    PUPPY::PluginType::EFFECT
};

extern "C" const PUPPY::PluginInterface *get_plugin_interface()
{
    return &gPluginInterface;
}

//===================================================================

bool WindowTest::ext_enable(const char *name) const
{
    return false;
}

void *WindowTest::ext_get_func(const char *extension, const char *func) const
{
    return nullptr;
}

void *WindowTest::ext_get_interface(const char *extension, const char *name)  const
{
    return nullptr;
}

const PUPPY::PluginInfo *WindowTest::get_info() const
{
    return &gPluginInfo;
}

PUPPY::Status WindowTest::init(const PUPPY::AppInterface* appInterface, const std::filesystem::path& path)
{
    gAppInterface = appInterface;

    if (appInterface->factory.widget)
    {
        const PUPPY::WidgetFactory *factory = appInterface->factory.widget;

        gWidgets.window = factory->window("AMOGUS", WINDOW_BODY);
        if (!gWidgets.window) {
            printf("We have a loh here\n");
        }
        else
            printf("%p\n", gWidgets.window);
    }

    appInterface->log("WindowTest: succesful initialization!");
    return PUPPY::Status::OK;
}

PUPPY::Status WindowTest::deinit()
{
    if (gWidgets.window) {
        gWidgets.window->set_to_delete();
    }
    else {
        printf("We have a loh here\n");
    }

    return PUPPY::Status::OK;
}

void WindowTest::dump() const
{
}

void WindowTest::on_tick(double dt) const
{
}

void WindowTest::effect_apply() const
{
}

void WindowTest::tool_on_press(const PUPPY::Vec2f &position) const
{
}

void WindowTest::tool_on_release(const PUPPY::Vec2f &position) const
{
}

void WindowTest::tool_on_move(const PUPPY::Vec2f &from, const PUPPY::Vec2f &to) const
{
}

void WindowTest::show_settings() const
{
}