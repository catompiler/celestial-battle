#ifndef _ENGINE_H_
#define _ENGINE_H_

#define ENGINE_NAMESPACE_BEGIN namespace Rage{
#define ENGINE_NAMESPACE_END }

#include "object/object.h"
#include <string>


class Window;
class Settings;


ENGINE_NAMESPACE_BEGIN

class Engine
    :public Object
{
public:
    Engine();
    ~Engine();
    
    const std::string& configFile() const;
    void setConfigFile(const std::string& config_file_);
    
    const Settings* settings() const;
    Settings* settings();
    bool readSettings();
    bool writeSettings();
    
    const Window* window() const;
    Window* window();
    bool initVideo(const std::string& title_);
    bool destroyVideo();
    
    
private:
    Settings* _settings;
    Window* _window;
};

ENGINE_NAMESPACE_END

#endif  //_ENGINE_H_
