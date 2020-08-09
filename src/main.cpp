/*只完成最基本的只有一个根节点以及根节点只有一层子节点的xml的读取与写入*/
#include "tinystr.h"
#include "tinyxml.h"
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include<Windows.h>
#include<tchar.h>
using namespace std;

#define DEBUG_LQC

bool  ReadXmlInfo(wstring& fileWPath, vector<pair<wstring, wstring>>& xmlInfo); //xml文件读取
bool WriteXmlInfo(wstring& fileWPath, vector<pair<wstring, wstring>>& xmlInfo); //xml文件写入
static std::wstring stringToWstring(const std::string& str);//string转换为wstring
static std::string UTF8ToGB(const char* str);//更改string编码
static bool UnicodeToUtf8(std::wstring& unicode_string, std::string& utf8_string);//wstring->string

#ifdef DEBUG_LQC
//#define XMLFilePath "C:\\Users\\liuquanchang\\Desktop\\new.xml"
#define XMLFilePath "C:\\Users\\liuquanchang\\Desktop\\NeedsXML.xml"
#define WriteXMLFilePath "C:\\Users\\liuquanchang\\Desktop\\新建文件夹as\\新建文本文档.xml"
int main()
{
    vector<pair<wstring, wstring>>xmlInfo;
    string filePath = XMLFilePath;
    wstring fileWPath = stringToWstring(filePath);

    //读取测试
    if (false == ReadXmlInfo(fileWPath, xmlInfo)) 
    {
        cout << "readXML error" << endl;
    }
    wcout.imbue(std::locale("chs"));
    for (auto i : xmlInfo)
    {
        wcout << i.first << ":" << i.second << endl;
    }

    //写入测试
    string writeFilePath = WriteXMLFilePath;
    wstring writeFileWPath = stringToWstring(writeFilePath);
    if (false == WriteXmlInfo(writeFileWPath, xmlInfo))
    {
        cout << "写文件错误" << endl;
    }
    else
    {
        cout << "文件写入成功" << endl;
    }
}
#endif

bool  ReadXmlInfo(wstring& fileWPath, vector<pair<wstring, wstring>>& xmlInfo)
{
    TiXmlDocument doc;//申明一个文档类型变量，用来存储读取的xml文档
    string filePath;
    if (!UnicodeToUtf8(fileWPath, filePath))
    {
        return false;
    }

    if (!doc.LoadFile(filePath.c_str()))  //检测xml文档是否存在
    {
        return false;
    }

    TiXmlElement* MassSpectrumLab = doc.FirstChildElement();//指向xml文档的根元素

    if (MassSpectrumLab == NULL)//检测根元素存在性     
    {
        doc.Clear();
        return false;
    }
    else
    {
        TiXmlElement* term = MassSpectrumLab->FirstChildElement(); // xml的id 根节点下第一个子节点
        while (term != NULL)
        {
            wstring contactType = stringToWstring(UTF8ToGB(term->Value()));
            wstring contactValue = stringToWstring(UTF8ToGB(term->GetText()));
            xmlInfo.push_back(pair<wstring, wstring>(contactType, contactValue));
            term = term->NextSiblingElement();
        }
    }
    return true;
}

bool WriteXmlInfo(wstring& fileWPath, vector<pair<wstring, wstring>>& xmlInfo)
{
    string filePath;
    if (!UnicodeToUtf8(fileWPath, filePath))
    {
        return false;
    }

    TiXmlDocument* doc = new TiXmlDocument(); //创建一个xml文档对象
    TiXmlElement* root = new TiXmlElement("root"); //设置根节点
    doc->LinkEndChild(root); //设置doc的子节点为root

    //写入xml
    for (auto i : xmlInfo)
    {
        string property, value;
        if (!UnicodeToUtf8(i.first, property) || !UnicodeToUtf8(i.second, value))
        {
            return false;
        }
        TiXmlElement* temp = new TiXmlElement(property.c_str());
        temp->LinkEndChild(new TiXmlText(value.c_str()));
        root->LinkEndChild(temp); //将该节点加入根节点下
    }

    //保存
    if (false == doc->SaveFile(filePath.c_str()))
    {
        return false;
    }
    return true;
}



bool UnicodeToUtf8(std::wstring& unicodeString, std::string& utf8String)
{
    utf8String = "";
    if (_wcsicmp(unicodeString.c_str(), L"") == 0)
    {
        return false;
    }

    DWORD utf8StringLen = WideCharToMultiByte(CP_ACP, NULL, unicodeString.c_str(), -1, NULL, 0, NULL, FALSE);// WideCharToMultiByte的运用
    if (0 == utf8StringLen)
    {
        return false;
    }
    char* tempUtf8String = new char[utf8StringLen + 1];
    memset(tempUtf8String, 0, sizeof(char) * (utf8StringLen + 1));
    if (0 == WideCharToMultiByte(CP_ACP, NULL, unicodeString.c_str(), -1, tempUtf8String, utf8StringLen, NULL, FALSE))
    {
        delete[] tempUtf8String;
        tempUtf8String = NULL;
        return false;
    }

    utf8String = (std::string)tempUtf8String;
    delete[] tempUtf8String;
    tempUtf8String = NULL;

    return true;
}

std::wstring stringToWstring(const std::string& str)
{
    std::wstring result;

    //获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
    int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
    TCHAR* buffer = new TCHAR[len + 1];

    //多字节编码转换成宽字节编码  
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);

    //添加字符串结尾  
    buffer[len] = '\0';

    //删除缓冲区并返回值  
    result.append(buffer);
    delete[] buffer;
    return result;
}


std::string UTF8ToGB(const char* str)
{
    std::string result;
    WCHAR* strSrc;
    LPSTR szRes;

    //获得临时变量的大小
    int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    strSrc = new WCHAR[i + 1];
    MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

    //获得临时变量的大小
    i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
    szRes = new CHAR[i + 1];
    WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

    result = szRes;
    delete[]strSrc;
    delete[]szRes;

    return result;
}