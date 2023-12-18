#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <iomanip>

using namespace std;

struct MenuItemType {
    string Name;
    double Price;
};

struct OrderedItemType {
    string Name;
    double Price;
    int Quantity;
};

void getData(MenuItemType menuList[], double Price[], string Names[], OrderedItemType OrderedItems[]) {
    for (int i = 0; i < 8; i++) {
        menuList[i].Name = Names[i];
        OrderedItems[i].Name = Names[i];
        menuList[i].Price = Price[i];
        OrderedItems[i].Price = 0;
        OrderedItems[i].Quantity = 0;
    }
}

void showMenu(MenuItemType menuList[]) {
    for (int i = 0; i < 8; i++) {
        cout << i + 1 << " " << left << setw(45) << menuList[i].Name << setw(5) << left << menuList[i].Price << "Eur" << endl;
    }
}

void Order(MenuItemType menuList[], OrderedItemType OrderedItems[], double &value) {
    bool ProgramWorks = true;
    int action;

    cout << endl;
    cout << "Iveskite patiekalo kuri, noretumete uzsisakyti numeri. Jei norite uzsisakyti kelis tokius pacius patiekalus iskart iveskite ir pageidaujama kieki." << endl;
    cout << "Noredami baigti uzsakyma iveskite skaiciu 0" << endl;
    cout << endl;
    
    while (ProgramWorks) {
        cin >> action;

        if (action == 0)
            break;

        else if (action > 0 && action < 9) {
            OrderedItems[action - 1].Price = OrderedItems[action - 1].Price + menuList[action - 1].Price;
            OrderedItems[action - 1].Quantity++;

            cout << "Sekmingai uzsisakete " << action << " patiekala is meniu." << endl;

            value = value + menuList[action - 1].Price;
        }

        else {
            cout << "Klaida! Tokio patiekalo nera. Iveskite kita patiekala." << endl;
            continue;
        }
    }
}

void printCheck(OrderedItemType OrderedItems[], double value) {
    
    ofstream fd;
    fd.open("Kvitas.txt");

    for (int i = 0; i < 8; i++) {
        if (OrderedItems[i].Price != 0)
            fd << left << setw(45) << OrderedItems[i].Name << left << setw(3) << OrderedItems[i].Quantity << left << setw(5) << OrderedItems[i].Price << " Eur" << endl;
    }
    fd << endl;
    fd << left << setw(48) << "Mokesciai" << fixed << setprecision(2) << value * 0.09 << "  Eur" << endl;
    fd << endl;
    fd << left << setw(48) << "Is viso moketi: " << fixed << setprecision(2) << value * 1.09 << " Eur" << endl;
    fd << endl;
    cout << "Savo kvita rasite Kvitas.txt faile." << endl;
    system("pause");

    fd.close();
}

int main()
{
    string Names[8]  = { "Kiausiniene", "Kiaulienos sonine su keptu kiausiniu", "Keksiukas su vysnia", "Prancuziskas skrebutis", "Vaisiu salotos", "Pusryciu dribsniai", "Kava", "Arbata" };
    double Prices[8] = { 1.45, 2.45, 0.99, 1.99, 2.49, 0.69, 0.50, 0.75 };

    MenuItemType menuList[8];
    OrderedItemType OrderedItems[8];

    getData(menuList, Prices, Names, OrderedItems);
    showMenu(menuList);

    double value = 0;
    Order(menuList, OrderedItems, value);

    printCheck(OrderedItems, value);


    return 0;
}

