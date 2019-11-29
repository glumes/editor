#pragma once

#include "../../include.h"
#include "../interface/serializer.h"

class Res {
public:
    enum TypeEnum {
        kNull,      //  无
        kTxt,       //  文本
        kImg,       //  图片
        kMap,       //  地图
        kFont,      //  字体
        kObj,       //  对象
        kVar,       //  变量
        kBlueprint, //  蓝图
    };

    class Ref {
    public:
        Ref(Res * owner);
        ~Ref();

        Ref * Clone();
        bool IsModify();
        void SetModify();

        template <class T>
        T Load()
        {
            ASSERT_LOG(_owner != nullptr, "");
            _modify = false;
            return std::any_cast<T>(_owner->Load());
        }

    private:
        Ref(const Ref & other) = delete;
        Ref & operator=(const Ref & other) = delete;

    private:
        Res * _owner;
        bool  _modify;
    };

public:
    Res(uint id);
    ~Res();

    std::any Load();

    Ref* AppendRef();
    void DeleteRef(Ref * ref);

    void SetType(TypeEnum type);
    TypeEnum GetType();

    void BindMeta(uint                val);
    void BindMeta(const std::string & val);

    std::string GetPath();
    uint GetRefCount();
    uint GetID();

private:
    void WakeRefs();

private:
    uint                _id;
    TypeEnum            _type;  //  标签
    std::vector<Ref *>  _refs;  //  引用集
    std::string         _metas; //  字符元数据
    uint                _metai; //  数值元数据
};