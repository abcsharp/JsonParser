#include "Json.h"

namespace Json
{
	Item::Item(void)
	{
		IsNull_Value=true;
		Type_Value=Type::Null;
		return;
	}

	Item::Item(const Item& LeftRef)
	{
		Type_Value=LeftRef.Type();
		switch(Type_Value){
		case Type::Int:
			Int_Value=LeftRef.Int_Value;
			break;
		case Type::Double:
			Double_Value=LeftRef.Double_Value;
			break;
		case Type::Bool:
			Bool_Value=LeftRef.Bool_Value;
			break;
		case Type::String:
			String_Value=LeftRef.String_Value;
			break;
		case Type::Hash:
			Hash_Value=LeftRef.Hash_Value;
			break;
		case Type::Array:
			Array_Value=LeftRef.Array_Value;
			break;
		}
		IsNull_Value=Type_Value==Type::Null?true:false;
		return;
	}

	Item::Item(Item&& RightRef)
	{
		Type_Value=RightRef.Type();
		switch(Type_Value){
		case Type::Int:
			Int_Value=std::move(RightRef.Int_Value);
			break;
		case Type::Double:
			Double_Value=std::move(RightRef.Double_Value);
			break;
		case Type::Bool:
			Bool_Value=std::move(RightRef.Bool_Value);
			break;
		case Type::String:
			String_Value=std::move(RightRef.String_Value);
			break;
		case Type::Hash:
			Hash_Value=std::move(RightRef.Hash_Value);
			break;
		case Type::Array:
			Array_Value=std::move(RightRef.Array_Value);
			break;
		}
		IsNull_Value=Type_Value==Type::Null?true:false;
		return;
	}

	Item::Item(Json::Type ItemType)
	{
		Type_Value=ItemType;
		switch(ItemType){
		case Type::Int:
			Int_Value.reset(new long long);
			break;
		case Type::Double:
			Double_Value.reset(new double);
			break;
		case Type::Bool:
			Bool_Value.reset(new bool);
			break;
		case Type::String:
			String_Value.reset(new JsonString);
			break;
		case Type::Hash:
			Hash_Value.reset(new JsonHash);
			break;
		case Type::Array:
			Array_Value.reset(new JsonArray);
			break;
		}
		IsNull_Value=ItemType==Type::Null?true:false;
		return;
	}

	Item::Item(const long long& Int):Int_Value(new long long(Int))
	{
		Type_Value=Type::Int;
		return;
	}

	Item::Item(const unsigned long long& Int):Int_Value(new long long(Int))
	{
		Type_Value=Type::Int;
		return;
	}

	Item::Item(const int& Int):Int_Value(new long long(Int))
	{
		Type_Value=Type::Int;
		return;
	}

	Item::Item(const unsigned int& Int):Int_Value(new long long(Int))
	{
		Type_Value=Type::Int;
		return;
	}

	Item::Item(const double& Double):Double_Value(new double(Double))
	{
		Type_Value=Type::Double;
		return;
	}

	Item::Item(const float& Float):Double_Value(new double(Float))
	{
		Type_Value=Type::Double;
		return;
	}

	Item::Item(const bool& Bool):Bool_Value(new bool(Bool))
	{
		Type_Value=Type::Bool;
		return;
	}

	Item::Item(const JsonString& String):String_Value(new JsonString(String))
	{
		Type_Value=Type::String;
		return;
	}

	Item::Item(const JsonHash& Hash):Hash_Value(new JsonHash(Hash))
	{
		Type_Value=Type::Hash;
		return;
	}

	Item::Item(const JsonArray& Array):Array_Value(new JsonArray(Array))
	{
		Type_Value=Type::Array;
		return;
	}

	Item::Item(long long&& Int):Int_Value(new long long(std::move(Int)))
	{
		Type_Value=Type::Int;
		return;
	}

	Item::Item(unsigned long long&& Int):Int_Value(new long long(std::move(Int)))
	{
		Type_Value=Type::Int;
		return;
	}

	Item::Item(int&& Int):Int_Value(new long long(std::move(Int)))
	{
		Type_Value=Type::Int;
		return;
	}

	Item::Item(unsigned int&& Int):Int_Value(new long long(std::move(Int)))
	{
		Type_Value=Type::Int;
		return;
	}

