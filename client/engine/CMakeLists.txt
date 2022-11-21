cmake_minimum_required(VERSION 3.24)
project(ClientEngine VERSION 1.0)

set(SOURCES 
    src/Actions/Action.h

    src/Actions/UseAction/UseAction.h
    src/Actions/UseAction/UseActionConsumable.h
    src/Actions/UseAction/UseActionSkill.h
    src/Actions/UseAction/UseActionSpell.h
    src/Actions/UseAction/UseActionWeapon.h
    
    src/Buffers/BufferLayout.h
    src/Buffers/IndexBuffer.cpp  src/Buffers/IndexBuffer.h
    src/Buffers/VertexArray.cpp  src/Buffers/VertexArray.h
    src/Buffers/VertexBuffer.cpp src/Buffers/VertexBuffer.h
    
    src/Core/Application.cpp src/Core/Application.h
    src/Core/Base.h
    src/Core/Color.h
    src/Core/KeyCode.h src/Core/MouseCode.h
    src/Core/Window.cpp src/Core/Window.h
    
    src/Events/Events.h
    src/Events/EventInterface.h src/Events/EventDispatcher.h src/Events/EventQueue.h
    src/Events/EventKey.h src/Events/EventMouse.h src/Events/EventWindow.h
    
    src/Layers/Layer.h
    src/Layers/LayerLocation.cpp src/Layers/LayerLocation.h
    src/Layers/LayerMainMenu.cpp src/Layers/LayerMainMenu.h
    src/Layers/LayerSettings.cpp src/Layers/LayerSettings.h
    src/Layers/LayerStack.cpp src/Layers/LayerStack.h
    
    src/Renderables/Renderable.h 

    src/Renderables/Gui/RenderableGui.h src/Renderables/Gui/RenderableGuiAlign.h 
    src/Renderables/Gui/RenderableGuiGroup.cpp src/Renderables/Gui/RenderableGuiGroup.h
    src/Renderables/Gui/RenderableGuiTexture.cpp src/Renderables/Gui/RenderableGuiTexture.h

    src/Renderables/Gui/RenderableBottomAction/RenderableBottomAction.cpp 
    src/Renderables/Gui/RenderableBottomAction/RenderableBottomAction.h
    src/Renderables/Gui/RenderableBottomAction/RenderableBottomActionGroup.cpp 
    src/Renderables/Gui/RenderableBottomAction/RenderableBottomActionGroup.h
    src/Renderables/Gui/RenderableBottomAction/RenderableBottomConsumable.h
    src/Renderables/Gui/RenderableBottomAction/RenderableBottomSkill.h
    src/Renderables/Gui/RenderableBottomAction/RenderableBottomSpell.h
    src/Renderables/Gui/RenderableBottomAction/RenderableBottomWeapon.h

    src/Renderables/Scene/RenderableScene.h
    src/Renderables/Scene/RenderableSceneTexture.cpp src/Renderables/Scene/RenderableSceneTexture.h
    src/Renderables/Scene/RenderableTile.cpp src/Renderables/Scene/RenderableTile.h

    src/Renderers/Renderer.h
    src/Renderers/Gui/RendererGui.cpp src/Renderers/Gui/RendererGui.h
    src/Renderers/Scene/RendererScene.cpp src/Renderers/Scene/RendererScene.h

    src/Scenes/Scene.h
    src/Scenes/Gui/SceneGui.cpp src/Scenes/Gui/SceneGui.h
    src/Scenes/Scene/SceneScene.cpp src/Scenes/Scene/SceneScene.h
    
    src/Shader/Shader.cpp src/Shader/Shader.h
    src/Shader/ShaderLayout.cpp src/Shader/ShaderLayout.h
    src/Shader/ShaderDataType.h

    src/Textures/Texture2D.cpp src/Textures/Texture2D.h
    
    src/Transform/Transform.cpp src/Transform/Transform.h
    src/Transform/Rotation.h

    src/Utils/Timer.h)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} glm)

add_subdirectory(deps/glm)
add_subdirectory(tests)

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Client/Engine")
endif()
