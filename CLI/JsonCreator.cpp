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
		return Value->ToString();
	}

	String^ JsonCreator::Create(Object^ DataArray)
	{
		Level=gcnew Stack();
		JsonStr=gcnew StringBuilder();
		Type^ CurrentType=DataArray->GetType();
		IEnumerator^ Enumerate;
		if(CurrentType==Hashtable::typeid){
			JsonStr->Append(L'{');
			Enumerate=((Hashtable^)DataArray)->Keys->GetEnumerator();
		}else if(CurrentType==ArrayList::typeid){
			JsonStr->Append(L'[');
			Enumerate=((IEnumerable^)DataArray)->GetEnumerator();
		}else throw gcnew FormatException("�z�񖔂͘A�z�z���\���^�́ASystem.Collections.ArrayList\n����System.Collections.Hashtable�łȂ���΂Ȃ�܂���B");
		Level->Push(DataArray);
		do{
			bool Result=Enumerate->MoveNext();
			CurrentType=Level->Peek()->GetType();
			if(CurrentType==Hashtable::typeid){
				if(Result){
					Object^ Member=((Hashtable^)Level->Peek())[(String^)Enumerate->Current];
					Type^ MemberType=(Member==nullptr)?(nullptr):(Member->GetType());
					JsonStr->Append(CreateString((String^)Enumerate->Current));
					JsonStr->Append(L':');
					if(MemberType==nullptr) JsonStr->Append(L"null");
					else if(MemberType==__int64::typeid) JsonStr->Append((__int64)Member);
					else if(MemberType==double::typeid) JsonStr->Append((double)Member);
					else if(MemberType==bool::typeid) JsonStr->Append(((bool)Member).ToString()->ToLower());
					else if(MemberType==String::typeid) JsonStr->Append(CreateString((String^)Member));
					else if(MemberType==Hashtable::typeid){
						JsonStr->Append(L'{');
						Level->Push(Enumerate);
						Level->Push(Member);
						Enumerate=((Hashtable^)Level->Peek())->Keys->GetEnumerator();
						continue;
					}else if(MemberType==ArrayList::typeid){
						JsonStr->Append(L'[');
						Level->Push(Enumerate);
						Level->Push(Member);
						Enumerate=((ArrayList^)Level->Peek())->GetEnumerator();
						continue;
					}else throw gcnew FormatException("�I�u�W�F�N�g�̌^�����l(System.Int64,System.Double)�A\n"
												  "�_���l(System.Boolean)�A������(System.String)�A�z��(System.Collections.ArrayList)�A\n"
												  "�A�z�z��(System.Collections.Hashtable)�ȊO�̌^�ł��B");
					JsonStr->Append(L',');
				}else{
					JsonStr[JsonStr->Length-1]=L'}';
					Level->Pop();
					if(Level->Count>0){
						Enumerate=(IEnumerator^)Level->Pop();
						JsonStr->Append(L",");
					}
				}
			}else if(CurrentType==ArrayList::typeid){
				if(Result){
					Object^ Member=Enumerate->Current;
					Type^ MemberType=(Member==nullptr)?(nullptr):(Member->GetType());
					if(MemberType==nullptr) JsonStr->Append(L"null");
					else if(MemberType==__int64::typeid) JsonStr->Append((__int64)Member);
					else if(MemberType==double::typeid) JsonStr->Append((double)Member);
					else if(MemberType==bool::typeid) JsonStr->Append(((bool)Member).ToString()->ToLower());
					else if(MemberType==String::typeid) JsonStr->Append(CreateString((String^)Member));
					else if(MemberType==Hashtable::typeid){
						JsonStr->Append(L'{');
						Level->Push(Enumerate);
						Level->Push(Member);
						Enumerate=((Hashtable^)Level->Peek())->Keys->GetEnumerator();
						continue;
					}else if(MemberType==ArrayList::typeid){
						JsonStr->Append(L'[');
						Level->Push(Enumerate);
						Level->Push(Member);
						Enumerate=((ArrayList^)Level->Peek())->GetEnumerator();
						continue;
					}else throw gcnew FormatException("�I�u�W�F�N�g�̌^�����l(System.Int64,System.Double)�A\n"
												  "�_���l(System.Boolean)�A������(System.String)�A�z��(System.Collections.ArrayList)�A\n"
												  "�A�z�z��(System.Collections.Hashtable)�ȊO�̌^�ł��B");
					JsonStr->Append(L',');
				}else{
					JsonStr[JsonStr->Length-1]=L']';
					Level->Pop();
					if(Level->Count>0){
						Enumerate=(IEnumerator^)Level->Pop();
						JsonStr->Append(L',');
					}
				}
			}else throw gcnew FormatException("�z�񖔂͘A�z�z���\���^�́ASystem.Collections.ArrayList\n����System.Collections.Hashtable�łȂ���΂Ȃ�܂���B");
			delete CurrentType;
		}while(Level->Count>0);
		delete CurrentType;
		return JsonStr->ToString();
	}
}