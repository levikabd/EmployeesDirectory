#include <pqxx/pqxx>
#include <iostream>

//#include <thread>

#include "employee.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Not enough parameters!" << std::endl;
        return 1;
    };
    
    int mode = atoi(argv[1]);   
    
    std::string num2 = "";
    std::string num3 = "";
    std::string num4 = "";

    if (mode==2)
    {
        if (argc>=3){
            num2 = std::string(argv[2]);
        };
        if (argc>=4){
            num3 = std::string(argv[3]);
        };
        if (argc>=5){
            num4 = std::string(argv[4]);
        };
    };
    
    // log out
    std::cout << "Mode: " << mode << std::endl;

//    if ((mode<1) || (mode>6))
    if ((mode<1) || (mode>6))
    {
        std::cout << "Invalid parameter: " << mode << std::endl;
        return 1;
    };
    
    if ((mode==2)&(argc<4)) 
    {
        std::cout << "Not enough parameters! " << std::endl;
        return 1;
    };    

    try {
        //EmployeeDB db("dbname=employees user=postgres");
        EmployeeDB db("dbname = employees user = postgres password = postgres \
        hostaddr = 127.0.0.1  port = 5432");

        if (mode==1){           
            db.createTable();
            return 0;
        };
        if(mode==2){
            // 2 добавления сотрудника
            //db.addEmployee("Ivanov Petr Sergeevich", "2020-01-01", "male");
            db.addEmployee(num2, num3, num4);
            
        } else if(mode==3){
            // 3 Вывод списка сотрудников
            db.listEmployees();

        } else if(mode==4){
            // 4 создание 1 000 000 сотрудников
            db.fillDirectory();

            // std::thread employeeMln(db.autoAddEmployee1000000(), NULL);
            // std::thread emploeeSto(db.packetAddEmployee(), NULL);
            // if (employeeMln.joinable()){employeeMln.join();};
            // if (emploeeSto.joinable()){emploeeSto.join();};

            db.autoAddEmployee1000000();
            db.packetAddEmployee();
        
        } else if(mode==5){
            // 5 результат выборки из таблицы
            db.listEmployees_f();

        } else if(mode==6){
            // 6 оптимизация базы 
            db.optimizeDB();       

        // } else if(mode==7){
        //     // 7 packet create 100
        //     db.packetAddEmployee();     
        };

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    };
    
    return 0;
};
