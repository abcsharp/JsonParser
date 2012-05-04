#include "Stdafx.h"
#include "Json.h"

namespace Json{

	JsonCreator::JsonCreator(void)
	{
		return;
	}

	JsonCreator::~JsonCreator(void)
	{
		return;
	}

	void JsonCreator::ClearCache(bool IsActivateGC)
	{
		return;
	}

	String^ JsonCreator::CreateString(String^ Raw)
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

	String^ JsonCreator::Create(Object^ Data)
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
		}else throw gcnew FormatException("�z�񖔂͘A�z�z���\���^�́ASystem.Collections.Generic.List(System.Object)\n�����System.Collections.Generic.Dictionary(System.String,System.Object)�łȂ���΂Ȃ�܂���B");
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
					else if(MemberType==double::typeid) JsonStr->Append((double)Member);
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
					}else throw gcnew FormatException("�I�u�W�F�N�g�̌^�����l(System.Int64,System.Double)�A\n"
												  "�_���l(System.Boolean)�A������(System.String)�A�z��(System.Collections.Generic.List(System.Object))�A\n"
												  "�A�z�z��(System.Collections.Generic.Dictionary(System.String,System.Object))�ȊO�̌^�ł��B");
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
					else if(MemberType==double::typeid) JsonStr->Append((double)Member);
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
					}else throw gcnew FormatException("�I�u�W�F�N�g�̌^�����l(System.Int64,System.Double)�A\n"
						"�_���l(System.Boolean)�A������(System.String)�A�z��(System.Collections.Generic.List(Object))�A\n"
												  "�A�z�z��(System.Collections.Generic.Dictionary(System.String,System.Object))�ȊO�̌^�ł��B");
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
			}else throw gcnew FormatException("�z�񖔂͘A�z�z���\���^�́ASystem.Collections.Generic.List(System.Object)\n�����System.Collections.Generic.Dictionary(System.String,System.Object)�łȂ���΂Ȃ�܂���B");
			delete CurrentType;
		}while(Level->Count>0);
		delete CurrentType;
		return JsonStr->ToString();
	}
}