#include"Core/Type/Object/RTTI.h"

namespace VIEngine {
	RTTI::RTTI(const char* typeName, const RTTI* parent) : mTypeName(typeName), mTypeNameID(typeName), mParentClass(parent) {
	}

	bool RTTI::IsTypeOf(const RTTI& other) const {
		return mTypeNameID == other.GetTypeNameID();
	}

	bool RTTI::IsDerivedFrom(const RTTI& other) const {
		const RTTI* parent = this;

		while (parent) {
			if (parent->GetTypeNameID() == other.GetTypeNameID()) {
				return true;
			}

			parent = parent->mParentClass;
		}

		return false;
	}
}