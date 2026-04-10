#pragma once

#include"Core/pch.h"
#include"Core/Type/String/StringID.h"

namespace VIEngine {
	class VI_API RTTI {
	public:
		RTTI(const char* typeName, const RTTI* parent = nullptr);

		bool IsTypeOf(const RTTI& other) const;
		bool IsDerivedFrom(const RTTI& other) const;

		VI_FORCE_INLINE const char* GetTypeName() const { return mTypeName; }
		VI_FORCE_INLINE const StringID& GetTypeNameID() const { return mTypeNameID; }
		VI_FORCE_INLINE const RTTI* GetParentClass() const { return mParentClass; }
	private:
		const char* mTypeName;
        StringID mTypeNameID;
		const RTTI* mParentClass;
	};
}

#define DECLARE_RTTI \
	public: \
		static const VIEngine::RTTI RunTimeType; \
		virtual const VIEngine::RTTI& GetRunTimeTypeInfo() const;

#define DEFINE_RTTI(typeName, parent) \
	const VIEngine::RTTI typeName::RunTimeType(#typeName, &parent); \
	const VIEngine::RTTI& typeName::GetRunTimeTypeInfo() const { return RunTimeType; }

#define DEFINE_RTTI_NO_PARENT(typeName) \
	const VIEngine::RTTI typeName::RunTimeType(#typeName); \
	const VIEngine::RTTI& typeName::GetRunTimeTypeInfo() const { return RunTimeType; }