	Item::Item(double&& Double):Double_Value(new double(std::move(Double)))
	{
		Type_Value=Type::Double;
		return;
	}

	Item::Item(float&& Float):Double_Value(new double(std::move(Float)))
	{
		Type_Value=Type::Double;
		return;
	}

	Item::Item(bool&& Bool):Bool_Value(new bool(std::move(Bool)))
	{
		Type_Value=Type::Bool;
		return;
	}

	Item::Item(JsonString&& String):String_Value(new JsonString(std::move(String)))
	{
		Type_Value=Type::String;
		return;
	}

	Item::Item(JsonHash&& Hash):Hash_Value(new JsonHash(std::move(Hash)))
	{
		Type_Value=Type::Hash;
		return;
	}

	Item::Item(JsonArray&& Array):Array_Value(new JsonArray(std::move(Array)))
	{
		Type_Value=Type::Array;
		return;
	}

	Item::~Item(void)
	{
		return;
	}

	Type Item::Type(void)const
	{
		return Type_Value;
	}

	bool Item::IsNull(void)const
	{
		return IsNull_Value;
	}

	long long& Item::Int(void)
	{
		if(Int_Value) return *Int_Value;
		else throw std::exception();
	}

	double& Item::Double(void)
	{
		if(Double_Value) return *Double_Value;
		else throw std::exception();
	}

	bool& Item::Bool(void)
	{
		if(Bool_Value) return *Bool_Value;
		else throw std::exception();
	}

	JsonString& Item::String(void)
	{
		if(String_Value) return *String_Value;
		else throw std::exception();
	}

	JsonHash& Item::Hash(void)
	{
		if(Hash_Value) return *Hash_Value;
		else throw std::exception();
	}

	JsonArray& Item::Array(void)
	{
		if(Array_Value) return *Array_Value;
		else throw std::exception();
	}

	const long long& Item::Int(void)const
	{
		if(Int_Value) return *Int_Value;
		else throw std::exception();
	}

	const double& Item::Double(void)const
	{
		if(Double_Value) return *Double_Value;
		else throw std::exception();
	}

	const bool& Item::Bool(void)const
	{
		if(Bool_Value) return *Bool_Value;
		else throw std::exception();
	}

	const JsonString& Item::String(void)const
	{
		if(String_Value) return *String_Value;
		else throw std::exception();
	}

	const JsonHash& Item::Hash(void)const
	{
		if(Hash_Value) return *Hash_Value;
		else throw std::exception();
	}

	const JsonArray& Item::Array(void)const
	{
		if(Array_Value) return *Array_Value;
		else throw std::exception();
	}

	Item& Item::operator=(const Item& LeftRef)
	{
		Json::Type ItemType=LeftRef.Type();
		switch(ItemType){
		case Type::Int:
			Int_Value=LeftRef.Int_Value;
			break;
		case Type::Double:
			Double_Value=LeftRef.Double_Value;
			break;
		case Type::Bool:
			Bool_Value=LeftRef.Bool_Value;
			break;
		case Type::String:
			String_Value=LeftRef.String_Value;
			break;
		case Type::Hash:
			Hash_Value=LeftRef.Hash_Value;
			break;
		case Type::Array:
			Array_Value=LeftRef.Array_Value;
			break;
		}
		IsNull_Value=ItemType==Type::Null?true:false;
		return *this;
	}

	Item& Item::operator=(Item&& RightRef)
	{
		Type_Value=RightRef.Type();
		switch(Type_Value){
		case Type::Int:
			Int_Value=std::move(RightRef.Int_Value);
			break;
		case Type::Double:
			Double_Value=std::move(RightRef.Double_Value);
			break;
		case Type::Bool:
			Bool_Value=std::move(RightRef.Bool_Value);
			break;
		case Type::String:
			String_Value=std::move(RightRef.String_Value);
			break;
		case Type::Hash:
			Hash_Value=std::move(RightRef.Hash_Value);
			break;
		case Type::Array:
			Array_Value=std::move(RightRef.Array_Value);
			break;
		}
		IsNull_Value=Type_Value==Type::Null?true:false;
		return *this;
	}

	Item::operator long long(void)
	{
		if(Type_Value==Type::Int) return *Int_Value;
		else throw std::exception();
	}

