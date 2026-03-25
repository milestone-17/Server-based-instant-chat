#include<iostream>
#include"contacts.pb.h"

int main(){
    std::string people_str;
    
        //对一个联系人,使用pb序列化,并将结果打印除了
        contacts::PeopleInfo people;
        people.set_age(20);
        people.set_name("张三");
        // 调⽤序列化⽅法，将序列化后的⼆进制序列存⼊string中
        if(!people.SerializeToString(&people_str)){//SerializeToString--序列化为字符串
            std::cout<<"序列化联系⼈失败."<<std::endl;
            return -1;
        }
        //// 打印序列化结果
        std::cout<<"序列化联系人"<<people_str<<std::endl;//二进制

        //// 调⽤反序列化⽅法，读取string中存放的⼆进制序列，并反序列化出对象
        contacts::PeopleInfo pe;
        if(!pe.ParseFromString(people_str)){
            std::cout<<"反序列化失败"<<std::endl;
            return -1;
        }
        std::cout<<"反序列化的年龄 :"<<pe.age()<<std::endl;
        std::cout<<"反序列化的姓名"<<pe.name()<<std::endl;


    

    return 0;
}
