#include <iostream>
#include"contacts.pb.h"
#include<fstream>
using namespace std;
using namespace contacts2;

void PrintContacts(Contacts&contacts){
    //数组
    cout<<"打印通讯录"<<endl;
    for(int i=0;i<contacts.contacts_size();++i){
      auto contact= contacts.contacts(i);
      cout<<"第"<<i<<"位联系人"<<endl;
      cout<<"name:"<<contact.name();
      cout<<"age:"<<contact.age();
      for(int i=0;i<contact.phone_numbers_size();++i){
        auto phone=contact.phone_numbers(i);
        cout<<"phone "<<i<<":"<<phone.number()<<endl;
      }
    }
    cout<<"打印完成"<<endl;
}
int main(){
  fstream input("contacts.bin",ios::in|ios::binary);//二进制.binary:不做任何转换,,in --只读打开文件 input
    if(!input){
        cout<<"读取失败"<<endl;
        return -1;
    }
    //反序列化
    Contacts contacts;
    if(!contacts.ParseFromIstream(&input)){
        cout<<"prase error"<<endl;
        input.close();
        return -1;
    }
    //打印
    PrintContacts(contacts);
    input.close();
}


//命令行读取
//protoc --decode=contacts2.Contacts ./contacts.proto < ./contacts.b

//contacts2--package
//Contacts ---message
//目录
//默认从标准输入读取 < 重定向