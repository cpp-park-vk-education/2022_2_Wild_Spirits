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
            { ShaderSource::Type::kVertex, ShaderSource::fromFile(std::string(RES_FOLDER) + "Shaders/Simple.vert") },
            { ShaderSource::Type::kFragment, ShaderSource::fromFile(std::string(RES_FOLDER) + "Shaders/Simple.frag") }
            }));
    }

    void Renderer::start(glm::uvec2 windowSize, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
        m_Shader->enable();
        glViewport(0, 0, windowSize.x, windowSize.y);
        m_Shader->setUniformMat4("u_ProjectionMatrix", projectionMatrix);
        m_Shader->setUniformMat4("u_ViewMatrix", viewMatrix);
    }


    void Renderer::pushTransform(const glm::mat4 transform) {
        m_Transforms.push_back(transform * m_Transforms[m_Transforms.size() - 1]);
    }

    void Renderer::popTransform() {
        m_Transforms.pop_back();
    }

    void Renderer::draw(RenderableTexture* renderable) {
        m_Shader->setUniformMat4(
            "u_Transform",
            m_Transforms[m_Transforms.size() - 1] * renderable->getTransform().getMatrix());
        m_Shader->setUniform4f("u_Color", renderable->getColor());

        renderable->getVertexArray()->bind();
        renderable->getTexture()->bind(0);
        if (renderable->getVertexArray()->getIndexBuffer()->getCount()) {
            glDrawElements(
                GL_TRIANGLES,
                renderable->getVertexArray()->getIndexBuffer()->getCount(),
                GL_UNSIGNED_INT,
                NULL);
        }
    }

    void Renderer::draw(RenderableGroupInterface* renderable) {
        (void)renderable;
        LOGI("void Renderer::draw(RenderableGroupInterface* renderable)");
    }

}    // namespace LM
