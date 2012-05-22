#pragma once
#ifndef __INC_JSON_HPP__
#define __INC_JSON_HPP__
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <regex>
#include <sstream>
#include <memory>
#ifdef _VisualCpp
#define _Export __declspec(dllexport)
#else
#define _Export
#endif

namespace Json
{
	enum _Export Type
	{
		Int,
		Double,
		Bool,
		String,
		Hash,
		Array,
		Null
	};

	class _Export Item;
	typedef _Export std::wstring JsonString;
	typedef _Export std::vector<Item> JsonArray;
	typedef _Export std::map<JsonString,Item> JsonHash;
	typedef _Export std::pair<JsonString,Item> JsonHashPair;

	class _Export Item
	{
	private:
		struct Values
		{
			long long Int_Value;
			double Double_Value;
			bool Bool_Value;
			JsonString String_Value;
			JsonHash Hash_Value;
			JsonArray Array_Value;

			Values(void)
			{
				return;
			}

			Values(const long long& Int):Int_Value(Int)
			{
				return;
			}

			Values(const double& Double):Double_Value(Double)
			{
				return;
			}

			Values(const bool& Bool):Bool_Value(Bool)
			{
				return;
			}

			Values(const JsonString& String):String_Value(String)
			{
				return;
			}

			Values(const wchar_t* String):String_Value(String)
			{
				return;
			}

			Values(const JsonHash& Hash):Hash_Value(Hash)
			{
				return;
			}

			Values(const JsonArray& Array):Array_Value(Array)
			{
				return;
			}

			Values(long long&& Int):Int_Value(Int)
			{
				return;
			}

			Values(double&& Double):Double_Value(Double)
			{
				return;
			}

			Values(bool&& Bool):Bool_Value(Bool)
			{
				return;
			}

			Values(JsonString&& String):String_Value(String)
			{
				return;
			}

			Values(JsonHash&& Hash):Hash_Value(Hash)
			{
				return;
			}

			Values(JsonArray&& Array):Array_Value(Array)
			{
				return;
			}

		};

		std::shared_ptr<Values> Value;
		Type Type_Value;
		bool IsNull_Value;

	public:
		Item(void):Value(std::make_shared<Values>())
		{
			IsNull_Value=true;
			Type_Value=Type::Null;
			return;
		}

		Item(const Item& LeftRef)
		{
			Type_Value=LeftRef.GetType();
			Value=LeftRef.Value;
			IsNull_Value=Type_Value==Type::Null?true:false;
			return;
		}

		Item(Item&& RightRef)
		{
			Type_Value=RightRef.GetType();
			Value=std::move(RightRef.Value);
			IsNull_Value=Type_Value==Type::Null?true:false;
			return;
		}

		Item(Json::Type ItemType):Value(std::make_shared<Values>())
		{
			Type_Value=ItemType;
			IsNull_Value=ItemType==Type::Null?true:false;
			return;
		}

		Item(const long long& Int):Value(std::make_shared<Values>(Int))
		{
			Type_Value=Type::Int;
			return;
		}

		Item(const unsigned long long& Int):Value(std::make_shared<Values>((long long)Int))
		{
			Type_Value=Type::Int;
			return;
		}

		Item(const int& Int):Value(std::make_shared<Values>((long long)Int))
		{
			Type_Value=Type::Int;
			return;
		}

		Item(const unsigned int& Int):Value(std::make_shared<Values>((long long)Int))
		{
			Type_Value=Type::Int;
			return;
		}

		Item(const double& Double):Value(std::make_shared<Values>(Double))
		{
			Type_Value=Type::Double;
			return;
		}

		Item(const float& Float):Value(std::make_shared<Values>((double)Float))
		{
			Type_Value=Type::Double;
			return;
		}

		Item(const bool& Bool):Value(std::make_shared<Values>(Bool))
		{
			Type_Value=Type::Bool;
			return;
		}

		Item(const JsonString& String):Value(std::make_shared<Values>(String))
		{
			Type_Value=Type::String;
			return;
		}

