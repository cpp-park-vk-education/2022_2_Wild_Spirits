#include <gmock/gmock.h>

#include <Core/Application.h>

#include <Textures/TextureLoader.h>
#include <Buffers/BufferLayout.h>
#include <Transform/Transform.h>

using namespace LM;

TEST(Texture, LoadTexture) {
    TextureLoader tl1(TextureLoader::FromFile{ "test.png" });
    EXPECT_TRUE(tl1.isOk());
    EXPECT_EQ(tl1.getWidht(), 32);
    EXPECT_EQ(tl1.getHeight(), 32);

    //std::string someGoodImgSource = "";
    //TextureLoader tl2(TextureLoader::FromSource{ someGoodImgSource });
    //EXPECT_TRUE(tl2.isOk());
    //EXPECT_EQ(tl2.getWidht(), 32);
    //EXPECT_EQ(tl2.getHeight(), 32);

    TextureLoader tl3(TextureLoader::FromFile{ "fileWithWrongName.png" });
    EXPECT_FALSE(tl3.isOk());


    //std::string someBadImgSource = "";
    //TextureLoader tl4(TextureLoader::FromSource{ someBadImgSource });
    //EXPECT_TRUE(tl4.isOk());
}

TEST(Transform, TransformRotationPlus) {
    Transform transform;
    EXPECT_EQ(static_cast<float>(transform.rotation), 0.0f);

    transform.rotation += 10.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 10.0f);

    transform.rotation = transform.rotation + 10.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 20.0f);

    transform.rotation = 10.0f + transform.rotation;
    EXPECT_EQ(static_cast<float>(transform.rotation), 30.0f);

    transform.rotation = Rotation(10.0f) + transform.rotation;
    EXPECT_EQ(static_cast<float>(transform.rotation), 40.0f);
}

TEST(Transform, TransformRotationMinus) {

    Transform transform;
    transform.rotation = 100.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 0.0f);

    transform.rotation -= 10.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 90.0f);

    transform.rotation = transform.rotation - 10.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 80.0f);

    transform.rotation = 100.0f - transform.rotation;
    EXPECT_EQ(static_cast<float>(transform.rotation), 20.0f);

    transform.rotation = Rotation(50.0f) - transform.rotation;
    EXPECT_EQ(static_cast<float>(transform.rotation), 30.0f);
}

TEST(Transform, TransformRotationSub) {
    Transform transform;
    transform.rotation = 100.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 100.0f);

    transform.rotation /= 2.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 50.0f);

    transform.rotation = transform.rotation / 10.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 5.0f);

    transform.rotation = 100.0f / transform.rotation;
    EXPECT_EQ(static_cast<float>(transform.rotation), 20.0f);

    transform.rotation = Rotation(40.0f) / transform.rotation;
    EXPECT_EQ(static_cast<float>(transform.rotation), 2.0f);
}

TEST(Transform, TransformRotationMulti) {
    Transform transform;
    transform.rotation = 4.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 4.0f);

    transform.rotation *= 2.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 8.0f);

    transform.rotation = transform.rotation * 4.0f;
    EXPECT_EQ(static_cast<float>(transform.rotation), 32.0f);

    transform.rotation = 2.0f * transform.rotation;
    EXPECT_EQ(static_cast<float>(transform.rotation), 64.0f);

    transform.rotation = Rotation(2) * transform.rotation;
    EXPECT_EQ(static_cast<float>(transform.rotation), 128.0f);
}

TEST(BufferLayout, TypeTest) {
    BufferLayout layout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float2, "a_TexCoord" },
            { ShaderDataType::Float3, "a_Normal" },
            { ShaderDataType::Float3, "a_Tangent" } });

    EXPECT_EQ(layout.getStride(), 44);
    EXPECT_EQ(layout.getElements()[0].offset, 0);
    EXPECT_EQ(layout.getElements()[1].offset, 12);
    EXPECT_EQ(layout.getElements()[2].offset, 20);
    EXPECT_EQ(layout.getElements()[3].offset, 32);
}
