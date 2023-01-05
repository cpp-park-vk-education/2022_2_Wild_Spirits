#include <gmock/gmock.h>

#include <fstream>

#include <Core/Application.h>

#include <Buffers/BufferLayout.h>
#include <Textures/TextureLoader.h>
#include <Transform/Transform.h>

TEST(Texture, LoadTexture) {
    LOG_INIT();
    LM::TextureLoader tl1(LM::FromFile { std::string(RES_FOLDER_TEST) + "Textures/Stone.png" });
    EXPECT_TRUE(tl1.isOk());
    EXPECT_EQ(tl1.getWidht(), 16);
    EXPECT_EQ(tl1.getHeight(), 16);

    std::ifstream input(std::string(RES_FOLDER_TEST) + "Textures/Stone.png", std::ios::binary);
    LM::TextureLoader tl2(LM::FromSource { std::string(std::istreambuf_iterator<char>(input), {}) });
    EXPECT_TRUE(tl2.isOk());
    EXPECT_EQ(tl2.getWidht(), 16);
    EXPECT_EQ(tl2.getHeight(), 16);

    LM::TextureLoader tl3(LM::FromFile { "fileWithWrongName.png" });
    EXPECT_FALSE(tl3.isOk());

    LM::TextureLoader tl4(LM::FromSource {});
    EXPECT_FALSE(tl4.isOk());
}

TEST(Transform, TransformRotationPlus) {
    LOG_INIT();
    LM::Transform transform;
    EXPECT_EQ(static_cast<float>(transform.rotation), 0.0f);

    transform.rotation += 10.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 10.0f);

    transform.rotation = transform.rotation + 10.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 20.0f);

    transform.rotation = 10.0f + transform.rotation;
    EXPECT_EQ(static_cast<float>(transform.rotation), 30.0f);

    transform.rotation = LM::Rotation(10.0f) + transform.rotation;
    EXPECT_EQ(static_cast<float>(transform.rotation), 40.0f);
}

TEST(Transform, TransformRotationMinus) {
    LOG_INIT();
    LM::Transform transform;
    transform.rotation = 100.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 100.0f);

    transform.rotation -= 10.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 90.0f);

    transform.rotation = transform.rotation - 10.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 80.0f);

    transform.rotation = 100.0f - transform.rotation;
    EXPECT_EQ(static_cast<float>(transform.rotation), 20.0f);

    transform.rotation = LM::Rotation(50.0f) - transform.rotation;
    EXPECT_EQ(static_cast<float>(transform.rotation), 30.0f);
}

TEST(Transform, TransformRotationSub) {
    LM::Transform transform;
    transform.rotation = 100.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 100.0f);

    transform.rotation /= 2.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 50.0f);

    transform.rotation = transform.rotation / 10.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 5.0f);

    transform.rotation = 100.0f / transform.rotation;
    EXPECT_EQ(static_cast<float>(transform.rotation), 20.0f);

    transform.rotation = LM::Rotation(40.0f) / transform.rotation;
    EXPECT_EQ(static_cast<float>(transform.rotation), 2.0f);
}

TEST(Transform, TransformRotationMulti) {
    LM::Transform transform;
    transform.rotation = 4.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 4.0f);

    transform.rotation *= 2.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 8.0f);

    transform.rotation = transform.rotation * 4.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 32.0f);

    transform.rotation = 2.0f * transform.rotation;
    EXPECT_EQ(static_cast<float>(transform.rotation), 64.0f);

    transform.rotation = LM::Rotation(2.0f) * transform.rotation;
    EXPECT_EQ(static_cast<float>(transform.rotation), 128.0f);
}

TEST(BufferLayout, TypeTest) {
    LM::BufferLayout layout({
        {LM::ShaderDataType::Float3, "a_Position"},
        {LM::ShaderDataType::Float2, "a_TexCoord"},
        {LM::ShaderDataType::Float3,   "a_Normal"},
        {LM::ShaderDataType::Float3,  "a_Tangent"}
    });

    EXPECT_EQ(layout.getStride(), 44);
    EXPECT_EQ(layout.getElements()[0].offset, 0);
    EXPECT_EQ(layout.getElements()[1].offset, 12);
    EXPECT_EQ(layout.getElements()[2].offset, 20);
    EXPECT_EQ(layout.getElements()[3].offset, 32);
}
