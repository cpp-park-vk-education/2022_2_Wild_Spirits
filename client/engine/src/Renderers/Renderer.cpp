#include "Renderer.h"

#include <glm/gtx/transform.hpp>
#include <GLFW/glfw3.h>

#include <Renderables/RenderableTexture.h>
#include <Renderables/RenderableGroupInterface.h>
#include <Utils/ConsoleLog.h>

namespace LM {

    Renderer::Renderer() {
        m_Transforms.push_back(glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)));
        m_Shader = CreateScope<Shader>(ShaderLayout({
            { ShaderSource::Type::kVertex, ShaderSource::fromFile("./res/Shaders/Simple.vert") },
            { ShaderSource::Type::kFragment, ShaderSource::fromFile("./res/Shaders/Simple.frag") } }));
    }

    void Renderer::start() {
        m_Shader->enable();
    }

    void Renderer::draw(RenderableTexture* renderable) {
        //m_Shader->setUniform1f();
        //renderable->getTransform();
        renderable->getVertexArray()->bind();
        renderable->getIndexBuffer()->bind();
        //glBegin(GL_TRIANGLES);
        //glColor3f(1.0f, 1.0f, 1.0f);
        //glVertex2f(0.0f, 0.0f);
        //glVertex2f(0.0f, 1.0f);
        //glVertex2f(1.0f, 1.0f);
        //glEnd();
        if (renderable->getIndexBuffer()->getCount())
        {
            glDrawElements(GL_TRIANGLES, renderable->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, NULL);
        }
    }

    void Renderer::draw(RenderableGroupInterface* renderable) {

    }

}
