#include <iostream>
#include"contacts.pb.h"
#include<fstream>
#include <string>
using namespace std;
using namespace contacts2;

void AddPeopleInfo(contacts2::PeopleInfo* people){
    cout<<"------------新增联系人--------------"<<endl;
    cout<<"请输入联系人"<<endl;
    cout<<"请输入联系人姓名:";
    string name;
    getline(cin,name);
    people->set_name(name);

    cout<<"请输入联系人年龄:";
    int age;
    cin>>age;
    people->set_age(age);
    cin.ignore(256, '\n');
    //电话
    for(int phone_idx=1;;++phone_idx){
      

        cout<<"请输入联系人电话"<<phone_idx<<"(按回车为输入完成):";
        string number;
        getline(cin,number);
        if(number.empty()){
            cout<<"该联系人所有电话输入完成"<<endl;
            break;
        }
        //先新增一个电话,再对number设置
        auto phone=people->add_phone_numbers();
        phone->set_number(number);
          cout<<"请确定电话类型 (MP:1, TEL=2),输入:";
        int type;
        cin>>type;
        cin.ignore(256, '\n');
        switch(type){
            case 1:
             phone->set_type(::contacts2::PeopleInfo_Phone_PhoneType::PeopleInfo_Phone_PhoneType_MP);
             break;
            case 2: 
            phone->set_type(::contacts2::PeopleInfo_Phone_PhoneType::PeopleInfo_Phone_PhoneType_TEL);
            break;
            default:
                cout<<"选择错误,使用默认值MP"<<endl;
                //没有设置,系统会有默认值,即常量值为0的常量0
                //  phone->set_type(::contacts2::PeopleInfo_Phone_PhoneType_MP);
                break;
        }
        //往any变量的data设置,但因为是定义任何类型的,设置前,我们先设置一个message
        std::string address;
        contacts2::AddRess _address;
        cout<<"请输入联系人家庭地址 :";
        getline(cin,address);
        _address.set_home_address(address);
        cout<<"请输入联系人单位地址: ";
        string ar;
        getline(cin,ar);
        _address.set_unit_address(ar);

        people->mutable_data()->PackFrom(_address);//PackFrom 类型转换
        cout<<" 请选择其他联系方式      (1->QQ   2->WeChat)   :";
        int other_contact;
        cin>>other_contact;
          cin.ignore(256, '\n');
        if(other_contact==1){
            cout<<"请输入QQ号:";
            std::string QQ;
            getline(cin,QQ);
            people->set_qq(QQ);
        }else if(other_contact==2){
            cout<<"请输入WeChat号:";
            std::string WeChat;
            getline(cin,WeChat);
            people->set_wechat(WeChat);
        }else{
            cout<<"未输入更多联系方式"<<endl;
        }
        
        }
        cout<<"请设置备注信息: "<<endl;
        for(int i=1;;++i){
            cout<<"备注信息"<<i<<":(按回车完成所有备注):"<<endl;;
            string remark_key;
            getline(cin,remark_key);
            if(remark_key.empty()){
                cout<<"备注输入完成"<<endl;
                break;
            }
            string remark_value;
            cout<<"设置备注内容"<<i<<endl;
            getline(cin,remark_value);

            (*people->mutable_remark())[remark_key] = remark_value;
    }
    cout << "-----------添加联系⼈成功-----------" << endl;
}

int main(){
     // GOOGLE_PROTOBUF_VERIFY_VERSION 宏: 验证没有意外链接到与编译的头⽂件不兼容的库版
//本。如果检测到版本不匹配，程序将中⽌。注意，每个 .pb.cc ⽂件在启动时都会⾃动调⽤此宏。在使
//⽤ C++ Protocol Buffer 库之前执⾏此宏是⼀种很好的做法，但不是绝对必要的。
 GOOGLE_PROTOBUF_VERIFY_VERSION;
    contacts2::Contacts contacts;
    //先读取本地已存在的,有就写入 . 打开,读取,即使没有这个文件,也会新建
    fstream input("contacts.bin",ios::in|ios::binary);//二进制.binary:不做任何转换,,in --只读打开文件 input
    if(!input){
        cout<<"file is not exist,creat new file"<<endl;
    }//并反序列化
    else if(!contacts.ParseFromIstream(&input)){
        cout<<"反序列化失败"<<endl;
        input.close();
        return -1;
    }
    //向铜通讯录添加联系人
    AddPeopleInfo(contacts.add_contacts());
    //把通讯录写入本地文件
    fstream output("contacts.bin",ios::out|ios::trunc|ios::binary);//trunc--覆盖式写入
    if(!contacts.SerializeToOstream(&output)){
        cout<<"write error"<<endl;
        output.close();
        return -1;
    }
    input.close();
    output.close();

    // 在程序结束时调⽤ ShutdownProtobufLibrary()，为了删除 Protocol Buffer 库分配的所
//有全局对象。对于⼤多数程序来说这是不必要的，因为该过程⽆论如何都要退出，并且操作系统将负责
//回收其所有内存。但是，如果你使⽤了内存泄漏检查程序，该程序需要释放每个最后对象，或者你正在
//编写可以由单个进程多次加载和卸载的库，那么你可能希望强制使⽤ Protocol Buffers 来清理所有
//内容。
 google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
