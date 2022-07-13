#pragma once

#include <string>
#include <locale>
#include <codecvt>
#include <stdexcept>


namespace Game
{
	/**
	 * 게임 내의 문자열 관련 기능을 제공하는 클래스입니다.
	 */
	class StringHelper
	{
	public:
		/**
		 * 형식화된 문자열을 반환합니다.
		 * 
		 * @param InFormat - 형식 문자열입니다.
		 * @param ... InArgs - 포멧팅을 수행할 데이터를 지정하는 인수입니다.
		 * 
		 * @return 포멧팅이 완료된 문자열을 반환합니다.
		 * 
		 * @warning 문자열은 UTF-8이여야 합니다.
		 * 
		 * @note 이 메서드는 snprintf를 대체하기 위한 메서드입니다.
		 * 
		 * @see https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
		 */
		template<typename ... Args>
		static inline std::string Format(const std::string& InFormat, Args ... InArgs_)
		{
			size_t Size = static_cast<size_t>(std::snprintf(nullptr, 0, InFormat.c_str(), InArgs_ ...)) + 1;

			auto Buffer = std::make_unique<char[]>(Size);
			std::snprintf(Buffer.get(), Size, InFormat.c_str(), InArgs_ ...);

			return std::string(Buffer.get(), Buffer.get() + Size - 1);
		}


		/**
		 * 형식화된 문자열을 반환합니다.
		 * 
		 * @param InFormat - 형식 문자열입니다.
		 * @param ... InArgs - 포멧팅을 수행할 데이터를 지정하는 인수입니다.
		 * 
		 * @return 포멧팅이 완료된 문자열을 반환합니다.
		 * 
		 * @warning 문자열은 UTF-16이여야 합니다.
		 * 
		 * @note 이 메서드는 snprintf를 대체하기 위한 메서드입니다.
		 * 
		 * @see https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
		 */
		template<typename ... Args>
		static inline std::wstring Format(const std::wstring& InFormat, Args ... InArgs_)
		{
			size_t Size = static_cast<size_t>(std::swprintf(nullptr, 0, InFormat.c_str(), InArgs_ ...)) + 1;

			auto Buffer = std::make_unique<wchar_t[]>(Size);
			std::swprintf(Buffer.get(), Size, InFormat.c_str(), InArgs_ ...);

			return std::wstring(Buffer.get(), Buffer.get() + Size - 1);
		}


		/**
		 * UTF-8 문자열을 UTF-16 문자열로 변환합니다.
		 * 
		 * @param InUTF8 - UTF-16으로 변환할 UTF-8 문자열입니다.
		 * 
		 * @return UTF-16으로 변환이 완료된 문자열을 반환합니다.
		 * 
		 * @see https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
		 */
		static inline std::wstring ConvertUTF8ToUTF16(const std::string& InUTF8)
		{
			static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> Converter;
			return Converter.from_bytes(InUTF8);
		}


		/**
		 * UTF-16 문자열을 UTF-8 문자열로 변환합니다.
		 * 
		 * @param InUTF16 - UTF-8으로 변환할 UTF-16 문자열입니다.
		 * 
		 * @return UTF-8으로 변환이 완료된 문자열을 반환합니다.
		 * 
		 * @see https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
		 */
		static inline std::string ConvertUTF16ToUTF8(const std::wstring& InUTF16)
		{
			static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> Converter;
			return Converter.to_bytes(InUTF16);
		}


		/**
		 * UTF-8 문자열의 Hash 값을 반환합니다.
		 * 
		 * @param InUTF8 - Hash 값으로 변환할 UTF-8 문자열입니다.
		 * 
		 * @return UTF-8 문자열의 Hash 값입니다. 
		 */
		static inline std::size_t GetHash(const std::string& InUTF8)
		{
			return std::hash<std::string>{}(InUTF8);
		}


		/**
		 * UTF-16 문자열의 Hash 값을 얻습니다.
		 * 
		 * @param InUTF16 - Hash 값으로 변환할 UTF-16 문자열입니다.
		 * 
		 * @return UTF-16 문자열의 Hash 값입니다.
		 */
		static inline std::size_t GetHash(const std::wstring& InUTF16)
		{
			return std::hash<std::wstring>{}(InUTF16);
		}
	};
}