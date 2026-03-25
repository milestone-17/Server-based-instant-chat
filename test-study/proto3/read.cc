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
      cout<<"---------第"<<i+1<<"位联系人----------"<<endl;
      cout<<"name:"<<contact.name()<<endl;
      cout<<"age:"<<contact.age()<<endl;
      //电话:1111111(MP/TEL )
      for(int i=0;i<contact.phone_numbers_size();++i){
        auto phone=contact.phone_numbers(i);
        cout<<"phone "<<i<<":"<<phone.number()<<"        "<<"("<< phone.type()<<")"<<endl;
      }
      //打印地址

      //Is<contacts2::AddRess>()含义：模板类型判断函数作用：检查当前数据的实际类型，是不是 contacts2::AddRess 这个自定义类型
     if(contact.has_data()&&contact.data().Is<contacts2::AddRess>()){
            contacts2::AddRess address;
            contact.data().UnpackTo(&address);
            if(!address.home_address().empty()){
                cout<<"家庭地址:"<<address.home_address()<<endl;

            }
            if(!address.unit_address().empty()){
                cout<<"单位地址"<<address.unit_address()<<endl;
            }
     }
     else{
        cout<<"未设置地址"<<endl;
     }
    //  if(contact._internal_has_qq())
    //  else if(wechat)
    auto other_contact=contact.other_contact_case();
    switch(other_contact){
        case contacts2::PeopleInfo::OtherContactCase::kQQ:
            cout<<"QQ号为"<<contact.qq()<<endl;
            break;
        case contacts2::PeopleInfo::OtherContactCase::kWeChat:
        cout<<"WECHAT 为"<<contact.wechat()<<endl;
        break;
        default:
        break;
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