		Item(const wchar_t* String):Value(std::make_shared<Values>(String))
		{
			Type_Value=Type::String;
			return;
		}

		Item(const JsonHash& Hash):Value(std::make_shared<Values>(Hash))
		{
			Type_Value=Type::Hash;
			return;
		}

		Item(const JsonArray& Array):Value(std::make_shared<Values>(Array))
		{
			Type_Value=Type::Array;
			return;
		}

		Item(long long&& Int):Value(std::make_shared<Values>(std::move(Int)))
		{
			Type_Value=Type::Int;
			return;
		}

		Item(unsigned long long&& Int):Value(std::make_shared<Values>(std::move((long long&&)Int)))
		{
			Type_Value=Type::Int;
			return;
		}

		Item(int&& Int):Value(std::make_shared<Values>(std::move((long long&&)Int)))
		{
			Type_Value=Type::Int;
			return;
		}

		Item(unsigned int&& Int):Value(std::make_shared<Values>(std::move((long long&&)Int)))
		{
			Type_Value=Type::Int;
			return;
		}

		Item(double&& Double):Value(std::make_shared<Values>(std::move(Double)))
		{
			Type_Value=Type::Double;
			return;
		}

		Item(float&& Float):Value(std::make_shared<Values>(std::move((double&&)Float)))
		{
			Type_Value=Type::Double;
			return;
		}

		Item(bool&& Bool):Value(std::make_shared<Values>(std::move(Bool)))
		{
			Type_Value=Type::Bool;
			return;
		}

		Item(JsonString&& String):Value(std::make_shared<Values>(std::move(String)))
		{
			Type_Value=Type::String;
			return;
		}

		Item(JsonHash&& Hash):Value(std::make_shared<Values>(std::move(Hash)))
		{
			Type_Value=Type::Hash;
			return;
		}

		Item(JsonArray&& Array):Value(std::make_shared<Values>(std::move(Array)))
		{
			Type_Value=Type::Array;
			return;
		}

		~Item(void)
		{
			return;
		}

		Type GetType(void)const
		{
			return Type_Value;
		}

		bool IsNull(void)const
		{
			return IsNull_Value;
		}

		long long& Int(void)
		{
			return Value->Int_Value;
		}

		double& Double(void)
		{
			return Value->Double_Value;
		}

		bool& Bool(void)
		{
			return Value->Bool_Value;
		}

		JsonString& String(void)
		{
			return Value->String_Value;
		}

		JsonHash& Hash(void)
		{
			return Value->Hash_Value;
		}

		JsonArray& Array(void)
		{
			return Value->Array_Value;
		}

		const long long& Int(void)const
		{
			return Value->Int_Value;
		}

		const double& Double(void)const
		{
			return Value->Double_Value;
		}

		const bool& Bool(void)const
		{
			return Value->Bool_Value;
		}

		const JsonString& String(void)const
		{
			return Value->String_Value;
		}

		const JsonHash& Hash(void)const
		{
			return Value->Hash_Value;
		}

		const JsonArray& Array(void)const
		{
			return Value->Array_Value;
		}

		Item& operator=(const Item& LeftRef)
		{
			Type_Value=LeftRef.GetType();
			Value=LeftRef.Value;
			IsNull_Value=Type_Value==Type::Null?true:false;
			return *this;
		}

		Item& operator=(Item&& RightRef)
		{
			Type_Value=RightRef.GetType();
			Value=std::move(RightRef.Value);
			IsNull_Value=Type_Value==Type::Null?true:false;
			return *this;
		}

		operator long long(void)
		{
			return Value->Int_Value;
		}

		operator unsigned long long(void)
		{
			return Value->Int_Value;
		}

		operator int(void)
		{
			return Value->Int_Value;
		}

		operator unsigned int(void)
		{
			return Value->Int_Value;
		}

		operator double(void)
		{
			return Value->Double_Value;
		}

		operator float(void)
		{
			return Value->Double_Value;
		}

