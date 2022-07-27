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
    int ceiling_height;
    int rooms;
    vector <room> room;
};

struct construction {
    building_type buildingType;
    bool stove_with_pipe;
    int floorsCount;
    int constructionArea;
    vector <floor> floors;
};

struct village
{
    int lotNumber;
    int buildingsCount;
    int plot_area = 0;
    int unoccupied_land_area = plot_area;
    vector <construction> building;

};

int main() {
    // вводим количество участков
    cout << "Enter the number of plots in the village: ";
    int countPlots;
    cin >> countPlots;
    while (overflow()) {cout << "Input error. Try again: "; cin >> countPlots;}

    if (countPlots <= 0 ) { // если количество участков меньше или равно 0
        cout << "There are no plots in this village\n";
    }else {
        // инициализация участков
        village plot [countPlots];
        for (int i = 0; i < countPlots; i++) {

            // заполняем участок
            plot[i].lotNumber = i+1;
            cout << "Plot # " << plot[i].lotNumber<< endl;

            // вводим площадь участка
            cout << "enter the area of the plot: ";
            cin >> plot[i].plot_area;
            plot[i].unoccupied_land_area = plot[i].plot_area;

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
                // проверяем корректность ввода
                while (overflow ()) {cin >> plot[i].building[j].constructionArea;}
                while (plot[i].building[j].constructionArea  <=0) {
                    cout << "Building area cannot be less than or equal to 0. Enter again: ";
                    cin >> plot[i].building[j].constructionArea;
                    while (overflow ()) {cin >> plot[i].building[j].constructionArea;}
                }
                // проверка площади относительно участка
                while (plot[i].building[j].constructionArea >= plot[i].plot_area
                        || plot[i].building[j].constructionArea > plot[i].unoccupied_land_area) {
                    cout << "Building area cannot be more or equal to plot area and more unoccupied land area. Enter again: ";
                    cin >> plot[i].building[j].constructionArea;
                    while (overflow ()) {cin >> plot[i].building[j].constructionArea;}
                }
                // вычитаем из незанятой площади - площадь постройки
                plot[i].unoccupied_land_area -= plot[i].building[j].constructionArea;

                // если здание дом
                if (plot[i].building[j].buildingType == house) {

                    //проверяем в доме печь с трубой
                    cout << "Does the house have a stove with a chimney?\ny/n :";
                    char tmp;
                    cin >> tmp;
                    while (tmp != 'y' && tmp != 'Y' && tmp != 'n' && tmp != 'N') {
                        cout << "Incorrect symbol. Enter again: ";
                        cin >> tmp;
                    }
                    if (tmp == 'y'|| tmp == 'Y') {plot[i].building[j].stove_with_pipe = true;}
                    else if (tmp == 'n'|| tmp == 'N'){plot[i].building[j].stove_with_pipe = false;}

                    // вводим количество этажей
                    cout << "Enter floor count for house: ";
                    cin >> plot[i].building[j].floorsCount;

                    // проверяем корректность ввода.
                    while (overflow()) {cin >> plot[i].building[j].floorsCount;}
                        while(plot[i].building[j].floorsCount < 1 || plot[i].building[j].floorsCount >3){
                            cout << "the house cannot have less than 1 and more than 3 floors\nEnter again: ";
                            cin >> plot[i].building[j].floorsCount;
                            while (overflow()) {cin >> plot[i].building[j].floorsCount;}
                        }
                        // расширяем вектор до размера этажей
                    plot[i].building[j].floors.resize (plot[i].building[j].floorsCount);

                    for (int f = 0; f< plot[i].building[j].floorsCount;f++ ){

                        // вводим высоту потолка для f этажа
                        cout <<  "Enter ceiling height for " << f+1 << " floor: ";
                        cin >> plot[i].building[j].floors[f].ceiling_height;

                        // вводим количество комнат для каждого этажа
                        cout << "Floor # " << f+1 << endl;
                        cout << "Enter rooms count: ";
                        cin >> plot[i].building[j].floors[f].rooms;

                        // проверка корректности ввода комнат
                        while (overflow()) {cin >> plot[i].building[j].floors[f].rooms;}
                        while ( plot[i].building[j].floors[f].rooms <2 || plot[i].building[j].floors[f].rooms >4){
                            cout << "rooms cannot be less than 2 and more than 4";
                            cin >> plot[i].building[j].floors[f].rooms;
                            while (overflow()) {cin >> plot[i].building[j].floors[f].rooms;}
                        }

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
                                // присваивание типа
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
                }else if (plot[i].building[j].buildingType == bath){ // если здание - баня
                    // проверяем печь.
                    cout << "Does the bath have a stove with a chimney?\ny/n :";
                    char tmp;
                    cin >> tmp;
                    while (tmp != 'y' && tmp != 'Y' && tmp != 'n' && tmp != 'N') {
                        cout << "Incorrect symbol. Enter again: ";
                        cin >> tmp;
                    }
                    if (tmp == 'y'|| tmp == 'Y') {plot[i].building[j].stove_with_pipe = true;}
                    else if (tmp == 'n'|| tmp == 'N'){plot[i].building[j].stove_with_pipe = false;}
                }
            }

        }
        // расчет % площади участков к площади зданий
        int all_plot_area = 0;
        int all_construction_area = 0;
        for (int i = 0; i < countPlots; i++){
            all_plot_area += plot[i].plot_area;
            all_construction_area += plot[i].plot_area - plot[i].unoccupied_land_area;
        }
        cout << (int) (((float)all_construction_area / (float)all_plot_area ) * 100.0)
             << " %. Occupies the area of all buildings to the area of plots.";
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