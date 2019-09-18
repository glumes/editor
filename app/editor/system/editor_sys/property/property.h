#pragma once

#include "../../../include.h"
#include "../../ui_sys/ui_state/ui_state.h"
#include "../../ui_sys/ui_object/ui_object.h"

class ComponentHeader : public UIObject {
public:
    ComponentHeader(const std::string & name): UIObject(UITypeEnum::kOTHER, new UIState())
    {
        GetState()->Name = name;
    }

private:
    virtual bool OnEnter() override;
};

template <class T, class B = T>
class PropertyState : public UIState {
public:
    using Handler_t = std::function<bool(const std::any & value, const std::string & title, const std::any & backup)>;

public:
    PropertyState(
        T & value, 
        const std::string & title, 
        const Handler_t & handler)
        : mTitle(title)
        , mValue(value)
        , mBackup(value)
        , mHandler(handler)
    { }

    B           mBackup;
    T &         mValue;
    std::string mTitle;
    Handler_t mHandler;
};

template <class T, class B = T>
class PropertyObject : public UIObject {
public:
    using Handler_t = typename PropertyState<T>::Handler_t;

protected:
    PropertyObject(
        T & value,
        const std::string & title,
        const Handler_t & handler)
        : UIObject(UITypeEnum::kOTHER, new PropertyState<T, B>(value, title, handler))
    { }

    const std::string & GetTitle() const
    {
        return GetState<PropertyState<T, B>>()->mTitle;
    }

    const T & GetValue() const
    {
        return GetState<PropertyState<T, B>>()->mValue;
    }

    T & GetValue()
    {
        return GetState<PropertyState<T, B>>()->mValue;
    }

    B & GetBackup()
    {
        return GetState<PropertyState<T, B>>()->mBackup;
    }

    bool Modify()
    {
        auto ret = GetState<PropertyState<T, B>>()->mHandler(GetBackup(), GetTitle(), GetValue());
        if (ret) { GetValue() = GetBackup(); }
        else { GetBackup() = GetValue(); }
        return ret;
    }

    virtual void OnRender(float dt) override
    {
        auto width = ImGui::GetWindowWidth();
        ImGui::Columns(2, nullptr, false);
        ImGui::SetColumnWidth(1, width * 0.7f);
        ImGui::SetColumnOffset(1, width * 0.3f);

        ImGui::Text(GetTitle().c_str());
        ImGui::NextColumn();
    }
};

// ---
//  属性 int
// ---
class PropertyInt : public PropertyObject<int> {
public:
    PropertyInt(
        int & value, 
        const std::string & title, 
        const Handler_t & handler)
        : PropertyObject<int>(value, title, handler)
    { }

    virtual void OnRender(float dt) override;
};

// ---
//  属性 bool
// ---
class PropertyBool : public PropertyObject<bool> {
public:
    PropertyBool(
        bool & value,
        const std::string & title,
        const Handler_t & handler)
        : PropertyObject<bool>(value, title, handler)
    { }

    virtual void OnRender(float dt) override;
};

// ---
//  属性 float
// ---
class PropertyFloat : public PropertyObject<float> {
public:
    PropertyFloat(
        float & value,
        const std::string & title,
        const Handler_t & handler)
        : PropertyObject<float>(value, title, handler)
    { }

    virtual void OnRender(float dt) override;
};

// ---
//  属性 string
// ---
class PropertyString : public PropertyObject<std::string> {
public:
    PropertyString(
        std::string & value,
        const std::string & title,
        const Handler_t & handler)
        : PropertyObject<std::string>(value, title, handler)
    { }

    virtual void OnRender(float dt) override;
};

// ---
//  属性 combo
// ---
class PropertyCombo : public PropertyObject<
    std::pair<
        size_t, 
        std::vector<std::string>
    >
> {
public:
    PropertyCombo(
        std::pair<
            size_t, 
            std::vector<std::string>
        > & value,
        const std::string & title,
        const Handler_t & handler)
        : PropertyObject<
            std::pair<
                size_t, 
                std::vector<std::string>
            >
        >(value, title, handler)
    { }

    virtual void OnRender(float dt) override;
};

// ---
//  属性 vec2
// ---
class PropertyVector2 : public PropertyObject<glm::vec2> {
public:
    PropertyVector2(
        glm::vec2 & value,
        const std::string & title,
        const Handler_t & handler)
        : PropertyObject<glm::vec2>(value, title, handler)
    { }
    
    virtual void OnRender(float dt) override;
};

// ---
//  属性 vec3
// ---
class PropertyVector3 : public PropertyObject<glm::vec3> {
public:
    PropertyVector3(
        glm::vec3 & value,
        const std::string & title,
        const Handler_t & handler)
        : PropertyObject<glm::vec3>(value, title, handler)
    { }

    virtual void OnRender(float dt) override;
};

// ---
//  属性 vec4
// ---
class PropertyVector4 : public PropertyObject<glm::vec4> {
public:
    PropertyVector4(
        glm::vec4 & value,
        const std::string & title,
        const Handler_t & handler)
        : PropertyObject<glm::vec4>(value, title, handler)
    { }

    virtual void OnRender(float dt) override;
};

// ---
//  属性 color4
// ---
class PropertyColor4 : public PropertyObject<glm::vec4> {
public:
    PropertyColor4(
        glm::vec4 & value,
        const std::string & title,
        const Handler_t & handler)
        : PropertyObject<glm::vec4>(value, title, handler)
    { }

    virtual void OnRender(float dt) override;
};