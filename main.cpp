#include <iostream>
#include <iomanip>
#include <random>
#include <fstream>
using namespace std;

struct trangthai{
    int gtri;
    bool DangMo;
    bool DangCamCo;
};
void kichthuoc(trangthai *board, int x, int y, int bom){//ghi lai kich thuoc cua mang
    ofstream f;
    f.open("INPUT.txt", ios::out);
    if (f.is_open()){
        f << x << " " << y << " " << bom << endl;
        f.close();
    }
}
void inputfile(trangthai *board, int a, int b, int F){//ghi lai du lieu nguoi dung nhap
    ofstream f;
    f.open("INPUT.txt", ios::app);
    if (f.is_open()){
        f << F << " " << a << " "<< b << endl;
        f.close();
    }
}
void outputfile(trangthai *board, int x, int y, int trangthaigame){//ghi lai du lieu cua game
    ofstream f;
    f.open("OUTPUT.txt", ios :: app);
    if (f.is_open()){
        f << "         trang thai: ";
        if (trangthaigame == 0) f << "da thua" << endl;
        else if (trangthaigame == 1) f << "da thang" << endl;
        else f << "dang choi" << endl;
        f << "        ";
        for(int j=0; j<y; j++) f << setw(2) << j << " "; 
        f << "  <-- COT";
        f << endl;
        for (int i = 0; i < x; i++){
            f << "DONG " << setw(2) << i << "|";
            for (int j = 0; j < y; j++){
                int index = i*y + j;
                if(board[index].DangMo){
                    if (board[index].gtri == -1) f << " * ";
                    else if (board[index].gtri == 0) f << " . ";
                    else f << " " << board[index].gtri << " ";
                }
                else{
                    if(board[index].DangCamCo) f << " F ";
                    else f << " # ";
                }
            }
        f << endl;
        }
    f.close();
    }
    else cout << "ko mo dc file output";
}
void nhapmang(trangthai *board, int x, int y){//nhap mang dua vao kich thuoc
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            board[i*y+j].gtri = 0;
            board[i*y+j].DangMo = false;
            board[i*y+j].DangCamCo = false;
        }
    }
}
void tinhso(trangthai *board, int x, int y, int a, int b){ //xet 8 o xung quanh bom
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            int ToaDoXqX = a + i;
            int ToaDoXqY = b + j;
            if (ToaDoXqX >= 0 && ToaDoXqX < x && ToaDoXqY >= 0 && ToaDoXqY < y){
                if(!(i == 0 && j == 0)){
                    int sobomxq = ToaDoXqX * y + ToaDoXqY;
                    if(board[sobomxq].gtri != -1) board[sobomxq].gtri++;
                }
            }
        } 
    }
}
void raibom(trangthai *board, int x, int y, int bom, int azone, int bzone){//rai bom (co set zone de luon luon khong dinh bom lan dau)
    int count = 0;
    random_device dev; //độ hỗn loạn -> lấy tốc độ xử lí cpu, tốc độ tính toán, hoặc là số gì đó trong cpu
    mt19937 rng(dev()); //bộ máy random mt19937 19937
    uniform_int_distribution<mt19937::result_type>TEMPa(0,x - 1); //uniform_int_dis.. (phân phối random trong khoảng)
    uniform_int_distribution<mt19937::result_type>TEMPb(0,y - 1); //source: stack overflow
    while(count < bom){
        int a = TEMPa(rng);
        int b = TEMPb(rng);
        if(abs(a-azone) <= 1 && abs(b - bzone) <= 1) continue;
        if(board[a*y + b].gtri != -1 ){
            board[a*y + b].gtri = -1;
            count++;
        }
    }
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            if(board[i*y + j].gtri == -1) tinhso(board, x, y, i, j);
        }
    }
}
void vemang(trangthai *board, int x, int y){//ve mang ra de nguoi dung choi
    cout << "        "; 
    for(int j=0; j<y; j++) cout << setw(2) << j << " "; 
    cout << "  <-- COT";
    cout << endl;
    for (int i = 0; i < x; i++){
        cout << "DONG " << setw(2) << i << "|";
        for (int j = 0; j < y; j++){
            int index = i*y + j;
            if(board[index].DangMo){
                if (board[index].gtri == -1) cout << " * ";
                else if (board[index].gtri == 0) cout << " . ";
                else cout << " " << board[index].gtri << " ";
            } else{
                if(board[index].DangCamCo) cout << " F ";
                else cout << " # ";
            }
        }
        cout << endl;
    }
}
void floodfill(trangthai *board, int x, int y, int a, int b){//thuat toan floodfill (rat quan trong doi voi 1 tua game do min)
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            int ToaDoXqX = a + i;
            int ToaDoXqY = b + j;
            if (ToaDoXqX >= 0 && ToaDoXqX < x && ToaDoXqY >= 0 && ToaDoXqY < y){
                int index = ToaDoXqX * y + ToaDoXqY;
                if(!board[index].DangMo && board[index].gtri != -1 && !board[index].DangCamCo){
                    board[index].DangMo = true;
                    if (board[index].gtri == 0){
                        floodfill(board, x, y, ToaDoXqX, ToaDoXqY);
                    }
                }
            }
        } 
    }
}
void camco(trangthai *board, int x, int y, int a, int b){//cam co vao noi co bom
    int index = a*y + b;
    if (board[index].DangMo) return;
    board[index].DangCamCo = !board[index].DangCamCo;
}
void gameplay(trangthai *board, int x, int y, int a, int b, int &trangthaigame){//logic luc nguoi dung dang choi
    int index = a*y + b;
    if (board[index].DangMo || board[index].DangCamCo) return;
    board[index].DangMo = true;
    if (board[index].gtri == -1){
        trangthaigame = 0;
        return;
    }
    if (board[index].gtri == 0){
        floodfill(board, x, y, a, b);
    }
}
int count(trangthai *board, int x, int y){//dem so o da mo de tinh toan xem co du dieu kien thang hay ko
    int dem = 0;
    for(int i = 0; i < x * y; i++){
        if(board[i].DangMo) dem++;
    }
    return dem;
}
int main(){
    int x, y, a, b, F, bom, trangthaigame = 2; //0 la thua, 1 la thang, 2 la dang choi
    bool LanDau = true;
    ofstream f_reset("OUTPUT.txt"); f_reset.close(); 
    cout << "nhap kich thuoc va so bom: ";
    cin >> x >> y >> bom;
    trangthai *board = new trangthai[x*y];
    kichthuoc(board, x, y, bom);
    nhapmang(board, x, y); //truy cap: index = i * y + j
    do{//menu giup nguoi dung thao tac
        system("cls");
        vemang(board, x, y);
        outputfile(board, x, y, trangthaigame);
        cout << "\n0. Chon\n1. Cam Co\n";
        cin >> F;
        cout << "nhap toa do: ";
        cin >> a >> b;
        if(a < 0 || a >= x || b < 0 || b >= y) {
            continue;
        }
        switch (F){
            case 0:{
                if(LanDau){//neu la lan dau se tat co de rai bom
                    LanDau = false;
                    raibom(board, x, y, bom, a, b);
                }
                gameplay(board, x, y, a, b, trangthaigame);
                inputfile(board, a, b, F);
            }
            break;
            case 1:{
                camco(board, x, y, a, b);
                inputfile(board, a, b, F);
            }
            break;
            default: cout << "gia tri ko hop le"; break;
        }
        if (count(board, x, y)  == (x*y) - bom){
            trangthaigame = 1;
        }
    }while(trangthaigame == 2); 
    system("cls");
    if (trangthaigame == 1){
        vemang(board, x, y);
        outputfile(board, x, y, trangthaigame);
        cout << endl;
        cout << "ban da thang" << endl;
        system("pause");
    }
    if (trangthaigame == 0){
        cout << endl;
        for(int i = 0; i < x * y; i++){
            board[i].DangMo = true;
        }
        vemang(board, x, y);
        outputfile(board, x, y, trangthaigame);
        cout << endl;
        cout << "ban da thua" << endl;
        system("pause");
    }
    delete[] board;
}