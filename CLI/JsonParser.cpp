#include "stdafx.h"
#include "Json.h"

namespace Json{

	JsonParser::JsonParser(void)
	{
		return;
	}

	JsonParser::~JsonParser(void)
	{
		return;
	}

	void JsonParser::ClearCache(bool IsActivateGC)
	{
		return;
	}
	
	String^ JsonParser::ParseString(void)
	{
		Pos++;
		StringBuilder^ Value=gcnew StringBuilder();
		for(Pos;Raw[Pos]!=L'\"';Pos++){
			if(Raw[Pos]==L'\\'){
				Pos++;
				if(Raw[Pos]==L'u'){
					Pos++;
					Value->Append((wchar_t)UInt16::Parse(Raw->Substring(Pos,4),Globalization::NumberStyles::HexNumber));
					Pos=Pos+3;
				}else if(Raw[Pos]==L'\"') Value->Append(L'\"');
				else if(Raw[Pos]==L'\\') Value->Append(L'\\');
				else if(Raw[Pos]==L'/') Value->Append(L'/');
				else if(Raw[Pos]==L'b') Value->Append(L'\b');
				else if(Raw[Pos]==L'f') Value->Append(L'\f');
				else if(Raw[Pos]==L'n') Value->Append(L'\n');
				else if(Raw[Pos]==L'r') Value->Append(L'\r');
				else if(Raw[Pos]==L't') Value->Append(L'\t');
			}else Value->Append(Raw[Pos]);
		}
		return Value->ToString();
	}

	__int64 JsonParser::ParseInt(String^ Raw)
	{
		__int64 Value;
		Value=__int64::Parse(Raw);
		return Value;
	}

	double JsonParser::ParseDouble(String^ Raw)
	{
		double Value;
		Value=double::Parse(Raw);
		return Value;
	}

	bool JsonParser::ParseBoolean(void)
	{
		int Start=Pos;
		for(Pos;;Pos++) if(Raw[Pos]==L' '||Raw[Pos]==L'\t'||Raw[Pos]==L'\n'||Raw[Pos]==L'\r'||Raw[Pos]==L','||Raw[Pos]==L'}'||Raw[Pos]==L']') break;
		String^ Str=Raw->Substring(Start,Pos-Start);
		Pos--;
		return bool::Parse(Str);
	}

	Object^ JsonParser::ParseNull(void)
	{
		int Start=Pos;
		for(Pos;;Pos++) if(Raw[Pos]==L' '||Raw[Pos]==L'\t'||Raw[Pos]==L'\n'||Raw[Pos]==L'\r'||Raw[Pos]==L','||Raw[Pos]==L'}'||Raw[Pos]==L']') break;
		String^ Str;
		if((Str=Raw->Substring(Start,Pos-Start))==L"null") return nullptr;
		else throw gcnew FormatException("\""+Str+"\""+"は不正な形式のnull型文字列です。");
	}

