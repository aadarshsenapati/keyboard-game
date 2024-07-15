//Keyboard game
#include <iostream>
#include <string>
#include <cstdlib> 
#include <ctime>   
#include<conio.h>
#include <windows.h>
using namespace std;

#define s 10
char a[s][s];
int score=0;
int wrong=0,skip=0;
int del=3;
bool cont=true;
void start(){
    for(int i = 0; i < s; i++) {
        for(int j = 0; j < s; j++) {
            a[i][j] = ' ';
        }
    }
    cout<<"*******************Welcome to keyboard game!**************************\n";
    cout<<"*************************RULES****************************************\n";
    cout<<"1. You will get 1 min to play\n2. Press the keys in keyboard to pop the characters\n3. If you don't press any key new 2 blocks will be added\n4. Press enter to exit\n";
    cout<<"Enjoy Playing!\n";
    cout<<"Press any key to start!";
    getch();
    system("cls");
}

void setup() {
    const string chars = 
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz";
    
    srand(time(0));

    int randomIndex = rand() % chars.size();
    char randomChar = chars[randomIndex];
    int pop_i = rand() % 10;
    int pop_j = rand() % 10;
    a[pop_i][pop_j] = randomChar;
}

void display() {
    cout<<"=========================================================================================\n";
    for(int i = 0; i < s; i++) {
        cout<<"||"<<"\t";
        for(int j = 0; j < s; j++) {
            cout << a[i][j] << "\t";
        }
        cout <<"||"<<endl;
    }
    cout<<"=========================================================================================\n";
}

void check() {
    bool inc = false;
    bool x = false;
    time_t startWait = time(0);

    while (difftime(time(0), startWait) < del) {
        if (kbhit()) {
            x = true;
            char ch = getch();
            if (ch == '\r') { 
                cont = false;
                return;
            }
            Beep(523, 200);
            for (int i = 0; i < s; i++) {
                for (int j = 0; j < s; j++) {
                    if (ch == a[i][j]) {
                        a[i][j] = ' ';
                        score++;
                        inc = true;
                        break;
                    }
                }
                if (inc) break;
            }
            break;
        }
    }

    if (!x) {
        skip++;
    }

    if (!inc && x) {
        wrong++;
        for (int k = 0; k < 2; k++) {
            setup();
            setup();
            setup();
            setup();
        }
    }

    display();
}



void end(){
    cout<<"\n***************Game over***********!\n";
    cout<<"Score: "<<score-wrong-skip<<endl;
    cout<<"You pressed "<<wrong<<" keys wrong ,skipped "<<skip<<" keys and "<<score<<" keys correct\n";
}

int main() {
    start();
    setup();
    time_t startTime = time(0);
    while (difftime(time(0), startTime) < 60&&cont) {
        system("cls");
        setup();
        display();
        check();
        if(startTime==20){
            del=2;
        }
    }
    end();
}
