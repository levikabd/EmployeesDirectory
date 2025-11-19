#include <pqxx/pqxx>
#include <iostream>

#include <vector>
// #include <string>


class EmployeeDB {
private:
    pqxx::connection m_conn;

    std::vector<std::string> russian_surnames;    
public:
    EmployeeDB(const std::string& conn_str) : m_conn(conn_str) {};

    // 1
    void createTable();

    // 2
    void addEmployee(const std::string&, const std::string&, const std::string&);
    
    // 3
    void listEmployees();

    // 4
    void fillDirectory();
    void newEmployee(std::string*, std::string*, std::string*, size_t);
    void packetAddEmployee();
    void autoAddEmployee1000000();

    // 5
    void listEmployees_f();

    // 6
    void optimizeDB();

};