#include "stdafx.h"
#include "Json.h"

namespace Json{

	String^ Json::ParseString(void)
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

	__int64 Json::ParseInt(String^ Raw)
	{
		__int64 Value;
		Value=__int64::Parse(Raw);
		return Value;
	}

	double Json::ParseDouble(String^ Raw)
	{
		double Value;
		Value=double::Parse(Raw);
		return Value;
	}

	bool Json::ParseBoolean(void)
	{
		int Start=Pos;
		for(Pos;;Pos++) if(Raw[Pos]==L' '||Raw[Pos]==L'\t'||Raw[Pos]==L'\n'||Raw[Pos]==L'\r'||Raw[Pos]==L','||Raw[Pos]==L'}'||Raw[Pos]==L']') break;
		String^ Str=Raw->Substring(Start,Pos-Start);
		Pos--;
		return bool::Parse(Str);
	}

	Object^ Json::ParseNull(void)
	{
		int Start=Pos;
		for(Pos;;Pos++) if(Raw[Pos]==L' '||Raw[Pos]==L'\t'||Raw[Pos]==L'\n'||Raw[Pos]==L'\r'||Raw[Pos]==L','||Raw[Pos]==L'}'||Raw[Pos]==L']') break;
		String^ Str;
		if((Str=Raw->Substring(Start,Pos-Start))==L"null") return nullptr;
		else throw gcnew FormatException("\""+Str+"\""+"は不正な形式のnull型文字列です。");
	}

	Object^ Json::Parse(String^ DataString)
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

	String^ Json::CreateString(String^ Raw)
	{
		StringBuilder^ Value=gcnew StringBuilder();
		Value->Append("\"");
		for(int i=0;i<Raw->Length;i++){
			if(Raw[i]==L'\"') Value->Append(L"\\\"");
			else if(Raw[i]==L'\\') Value->Append(L"\\\\");
			else if(Raw[i]==L'/') Value->Append(L"\\/");
			else if(Raw[i]==L'\b') Value->Append(L"\\b");
			else if(Raw[i]==L'\f') Value->Append(L"\\f");
			else if(Raw[i]==L'\n') Value->Append(L"\\n");
			else if(Raw[i]==L'\r') Value->Append(L"\\r");
			else if(Raw[i]==L'\t') Value->Append(L"\\t");
			else if(Raw[i]<=L'\x007F') Value->Append(Raw[i]);
			else Value->AppendFormat(L"\\u{0:X4}",(UInt16)Raw[i]);
		}
		return Value->Append("\"")->ToString();
	}

