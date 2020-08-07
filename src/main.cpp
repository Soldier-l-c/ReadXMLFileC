#include "tinystr.h"
#include "tinyxml.h"
#include<stdio.h>
#include <string>
#include <iostream>
using namespace std;
#define XMLFilePath "C:\\Users\\liuquanchang\\source\\repos\\ReadXMLFileC\\ReadXMLFileC\\Debug\\MassSpectrumLab.xml"

void printSchoolXml();
void readSchoolXml();

int main(int argc, char** argv) {
    printSchoolXml();
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
        TiXmlElement* mark_id = MassSpectrumLab->FirstChildElement(); // xml的id 根节点下第一个子节点
        TiXmlElement* Chinese_name = mark_id->NextSiblingElement();        // mark_id 下一个子节点
        TiXmlElement* English_name = Chinese_name->NextSiblingElement();   // Chinese_name 下一个子节点
        TiXmlElement* Parent_ion = English_name->NextSiblingElement();   // English_name 下一个子节点
        TiXmlElement* DaughterNum = Parent_ion->NextSiblingElement();     // Parent_ion 下一个子节点
        TiXmlElement* Daughter_Ion = DaughterNum->NextSiblingElement();    // DaughterNum 下一个子节点
        TiXmlElement* Daughter = Daughter_Ion->FirstChildElement();//获得Daughter_ion的第一个子元素
        int temp = 0;

        while (mark_id != NULL)
        {
            temp++; 
            cout << temp << endl;
            Chinese_name = mark_id->NextSiblingElement();        // mark_id 下一个子节点
            English_name = Chinese_name->NextSiblingElement();   // Chinese_name 下一个子节点
            Parent_ion = English_name->NextSiblingElement();   // English_name 下一个子节点
            DaughterNum = Parent_ion->NextSiblingElement();     // Parent_ion 下一个子节点
            Daughter_Ion = DaughterNum->NextSiblingElement();    // DaughterNum 下一个子节点
            Daughter = Daughter_Ion->FirstChildElement();    //获得Daughter_ion的第一个子元素
            string TypeMark_id = mark_id->Value();
            string Mark_idValue = mark_id->GetText();
            cout << TypeMark_id << " : " << Mark_idValue << std::endl;

            string TypeChinese_name = Chinese_name->Value();
            string Chinese_nameValue = Chinese_name->GetText();
            cout << TypeChinese_name << " : " << Chinese_nameValue << std::endl;

            string TypeEnglish_name = English_name->Value();
            string English_nameValue = English_name->GetText();
            cout << TypeEnglish_name << " : " << TypeEnglish_name << std::endl;

            string TypeParent_ion = Parent_ion->Value();
            string Parent_ionValue = Parent_ion->GetText();
            cout << TypeParent_ion << " : " << TypeParent_ion << std::endl;

            string TypeDaughterNum = DaughterNum->Value();
            string DaughterNumValue = DaughterNum->GetText();
            cout << TypeDaughterNum << " : " << DaughterNumValue << std::endl;

            for (; Daughter != NULL; Daughter = Daughter->NextSiblingElement()) {
                string contactType = Daughter->Value();
                string contactValue = Daughter->GetText();
                cout << contactType << " : " << contactValue << std::endl;
            }
            mark_id = Daughter_Ion->NextSiblingElement();
        }
        cout << temp << endl;
    }
}