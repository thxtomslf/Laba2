#include <iostream>


struct Dec {
    int data;
    Dec *next;
    Dec *previuos;
};

int print(Dec *l);

Dec *add_to_end(Dec *last_item, int a);

Dec *add_to_beginning(Dec *last_item, int a);

Dec *delete_from_beginning(Dec *last_item);

Dec *delete_from_end(Dec *last_item);

bool is_in_dec(Dec *last_item, int value);

std::string convert_to_reverse_polish_notation(std::string expression);

int main() {
    std::string res = convert_to_reverse_polish_notation("7^(2*3)^4");
    std::cout << res;
}

void first_action(std::string &first_container, char elem_to_push_back) {
    first_container.push_back(elem_to_push_back);
}

void second_action(std::string &second_container, std::string &first_container) {
    second_container.push_back(first_container[first_container.size() - 1]);
    first_container.pop_back();
}

void third_action(std::string &first_container) {
    first_container.pop_back();
}

void fourth_action() {
    std::cout << "Converted successfully\n";
}

void fifth_action(std::string &second_container) {
    std::cout << "Wrong input string\n";
    second_container = "";
}

int get_num_of_function(char first_operator, char second_operator, int matrix[8][9]) {
    int i = 0;
    int j = 0;
    for (int iter = 1; iter < 8; ++iter) {
        if (matrix[iter][0] == (int)first_operator) {
            i = iter;
        }
        if (matrix[0][iter] == (int)second_operator) {
            j = iter;
        }
    }
    if (j == 0) {
        j = 8;
    }
    return matrix[i][j];
}

std::string convert_to_reverse_polish_notation(std::string expression) {
    int function_matrix[8][9] = {{0, (int)'!', (int)'+', (int)'-', (int)'*', (int)'/', (int)'(', (int)')', (int)'^'},
                                 {(int)'!', 4, 1, 1, 1, 1, 1, 5, 1},
                                 {(int)'+', 2, 2, 2, 1, 1, 1, 2, 1},
                                 {(int)'-', 2, 2, 2, 1, 1, 1, 2, 1},
                                 {(int)'*', 2, 2, 2, 2, 2, 1, 2, 1},
                                 {(int)'/', 2, 2, 2, 2, 2, 1, 2, 1},
                                 {(int)'(', 5, 1, 1, 1, 1, 1, 3, 1},
                                 {(int)'^', 2, 2, 2, 2, 2, 1, 2, 2}};
    std::string california;
    std::string texas = {'!'};
    expression += '!';
    for (int i = 0; i < expression.size(); ++i) {
        if (isdigit(expression[i])) {
            california.push_back(expression[i]);
        } else {
            int num_of_function = get_num_of_function(texas[texas.size() - 1],
                                                      expression[i], function_matrix);
            if (num_of_function == 1) {
                first_action(texas, expression[i]);
            } else if (num_of_function == 2) {
                second_action(california, texas);
                i--;
            } else if (num_of_function == 3) {
                third_action(texas);
            } else if (num_of_function == 4) {
                fourth_action();
                break;
            } else if (num_of_function == 5) {
                fifth_action(california);
                break;
            }
        }

    }
    return california;
}

bool is_in_dec(Dec *last_item, int value) {
    if (last_item != nullptr) {
        if (last_item->data == value) {
            std::cout << '[' << last_item << ']' << "->" << '[' <<
                      last_item->data << ", " << last_item->previuos << ']' << '\n';
            return true;
        } else {
            return is_in_dec(last_item->previuos, value);
        }
    }
    std::cout << "Element not found\n";
    return false;
}

Dec *delete_from_end(Dec *last_item) {
    if (last_item != nullptr) {
        if (last_item->previuos == nullptr) {
            delete last_item;
            return nullptr;
        } else if (last_item->previuos->previuos == nullptr) {
            delete last_item->previuos;
            last_item->next = nullptr;
            last_item->previuos = nullptr;
        } else {
            Dec *first_elem = last_item->next;
            last_item->next = first_elem->next;
            first_elem->next->previuos = nullptr;
            delete first_elem;
        }
    }
    return last_item;
}

Dec *delete_from_beginning(Dec *last_item) {
    if (last_item != nullptr) {
        Dec *newList = last_item->previuos;
        if (last_item->previuos == nullptr) {
            delete last_item;
            return nullptr;
        } else if (last_item->previuos->previuos == nullptr) {
            newList->next = last_item->previuos->previuos;
            delete last_item;
        } else {
            newList->next = last_item->next;
            delete last_item;
        }
        return newList;
    } else {
        return last_item;
    }
}

Dec *add_to_beginning(Dec *last_item, int a) {
    Dec *newItem = new Dec;
    newItem->data = a;
    if (last_item == nullptr) {
        newItem->next = last_item;
        newItem->previuos = last_item;
    } else if (last_item->previuos == nullptr){
        newItem->next = last_item;
        newItem->previuos = last_item;
        newItem->next->next = newItem;
    } else {
        newItem->next = last_item->next;
        newItem->previuos = last_item;
        last_item->next = newItem;
    }
    return newItem;
}

Dec *add_to_end(Dec *last_item, int a) {
    Dec *newItem = new Dec;
    newItem->data = a;
    if (last_item == nullptr) {
        return add_to_beginning(last_item, a);
    }
    if (last_item->previuos == nullptr) {
        newItem->previuos = last_item->previuos;
        newItem->next = last_item;
        last_item->previuos = newItem;
        last_item->next = newItem;
    } else {
        newItem->next = last_item->next;
        newItem->previuos = last_item->next->previuos;
        last_item->next->previuos = newItem;
        last_item->next = newItem;
    }
    return last_item;
}

int print(Dec *l) {
    if (l == nullptr) {
        return 0;
    }
    std::cout << '[' << l << ']' << "->" << '[' << l->data << ", " << l->previuos << ']' << '\n';
    l = l->previuos;
    print(l);
}