	Item::operator unsigned long long(void)
	{
		if(Type_Value==Type::Int) return *Int_Value;
		else throw std::exception();
	}

	Item::operator int(void)
	{
		if(Type_Value==Type::Int) return *Int_Value;
		else throw std::exception();
	}

	Item::operator unsigned int(void)
	{
		if(Type_Value==Type::Int) return *Int_Value;
		else throw std::exception();
	}

	Item::operator double(void)
	{
		if(Type_Value==Type::Double) return *Double_Value;
		else throw std::exception();
	}

	Item::operator bool(void)
	{
		if(Type_Value==Type::Bool) return *Bool_Value;
		else throw std::exception();
	}

	Item::operator JsonString(void)
	{
		if(Type_Value==Type::String) return *String_Value;
		else throw std::exception();
	}

	Item::operator JsonHash(void)
	{
		if(Type_Value=Type::Hash) return *Hash_Value;
		else throw std::exception();
	}

	Item::operator JsonArray(void)
	{
		if(Type_Value==Type::Array) return *Array_Value;
		else throw std::exception();
	}

	Item::operator const long long(void)const
	{
		if(Type_Value==Type::Int) return *Int_Value;
		else throw std::exception();
	}

	Item::operator const unsigned long long(void)const
	{
		if(Type_Value==Type::Int) return *Int_Value;
		else throw std::exception();
	}

	Item::operator const int(void)const
	{
		if(Type_Value==Type::Int) return *Int_Value;
		else throw std::exception();
	}

	Item::operator const unsigned int(void)const
	{
		if(Type_Value==Type::Int) return *Int_Value;
		else throw std::exception();
	}

	Item::operator const double(void)const
	{
		if(Type_Value==Type::Double) return *Double_Value;
		else throw std::exception();
	}

	Item::operator const float(void)const
	{
		if(Type_Value==Type::Double) return *Double_Value;
		else throw std::exception();
	}

	Item::operator const bool(void)const
	{
		if(Type_Value==Type::Bool) return *Bool_Value;
		else throw std::exception();
	}

	Item::operator const Json::JsonString(void)const
	{
		if(Type_Value==Type::String) return *String_Value;
		else throw std::exception();
	}

	Item::operator const JsonHash(void)const
	{
		if(Type_Value==Type::Hash) return *Hash_Value;
		else throw std::exception();
	}

	Item::operator const JsonArray(void)const
	{
		if(Type_Value==Type::Array) return *Array_Value;
		else throw std::exception();
	}

	Item& Item::operator()(const std::wstring& Key)
	{
		if(Type_Value==Type::Hash) return Hash_Value->at(Key);
		else throw std::exception();
	}

	Item& Item::operator()(const wchar_t*& Key)
	{
		if(Type_Value==Type::Hash) return Hash_Value->at(Key);
		else throw std::exception();
	}

	Item& Item::operator()(const int& Index)
	{
		if(Type_Value==Type::Array) return Array_Value->at(Index);
		else throw std::exception();
	}

	const Item& Item::operator()(const std::wstring& Key)const
	{
		if(Type_Value==Type::Hash) return Hash_Value->at(Key);
		else throw std::exception();
	}

	const Item& Item::operator()(const wchar_t*& Key)const
	{
		if(Type_Value==Type::Hash) return Hash_Value->at(Key);
		else throw std::exception();
	}

	const Item& Item::operator()(const int& Index)const
	{
		if(Type_Value==Type::Array) return Array_Value->at(Index);
		else throw std::exception();
	}

	bool operator==(const Item& Left,const Item& Right)
	{
		if(Left.Type()!=Right.Type()) return false;
		switch(Left.Type()){
		case Type::Null:
			return true;
		case Type::Int:
			return Left.Int()==Right.Int();
		case Type::Double:
			return Left.Double()==Right.Double();
		case Type::Bool:
			return Left.Bool()==Right.Bool();
		case Type::String:
			return Left.String()==Right.String();
		case Type::Hash:
			return Left.Hash()==Right.Hash();
		case Type::Array:
			return Left.Array()==Right.Array();
		}
		throw std::exception();
	}

	bool operator!=(const Item& Left,const Item& Right)
	{
		return !(Left==Right);
	}

}