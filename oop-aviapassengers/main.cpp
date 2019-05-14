#include <cstdio>
#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>

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
    public:
        std::string items[4] = {"Add", "Delete", "Edit", "ShowTable"};
        std::vector<Passenger> passengers;
        std::string getItemsText() {
            return "Введите [Add] (добавить) | [Delete] удалить | [Edit] изменить| [ShowTable] показать таблицу (примеры \"Add\" или \"Delete\"):";
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
            try {
                this->passengers.push_back(newPassenger);
                std::cout << "Пассажир добавлен" << std::endl;
            }
            catch(const std::bad_alloc &) {
                std::cout << "Пассажир НЕ добавлен (максимум 9 пассаижров)" << std::endl;
            }
            catch(const std::exception &) {
                std::cout << "Пассажир НЕ добавлен (ошибка)" << std::endl;
            }

            return true;
        };
        bool executeItem(std::string& item) {
            if (this->items[0] == item) {//Add
                std::cout << "<Выбрано Добавление пассажира>" << std::endl;
                return this->addNewPassenger();
            } else if (this->items[1] == item) {//Delete
                std::cout << "<Выбрано Удаление пассажира>" << std::endl;
            } else if (this->items[2] == item) {//Edit
                std::cout << "<Выбрано Изменение пассажира>" << std::endl;
            } else if (this->items[2] == item) {//ShowTable
                std::cout << "<Выбрано Отображение таблицы>" << std::endl;
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
    Menu menu;

    std::cout << "<Программа принимает только латинские символы>" << std::endl;
    menuCmd = chooseMenuItem(menu);
    menu.executeItem(menuCmd);

    std::cout << "Конец" << std::endl;

    return 0;
}