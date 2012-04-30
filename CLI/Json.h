#pragma once

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace System::Text::RegularExpressions;

namespace Json{

	typedef List<Object^> JsonArray;
	typedef Dictionary<String^,Object^> JsonHash;

	public ref class JsonParser
	{
	private:
		String^ Raw;
		Stack<Object^>^ Bracket;
		Object^ Root;
		int Pos;

		String^ ParseString(void);
		__int64 ParseInt(String^ Raw);
		double ParseDouble(String^ Raw);
		bool ParseBoolean(void);
		Object^ ParseNull(void);

	public:
		JsonParser(void);
		~JsonParser(void);

		void ClearCache(bool IsActivateGC);
		Object^ Parse(String^ DataString);
	};

	public ref class JsonCreator
	{
	private:
		Stack<Object^>^ Level;
		StringBuilder^ JsonStr;

	public:
		JsonCreator(void);
		~JsonCreator(void);

		String^ CreateString(String^ Raw);

		void ClearCache(bool IsActivateGC);
		String^ Create(Object^ Data);
	};
}
