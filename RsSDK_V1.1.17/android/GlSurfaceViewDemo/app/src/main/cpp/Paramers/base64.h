/*base_64.h文件*/
#pragma once
#ifndef BASE_64_H
#define BASE_64_H

/**
 * Base64 编码/解码
 */
#include <string>
#include <cstring>

class Base64{
private:
    static std::string _base64_table; /*这是Base64编码使用的标准字典*/
    static const char base64_pad = '=';
public:
    /**
     * 这里必须是unsigned类型，否则编码中文的时候出错
     */
    static std::string Encode(const unsigned char * str,int bytes);
    static std::string Decode(const char *str,int length);
    
};
#endif