		operator bool(void)
		{
			return Value->Bool_Value;
		}

		operator JsonString(void)
		{
			return Value->String_Value;
		}

		operator JsonHash(void)
		{
			return Value->Hash_Value;
		}

		operator JsonArray(void)
		{
			return Value->Array_Value;
		}

		operator const long long(void)const
		{
			return Value->Int_Value;
		}

		operator const unsigned long long(void)const
		{
			return Value->Int_Value;
		}

		operator const int(void)const
		{
			return Value->Int_Value;
		}

		operator const unsigned int(void)const
		{
			return Value->Int_Value;
		}

		operator const double(void)const
		{
			return Value->Double_Value;
		}

		operator const float(void)const
		{
			return Value->Double_Value;
		}

		operator const bool(void)const
		{
			return Value->Bool_Value;
		}

		operator const Json::JsonString(void)const
		{
			return Value->String_Value;
		}

		operator const JsonHash(void)const
		{
			return Value->Hash_Value;
		}

		operator const JsonArray(void)const
		{
			return Value->Array_Value;
		}

		Item& operator()(const std::wstring& Key)
		{
			return Value->Hash_Value[Key];
		}

		Item& operator()(const wchar_t*& Key)
		{
			return Value->Hash_Value[Key];
		}

		Item& operator()(const int& Index)
		{
			return Value->Array_Value[Index];
		}

		const Item& operator()(const std::wstring& Key)const
		{
			return Value->Hash_Value.at(Key);
		}

		const Item& operator()(const wchar_t*& Key)const
		{
			return Value->Hash_Value.at(Key);
		}

		const Item& operator()(const int& Index)const
		{
			return Value->Array_Value.at(Index);
		}

		Item& operator+=(const Item& Element)
		{
			if(Type_Value!=Type::Array){
				Value=std::make_shared<Values>(JsonArray());
				Type_Value=Type::Array;
			}
			Value->Array_Value.push_back(Element);
			return *this;
		}

		Item& operator+=(Item&& Element)
		{
			if(Type_Value!=Type::Array){
				Value=std::make_shared<Values>(JsonArray());
				Type_Value=Type::Array;
			}
			Value->Array_Value.push_back(std::move(Element));
			return *this;
		}

		Item& operator+=(const JsonArray& Elements)
		{
			if(Type_Value!=Type::Array){
				Value=std::make_shared<Values>(JsonArray());
				Type_Value=Type::Array;
			}
			std::for_each(Elements.cbegin(),Elements.cend(),[&](const Item& Element){Value->Array_Value.push_back(Element);});
			return *this;
		}

		Item& operator+=(JsonArray&& Elements)
		{
			if(Type_Value!=Type::Array){
				Value=std::make_shared<Values>(JsonArray());
				Type_Value=Type::Array;
			}
			std::for_each(Elements.begin(),Elements.end(),[&](Item& Element){Value->Array_Value.push_back(Element);});
			return *this;
		}

	};

