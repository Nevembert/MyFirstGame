//poopy_game)))
#include <iostream>
#include <random>
#include <ctime>
#include <fstream>

char graund[41][41];

//не реализованы сохранение и загрузка

struct game {
  std::string name;
  int hp, ar, dem;
  int x, y, x1, y1;
 
  void start(){
    for(int i = 0; i < 40; i++){
      for(int j = 0; j < 40; j++){
        graund[i][j] = '.';
      }
    }
  }

  void show(){
    system("clear");
    std::cout << "Name:" << name << std::endl;
    std::cout << "HP:" << hp << std::endl;
    std::cout << "Amor:" << ar << std::endl;
    std::cout << "Demage:" << dem << std::endl;
    std::cout << "Left = a; Right = d; Top = w; Bottom = s" << std::endl;
    std::cout << "Save = q" << std::endl;
    for(int i = 0; i < 40; i++){
      for(int j = 0; j < 40; j++){
        std::cout << graund[i][j] << ' ';
      }
      std::cout << std::endl;
    }
      std::cout << "Command:";
  }

  void live(){
    if(hp <= 0){
      graund[y][x] = '.';
      x = 40;
      y = 40;
    }
  }

};

  game EN[5];
  game PL;

  void atak(int x, int y, int dem){
            for(int i = 0; i < 5; i++){
          if(EN[i].x == x && EN[i].y == y){
            if (EN[i].ar == 0){
              EN[i].hp -= dem;
              EN[i].live();
              break;
          } else if (EN[i].ar >= dem) {
              EN[i].ar -= dem;
              break;
          } else {
              EN[i].ar = 0;
              EN[i].hp -= (dem - EN[i].ar);
              break;
          }
        }     
    }
  }

void atakp(int x, int y, int dem){
          if(PL.x == x && PL.y == y){
            if (PL.ar == 0){
              PL.hp -= dem;
              PL.live();
          } else if (PL.ar >= dem) {
              PL.ar -= dem;
          } else {
              PL.ar = 0;
              PL.hp -= (dem - PL.ar);
          }
        }     
  }
  
void saving(){
  
  std::ofstream file("save1.bin", std::ios_base::binary|std::ios::out);
  size_t F = sizeof(PL), L = sizeof(EN);
  file.write((char*)&F, sizeof(size_t));
  file.write((char*)&L, sizeof(size_t));
  file.write((char*)&PL, F);
  for(int y = 0; y < 5; y ++){
    file.write((char*)&EN[y], L);
  }
  file.close();
  
  
}

void loading(){
  
  std::ifstream file("save1.bin", std::ios_base::binary|std::ios::in);
  size_t F, L;
  file.read((char*)&F, sizeof(size_t));
  file.read((char*)&L, sizeof(size_t));
  file.read((char*)&PL, F);
  graund[PL.y][PL.x] = 'P';
  for(int y = 0; y < 5; y ++){
    file.read((char*)&EN[y], L);
    graund[EN[y].y][EN[y].x] = 'E';
  }
  file.close();
}

