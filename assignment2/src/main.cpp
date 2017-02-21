#include <iostream>

#include <atlas\gl\ErrorCheck.hpp>
#include <atlas\utils\Application.hpp>
#include <atlas\utils\Utils.hpp>
#include <atlas\utils\WindowSettings.hpp>
#include <atlas\tools\ModellingScene.hpp>
#include "PolygonizationScene.hpp"

// Configure the settings we need to create an openGL context
atlas::utils::WindowSettings config_window_settings() {
    auto window_settings = atlas::utils::WindowSettings();
    window_settings.title = "Assignment 2";
    window_settings.contextVersion = std::tuple<int, int>(4, 4);
    window_settings.isMaximized = true;
    window_settings.windowSize = std::tuple<int, int>(400, 400);

    return window_settings;
}

int main(void) {
    auto window_settings = config_window_settings();

    atlas::gl::setGLErrorSeverity(ATLAS_GL_ERROR_SEVERITY_HIGH | ATLAS_GL_ERROR_SEVERITY_MEDIUM);


    //Create window
    atlas::utils::Application::getInstance().createWindow(window_settings);
    atlas::utils::Application::getInstance().addScene(atlas::utils::ScenePointer(new assignment2::PolygonizationScene()));
    atlas::utils::Application::getInstance().runApplication();

    return 0;
}