	Object^ JsonParser::Parse(String^ DataString)
	{
		Pos=0;
		Root=nullptr;
		Raw=String::Copy(DataString);
		Bracket=gcnew Stack<Object^>();
		while(Root==nullptr){
			if(Raw[Pos]==L'{'){
				Root=gcnew JsonHash();
				break;
			}else if(Raw[Pos]==L'['){
				Root=gcnew JsonArray();
				break;
			}else if(Raw[Pos]!=L' '&&Raw[Pos]!=L'\t'&&Raw[Pos]!=L'\n'&&Raw[Pos]!=L'\r'){
				throw gcnew FormatException("不正な文字が発見されました。位置:"+Pos.ToString()+" 文字:"+Raw[Pos].ToString());
			}
			Pos++;
		}
		Bracket->Push(Root);
		do{
			Pos++;
			if(Raw[Pos]==L','||Raw[Pos]==L' '||Raw[Pos]==L'\t'||Raw[Pos]==L'\n'||Raw[Pos]==L'\r') continue;
			Type^ ObjType=Bracket->Peek()->GetType();
			if(ObjType==JsonHash::typeid){
				String^ Key;
				if(Raw[Pos]==L'\"'){
					Key=ParseString();
					for(Pos;Raw[Pos]!=L':';Pos++) continue;
					for(Pos=Pos+1;Raw[Pos]==L' '||Raw[Pos]==L'\t'||Raw[Pos]==L'\n'||Raw[Pos]==L'\r';Pos++) continue;
				}
				if(Raw[Pos]==L'\"'){
					((JsonHash^)Bracket->Peek())->Add(Key,ParseString());
				}else if(Raw[Pos]==L'-'||(Raw[Pos]>=L'0'&&Raw[Pos]<=L'9')){
					int Start=Pos;
					for(Pos;;Pos++) if(Raw[Pos]==L' '||Raw[Pos]==L'\t'||Raw[Pos]==L'\n'||Raw[Pos]==L'\r'||Raw[Pos]==L','||Raw[Pos]==L'}'||Raw[Pos]==L']') break;
					String^ Input=Raw->Substring(Start,Pos-Start);
					if(Regex::IsMatch(Input,L"-?\\d+")) ((JsonHash^)Bracket->Peek())->Add(Key,ParseInt(Input));
					else if(Regex::IsMatch(Input,L"-?\\d+\\.\\d+([eE][+-]\\d+)?")) ((JsonHash^)Bracket->Peek())->Add(Key,ParseDouble(Input));
					else throw gcnew FormatException("数字以外の文字が入っている、または不正な数値形式の文字列です。\nJSONの数値文字列は10進数で記述しなければなりません。");
					delete Input;
					Pos--;
				}else if(Raw[Pos]==L't'||Raw[Pos]==L'f'){
					((JsonHash^)Bracket->Peek())->Add(Key,ParseBoolean());
				}else if(Raw[Pos]==L'{'){
					JsonHash^ Obj=gcnew JsonHash();
					((JsonHash^)Bracket->Peek())->Add(Key,Obj);
					Bracket->Push(Obj);
				}else if(Raw[Pos]==L'['){
					JsonArray^ Ary=gcnew JsonArray();
					((JsonHash^)Bracket->Peek())->Add(Key,Ary);
					Bracket->Push(Ary);
				}else if(Raw[Pos]==L'n'){
					((JsonHash^)Bracket->Peek())->Add(Key,ParseNull());
				}else if(Raw[Pos]==L'}') Bracket->Pop();
			}else if(ObjType==JsonArray::typeid){
				if(Raw[Pos]==L'\"'){
					((JsonArray^)Bracket->Peek())->Add(ParseString());
				}else if(Raw[Pos]==L'-'||(Raw[Pos]>=L'0'&&Raw[Pos]<=L'9')){
					int Start=Pos;
					for(Pos;;Pos++) if(Raw[Pos]==L' '||Raw[Pos]==L'\t'||Raw[Pos]==L'\n'||Raw[Pos]==L'\r'||Raw[Pos]==L','||Raw[Pos]==L'}'||Raw[Pos]==L']') break;
					String^ Input=Raw->Substring(Start,Pos-Start);
					if(Regex::IsMatch(Input,L"-?\\d+")) ((JsonArray^)Bracket->Peek())->Add(ParseInt(Input));
					else if(Regex::IsMatch(Input,L"-?\\d+\\.\\d+([eE][+-]\\d+)?")) ((JsonArray^)Bracket->Peek())->Add(ParseDouble(Input));
					else throw gcnew FormatException("数字以外の文字が入っている、または不正な数値形式の文字列です。\nJSONの数値文字列は10進数で記述しなければなりません。");
					delete Input;
					Pos--;
				}else if(Raw[Pos]==L't'||Raw[Pos]==L'f'){
					((JsonArray^)Bracket->Peek())->Add(ParseBoolean());
				}else if(Raw[Pos]==L'{'){
					JsonHash^ Obj=gcnew JsonHash();
					((JsonArray^)Bracket->Peek())->Add(Obj);
					Bracket->Push(Obj);
				}else if(Raw[Pos]==L'['){
					JsonArray^ Ary=gcnew JsonArray();
					((JsonArray^)Bracket->Peek())->Add(Ary);
					Bracket->Push(Ary);
				}else if(Raw[Pos]==L'n'){
					((JsonArray^)Bracket->Peek())->Add(ParseNull());
				}else if(Raw[Pos]==L']') Bracket->Pop();
			}
			delete ObjType;
		}while(Bracket->Count!=0);
		return Root;
	}
}