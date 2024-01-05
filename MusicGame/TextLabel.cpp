#include "TextLabel.h"
#include <sstream>
#include <iomanip>


CharTexturesMap::~CharTexturesMap()
{
    for (auto i = charTexturesMap.begin(); i != charTexturesMap.end(); i++) {
        for (auto j = i->second.begin(); j != i->second.end(); j++) {
            for (auto k = j->second.begin(); k != j->second.end(); k++) {
                if (k->second)
                    delete k->second;
            }
        }
    }
}

CharTexture* CharTexturesMap::loadCharTexture(char c, unsigned int fontsize)
{
    CharTexture* chartex = findCharTexture("FiraCode-Regular", c, fontsize);
    if (chartex == nullptr) {
        FT_Library ft;
        if (FT_Init_FreeType(&ft))
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

        std::string fontfile = std::string(ROOT_PATH) + "assets/fonts/FiraCode-Regular.ttf";
        FT_Face face;
        if (FT_New_Face(ft, fontfile.c_str(), 0, &face)) {
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
            return nullptr;
        }
        FT_Set_Pixel_Sizes(face, 0, fontsize);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            return nullptr;
        }
        chartex = new CharTexture(face);

        auto _f = charTexturesMap.find("FiraCode-Regular");
        if (_f == charTexturesMap.end()) {
            std::map<char, std::map<unsigned int, CharTexture*>> cmap;
            std::map<unsigned int, CharTexture*> smap;
            smap[fontsize] = chartex;
            cmap[c] = smap;
            charTexturesMap["FiraCode-Regular"] = cmap;
            return chartex;
        }
        else {
            auto _c = _f->second.find(c);
            if (_c == _f->second.end()) {
                std::map<unsigned int, CharTexture*> smap;
                smap[fontsize] = chartex;
                _f->second[c] = smap;
                return chartex;
            }
            else {
                auto _s = _c->second.find(fontsize);
                if (_s == _c->second.end()) {
                    _c->second[fontsize] = chartex;
                    return chartex;
                }
            }
        }

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }
    return chartex;
}

CharTexture* CharTexturesMap::findCharTexture(const std::string& font, const char c, const unsigned int fontsize)
{
    auto f = charTexturesMap.find(font);
    if (f == charTexturesMap.end())
        return nullptr;
    auto _c = (f->second).find(c);
    if (_c == (f->second).end())
        return nullptr;
    auto _s = (_c->second).find(fontsize);
    if (_s == (_c->second).end())
        return nullptr;

    return _s->second;
}


namespace UI {
    CharTexturesMap TextLabel::chartexmap;
    TextLabel::TextLabel(unsigned int fontSize, const std::string& fontfile, const std::string& text, Object2D* parent)
        : Object2D(parent), text(text), fontSize(fontSize), textColor(textColor)
    {
        type = "TextLabel";

        font = fontfile.substr(fontfile.find_last_of("/") + 1);
        font = font.substr(0, font.find("."));

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 5, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (const void*)(3 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);


        for (int i = 0; i < text.size(); i++) {
            texttexs.push_back(chartexmap.loadCharTexture(text[i], fontSize));
        }

        timer.startTimer();
    }

    TextLabel::~TextLabel()
    {
    }

    void TextLabel::draw(const Camera& camera) const
    {
        shader->useprogram();
        shader->setUniformMat4x4f("_projection", 1, glm::value_ptr(camera.getProjection()));
        shader->setUniformMat4x4f("_view", 1, glm::value_ptr(camera.getView()));
        shader->setUniformMat4x4f("_model", 1, glm::value_ptr(transform.localToWorld()));
        shader->setUniformVec4f("_textColor", (float)textColor.r / 255.0f, (float)textColor.g / 255.0f, (float)textColor.b / 255.0f, (float)textColor.a / 255.0f);
        glActiveTexture(GL_TEXTURE0);
        shader->setUniform1i("_text", 0);

        glBindVertexArray(vao);

        float x = 0;
        float y = 0;
        float z = 0;

        for (int i = 0; i < text.size(); i++) {
            CharTexture* c = texttexs[i];

            float cx = x + c->bearing.x * camera.pixelPerUnit;
            float cy = y - (c->size.y - c->bearing.y) * camera.pixelPerUnit;
            float cw = c->size.x * camera.pixelPerUnit;
            float ch = c->size.y * camera.pixelPerUnit;

            float vertices[6][5] = {
                {cx,      cy + ch, z, 0.0f, 0.0f},
                {cx,      cy,      z, 0.0f, 1.0f},
                {cx + cw, cy,      z, 1.0f, 1.0f},
                                   
                {cx,      cy + ch, z, 0.0f, 0.0f},
                {cx + cw, cy,      z, 1.0f, 1.0f},
                {cx + cw, cy + ch, z, 1.0f, 0.0f}
            };

            glBindTexture(GL_TEXTURE_2D, c->texid());

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glDrawArrays(GL_TRIANGLES, 0, 6);

            x += (c->advancex >> 6) * camera.pixelPerUnit;
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void TextLabel::setText(std::string s)
    {
        text = s;
        texttexs.clear();
        for (int i = 0; i < text.size(); i++) {
            texttexs.push_back(chartexmap.loadCharTexture(text[i], fontSize));
        }
    }


    void TextLabel::update()
    {
        if (timer.currentTime() >= 1) {
            double fps = 1.0 / Core::getFrameIntervalTime();
            std::stringstream ss;
            ss << (int)fps;
            setText("FPS: " + ss.str());

            timer.startTimer();
        }
    }
}