	_Export inline bool operator==(const Item& Left,const Item& Right)
	{
		if(Left.GetType()!=Right.GetType()) return false;
		switch(Left.GetType()){
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

	_Export inline bool operator!=(const Item& Left,const Item& Right)
	{
		return !(Left==Right);
	}

	struct IteratorContainer
	{
		Type IteratorType;
		JsonHash::const_iterator Hash;
		JsonArray::const_iterator Array;

		IteratorContainer(JsonHash::const_iterator HashIterator)
		{
			IteratorType=Type::Hash;
			Hash=HashIterator;
			return;
		}

		IteratorContainer(JsonArray::const_iterator ArrayIterator)
		{
			IteratorType=Type::Array;
			Array=ArrayIterator;
			return;
		}

	};

	inline bool ParseBool(JsonString::const_iterator& Char)
	{
		auto Start=Char;
		for(;;Char++) if(*Char==L' '||*Char==L'\t'||*Char==L'\n'||*Char==L'\r'||*Char==L','||*Char==L'}'||*Char==L']') break;
		std::wstring BoolString(Start,Char--);
		if(!BoolString.compare(L"true")) return true;
		else if(!BoolString.compare(L"false")) return false;
		throw std::exception();
	}

	inline JsonString ParseString(JsonString::const_iterator& Char)
	{
		auto Start=++Char;
		std::wistringstream Converter;
		Converter.setf(std::ios::hex,std::ios::basefield);
		for(;;Char++) if(*Char==L'\"'&&*(Char-1)!=L'\\') break;
		std::wstring TempString(Start,Char),String;
		String.reserve(TempString.length());
		for(auto Position=TempString.cbegin();Position!=TempString.cend();Position++){
			if(*Position==L'\\'){
				const std::wstring Pattern=L"\"\\/bfnrtu";
				auto Index=Pattern.find(*++Position);
				if(Index==Pattern.npos) return L"";
				else if(Index<=2) String+=Pattern[Index];
				else if(Index<=7){
					auto Char=Pattern[Index];
					String+=Char==L'b'?L'\b':Char==L'f'?L'\f':Char==L'n'?L'\n':Char==L'r'?L'\r':Char==L't'?L'\t':L' ';
				}else{
					Position+=4;
					Converter.str(JsonString(Position-3,Position+1));
					unsigned int Char;
					(Converter>>Char).clear();
					String+=(wchar_t)Char;
				}
			}else String.push_back(*Position);
		}
		return String;
	}

	inline bool ParseNull(JsonString::const_iterator& Char)
	{
		auto Start=Char;
		for(;;Char++) if(*Char==L' '||*Char==L'\t'||*Char==L'\n'||*Char==L'\r'||*Char==L','||*Char==L'}'||*Char==L']') break;
		std::wstring NullString(Start,Char--);
		if(!NullString.compare(L"null")) return true;
		else return false;
	}

	inline JsonString ToEscapeString(const JsonString& String)
	{
		std::wstring EscapeString;
		std::wostringstream Converter;
		Converter.setf(std::ios::hex,std::ios::basefield);
		EscapeString.reserve(String.length()*2);
		EscapeString+=L"\"";
		for(auto Position=String.cbegin();Position!=String.cend();Position++){
			auto Char=*Position;
			const std::wstring Pattern=L"\"\\/\b\f\n\r\t";
			auto Index=Pattern.find(Char);
			if(Index==Pattern.npos){
				if(Char<=L'\x007F') EscapeString+=Char;
				else{
					Converter.str(JsonString());
					(Converter<<L"\\u"<<(int)Char).clear();
					EscapeString+=Converter.str();
				}
			}else if(Index<=2) EscapeString+=L'\\',EscapeString+=Char;
			else EscapeString+=L'\\',EscapeString+=Char==L'\b'?L'b':Char==L'\f'?L'f':Char==L'\n'?L'n':Char==L'\r'?L'r':Char==L'\t'?L't':L' ';
		}
		EscapeString+=L"\"";
		return EscapeString;
	}

	_Export inline JsonString ToString(const Item& Root)
	{
		std::stack<Item> Level;
		std::stack<IteratorContainer> IteratorLevel;
		std::wstring JsonString;
		std::wostringstream Converter;
		Converter.precision(10);
		Converter.setf(std::ios::scientific);
		JsonString.reserve(1000);
		if(Root.GetType()==Type::Hash){
			JsonString+=L'{';
			IteratorLevel.push(IteratorContainer(Root.Hash().cbegin()));
		}else if(Root.GetType()==Type::Array){
			JsonString+=L'[';
			IteratorLevel.push(IteratorContainer(Root.Array().cbegin()));
		}else if(Root.GetType()==Type::Null) return JsonString;
		else throw std::exception(/*"配列又は連想配列を表す型は、Json::Array\n又はJson::Hashでなければなりません。"*/);
		Level.push(Root);
		while(Level.size()>0){
			Type ObjType=Level.top().GetType();
			if(ObjType==Type::Hash){
				if(IteratorLevel.top().Hash!=Level.top().Hash().cend()){
					JsonString+=L'\"';
					JsonString+=(*IteratorLevel.top().Hash).first;
					JsonString+=L"\":";
					const Item& Member=(*IteratorLevel.top().Hash).second;
					switch(Member.GetType()){
					case Type::Null:
						JsonString+=L"null";
						break;
					case Type::Int:
						Converter<<Member.Int();
						JsonString+=Converter.str();
						Converter.str(Json::JsonString());
						break;
					case Type::Double:
						Converter<<Member.Double();
						JsonString+=Converter.str();
						Converter.str(Json::JsonString());
						break;
					case Type::Bool:
						JsonString+=Member.Bool()?L"true":L"false";
						break;
					case Type::String:
						JsonString+=ToEscapeString(Member.String());
						break;
					case Type::Hash:
						JsonString+=L'{';
						Level.push(Member);
						IteratorLevel.top().Hash++;
						IteratorLevel.push(IteratorContainer(Member.Hash().cbegin()));
						continue;
					case Type::Array:
						JsonString+=L'[';
						Level.push(Member);
						IteratorLevel.top().Hash++;
						IteratorLevel.push(IteratorContainer(Member.Array().cbegin()));
						continue;
					}
					JsonString+=L',';
					IteratorLevel.top().Hash++;
				}else{
					JsonString[JsonString.length()-1]=L'}';
					Level.pop();
					IteratorLevel.pop();
					if(Level.size()>0) JsonString+=L",";
				}
			}else if(ObjType==Type::Array){
				if(IteratorLevel.top().Array!=Level.top().Array().cend()){
					const Item& Member=*IteratorLevel.top().Array;
					switch(Member.GetType()){
					case Type::Null:
						JsonString+=L"null";
						break;
					case Type::Int:
						Converter<<Member.Int();
						JsonString+=Converter.str();
						Converter.str(Json::JsonString());
						break;
					case Type::Double:
						Converter<<Member.Double();
						JsonString+=Converter.str();
						Converter.str(Json::JsonString());
						break;
					case Type::Bool:
						JsonString+=Member.Bool()?L"true":L"false";
						break;
					case Type::String:
						JsonString+=ToEscapeString(Member.String());
						break;
					case Type::Hash:
						JsonString+=L'{';
						Level.push(Member);
						IteratorLevel.top().Array++;
						IteratorLevel.push(IteratorContainer(Member.Hash().cbegin()));
						continue;
					case Type::Array:
						JsonString+=L'[';
						Level.push(Member);
						IteratorLevel.top().Array++;
						IteratorLevel.push(IteratorContainer(Member.Array().cbegin()));
						continue;
					}
					JsonString+=L',';
					IteratorLevel.top().Array++;
				}else{
					JsonString[JsonString.length()-1]=L']';
					Level.pop();
					IteratorLevel.pop();
					if(Level.size()>0) JsonString+=L',';
				}
			}else throw std::exception(/*"配列又は連想配列を表す型は、Json::Array\n又はJson::Hashでなければなりません。"*/);
		}
		return JsonString;
	}

	_Export inline Item Parse(const JsonString& JsonString)
	{
		auto Char=JsonString.cbegin();
		std::stack<Item> Level;
		Item Root;
		std::wistringstream Converter;
		Converter.precision(10);
		do{
			if(*Char==L'{') Root=Item(Type::Hash);
			else if(*Char==L'[') Root=Item(Type::Array);
			else if(*Char!=L' '&&*Char!=L'\t'&&*Char!=L'\n'&&*Char!=L'\r') throw std::exception(/*"不正な文字が含まれています。"*/);
		}while(Root.GetType()==Type::Null&&++Char!=JsonString.cend());
		Level.push(Root);
		do{
			Char++;
			if(*Char==L','||*Char==L' '||*Char==L'\t'||*Char==L'\n'||*Char==L'\r') continue;
			Type ObjType=Level.top().GetType();
			if(ObjType==Type::Hash){
				std::wstring Key;
				if(*Char==L'\"'){
					Key=ParseString(Char);
					for(;*Char!=L':';Char++) continue;
					for(Char++;*Char==L' '||*Char==L'\t'||*Char==L'\n'||*Char==L'\r';Char++) continue;
				}
				if(*Char==L'\"'){
					Level.top().Hash().insert(std::make_pair(Key,Item(ParseString(Char))));
				}else if(*Char==L'-'||(*Char>=L'0'&&*Char<=L'9')){
					auto Start=Char;
					for(;;Char++) if(*Char==L' '||*Char==L'\t'||*Char==L'\n'||*Char==L'\r'||*Char==L','||*Char==L'}'||*Char==L']') break;
					if(std::regex_match(Start,Char,std::wregex(L"-?\\d+"))){
						Converter.str(std::wstring(Start,Char--));
						long long Temp;
						Converter>>Temp;
						Level.top().Hash().insert(std::make_pair(Key,Item(Temp)));
					}else if(std::regex_match(Start,Char,std::wregex(L"-?\\d+\\.\\d+([eE][+-]\\d+)?"))){
						Converter.str(std::wstring(Start,Char--));
						double Temp;
						Converter>>Temp;
						Level.top().Hash().insert(std::make_pair(Key,Item(Temp)));
					}else throw std::exception(/*"数字以外の文字が入っている、または不正な数値形式の文字列です。\nJSONの数値文字列は10進数で記述しなければなりません。"*/);
				}else if(*Char==L't'||*Char==L'f'){
					Level.top().Hash().insert(std::make_pair(Key,Item(ParseBool(Char))));
				}else if(*Char==L'{'){
					Item Obj(Type::Hash);
					Level.top().Hash().insert(std::make_pair(Key,Obj));
					Level.push(Obj);
				}else if(*Char==L'['){
					Item Obj(Type::Array);
					Level.top().Hash().insert(std::make_pair(Key,Obj));
					Level.push(Obj);
				}else if(*Char==L'n'){
					Level.top().Hash().insert(std::make_pair(Key,ParseNull(Char)?Item(Type::Null):throw std::exception()));
				}else if(*Char==L'}') Level.pop();
			}else if(ObjType==Type::Array){
				if(*Char==L'\"'){
					Level.top().Array().push_back(Item(ParseString(Char)));
				}else if(*Char==L'-'||(*Char>=L'0'&&*Char<=L'9')){
					auto Start=Char;
					for(;;Char++) if(*Char==L' '||*Char==L'\t'||*Char==L'\n'||*Char==L'\r'||*Char==L','||*Char==L'}'||*Char==L']') break;
					if(std::regex_match(Start,Char,std::wregex(L"-?\\d+"))){
						Converter.str(std::wstring(Start,Char));
						long long Temp;
						Converter>>Temp;
						Level.top().Array().push_back(Item(Temp));
					}else if(std::regex_match(Start,Char,std::wregex(L"-?\\d+\\.\\d+([eE][+-]\\d+)?"))){
						Converter.str(std::wstring(Start,Char));
						double Temp;
						Converter>>Temp;
						Level.top().Array().push_back(Item(Temp));
					}else throw std::exception(/*"数字以外の文字が入っている、または不正な数値形式の文字列です。\nJSONの数値文字列は10進数で記述しなければなりません。"*/);
					Char--;
				}else if(*Char==L't'||*Char==L'f'){
					Level.top().Array().push_back(Item(ParseBool(Char)));
				}else if(*Char==L'{'){
					Item Obj(Type::Hash);
					Level.top().Array().push_back(Obj);
					Level.push(Obj);
				}else if(*Char==L'['){
					Item Obj(Type::Array);
					Level.top().Array().push_back(Obj);
					Level.push(Obj);
				}else if(*Char==L'n'){
					Level.top().Array().push_back(ParseNull(Char)?Item(Type::Null):throw std::exception());
				}else if(*Char==L']') Level.pop();
			}
		}while(Level.size()!=0&&Char!=JsonString.cend());
		return Root;
	}

}
#endif