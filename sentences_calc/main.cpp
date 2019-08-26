#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>

enum State {
    q1,
    q2,
    q3,
    q4,
    q5,
    q6,
    q7,
    q8,
    qEnd,
    qErr
};
enum Move {
    LEFT,
    STAY,
    RIGHT
};

struct Step {
    State nextState;
    char out;
    Move move;
};

struct ConfigKey {
    State state;
    char cellValue;

    bool operator==(const ConfigKey &other) const
    {
        return (state == other.state && cellValue == other.cellValue);
    }
};
template <>
struct std::hash<ConfigKey>
{
    std::size_t operator()(const ConfigKey& k) const
    {
        using std::size_t;
        using std::hash;
        using std::string;

        // Compute individual hash values for first,
        // second and third and combine them using XOR
        // and bit shifting:

        //todo: разобраться в этом
        return ((hash<State>()(k.state) ^ (hash<char>()(k.cellValue) << 1)) >> 1);
    }
};

std::unordered_map<ConfigKey, Step> config;

void appendSpaceToEnd(std::fstream& fs)
{
    std::cout << "<Append a space>" << std::endl;
    //можно было использовать peek для проверки
    fs.clear();
    fs.seekp(0, std::fstream::end);
    fs.put(' ');
    fs.seekp((fs.tellp() - static_cast<std::streampos>(1)));
}
void moveHeadTo(std::fstream& fs, Move move)
{
    // for fstream, seekp and seekg use the same pointer
    if (move == Move::RIGHT) {
        std::cout << "[Move right]" << std::endl;
        fs.seekp((fs.tellp() + static_cast<std::streampos>(1)));
    } else if (move == Move::LEFT) {
        std::cout << "[Move left]" << std::endl;
        fs.seekp((fs.tellp() - static_cast<std::streampos>(1)));
    }
}
char readCell(std::fstream& fs)
{
    char cell;
    fs.get(cell);
    if (fs.eof()) {
        //костыль для возврата кракозябры перед "eof"
        appendSpaceToEnd(fs);
        fs.get(cell);
    }
    //get переносит указатель вправо, возвращаем назад, т.к. у нас есть своя функция для перемещения
    fs.seekp((fs.tellp() - static_cast<std::streampos>(1)));

    return cell;
}
void writeCell(std::fstream& fs, char value)
{
    fs.put(value);
    fs.seekp((fs.tellp() - static_cast<std::streampos>(1)));
}
Step getNextStep(State currentState, char cell)
{
    //подменяем значение в случае буквы алфавита (чтоб не выписывать всё в конфиг, там просто "a")
    char newCellValue = cell;
    bool found = false;
    Step next = {};
    if (cell != ' ' && cell != '.' && cell != '~' && cell != '1' && cell != '=') {
        newCellValue = 'a';
    }

    for (auto itr = config.find({currentState, newCellValue}); itr != config.end(); itr++) {
        found = true;
        // itr works as a pointer to pair<string, double>
        // type itr->first stores the key part  and
        // itr->second stores the value part
        next = itr->second;
        if (newCellValue == 'a' || next.out == 'a') {
            next.out = cell;
        }
        //иначе итератор будет перебирать. Нам надо только один step
        break;

    }
    if (!found) {
        std::cout << "Config not found";
        return {State::qErr, ' ', Move::STAY};
    }

    return next;
}

