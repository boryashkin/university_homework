#include <cstdio>
#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <iomanip>

enum GeoType {COUNTRY, CITY};
//Страна или город
struct GeoObject {
    GeoType type;
    //страна для города (пока не используется)
    GeoObject *parent;
    std::string name;
};
struct DateTime
{
    int year;
    int month;
    int day;
};
struct Passenger
{
    //идентификатор пассажира в таблице
    int id;
    //код авиапредприятия
    std::string airline_code;
    //город назначения
    GeoObject *destination_city;
    //номер рейса
    int flight_number;
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
        std::string items[5] = {"Add", "Delete", "Edit", "ShowTable", "Quit"};
        bool isQuitCmd = false;
        std::vector<Passenger> passengers;
        std::string getItemsText() {
            return "Введите [Add] (добавить) | [Delete] удалить | [Edit] изменить| [ShowTable] показать таблицу | [Quit] завершить программу (примеры \"Add\" или \"Delete\"):";
        };
        bool addNewPassenger() {
            char input[51];
            int inputInt = 0;
            Passenger newPassenger;
            std::cout << "Введите имя пассажира" << std::endl;
            scanf_s("%s", input, 51);
            newPassenger.name = input;
            std::cout << "Введите фамилию пассажира" << std::endl;
            scanf_s("%s", input, 51);
            newPassenger.surname = input;
            std::cout << "Введите город назначения" << std::endl;
            scanf_s("%s", input, 51);
            GeoObject passengerCity;
            passengerCity.type = GeoType::CITY;
            passengerCity.name = input;
            newPassenger.destination_city = &passengerCity;
            std::cout << "Введите код или название авиакомпании" << std::endl;
            scanf_s("%s", input, 51);
            newPassenger.airline_code = input;
            std::cout << "Введите номер рейса" << std::endl;
            std::cin >> inputInt;
            newPassenger.flight_number = inputInt;
            DateTime departure_date;
            std::cout << "Введите дату вылета (день) [1-31]" << std::endl;
            std::cin >> inputInt;
            departure_date.day = inputInt;
            std::cout << "Введите дату вылета (месяц) [1-31]" << std::endl;
            std::cin >> inputInt;
            departure_date.month = inputInt;
            std::cout << "Введите дату вылета (год) [19-21]" << std::endl;
            std::cin >> inputInt;
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
        std::string showTable() {
            std::cout << "Введите ширину столбца (кол-во символов) [20]" << std::endl;
            std::cin >> this->columnWidth;
            if (this->columnWidth < 5) {
                this->columnWidth = 20;
            }
            std::cout << std::left;
            std::cout
                << std::setw(this->columnWidth) <<  "[Имя]"
                << std::setw(this->columnWidth) <<  "[Фамилия]"
                << std::setw(this->columnWidth) <<  "[Город]"
                << std::setw(this->columnWidth) <<  "[Авиакомпания]"
                << std::setw(this->columnWidth) <<  "[Рейс]"
                << std::setw(this->columnWidth) <<  "[Дата вылета]"
                << std::endl;
            for (const Passenger& i : this->passengers) {
                std::cout
                    << std::setw(this->columnWidth) <<  i.name
                    << std::setw(this->columnWidth) <<  i.surname
                    << std::setw(this->columnWidth) <<  i.destination_city->name
                    << std::setw(this->columnWidth) <<  i.airline_code
                    << std::setw(this->columnWidth) <<  i.flight_number
                    << std::setw(this->columnWidth) <<  i.departure_date.day << "-" << i.departure_date.month << "-" << i.departure_date.year
                    << std::endl;
            }

            return "end";
        };
        bool executeItem(std::string& item) {
            if (this->items[0] == item) {//Add
                std::cout << "<Выбрано Добавление пассажира>" << std::endl;
                return this->addNewPassenger();
            } else if (this->items[1] == item) {//Delete
                std::cout << "<Выбрано Удаление пассажира>" << std::endl;
            } else if (this->items[2] == item) {//Edit
                std::cout << "<Выбрано Изменение пассажира>" << std::endl;
            } else if (this->items[3] == item) {//ShowTable
                std::cout << "<Выбрано Отображение таблицы>" << std::endl;
                std::cout << this->showTable() << std::endl;
            } else if (this->items[4] == item) {//ShowTable
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
        std::cout << "<Для завершения программы введите Quit>" << std::endl;
    }

    std::cout << "Конец" << std::endl;

    return 0;
}