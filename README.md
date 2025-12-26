<div align="center">
<h1>EmployeesDirectory</h1>
</div>

* The application is launched from the console with the parameters. The first parameter passed at startup selects the operating mode of the application corresponding to the task item. 
* English is used for the full name. 
* The application connects to the Postgresql database using the PQXX libraries.
* The development uses an object-oriented approach.
* The C++ programming language is used as the development environment.

**Application operating modes:**

* 1. Create a table with employee directory fields representing "Last Name, First Name, Patronymic", "Date of birth", "Gender".
**Application launch example:**
```shell
EmployeesDirectory 1
```

* 2. Create an employee directory entry.
To work with the data, a class and a class object are created with the data entered by the user. 
A string is generated, an object is created, and it is sent to the database.
The object must have the following methods:
	* sends the object to the database;
	* calculates the age (full years).
**Example of running in 2 mode:**
```shell
EmployeesDirectory 2 "Ivanov Petr Sergeevich" 2009-07-12 Male
```

* 3. Output of all lines of the employee directory, with a unique value of full name+date, sorted by full name. 
The full name, date of birth, gender, and number of full years are displayed.
**Application launch example:**
```shell
EmployeesDirectory 3
```

* 4. 1,000,000 lines of the employee directory are filled in automatically. The gender distribution is alternating. The initial letter of the full name is also. 
Additionally, the class has a method that batch sends data to the database by accepting an array of objects.
100 lines are filled in automatically, in which the gender is male and the last name begins with "F".
**Application launch example:**
```shell
EmployeesDirectory 4
```

* 5. Output of the sample from the table according to the criterion: gender is male, Last name begins with "F". The execution time is measured and displayed.
**Application launch example:**
```shell
EmployeesDirectory 5
```

* 6. The database is being optimized, and an index is added to the employees table to speed up the implementation of paragraph 5.
**Application launch example:**
```shell
EmployeesDirectory 6
```
