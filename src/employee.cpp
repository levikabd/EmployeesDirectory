#include <pqxx/pqxx>
#include <iostream>
#include <fstream>

#include <string>
#include <ctime>
#include <random>

#include "employee.h"

//#define RAND_MAX 38325

// class EmployeeDB {
// private:
//    pqxx::connection m_conn;
//    std::vector<std::string> russian_surnames; 
// public:
//     EmployeeDB(const std::string& conn_str) 
//         : m_conn(conn_str) {}

    // 1 
    void EmployeeDB::createTable() {
        pqxx::work txn(m_conn);
        txn.exec("CREATE TABLE IF NOT EXISTS employees (id SERIAL PRIMARY KEY, name VARCHAR(100), dateob VARCHAR(10), gender VARCHAR(6));");
        txn.commit();
    };

    // 2
    void EmployeeDB::addEmployee(const std::string& name, const std::string& dateob,  const std::string& gender)
    {
        pqxx::work txn(m_conn);
        txn.exec_params("INSERT INTO employees (name, dateob, gender) "
                "VALUES ($1, $2, $3) ", 
                pqxx::internal::params{name, dateob, gender});
        txn.commit();
    };

    int countYears(std::string date)
    {
        // date 10 char
        // 2025-11-18

        // if (date.size()<10)
        // {
        //     std::cout << "Date of birth is incorrect." << std::endl;
        // };

        if (date.size()<4)
        {
            //std::cout << "Date of birth is incorrect." << std::endl;
            return 0;        
        };        

        int years, year_birth, month_birth; // day_birth;
        int year_today, month_today; //day_today;

        time_t timestamp = time(NULL);
        struct tm datetime = *localtime(&timestamp);
        year_today = datetime.tm_year+1900;
        month_today = datetime.tm_mon+1;
        //std::cout << "Today: y: " << year_today << ", m: " << month_today << "\n";
        
        // 2025-11-18
        year_birth = stoi(date.substr(0, 4));

        years = year_today - year_birth;

        if (date.size()<7)
        {
            if (years<0)
            {
                return 0;
            } else {
                return years;
            };
        };
        
        // 2025-11-18
        month_birth = stoi(date.substr(5, 2));     

        if (month_today < month_birth){years--;};

        if (years<0)
        {
            return 0;
        };                

        return years;
    };

    // 3
    void EmployeeDB::listEmployees() 
    {
        clock_t start = clock();

        pqxx::work txn(m_conn);
        pqxx::result res = txn.exec("SELECT * FROM employees ORDER BY name");        
        for (const auto& row : res) {
            std::cout << "Name:   " << row["name"]   << " | "
                      << "Dateob: " << row["dateob"] << " | "
                      << "Gender: " << row["gender"] << " | "
                      << "Age:    " << countYears(pqxx::to_string(row["dateob"])) << std::endl;
        };

        clock_t end = clock();
        double elapsed = double(end - start) / CLOCKS_PER_SEC;
        std::cout << std::endl;
        std::cout << "======================================================" << std::endl;
        std::cout << "Elapsed time: " << elapsed << " seconds." << std::endl;
    };

    // 4
    void EmployeeDB::fillDirectory()
    {
            std::string line="";
            std::ifstream file("russian_surnames.txt");
            if (file.is_open()!=true)
            {
                std::cout << "File 'russian_surnames.txt' is not open! \n";
                russian_surnames.push_back("Fedorov");
                return;
            };            

            while (!file.eof())
            {
                file >> line;
                russian_surnames.push_back(line);
            }; // end file                  
            file.close();     

            //log out
            std::cout << "The directory has been filled in." << std::endl;
    };

    std::string generator7()
    {
        std::string suff = "";
        for (size_t i = 0; i < 7; i++)
        {
            srand(i);
            int cKode    = rand() % 25;
            char newChar = 'a' + cKode;
            suff.push_back(newChar);
        };       
        return suff;
    };

    void EmployeeDB::newEmployee(std::string* name, std::string* dateob, std::string* gender, size_t iter)
    {
        // max = 38325 to 2005  
        srand(iter);      
        int dayob = rand() % 38325;
        int year0 = dayob/365;
        int day0 = dayob % 365;
        int year = 1900 + year0;
        int month = day0 / 30;
        int day = day0 % 30;        
        std::string yearS  = std::to_string(year);
        std::string monthS = std::to_string(month);
        std::string dayS   = std::to_string(day);
        if (monthS.size()<2)
        {
            monthS = "0" + monthS;
        };
        if (dayS.size()<2)
        {
            dayS = "0" + dayS;
        };      

        *dateob= yearS + "-" + monthS + "-" + dayS;
        if (*gender != "male")
        {
            if ((iter%2)==1)
            {
                *gender ="female";            
            }else{
                *gender="male";
            };
        };        
        
        std::string family = "";
        int sizeD=russian_surnames.size();
        if (sizeD>1)
        {
            srand(iter);
            int pos = rand() % sizeD;
            family  = russian_surnames.at(pos);
        }else
        {
            std::string family = "Fedor";
        };

        family = family+generator7();
        if (*gender == "female")
        {
            family+="a";
        };

        std::string fio="";
        if (*gender=="female")
        {
            fio = "Polina Sergeevna";
        }else
        {
            fio = "Petr Sergeevich";
        };               

        fio = family + " " + fio;
        srand(iter);
        int newInt=rand();
        size_t numC = newInt % 25;
        char Zag = 'A' + numC;
        *name = Zag + fio;
    };

    void EmployeeDB::packetAddEmployee()
    {
        clock_t start = clock();
        
        std::string sql="";
        std::string sqlinsert = "INSERT INTO employees (name, dateob, gender) VALUES (";
        // std::string sqlvalues = "VALUES (";
        std::string sqlend = "); ";
        for (size_t i = 0; i < 100; i++)
        {
            std::string addsql="", sqlname="", sqldateob="", sqlgender="";
            // std::string addsql="", sqlinsert="", sqlvalues="", sqlend="", sqlname="", sqldateob="", sqlgender="";
            // addsql = "INSERT INTO MYSTORE (ID,ТИП,ЦВЕТ,МАТЕРИАЛ,ЗАПАС,ЦЕНА) "  \
            // "VALUES (1, 'Футболка', 'Синий', 'Хлопок', 500, 2000.00 ); " \
            // "";
            //"VALUES ($1, $2, $3) ", 
            //pqxx::internal::params{name, dateob, gender});

            sqlgender = "male";
            newEmployee(&sqlname, &sqldateob, &sqlgender, i);
                      
            addsql =  addsql + sqlinsert;
            // addsql =  addsql + sqlvalues;
            addsql =  addsql + "'F" + sqlname   +"', ";
            addsql =  addsql + "'" + sqldateob +"', ";
            addsql =  addsql + "'"+sqlgender+"'";
            addsql =  addsql + sqlend;

            sql =  sql + addsql;
            //strcat(sql, addsql);
        };
        
        //std::cout << sql << "\n";

        pqxx::work txn(m_conn);
        txn.exec(sql);
        txn.commit();
        std::cout << "100 записей успешно создано." << std::endl;

        clock_t end = clock();
        double elapsed = double(end - start) / CLOCKS_PER_SEC;
        std::cout << std::endl;
        std::cout << "======================================================" << std::endl;
        std::cout << "Elapsed time: " << elapsed << " seconds." << std::endl;

    };

    void EmployeeDB::autoAddEmployee1000000()
    {
        clock_t start = clock();
        pqxx::work txn(m_conn);

        for (size_t i = 0; i < 1000000; i++)
        {
            std::string name="", dateob="", gender="";
            newEmployee(&name, &dateob, &gender,i);

            txn.exec_params("INSERT INTO employees (name, dateob, gender) "
                "VALUES ($1, $2, $3) ", 
            pqxx::internal::params{name, dateob, gender});
            txn.commit();
        };
        
        clock_t end = clock();
        double elapsed = double(end - start) / CLOCKS_PER_SEC;
        std::cout << std::endl;
        std::cout << "======================================================" << std::endl;
        std::cout << "Elapsed time: " << elapsed << " seconds." << std::endl;
    };


    // 5
    void EmployeeDB::listEmployees_f()
    {
        clock_t start = clock();

        pqxx::work txn(m_conn);
        pqxx::result res = txn.exec("SELECT * FROM employees WHERE name LIKE 'F%' AND gender = 'male'");        
        for (const auto& row : res) {
            std::cout << "Name: " << row["name"] << " | "
                      << "Dateob: " << row["dateob"] << " | "
                      << "Gender: " << row["gender"] << " | "
                      << "Age: " << countYears(pqxx::to_string(row["dateob"])) << std::endl;
        };

        clock_t end = clock();
        double elapsed = double(end - start) / CLOCKS_PER_SEC;
        std::cout << std::endl;
        std::cout << "======================================================" << std::endl;
        std::cout << "Elapsed time: " << elapsed << " seconds." << std::endl;
    };

    // 6
    void EmployeeDB::optimizeDB()
    {
        pqxx::work txn(m_conn);
        txn.exec("CREATE INDEX name_idx ON employees (name);");
        txn.commit();
    };

// };