int main()
{
    setlocale(LC_ALL, "ru");

    //q1 - поиск "."
    config.insert({{State::q1, '.'}, {State::q2, '.', Move::RIGHT}});
    config.insert({{State::q1, ' '}, {State::q8, ' ', Move::RIGHT}});
    config.insert({{State::q1, '1'}, {State::q1, '1', Move::RIGHT}});
    config.insert({{State::q1, '='}, {State::q1, '=', Move::RIGHT}});
    config.insert({{State::q1, '~'}, {State::qEnd, '~', Move::STAY}});
    config.insert({{State::q1, 'a'}, {State::q1, 'a', Move::RIGHT}});
    //q2 - поиск ". "
    config.insert({{State::q2, '.'}, {State::q2, '.', Move::RIGHT}});
    config.insert({{State::q2, ' '}, {State::q6, ' ', Move::LEFT}});
    config.insert({{State::q2, '1'}, {State::q1, '1', Move::RIGHT}});
    config.insert({{State::q2, '='}, {State::q1, '=', Move::RIGHT}});
    config.insert({{State::q2, '~'}, {State::qEnd, '~', Move::STAY}});
    config.insert({{State::q2, 'a'}, {State::q1, 'a', Move::RIGHT}});
    //q6 - замена точки перед пробелом на "~"
    config.insert({{State::q6, '.'}, {State::q3, '~', Move::RIGHT}});
    config.insert({{State::q6, ' '}, {State::qEnd, ' ', Move::STAY}});//в эти состояния он не должен зайти
    config.insert({{State::q6, '1'}, {State::qEnd, '1', Move::STAY}});
    config.insert({{State::q6, '='}, {State::qEnd, '=', Move::STAY}});
    config.insert({{State::q6, '~'}, {State::qEnd, '~', Move::STAY}});
    config.insert({{State::q6, 'a'}, {State::qEnd, 'a', Move::STAY}});
    //q3 - поиск конца текста
    config.insert({{State::q3, '.'}, {State::q3, '.', Move::RIGHT}});
    config.insert({{State::q3, ' '}, {State::q7, ' ', Move::RIGHT}});
    config.insert({{State::q3, '1'}, {State::q3, '1', Move::RIGHT}});
    config.insert({{State::q3, '='}, {State::q3, '=', Move::RIGHT}});
    config.insert({{State::q3, '~'}, {State::q3, '~', Move::RIGHT}});
    config.insert({{State::q3, 'a'}, {State::q3, 'a', Move::RIGHT}});
    //q7 - проверка двойного пробела или "=" (конец файла, куда писать результат)
    config.insert({{State::q7, '.'}, {State::q3, '.', Move::RIGHT}});
    config.insert({{State::q7, ' '}, {State::q4, '=', Move::RIGHT}});
    config.insert({{State::q7, '1'}, {State::q3, '1', Move::RIGHT}});
    config.insert({{State::q7, '='}, {State::q4, '=', Move::RIGHT}});
    config.insert({{State::q7, '~'}, {State::q3, '~', Move::RIGHT}});
    config.insert({{State::q7, 'a'}, {State::q3, 'a', Move::RIGHT}});
    //q4 - проверка двойного пробела, добавление "1" к результату
    config.insert({{State::q4, '.'}, {State::q3, '.', Move::RIGHT}});
    config.insert({{State::q4, ' '}, {State::q5, '1', Move::LEFT}});
    config.insert({{State::q4, '1'}, {State::q4, '1', Move::RIGHT}});
    config.insert({{State::q4, '='}, {State::q3, '=', Move::RIGHT}});
    config.insert({{State::q4, '~'}, {State::q3, '~', Move::RIGHT}});
    config.insert({{State::q4, 'a'}, {State::q3, 'a', Move::RIGHT}});
    //q5 - возврат "." на место "~"
    config.insert({{State::q5, '.'}, {State::q5, '.', Move::LEFT}});
    config.insert({{State::q5, ' '}, {State::q5, ' ', Move::LEFT}});
    config.insert({{State::q5, '1'}, {State::q5, '1', Move::LEFT}});
    config.insert({{State::q5, '='}, {State::q5, '=', Move::LEFT}});
    config.insert({{State::q5, '~'}, {State::q1, '.', Move::RIGHT}});
    config.insert({{State::q5, 'a'}, {State::q5, 'a', Move::LEFT}});
    //q8 - Стоп при двойном пробеле на поиске
    config.insert({{State::q8, '.'}, {State::q1, '.', Move::RIGHT}});
    config.insert({{State::q8, ' '}, {State::qEnd, ' ', Move::STAY}});
    config.insert({{State::q8, '1'}, {State::q1, '1', Move::RIGHT}});
    config.insert({{State::q8, '='}, {State::q1, '=', Move::RIGHT}});
    config.insert({{State::q8, '~'}, {State::q1, '.', Move::RIGHT}});
    config.insert({{State::q8, 'a'}, {State::q1, 'a', Move::RIGHT}});

    char cell;
    Step step = {State::q1};//initiated with default or "current" state

    std::fstream fs("example.txt", std::fstream::in | std::fstream::out);
    if (!fs.is_open() || !fs.good()) {
        std::cout << "Failed to open a file 'example.txt'";
        return 1;
    }

    while (step.nextState != State::qEnd) {
        cell = readCell(fs);
        std::cout << "Read: " << cell << std::endl;
        std::cout << "State: " << step.nextState << std::endl;

        step = getNextStep(step.nextState, cell);

        std::cout << "Write: " << step.out << std::endl;
        std::cout << "Next state: " << step.nextState << std::endl;
        std::cout << "Move: " << step.move << std::endl;

        if (step.nextState == State::qErr) {
            std::cout << "Config not found for cell value";
            return 1;
        }
        writeCell(fs, step.out);
        moveHeadTo(fs, step.move);
        std::cout << "-- End of step --" << std::endl;
    }
    fs.close();


    char input;
    std::cout << "Type any character and press'enter' to quit" << std::endl;
    std::cin >> input;
    std::cout << input;

    return 0;
}