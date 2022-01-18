/*base_64.h�ļ�*/
#pragma once
#ifndef BASE_64_H
#define BASE_64_H

/**
 * Base64 ����/����
 */
#include <string>
#include <cstring>

class Base64{
private:
    static std::string _base64_table; /*����Base64����ʹ�õı�׼�ֵ�*/
    static const char base64_pad = '=';
public:
    /**
     * ���������unsigned���ͣ�����������ĵ�ʱ�����
     */
    static std::string Encode(const unsigned char * str,int bytes);
    static std::string Decode(const char *str,int length);
    
};
#endif
