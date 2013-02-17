#pragma once

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace System::Text::RegularExpressions;

namespace Json{

	typedef List<Object^> JsonArray;
	typedef Dictionary<String^,Object^> JsonHash;

	public ref class Json
	{
	private:
		Stack<Object^>^ Level;
		StringBuilder^ JsonStr;
		String^ Raw;
		Stack<Object^>^ Bracket;
		Object^ Root;
		int Pos;

		String^ ParseString(void);
		__int64 ParseInt(String^ Raw);
		double ParseDouble(String^ Raw);
		bool ParseBoolean(void);
		Object^ ParseNull(void);
		String^ CreateString(String^ Raw);

	public:
		Object^ Parse(String^ DataString);
		String^ ToString(Object^ Data);

	};
}
