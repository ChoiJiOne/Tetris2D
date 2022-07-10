#pragma once

// 표준 라이브러리를 사용하기 위해서 헤더 파일을 추가합니다.
#include "Header.h"


namespace Game
{
    // 게임 내의 문자열 관련 기능을 제공하는 클래스입니다.
    class StringHelper
    {
    public:
        // 기존의 sprintf 를 대체할 때 호출합니다.
        // https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
        // 
        // @param InFormat - 형식 문자열입니다.
        // @param ... InArgs - 포멧팅을 수행할 데이터를 지정하는 인수입니다.
        // @return - 포멧팅이 완료된 문자열을 반환합니다.
        // @warning - 문자열은 UTF-8이여야 합니다.
        template<typename ... Args>
        static inline std::string Format(const std::string& InFormat, Args ... InArgs_)
        {
            size_t Size = static_cast<size_t>(std::snprintf(nullptr, 0, InFormat.c_str(), InArgs_ ...)) + 1;

            if (Size <= 0)
            {
                throw std::runtime_error("error during formatting.");
            }

            auto Buffer = std::make_unique<char[]>(Size);
            std::snprintf(Buffer.get(), Size, InFormat.c_str(), InArgs_ ...);

            return std::string(Buffer.get(), Buffer.get() + Size - 1);
        }


        // 기존의 swprintf 를 대체할 때 호출합니다.
        // 코드는 위의 StringFormat 을 기반으로 구현되었습니다.
        // 
        // @param InFormat - 형식 문자열입니다. 
        // @param ... InArgs - 포멧팅을 수행할 데이터를 지정하는 인수입니다.
        // @return - 포멧팅이 완료된 문자열을 반환합니다.
        // @warning - 문자열은 UTF-16이여야 합니다.
        template<typename ... Args>
        static inline std::wstring Format(const std::wstring& InFormat, Args ... InArgs_)
        {
            size_t Size = static_cast<size_t>(std::swprintf(nullptr, 0, InFormat.c_str(), InArgs_ ...)) + 1;

            if (Size <= 0)
            {
                throw std::runtime_error("error during formatting.");
            }

            auto Buffer = std::make_unique<wchar_t[]>(Size);
            std::swprintf(Buffer.get(), Size, InFormat.c_str(), InArgs_ ...);

            return std::wstring(Buffer.get(), Buffer.get() + Size - 1);
        }


        // UTF-8 문자열을 UTF-16 문자열로 변환합니다.
        // https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
        // 
        // @param InUTF8 - UTF-16으로 변환할 UTF-8 문자열입니다.
        // @return - UTF-16으로 변환이 완료된 문자열을 반환합니다.
        static inline std::wstring ConvertUTF16(const std::string& InUTF8)
        {
            static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> Converter;
            return Converter.from_bytes(InUTF8);
        }


        // UTF-16 문자열을 UTF-8 문자열로 변환합니다.
        // https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
        // 
        // @param InUTF16 - UTF-8으로 변환할 UTF-16 문자열입니다.
        // @return - UTF-8으로 변환이 완료된 문자열을 반환합니다.
        static inline std::string ConvertUTF8(const std::wstring& InUTF16)
        {
            static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> Converter;
            return Converter.to_bytes(InUTF16);
        }


        // UTF-8 문자열의 Hash 값을 얻습니다.
        //
        // @param InUTF8 - Hash 값으로 변환할 UTF-8 문자열입니다.
        // @return - UTF-8 문자열의 Hash 값입니다. 
        static inline std::size_t GetHash(const std::string& InUTF8)
        {
            return std::hash<std::string>{}(InUTF8);
        }


        // UTF-16 문자열의 Hash 값을 얻습니다.
        //
        // @param InUTF16 - Hash 값으로 변환할 UTF-16 문자열입니다.
        // @return - UTF-16 문자열의 Hash 값입니다. 
        static inline std::size_t GetHash(const std::wstring& InUTF16)
        {
            return std::hash<std::wstring>{}(InUTF16);
        }
    };
}