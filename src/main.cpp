#include "tinystr.h"
#include "tinyxml.h"
#include<stdio.h>
#include <string>
#include <iostream>
#include <tchar.h>
#include <windows.h>
using namespace std;
//"C:\\Users\\liuquanchang\\Desktop\\NeedsXML.xml"
//"C:\\Users\\liuquanchang\\source\\repos\\ReadXMLFileC\\ReadXMLFileC\\Debug\\MassSpectrumLab.xml"
#define XMLFilePath "C:\\Users\\liuquanchang\\Desktop\\NeedsXML.xml"

void printSchoolXml();
void readSchoolXml();

int main(int argc, char** argv) {
    //printSchoolXml();
    readSchoolXml();
    return 0;
}

void printSchoolXml() {
    using namespace std;
    TiXmlDocument doc;
    if (doc.LoadFile(XMLFilePath)) {
        doc.Print();
    }
    else {
        cout << "can not parse xml conf/school.xml" << endl;
    }
}

void readSchoolXml()
{
    TiXmlDocument doc;//申明一个文档类型变量，用来存储读取的xml文档
    if (!doc.LoadFile(XMLFilePath))   //检测xml文档是否存在
    {
        cerr << doc.ErrorDesc() << endl;
    }
    TiXmlElement* MassSpectrumLab = doc.FirstChildElement();//指向xml文档的根元素


    if (MassSpectrumLab == NULL)//检测根元素存在性     
    {
        cerr << "Failed to load file: No root element." << endl;
        doc.Clear();
    }
    else
    {
        //需求id
        TiXmlElement* requirement_id = MassSpectrumLab->FirstChildElement(); // xml的id 根节点下第一个子节点
        int temp = 0;

        while (requirement_id != NULL)
        {
            temp++; 
            cout << temp << endl;
            //需求名称
            TiXmlElement* requirement_name = requirement_id->NextSiblingElement();        // requirement_id 下一个子节点
            //需求地址
            TiXmlElement* requirement_address = requirement_name->NextSiblingElement();   // requirement_name 下一个子节点
            //代码地址
            TiXmlElement* code_address = requirement_address->NextSiblingElement();   // requirement_address 下一个子节点
            //本地地址
            TiXmlElement* local_address = code_address->NextSiblingElement();     // code_address 下一个子节点
            //bug列表
            TiXmlElement* bug_list = local_address->NextSiblingElement();    // local_address 下一个子节点
            //bug列表的第一个bug
            TiXmlElement* bug = bug_list->FirstChildElement();//获得bug_list的第一个子元素

            //需求id
            string TypeMark_id = requirement_id->Value();
            string Mark_idValue = requirement_id->GetText();
            cout << TypeMark_id << " : " << Mark_idValue << std::endl;
            
            //需求名称
            string TypeChinese_name = requirement_name->Value();
            string Chinese_nameValue = requirement_name->GetText();
            cout << TypeChinese_name << " : " << Chinese_nameValue << std::endl;

            //需求地址
            string TypeEnglish_name = requirement_address->Value();
            string English_nameValue = requirement_address->GetText();
            cout << TypeEnglish_name << " : " << English_nameValue << std::endl;

            //代码地址
            string TypeParent_ion = code_address->Value();
            string Parent_ionValue = code_address->GetText();
            cout << TypeParent_ion << " : " << Parent_ionValue << std::endl;

            //本地地址
            string TypeDaughterNum = local_address->Value();
            string DaughterNumValue = local_address->GetText();
            cout << TypeDaughterNum << " : " << DaughterNumValue << std::endl;

            //bug列表
            for (; bug != NULL; bug = bug->NextSiblingElement()) {
                string contactType = bug->Value();
                string contactValue = bug->GetText();
                cout << contactType << " : " << contactValue << std::endl;
            }
            requirement_id = bug_list->NextSiblingElement();
        }
    }
}