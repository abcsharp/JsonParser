#include <vector>
#include <string>
#include <map>
#include <stack>
#include <regex>
#include <sstream>
#include <tuple>
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
	typedef std::tuple<long long,double,bool,JsonString,JsonHash,JsonArray> JsonValue;

	class _Export Item
	{
	private:
		std::shared_ptr<JsonValue> Value;
		Type Type_Value;
		bool IsNull_Value;

		std::shared_ptr<JsonValue> InitValue(long long Int=0LL,double Double=0.0,bool Bool=false,JsonString String=JsonString(),JsonHash Hash=JsonHash(),JsonArray Array=JsonArray());
		
	public:
		Item(void);
		Item(const Item& LeftRef);
		Item(Item&& RightRef);
		Item(Type ItemType);
		Item(const long long& Int);
		Item(const unsigned long long& Int);
		Item(const int& Int);
		Item(const unsigned int& Int);
		Item(const double& Double);
		Item(const float& Float);
		Item(const bool& Bool);
		Item(const JsonString& String);
		Item(const JsonHash& Hash);
		Item(const JsonArray& Array);
		Item(long long&& Int);
		Item(unsigned long long&& Int);
		Item(int&& Int);
		Item(unsigned int&& Int);
		Item(double&& Double);
		Item(float&& Float);
		Item(bool&& Bool);
		Item(JsonString&& String);
		Item(JsonHash&& Hash);
		Item(JsonArray&& Array);
		~Item(void);
		Type Type(void)const;
		bool IsNull(void)const;
		long long& Int(void);
		double& Double(void);
		bool& Bool(void);
		JsonString& String(void);
		JsonHash& Hash(void);
		JsonArray& Array(void);
		const long long& Int(void)const;
		const double& Double(void)const;
		const bool& Bool(void)const;
		const JsonString& String(void)const;
		const JsonHash& Hash(void)const;
		const JsonArray& Array(void)const;
		Item& operator=(const Item& LeftRef);
		Item& operator=(Item&& RightRef);
		operator long long(void);
		operator unsigned long long(void);
		operator int(void);
		operator unsigned int(void);
		operator double(void);
		operator float(void);
		operator bool(void);
		operator JsonString(void);
		operator JsonHash(void);
		operator JsonArray(void);
		operator const long long(void)const;
		operator const unsigned long long(void)const;
		operator const int(void)const;
		operator const unsigned int(void)const;
		operator const double(void)const;
		operator const float(void)const;
		operator const bool(void)const;
		operator const JsonString(void)const;
		operator const JsonHash(void)const;
		operator const JsonArray(void)const;
		Item& operator()(const std::wstring& Key);
		Item& operator()(const wchar_t*& Key);
		Item& operator()(const int& Index);
		const Item& operator()(const std::wstring& Key)const;
		const Item& operator()(const wchar_t*& Key)const;
		const Item& operator()(const int& Index)const;
		bool operator!(void)const;

	};

	_Export bool operator==(const Item& Left,const Item& Right);
	_Export bool operator!=(const Item& Left,const Item& Right);

	class _Export Parser
	{
	private:
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

		bool ParseBool(std::wstring::const_iterator& Char);
		std::wstring ParseString(std::wstring::const_iterator& Char);
		bool ParseNull(std::wstring::const_iterator& Char);
		std::wstring ToEscapeString(const std::wstring& String);

	public:
		std::wstring Create(const Item& Root);
		Item Parse(const std::wstring& JsonString);

	};
	
	/*
	_Export Item Parse(const std::wstring& JsonString);
	_Export std::wstring ToString(const Item& Obj);
	*/

	Item::Item(void):Value(InitValue())
	{
		IsNull_Value=true;
		Type_Value=Type::Null;
		return;
	}

	Item::Item(const Item& LeftRef)
	{
		Type_Value=LeftRef.Type();
		Value=LeftRef.Value;
		IsNull_Value=Type_Value==Type::Null?true:false;
		return;
	}

	Item::Item(Item&& RightRef)
	{
		Type_Value=RightRef.Type();
		Value=std::move(RightRef.Value);
		IsNull_Value=Type_Value==Type::Null?true:false;
		return;
	}

	Item::Item(Json::Type ItemType):Value(InitValue())
	{
		Type_Value=ItemType;
		IsNull_Value=ItemType==Type::Null?true:false;
		return;
	}

	Item::Item(const long long& Int):Value(InitValue(long long(Int)))
	{
		Type_Value=Type::Int;
		return;
	}

	Item::Item(const unsigned long long& Int):Value(InitValue(long long(Int)))
	{
		Type_Value=Type::Int;
		return;
	}

	Item::Item(const int& Int):Value(InitValue(long long(Int)))
	{
		Type_Value=Type::Int;
		return;
	}

	Item::Item(const unsigned int& Int):Value(InitValue(long long(Int)))
	{
		Type_Value=Type::Int;
		return;
	}

	Item::Item(const double& Double):Value(InitValue(0LL,double(Double)))
	{
		Type_Value=Type::Double;
		return;
	}

	Item::Item(const float& Float):Value(InitValue(0LL,double(Float)))
	{
		Type_Value=Type::Double;
		return;
	}

	Item::Item(const bool& Bool):Value(InitValue(0LL,0.0,bool(Bool)))
	{
		Type_Value=Type::Bool;
		return;
	}

	Item::Item(const JsonString& String):Value(InitValue(0LL,0.0,false,JsonString(String)))
	{
		Type_Value=Type::String;
		return;
	}

	Item::Item(const JsonHash& Hash):Value(InitValue(0LL,0.0,false,JsonString(),JsonHash(Hash)))
	{
		Type_Value=Type::Hash;
		return;
	}

	Item::Item(const JsonArray& Array):Value(InitValue(0LL,0.0,false,JsonString(),JsonHash(),JsonArray(Array)))
	{
		Type_Value=Type::Array;
		return;
	}

	Item::Item(long long&& Int):Value(InitValue(long long(std::move(Int))))
	{
		Type_Value=Type::Int;
		return;
	}

	Item::Item(unsigned long long&& Int):Value(InitValue(long long(std::move(Int))))
	{
		Type_Value=Type::Int;
		return;
	}

	Item::Item(int&& Int):Value(InitValue(long long(std::move(Int))))
	{
		Type_Value=Type::Int;
		return;
	}

	Item::Item(unsigned int&& Int):Value(InitValue(long long(std::move(Int))))
	{
		Type_Value=Type::Int;
		return;
	}

	Item::Item(double&& Double):Value(InitValue(0LL,double(std::move(Double))))
	{
		Type_Value=Type::Double;
		return;
	}

	Item::Item(float&& Float):Value(InitValue(0LL,double(std::move(Float))))
	{
		Type_Value=Type::Double;
		return;
	}

	Item::Item(bool&& Bool):Value(InitValue(0LL,0.0,bool(std::move(Bool))))
	{
		Type_Value=Type::Bool;
		return;
	}

	Item::Item(JsonString&& String):Value(InitValue(0LL,0.0,false,JsonString(std::move(String))))
	{
		Type_Value=Type::String;
		return;
	}

	Item::Item(JsonHash&& Hash):Value(InitValue(0LL,0.0,false,JsonString(),JsonHash(std::move(Hash))))
	{
		Type_Value=Type::Hash;
		return;
	}

	Item::Item(JsonArray&& Array):Value(InitValue(0LL,0.0,false,JsonString(),JsonHash(),JsonArray(std::move(Array))))
	{
		Type_Value=Type::Array;
		return;
	}

	Item::~Item(void)
	{
		return;
	}

	std::shared_ptr<JsonValue> Item::InitValue(long long Int,double Double,bool Bool,JsonString String,JsonHash Hash,JsonArray Array)
	{
		return std::make_shared<JsonValue>(Int,Double,Bool,String,Hash,Array);
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
		return std::get<0>(*Value);
	}

	double& Item::Double(void)
	{
		return std::get<1>(*Value);
	}

	bool& Item::Bool(void)
	{
		return std::get<2>(*Value);
	}

	JsonString& Item::String(void)
	{
		return std::get<3>(*Value);
	}

	JsonHash& Item::Hash(void)
	{
		return std::get<4>(*Value);
	}

	JsonArray& Item::Array(void)
	{
		return std::get<5>(*Value);
	}

	const long long& Item::Int(void)const
	{
		return std::get<0>(*Value);
	}

	const double& Item::Double(void)const
	{
		return std::get<1>(*Value);
	}

	const bool& Item::Bool(void)const
	{
		return std::get<2>(*Value);
	}

	const JsonString& Item::String(void)const
	{
		return std::get<3>(*Value);
	}

	const JsonHash& Item::Hash(void)const
	{
		return std::get<4>(*Value);
	}

	const JsonArray& Item::Array(void)const
	{
		return std::get<5>(*Value);
	}

	Item& Item::operator=(const Item& LeftRef)
	{
		Json::Type ItemType=LeftRef.Type();
		Value=LeftRef.Value;
		IsNull_Value=ItemType==Type::Null?true:false;
		return *this;
	}

	Item& Item::operator=(Item&& RightRef)
	{
		Type_Value=RightRef.Type();
		Value=std::move(RightRef.Value);
		IsNull_Value=Type_Value==Type::Null?true:false;
		return *this;
	}

	Item::operator long long(void)
	{
		return std::get<0>(*Value);
	}

	Item::operator unsigned long long(void)
	{
		return std::get<0>(*Value);
	}

	Item::operator int(void)
	{
		return std::get<0>(*Value);
	}

	Item::operator unsigned int(void)
	{
		return std::get<0>(*Value);
	}

	Item::operator double(void)
	{
		return std::get<1>(*Value);
	}

	Item::operator float(void)
	{
		return std::get<1>(*Value);
	}

	Item::operator bool(void)
	{
		return std::get<2>(*Value);
	}

	Item::operator JsonString(void)
	{
		return std::get<3>(*Value);
	}

	Item::operator JsonHash(void)
	{
		return std::get<4>(*Value);
	}

	Item::operator JsonArray(void)
	{
		return std::get<5>(*Value);
	}

	Item::operator const long long(void)const
	{
		return std::get<0>(*Value);
	}

	Item::operator const unsigned long long(void)const
	{
		return std::get<0>(*Value);
	}

	Item::operator const int(void)const
	{
		return std::get<0>(*Value);
	}

	Item::operator const unsigned int(void)const
	{
		return std::get<0>(*Value);
	}

	Item::operator const double(void)const
	{
		return std::get<1>(*Value);
	}

	Item::operator const float(void)const
	{
		return std::get<1>(*Value);
	}

	Item::operator const bool(void)const
	{
		return std::get<2>(*Value);
	}

	Item::operator const Json::JsonString(void)const
	{
		return std::get<3>(*Value);
	}

	Item::operator const JsonHash(void)const
	{
		return std::get<4>(*Value);
	}

	Item::operator const JsonArray(void)const
	{
		return std::get<5>(*Value);
	}

	Item& Item::operator()(const std::wstring& Key)
	{
		return std::get<4>(*Value)[Key];
	}

	Item& Item::operator()(const wchar_t*& Key)
	{
		return std::get<4>(*Value)[Key];
	}

	Item& Item::operator()(const int& Index)
	{
		return std::get<5>(*Value)[Index];
	}

	const Item& Item::operator()(const std::wstring& Key)const
	{
		return std::get<4>(*Value).at(Key);
	}

	const Item& Item::operator()(const wchar_t*& Key)const
	{
		return std::get<4>(*Value).at(Key);
	}

	const Item& Item::operator()(const int& Index)const
	{
		return std::get<5>(*Value).at(Index);
	}

	bool Item::operator!(void)const
	{
		return IsNull_Value;
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

	bool Parser::ParseBool(std::wstring::const_iterator& Char)
	{
		auto Start=Char;
		for(;;Char++) if(*Char==L' '||*Char==L'\t'||*Char==L'\n'||*Char==L'\r'||*Char==L','||*Char==L'}'||*Char==L']') break;
		std::wstring BoolString(Start,Char--);
		if(!BoolString.compare(L"true")) return true;
		else if(!BoolString.compare(L"false")) return false;
		throw std::exception();
	}

	std::wstring Parser::ParseString(std::wstring::const_iterator& Char)
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

	bool Parser::ParseNull(std::wstring::const_iterator& Char)
	{
		auto Start=Char;
		for(;;Char++) if(*Char==L' '||*Char==L'\t'||*Char==L'\n'||*Char==L'\r'||*Char==L','||*Char==L'}'||*Char==L']') break;
		std::wstring NullString(Start,Char--);
		if(!NullString.compare(L"null")) return true;
		else return false;
	}

	std::wstring Parser::ToEscapeString(const std::wstring& String)
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

	std::wstring Parser::Create(const Item& Root)
	{
		std::stack<const Item> Level;
		std::stack<IteratorContainer> IteratorLevel;
		std::wstring JsonString;
		std::wostringstream Converter;
		Converter.precision(10);
		Converter.setf(std::ios::scientific);
		JsonString.reserve(1000);
		if(Root.Type()==Type::Hash){
			JsonString+=L'{';
			IteratorLevel.push(IteratorContainer(Root.Hash().cbegin()));
		}else if(Root.Type()==Type::Array){
			JsonString+=L'[';
			IteratorLevel.push(IteratorContainer(Root.Array().cbegin()));
		}else if(Root.Type()==Type::Null) return JsonString;
		else throw std::exception("配列又は連想配列を表す型は、Json::Array\n又はJson::Hashでなければなりません。");
		Level.push(Root);
		while(Level.size()>0){
			Type ObjType=Level.top().Type();
			if(ObjType==Type::Hash){
				if(IteratorLevel.top().Hash!=Level.top().Hash().cend()){
					JsonString+=L'\"';
					JsonString+=(*IteratorLevel.top().Hash).first;
					JsonString+=L"\":";
					const Item& Member=(*IteratorLevel.top().Hash).second;
					switch(Member.Type()){
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
					switch(Member.Type()){
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
					IteratorLevel.top().Hash++;
				}else{
					JsonString[JsonString.length()-1]=L']';
					Level.pop();
					IteratorLevel.pop();
					if(Level.size()>0) JsonString+=L',';
				}
			}else throw std::exception("配列又は連想配列を表す型は、Json::Array\n又はJson::Hashでなければなりません。");
		}
		return JsonString;
	}

	Item Parser::Parse(const std::wstring& JsonString)
	{
		auto Char=JsonString.cbegin();
		std::stack<Item> Level;
		Item Root;
		std::wistringstream Converter;
		Converter.precision(10);
		do{
			if(*Char==L'{') Root=Item(Type::Hash);
			else if(*Char==L'[') Root=Item(Type::Array);
			else if(*Char!=L' '&&*Char!=L'\t'&&*Char!=L'\n'&&*Char!=L'\r') throw std::exception("不正な文字が含まれています。");
		}while(Root.Type()==Type::Null&&++Char!=JsonString.cend());
		Level.push(Root);
		do{
			Char++;
			if(*Char==L','||*Char==L' '||*Char==L'\t'||*Char==L'\n'||*Char==L'\r') continue;
			Type ObjType=Level.top().Type();
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
					}else throw std::exception("数字以外の文字が入っている、または不正な数値形式の文字列です。\nJSONの数値文字列は10進数で記述しなければなりません。");
				}else if(*Char==L't'||*Char==L'f'){
					Level.top().Hash().insert(std::make_pair(Key,Item(ParseBool(Char))));
				}else if(*Char==L'{'){
					Item& Obj=Item(Type::Hash);
					Level.top().Hash().insert(std::make_pair(Key,Obj));
					Level.push(Obj);
				}else if(*Char==L'['){
					Item& Obj=Item(Type::Array);
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
					}else throw std::exception("数字以外の文字が入っている、または不正な数値形式の文字列です。\nJSONの数値文字列は10進数で記述しなければなりません。");
					Char--;
				}else if(*Char==L't'||*Char==L'f'){
					Level.top().Array().push_back(Item(ParseBool(Char)));
				}else if(*Char==L'{'){
					Item& Obj=Item(Type::Hash);
					Level.top().Array().push_back(Obj);
					Level.push(Obj);
				}else if(*Char==L'['){
					Item& Obj=Item(Type::Array);
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