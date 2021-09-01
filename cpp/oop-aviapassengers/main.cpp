#include <cstdio>
#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <iomanip>

enum GeoType {CITY};
//Страна или город
struct GeoObject {
    GeoType type;
    std::string name;
};
struct DateTime
{
    int day;
    int month;
    int year;
    public:
        std::string getFormatted() {
            std::string formattedDate;
            formattedDate += this->day > 0 && this->day <= 9 ? "0" + std::to_string(this->day) : std::to_string(this->day);
            formattedDate += "-" + (this->month > 0 && this->month <= 9 ? "0" + std::to_string(this->month) : std::to_string(this->month));
            formattedDate += "-" + (this->year >= 0 && this->year <= 99 ? "20" + std::to_string(this->year) : std::to_string(this->year));

            return formattedDate;
        }
};
struct Passenger
{
    //идентификатор пассажира в таблице
    int id;
    //код авиапредприятия
    std::string airline_code;
    //город назначения
    GeoObject destination_city;
    //номер рейса
    std::string flight_number;
    //дата вылета
    DateTime departure_date;
    //имя пассажира
    std::string name;
    //фамилия пассажира
    std::string surname;
};
class Menu {
    private:
        int columnWidth = 20;
    public:
        std::string items[6] = {"Add", "Delete", "Edit", "ShowTable", "AddTest", "Quit"};
        bool isQuitCmd = false;
        std::vector<Passenger> passengers {};
        std::string getItemsText() {
            return "Введите [Add] добавить | [AddTest] добавить тестового пассажира | [Delete] удалить | [Edit] изменить| [ShowTable] показать таблицу | [Quit] завершить программу (примеры \"Add\" или \"Delete\"):";
        };
        bool addNewPassenger() {
            char input[21];
            int inputInt = 0;
            int tryCnt = 3;
            Passenger newPassenger;
            newPassenger.id = this->passengers.empty() ? 1 : (this->passengers[this->passengers.size() - 1].id + 1);
            std::cout << "Введите имя пассажира" << std::endl;
            scanf_s("%s", input, 21);
            newPassenger.name = input;
            std::cout << "Введите фамилию пассажира" << std::endl;
            scanf_s("%s", input, 21);
            newPassenger.surname = input;
            std::cout << "Введите город назначения" << std::endl;
            scanf_s("%s", input, 21);
            GeoObject passengerCity = {GeoType::CITY, input};
            newPassenger.destination_city = passengerCity;
            std::cout << "Введите код или название авиакомпании" << std::endl;
            scanf_s("%s", input, 21);
            newPassenger.airline_code = input;
            std::cout << "Введите номер рейса" << std::endl;
            scanf_s("%s", input, 21);
            newPassenger.flight_number = input;
            DateTime departure_date;
            do {
                std::cout << "Введите дату вылета (день) [1-31]" << std::endl;
                if (tryCnt-- < 0) {
                    break;
                }
                scanf_s("%i", &inputInt);
            } while (inputInt < 1 || inputInt > 31);
            departure_date.day = inputInt;
            do {
                std::cout << "Введите дату вылета (месяц) [1-12]" << std::endl;
                if (tryCnt-- < 0) {
                    break;
                }
                scanf_s("%d", &inputInt);
            } while (inputInt < 1 || inputInt > 12);
            departure_date.month = inputInt;
            do {
                std::cout << "Введите дату вылета (год) [19-21]" << std::endl;
                if (tryCnt-- < 0) {
                    break;
                }
                scanf_s("%d", &inputInt);
            } while (inputInt < 19 || inputInt > 21);
            departure_date.year = inputInt;

            newPassenger.departure_date = departure_date;
            try {
                this->passengers.push_back(newPassenger);
                std::cout << "Пассажир добавлен" << std::endl;
            }
            catch(const std::bad_alloc &) {
                std::cout << "Пассажир НЕ добавлен (максимум 9 пассажиров)" << std::endl;
            }
            catch(const std::exception &) {
                std::cout << "Пассажир НЕ добавлен (ошибка)" << std::endl;
            }

            return true;
        };
        bool editPassengers() {
            int id = 0;
            int pos = 0;

            std::cout << "Укажите id пассажира" << std::endl;
            scanf_s("%d", &id);
            if (id > 0) {
                for (Passenger &i : this->passengers) {
                    if (i.id == id) {
                        return this->editPassenger(i);
                    }
                    pos++;
                }
            } else {
                std::cout << "Ошибка, id выходит за рамки диапазона" << std::endl;
            }

            return false;
        };
        bool editPassenger(Passenger &passenger) {
            char input[8];
            char field[21];
            std::string strInp;
            std::cout << "Какое поле отредактировать? [name | surname | airline]" << std::endl;
            scanf_s("%s", input, 8);
            strInp = input;
            if (strInp == "name") {
                std::cout << "Введите новое значение (текущее: " << passenger.name << ")" << std::endl;
                scanf_s("%s", field, 21);
                passenger.name = field;
            } else if (strInp == "surname") {
                std::cout << "Введите новое значение (текущее: " << passenger.surname << ")" << std::endl;
                scanf_s("%s", field, 21);
                passenger.surname = field;
            } else if (strInp == "airline") {
                std::cout << "Введите новое значение (текущее: " << passenger.airline_code << ")" << std::endl;
                scanf_s("%s", field, 21);
                passenger.airline_code = field;
            } else {
                std::cout << "Поле не разрешено редактировать" << std::endl;
                return false;
            }
            std::cout << "Изменено" << std::endl;

            return true;
        };
        bool addTestPassenger() {
            Passenger newPassenger;
            newPassenger.id = this->passengers.empty() ? 1 : (this->passengers[this->passengers.size() - 1].id + 1);
            newPassenger.name = "testname";
            newPassenger.surname = "testsurname";
            GeoObject city = {GeoType::CITY, "testcity"};
            newPassenger.destination_city = city;
            newPassenger.airline_code = "SU";
            newPassenger.flight_number = "123";
            DateTime dateTime = {1, 12, 21};
            newPassenger.departure_date = dateTime;
            try {
                this->passengers.push_back(newPassenger);
                std::cout << "Пассажир добавлен" << std::endl;
            }
            catch(const std::bad_alloc &) {
                std::cout << "Пассажир НЕ добавлен (максимум 9 пассажиров)" << std::endl;
            }
            catch(const std::exception &) {
                std::cout << "Пассажир НЕ добавлен (ошибка)" << std::endl;
            }

            return true;
        }
        bool showTable() {
            std::cout << "Введите ширину столбца (кол-во символов) [20]" << std::endl;
            std::cin >> this->columnWidth;
            if (this->columnWidth < 5) {
                this->columnWidth = 20;
            }
            std::cout << std::left;
            std::cout
                << std::setw(this->columnWidth) << "[id]"
                << std::setw(this->columnWidth) << "[name]"
                << std::setw(this->columnWidth) << "[surname]"
                << std::setw(this->columnWidth) << "[destination city]"
                << std::setw(this->columnWidth) << "[airline]"
                << std::setw(this->columnWidth) << "[flight]"
                << std::setw(this->columnWidth) << "[departure date]"
                << '\n';
            for (Passenger& i : this->passengers) {
                std::cout << std::left;
                std::cout
                    << std::setw(this->columnWidth) << i.id
                    << std::setw(this->columnWidth) << i.name
                    << std::setw(this->columnWidth) << i.surname
                    << std::setw(this->columnWidth) << i.destination_city.name
                    << std::setw(this->columnWidth) << i.airline_code
                    << std::setw(this->columnWidth) << i.flight_number
                    << std::setw(this->columnWidth) << i.departure_date.getFormatted()
                    << '\n';
            }

            return true;
        };
        bool deletePassenger() {
            int id = 0;
            int pos = 0;
            std::cout << "Укажите id пассажира" << std::endl;
            scanf_s("%d", &id);
            if (id > 0) {
                for (const Passenger &i : this->passengers) {
                    if (i.id == id) {
                        this->passengers.erase(this->passengers.begin() + pos);
                        return true;
                    }
                    pos++;
                }
            } else {
                std::cout << "Ошибка, id выходит за рамки диапазона" << std::endl;
            }

            return false;
        };
        bool executeItem(std::string& item) {
            if (this->items[0] == item) {//Add
                std::cout << "<Выбрано Добавление пассажира>" << std::endl;
                return this->addNewPassenger();
            } else if (this->items[1] == item) {//Delete
                std::cout << "<Выбрано Удаление пассажира>" << std::endl;
                if (this->deletePassenger()) {
                    std::cout << "Удален" << std::endl;
                } else {
                    std::cout << "Не найден" << std::endl;
                }

                return true;
            } else if (this->items[2] == item) {//Edit
                std::cout << "<Выбрано Изменение пассажира>" << std::endl;
                return this->editPassengers();
            } else if (this->items[3] == item) {//ShowTable
                std::cout << "<Выбрано Отображение таблицы>" << std::endl;
                return this->showTable();
            } else if (this->items[4] == item) {//AddTest
                std::cout << "<Выбрано Добавление тестового пассажира>" << std::endl;
                this->addTestPassenger();
            } else if (this->items[5] == item) {//Quit
                std::cout << "<Выбран Выход>" << std::endl;
                this->isQuitCmd = true;
                return true;
            }

            return false;
        };
};

std::string chooseMenuItem(Menu& menu) {
    char menuCmd[21] = "";

    while (std::find(std::begin(menu.items), std::end(menu.items), menuCmd) == std::end(menu.items)) {
        //секретное инициализирующее "слово", чтобы не выводить предупреждение первый раз
        if (std::strcmp(menuCmd, "") != 0) {
            std::cout << "Элемент " << menuCmd << " не найден в меню, попробуйте еще раз" << std::endl;
        }
        std::cout << menu.getItemsText() << std::endl;
        scanf_s("%s", menuCmd, 21);
    }

    return menuCmd;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    std::string menuCmd;
    std::string quitCmd = "Quit";
    Menu menu;

    std::cout << "<Программа принимает только латинские символы>" << std::endl;
    while (menuCmd != quitCmd) {
        menuCmd = chooseMenuItem(menu);
        menu.executeItem(menuCmd);
        if (menu.isQuitCmd) {
            break;
        }
        std::cout << "<Для завершения программы введите Quit (все данные будут удалены)>" << std::endl;
    }

    std::cout << "Конец" << std::endl;

    return 0;
}