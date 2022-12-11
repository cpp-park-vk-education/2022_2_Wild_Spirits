cmake_minimum_required(VERSION 3.24)
project(ClientEngine VERSION 1.0)

set(SOURCES     
    src/Buffers/BufferLayout.h
    src/Buffers/IndexBuffer.cpp  src/Buffers/IndexBuffer.h
    src/Buffers/VertexArray.cpp  src/Buffers/VertexArray.h
    src/Buffers/VertexBuffer.cpp src/Buffers/VertexBuffer.h
    
    src/Core/Application.cpp src/Core/Application.h
    src/Core/Base.h
    src/Core/Assert.h
    src/Core/Color.h
    src/Core/KeyCode.h src/Core/MouseCode.h
    src/Core/Window.cpp src/Core/Window.h
    
    src/Events/Events.h
    src/Events/EventInterface.h 
    src/Events/EventKey.h
    src/Events/EventMouse.h 
    src/Events/EventWindow.h
    src/Events/EventDispatcher.h 
    src/Events/EventQueue.h
    
    src/Layers/Layer.cpp src/Layers/Layer.h
    src/Layers/LayerLocation.cpp src/Layers/LayerLocation.h
    src/Layers/LayerMainMenu.cpp src/Layers/LayerMainMenu.h
    src/Layers/LayerSettings.cpp src/Layers/LayerSettings.h
    src/Layers/LayerStack.cpp src/Layers/LayerStack.h
    
    src/Renderables/RenderableInterface.h 
    src/Renderables/Renderable.h 
    src/Renderables/RenderableGroupInterface.cpp src/Renderables/RenderableGroupInterface.h 
    src/Renderables/RenderableGroup.cpp src/Renderables/RenderableGroup.h 
    src/Renderables/RenderableTexture.cpp src/Renderables/RenderableTexture.h

    src/Renderables/Gui/RenderableGui.cpp src/Renderables/Gui/RenderableGui.h 
    src/Renderables/Gui/RenderableGuiAlign.h 
    src/Renderables/Gui/RenderableGuiGroup.cpp src/Renderables/Gui/RenderableGuiGroup.h
    src/Renderables/Gui/RenderableGuiTexture.cpp src/Renderables/Gui/RenderableGuiTexture.h

    src/Renderables/Gui/RenderableBottomAction/RenderableBottomAction.cpp 
    src/Renderables/Gui/RenderableBottomAction/RenderableBottomAction.h
    src/Renderables/Gui/RenderableBottomAction/RenderableBottomActionGroup.cpp 
    src/Renderables/Gui/RenderableBottomAction/RenderableBottomActionGroup.h

    src/Renderables/Scene/RenderableTile.cpp src/Renderables/Scene/RenderableTile.h
    src/Renderables/Scene/RenderableCharacter.cpp src/Renderables/Scene/RenderableCharacter.h
    src/Renderables/Scene/RenderableTileGroup.cpp src/Renderables/Scene/RenderableTileGroup.h

    src/Renderers/RendererInterface.h
    src/Renderers/Renderer.cpp src/Renderers/Renderer.h

    src/Scenes/SceneInterface.h
    src/Scenes/Gui/SceneGui.cpp src/Scenes/Gui/SceneGui.h
    src/Scenes/Scene/Scene.cpp src/Scenes/Scene/Scene.h
    
    src/Shader/Shader.cpp src/Shader/Shader.h
    src/Shader/ShaderLayout.cpp src/Shader/ShaderLayout.h
    src/Shader/ShaderDataType.h

    src/Textures/Texture2D.cpp src/Textures/Texture2D.h
    src/Textures/TextureLoader.cpp src/Textures/TextureLoader.h
    src/Textures/stb_image.h
    src/Textures/CalcTextureParameters.cpp src/Textures/CalcTextureParameters.h
    
    src/Transform/Transform.cpp src/Transform/Transform.h
    src/Transform/Rotation.h

    src/ImGui/ImGuiController.cpp src/ImGui/ImGuiController.h

    src/Utils/Timer.h
    src/Utils/ConsoleLog.cpp src/Utils/ConsoleLog.h)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} ClientRequestor)
target_link_libraries(${PROJECT_NAME} glm glfw glew ImGui opengl32)

add_definitions(-DGLEW_STATIC -D_LIB)

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG dd8a678a66f1967372e5a5e3deac41ebf65ee127
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG fc8f4bb442b9540969f2f3f351c4960d91bca17a
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
    glew
    GIT_REPOSITORY https://github.com/mihaillatyshov/glew.git
    GIT_TAG bd68b6e4b996d165451049637c1d66018f207b53
)
FetchContent_MakeAvailable(glew)

FetchContent_Declare(
    ImGui
    GIT_REPOSITORY https://github.com/mihaillatyshov/imgui.git
    GIT_TAG 01785d8581c14156043325472a4150dae4aba8b2
)
FetchContent_MakeAvailable(ImGui)

option(GLFW_BUILD_DOCS "GLFW_BUILD_DOCS" OFF)
add_subdirectory(tests)

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Client/Engine")
    set_target_properties(glfw PROPERTIES FOLDER "Client/Engine/deps")
    set_target_properties(update_mappings PROPERTIES FOLDER "Client/Engine/deps")
    set_target_properties(glew PROPERTIES FOLDER "Client/Engine/deps")
    set_target_properties(ImGui PROPERTIES FOLDER "Client/Engine/deps")
endif()