	String^ Json::ToString(Object^ Data)
	{
		Level=gcnew Stack<Object^>();
		JsonStr=gcnew StringBuilder();
		Type^ CurrentType=Data->GetType();
		IEnumerator<Object^>^ Enumerate;
		if(CurrentType==JsonHash::typeid){
			JsonStr->Append(L'{');
			Enumerate=(IEnumerator<Object^>^)(IEnumerator<String^>^)((JsonHash^)Data)->Keys->GetEnumerator();
		}else if(CurrentType==JsonArray::typeid){
			JsonStr->Append(L'[');
			Enumerate=((IEnumerable<Object^>^)Data)->GetEnumerator();
		}else throw gcnew FormatException("配列又は連想配列を表す型は、System.Collections.Generic.List(System.Object)\nおよびSystem.Collections.Generic.Dictionary(System.String,System.Object)でなければなりません。");
		Level->Push(Data);
		do{
			bool Result=Enumerate->MoveNext();
			CurrentType=Level->Peek()->GetType();
			if(CurrentType==JsonHash::typeid){
				if(Result){
					Object^ Member=((JsonHash^)Level->Peek())[(String^)Enumerate->Current];
					Type^ MemberType=(Member==nullptr)?(nullptr):(Member->GetType());
					JsonStr->Append(CreateString((String^)Enumerate->Current));
					JsonStr->Append(L':');
					if(MemberType==nullptr) JsonStr->Append(L"null");
					else if(MemberType==__int64::typeid) JsonStr->Append((__int64)Member);
					else if(MemberType==__int32::typeid) JsonStr->Append((__int64)(__int32)Member);
					else if(MemberType==__int16::typeid) JsonStr->Append((__int64)(__int16)Member);
					else if(MemberType==__int8::typeid) JsonStr->Append((__int64)(__int8)Member);
					else if(MemberType==unsigned __int32::typeid) JsonStr->Append((__int64)(unsigned __int32)Member);
					else if(MemberType==unsigned __int16::typeid) JsonStr->Append((__int64)(unsigned __int16)Member);
					else if(MemberType==unsigned __int8::typeid) JsonStr->Append((__int64)(unsigned __int8)Member);
					else if(MemberType==double::typeid) JsonStr->Append((double)Member);
					else if(MemberType==float::typeid) JsonStr->Append((double)(float)Member);
					else if(MemberType==bool::typeid) JsonStr->Append(((bool)Member).ToString()->ToLower());
					else if(MemberType==String::typeid) JsonStr->Append(CreateString((String^)Member));
					else if(MemberType==JsonHash::typeid){
						JsonStr->Append(L'{');
						Level->Push(Enumerate);
						Level->Push(Member);
						Enumerate=(IEnumerator<Object^>^)(IEnumerator<String^>^)((JsonHash^)Level->Peek())->Keys->GetEnumerator();
						continue;
					}else if(MemberType==JsonArray::typeid){
						JsonStr->Append(L'[');
						Level->Push(Enumerate);
						Level->Push(Member);
						Enumerate=((JsonArray^)Level->Peek())->GetEnumerator();
						continue;
					}else throw gcnew FormatException("オブジェクトの型が数値(System.Int64,System.Double)、\n"
												  "論理値(System.Boolean)、文字列(System.String)、配列(System.Collections.Generic.List(System.Object))、\n"
												  "連想配列(System.Collections.Generic.Dictionary(System.String,System.Object))以外の型です。");
					JsonStr->Append(L',');
				}else{
					int LastIndex=JsonStr->Length-1;
					if(JsonStr[LastIndex]==L',') JsonStr[LastIndex]=L'}';
					else JsonStr->Append(L'}');
					Level->Pop();
					if(Level->Count>0){
						Enumerate=(IEnumerator<Object^>^)Level->Pop();
						JsonStr->Append(L",");
					}
				}
			}else if(CurrentType==JsonArray::typeid){
				if(Result){
					Object^ Member=Enumerate->Current;
					Type^ MemberType=(Member==nullptr)?(nullptr):(Member->GetType());
					if(MemberType==nullptr) JsonStr->Append(L"null");
					else if(MemberType==__int64::typeid) JsonStr->Append((__int64)Member);
					else if(MemberType==__int32::typeid) JsonStr->Append((__int64)(__int32)Member);
					else if(MemberType==__int16::typeid) JsonStr->Append((__int64)(__int16)Member);
					else if(MemberType==__int8::typeid) JsonStr->Append((__int64)(__int8)Member);
					else if(MemberType==unsigned __int32::typeid) JsonStr->Append((__int64)(unsigned __int32)Member);
					else if(MemberType==unsigned __int16::typeid) JsonStr->Append((__int64)(unsigned __int16)Member);
					else if(MemberType==unsigned __int8::typeid) JsonStr->Append((__int64)(unsigned __int8)Member);
					else if(MemberType==double::typeid) JsonStr->Append((double)Member);
					else if(MemberType==float::typeid) JsonStr->Append((double)(float)Member);
					else if(MemberType==bool::typeid) JsonStr->Append(((bool)Member).ToString()->ToLower());
					else if(MemberType==String::typeid) JsonStr->Append(CreateString((String^)Member));
					else if(MemberType==JsonHash::typeid){
						JsonStr->Append(L'{');
						Level->Push(Enumerate);
						Level->Push(Member);
						Enumerate=(IEnumerator<Object^>^)(IEnumerator<String^>^)((JsonHash^)Level->Peek())->Keys->GetEnumerator();
						continue;
					}else if(MemberType==JsonArray::typeid){
						JsonStr->Append(L'[');
						Level->Push(Enumerate);
						Level->Push(Member);
						Enumerate=((JsonArray^)Level->Peek())->GetEnumerator();
						continue;
					}else throw gcnew FormatException("オブジェクトの型が数値(System.Int64,System.Double)、\n"
						"論理値(System.Boolean)、文字列(System.String)、配列(System.Collections.Generic.List(Object))、\n"
												  "連想配列(System.Collections.Generic.Dictionary(System.String,System.Object))以外の型です。");
					JsonStr->Append(L',');
				}else{
					int LastIndex=JsonStr->Length-1;
					if(JsonStr[LastIndex]==L',') JsonStr[LastIndex]=L']';
					else JsonStr->Append(L']');
					Level->Pop();
					if(Level->Count>0){
						Enumerate=(IEnumerator<Object^>^)Level->Pop();
						JsonStr->Append(L',');
					}
				}
			}else throw gcnew FormatException("配列又は連想配列を表す型は、System.Collections.Generic.List(System.Object)\nおよびSystem.Collections.Generic.Dictionary(System.String,System.Object)でなければなりません。");
			delete CurrentType;
		}while(Level->Count>0);
		delete CurrentType;
		return JsonStr->ToString();
	}
}