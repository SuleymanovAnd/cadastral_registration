#include <iostream>
#include <vector>
bool overflow ();
using namespace std;
enum room_type {
    bedroom,
    kitchen,
    bathroom,
    living,
    children,
};
enum building_type {
    house,
    barn,
    garage,
    bath,
};
struct room{
    int area;
    room_type roomType;
};
struct floor {
    int rooms;
    vector <room> room;
};

struct construction {
    building_type buildingType;
    int floorsCount;
    int constructionArea;
    vector <floor> floors;
};

struct village
{
    int lotNumber;
    int buildingsCount = 1;
    vector <construction> building;

};

int main() {
    // вводим количество участков
    cout << "Enter the number of plots in the village: ";
    int countPlots;
    cin >> countPlots;
    while (overflow()) {cout << "Input error. Try again: "; cin >> countPlots;}

    if (countPlots <= 0 ) {
        cout << "There are no plots in this village\n";
    }else {
        // инициализация участков
        village plot [countPlots];
        for (int i = 0; i < countPlots; i++) {

            // заполняем участок
            cout << "Plot # " << i+1<< endl;
            plot[i].lotNumber = i+1;

            // вводим количество построек
            cout << "Enter the number of buildings on the lot: ";
            cin >> plot[i].buildingsCount;
            while (overflow()) {cout << "Input error. Try again: "; cin >> plot[i].buildingsCount;}

            while (plot[i].buildingsCount <= 0) {
                cout << "There must be at least one building on the lot. Enter again: ";
                cin >> plot [i].buildingsCount;
            }
            // для каждой постройки
            plot[i].building.resize (plot[i].buildingsCount);
            for (int j = 0; j < plot[i].buildingsCount; j++){
                // вводим тип здания
                cout << "Select type of " << j+1 << " building.\n";
                int type;
                cout << "1 - house.\n2 - barn.\n3 - garage.\n4 - bath\n: ";
                cin>>type;

                while (overflow ()) {cin >> type;}
                while (type <1 || type > 4){
                    cout << "Incorrect type. Enter again: ";
                    cin >> type;
                    while (overflow ()) {cin >> type;}
                }
                //выбираем тип для здания
                switch (type){
                    case 1:plot[i].building[j].buildingType = house; break;
                    case 2:plot[i].building[j].buildingType = barn; break;
                    case 3:plot[i].building[j].buildingType = garage; break;
                    case 4:plot[i].building[j].buildingType = bath; break;
                    default: cout << "incorrect type";break;
                }

                // вводим площадь здания
                cout << "Enter building area: ";
                cin >> plot[i].building[j].constructionArea;
                while (overflow ()) {cin >> plot[i].building[j].constructionArea;}
                while (plot[i].building[j].constructionArea  <=0 ) {
                    cout << "Building area cannot be less than or equal to 0. Enter again: ";
                    cin >> plot[i].building[j].constructionArea;
                }

                // если здание дом
                if (plot[i].building[j].buildingType == house) {
                    // вводим количество этажей
                    cout << "Enter floor count for house: ";
                    cin >> plot[i].building[j].floorsCount;
                    while (overflow()) {cin >> plot[i].building[j].floorsCount;}

                    plot[i].building[j].floors.resize (plot[i].building[j].floorsCount);
                    for (int f = 0; f< plot[i].building[j].floorsCount;f++ ){
                        // вводим количество комнат для каждого этажа
                        cout << "Floor # " << f+1 << endl;
                        cout << "Enter rooms count: ";
                        cin >> plot[i].building[j].floors[f].rooms;
                        while (overflow()) {cin >> plot[i].building[j].floors[f].rooms;}
                        // вводим тип комнаты и площадь
                        plot[i].building[j].floors[f].room.resize(plot[i].building[j].floors[f].rooms);
                        for (int r = 0; r < plot[i].building[j].floors[f].rooms; r++ ) {
                            cout << "Enter type of "<< r+1 <<" room\n";
                            cout <<  "1 - bedroom.\n2 - kitchen.\n3 - bathroom.\n4 - living\n5 - children\n: ";
                            int typeRoom;
                            cin >> typeRoom;
                            while (overflow ()){cin >> typeRoom;}
                            while (typeRoom <1 || typeRoom > 5){
                                cout << "Incorrect type. Enter again: ";
                                cin >> typeRoom;
                                while (overflow ()){cin >> typeRoom;}
                            }
                            switch (typeRoom){
                                case 1: plot[i].building[j].floors[f].room[r].roomType = bedroom;break;
                                case 2: plot[i].building[j].floors[f].room[r].roomType = kitchen;break;
                                case 3: plot[i].building[j].floors[f].room[r].roomType = bathroom;break;
                                case 4: plot[i].building[j].floors[f].room[r].roomType = living;break;
                                case 5: plot[i].building[j].floors[f].room[r].roomType =children;break;
                                default: break;
                            }
                            cout << "Enter area of " << r+1 << " room:";
                            cin >> plot[i].building[j].floors[f].room[r].area;

                        }

                    }
                }
            }

        }
    }

}

bool overflow (){

    if (! std::cin){
        std::cout <<"Input Error. Enter again: ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');

        return true;
    } else{ return false;
    }
}