int main() {
  time_t seconds;
  srand(time(NULL));
  PL.start(); // заполнение массива точками
  for(int h = 0; h < 5; h++){ // характеристики врагов
    EN[h].name = "Enemy #" + h;
    EN[h].hp = 50 + rand() % 101;
    EN[h].ar = rand() % 51;
    EN[h].dem = 15 + rand() % 16;
  }
  char cor;
  std::cout << "New game?(y/n)";
  std::cin >> cor;
  if (cor == 'n') {
          loading();
      } else {
              // характеристики игрока
  std::cout << "Введите имя игрока:";
  std::cin >> PL.name;
  std::cout << "Введите здоровье игрока:";
  std::cin >> PL.hp;
  if(PL.hp > 150){
    PL.hp = 150;
  } else if(PL.hp < 50){
    PL.hp = 50;
  }
  std::cout << "Введите броню игрока:";
  std::cin >> PL.ar;
  if(PL.ar > 50){
    PL.ar = 50;
  } else if(PL.ar < 0){
    PL.ar = 0;
  }
  std::cout << "Введите урон игрока:";
  std::cin >> PL.dem;
  if(PL.dem > 30){
    PL.dem = 30;
  } else if(PL.dem < 15){
    PL.dem = 15;
  }
  //размещение на поле врагов и игрока
  for(int h = 0; h <= 5; h++){
    int x1 = rand() % 40;
    int y1 = rand() % 40;
    if(h < 5){
      if(graund[y1][x1] == '.'){
        EN[h].x = x1;
        EN[h].y = y1;
        graund[y1][x1] = 'E';
      } else {
        h--;
      }
    } else {
      if(graund[y1][x1] == '.'){
        PL.x = x1;
        PL.y = y1;
        graund[y1][x1] = 'P';
      } else {
        h--;
      }
    }
  }
    }
  // начало действий
  /*for(;;){
    PL.show(PL.name);
  
      switch(getch()){
      case 72: // up
        if(PL.y != 0){
          PL.y--;
        }
        break;
      case 80: // down
        if(PL.y != 39){
          PL.y++;
        }
        break;
      case 75: // left
        if(PL.x != 0){
          PL.x--;
        }
        break;
      case 77: // right
        if(PL.x != 39){
          PL.x++;
        }
        break;
        }
}
   */ 

  for(int i = 5;;i++){
    if(i == 5){ //player 
      PL.show();
      char com;
      std::cin >> com;
      if(com == 'a' && PL.x != 0){
        if(graund[PL.y][PL.x - 1] == '.'){
          graund[PL.y][PL.x] = '.';
          PL.x--;
          graund[PL.y][PL.x] = 'P';
        } else {
          atak(PL.x - 1, PL.y, PL.dem);
        }
      } else if (com == 'd' && PL.x != 39){
        if(graund[PL.y][PL.x + 1] == '.'){
          graund[PL.y][PL.x] = '.';
          PL.x++;
          graund[PL.y][PL.x] = 'P';
        } else {
          atak(PL.x + 1, PL.y, PL.dem);
        }
      } else if (com == 'w' && PL.y != 0){
        if(graund[PL.y - 1][PL.x] == '.'){
          graund[PL.y][PL.x] = '.';
          PL.y--;
          graund[PL.y][PL.x] = 'P';
        } else {
          atak(PL.x, PL.y - 1, PL.dem);
        }
      } else if (com == 's' && PL.y != 39){
        if(graund[PL.y + 1][PL.x] == '.'){
          graund[PL.y][PL.x] = '.';
          PL.y++;
          graund[PL.y][PL.x] = 'P';
        } else {
          atak(PL.x, PL.y + 1, PL.dem);
        }
      } else if (com == 'q') {
          saving();
          system("clear");
          std::cout << "Game saved";
          break;
      } else {
        std::cout << std::endl << "Incorrect command";
        i--;
        continue;
      }
    }  else { // случайные перемещения врагов


        if(EN[i].hp > 0){
          if(rand() % 4 == 0 && EN[i].x != 0){
        if(graund[EN[i].y][EN[i].x - 1] == '.'){
          graund[EN[i].y][EN[i].x] = '.';
          EN[i].x--;
          graund[EN[i].y][EN[i].x] = 'E';
        } else if (graund[EN[i].y][EN[i].x - 1] == 'P') {
          atakp(EN[i].x - 1, EN[i].y, EN[i].dem);
        }
      } else if (rand() % 4 == 1 && EN[i].x != 39){
        if(graund[EN[i].y][EN[i].x + 1] == '.'){
          graund[EN[i].y][EN[i].x] = '.';
          EN[i].x++;
          graund[EN[i].y][EN[i].x] = 'E';
        } else if (graund[EN[i].y][EN[i].x + 1] == 'P') {
          atakp(EN[i].x + 1, EN[i].y, EN[i].dem);
        }
      } else if (rand() % 4 == 2 && EN[i].y != 0){
        if(graund[EN[i].y - 1][EN[i].x] == '.'){
          graund[EN[i].y][EN[i].x] = '.';
          EN[i].y--;
          graund[EN[i].y][EN[i].x] = 'E';
        } else if(graund[EN[i].y - 1][EN[i].x] == 'P') {
          atakp(EN[i].x, EN[i].y - 1, EN[i].dem);
        }
      } else if (rand() % 4 == 3 && EN[i].y != 39){
        if(graund[EN[i].y + 1][EN[i].x] == '.'){
          graund[EN[i].y][EN[i].x] = '.';
          EN[i].y++;
          graund[EN[i].y][EN[i].x] = 'E';
        } else if(graund[EN[i].y + 1][EN[i].x] == 'P') {
          atakp(EN[i].x, EN[i].y + 1, EN[i].dem);
        }
      }
      }
    }
    if(i >= 5){
      i = -1;
    }
    if(PL.hp <= 0){
      system("clear");
      std::cout << "██─██──████──█─█      █────████──███──███      ────██\n─███───█──█──█─█      █────█──█──█────█        █──██ \n──█────█──█──█─█      █────█──█──███──███      ───█\n──█────█──█──█─█      █────█──█────█──█        █──██\n──█────████──███      ███──████──███──███      ────██\n";
      break;
    }
    if(EN[0].hp <= 0 && EN[1].hp <= 0 && EN[2].hp <= 2 && EN[3].hp <= 3 && EN[4].hp <= 0){
      system("clear");
      std::cout << "██─██──████──█─█      █───█──███──█──█──█──█──█\n─███───█──█──█─█      █───█───█───██─█──█──█──█\n──█────█──█──█─█      █─█─█───█───█─██──█──█──█\n──█────█──█──█─█      █████───█───█──█\n──█────████──███      ─█─█───███──█──█──█──█──█\n";

      break;
    }
  } 
}
