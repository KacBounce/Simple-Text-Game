#include <iostream>
#include <ctime>
#include <cmath>
#include <fstream>
using namespace std;

struct weapon{
  string name;
  string type;
  int damage;
};

struct armor{
  string name;
  string type;
  int value;
};

struct player{
  string name = "";
  int health = 100;
  int level = 1;
  int experience = 0;
  int next_level = 20;
  weapon current_weapon = {};
  armor current_armor = {};
  weapon weapon_eq[100];
  armor armor_eq[100];
  int armor_ammount = 0;
  int weapon_ammount = 0;
  int potion_ammount = 0;
};

struct enemy{
  string name;
  int damage;
  int health;
  int level;
  int experience;
};

struct HPpotion{
  int value = 10;
};

void stats(player &player){
  cout << "Name : " << player.name << endl << "Current HP : " << player.health << endl << "Current EXP : " << player.experience << endl << "Level : " << player.level << endl << "Armors : " << player.armor_ammount << endl << "Weapons : " << player.weapon_ammount << "\nPotions : " << player.potion_ammount << endl << "Next level : " << player.next_level << " EXP" <<  endl << endl;;
}

void equipment(player &player){
  int x;
  cout << "Do you want to :\n1.See currently equiped items\n2.Equip new weapon\n3.Equip new armor\nNumber : ";
  cin >> x;
  cin.ignore();
  cout << endl;
  switch(x){
    case 1:
      cout << "Current weapon : " << player.current_weapon.name << " DMG : " <<  player.current_weapon.damage << endl;
      cout << "Current armor : " << player.current_armor.name << " Armor value : " <<  player.current_armor.value << endl << endl;
      break;
    case 2:
      int z;
      cout << "Choose the number of a weapon you want to equip : \n";
      for(int i = 0;i<player.weapon_ammount;i++){
        cout << i+1 << "." << player.weapon_eq[i].name << " DMG : " << player.weapon_eq[i].damage << endl;
      }
      cout << "Number : ";
      cin >> z;
      cout << endl;
      z--;
      player.current_weapon = player.weapon_eq[z];
      break;
      case 3:
        int y;
        cout << "Choose the number of the armor you want to equip : \n";
        for(int i = 0;i<player.armor_ammount;i++){
          cout << i+1 << "." << player.armor_eq[i].name << " Armor value : " << player.armor_eq[i].value << endl;
        }
        cout << "Number : ";
        cin >> y;
        cout << endl;
        y--;
        player.current_armor = player.armor_eq[y];
        break;
      default:
        cout << "That's not an option" << endl;
  }
}

void player_creation(player &player){
  cout << "Hello. Please enter the name of your player : ";
  cin >> player.name;
  cout << endl;
  cout << "Hello " << player.name << ". Please enjoy the game :)" << endl << endl;
}

void random_weapon(player &player){
  string names1[5] = {"Sword of ","Axe of ","Dagger of ","Mace of ","Hammer of "};
  string names2[5] = {"Power","Doom","Might","Darkness","Light"};
  srand(time(NULL));
  weapon x;
  int y = rand() % 4 + 1;
  int n1 = rand() % 4;
  int n2 = rand() % 4;
  int min;
  int max;
  min = 10 * player.level / y;
  max = 20 * player.level /y;
  x.damage = rand()%max + min;
  x.name = names1[n1] + names2[n2];
  cout << "You have found a weapon : " << x.name << " DMG : " << x.damage;
  cout << endl << endl;
  player.weapon_eq[player.weapon_ammount] = x;
  player.weapon_ammount++;
}

void random_armor(player &player){
  string names1[5] = {"Light Armor of","Heavy Armor of ","Cape of ","Suit of ","Lancelot of "};
  string names2[5] = {"Power","Doom","Might","Darkness","Light"};
  srand(time(NULL));
  armor x;
  int y = rand() % 4 + 1;
  int n1 = rand() % 4;
  int n2 = rand() % 4;
  int min;
  int max;
  min = 10 * player.level / y;
  max = 20 * player.level /y;
  x.value = rand()%max + min;
  x.name = names1[n1] + names2[n2];
  cout << "You have found an armor : " << x.name << " Armor Value : " << x.value;
  cout << endl << endl;
  player.armor_eq[player.armor_ammount] = x;
  player.armor_ammount++;
}

void level_up(player &player){
  cout << "Congratulations!!! You've leveled up." << endl;
  player.level += 1;
  player.experience = 0;
  player.next_level *= 1.4;
  cout << "You are now level : " << player.level << endl << endl;
}

void drop(player &player){
  srand(time(NULL));
  int chance = rand()%100;
  if(0 <= chance && chance < 50){
    player.potion_ammount++;
    cout << "You have found an HP potion" << endl << endl;
  }
  else if(50 <= chance && chance < 75){
    random_weapon(player);
  }
  else{
    random_armor(player);
  }
}
//Balance
void fight(player &player){
  srand(time(NULL));
  int trigger = 0;
  int go = 1;
  int lvl = rand()%(player.level + 3) + (player.level - 3);
  int z = rand()%4 + 1;
  if(lvl <= 0){
    lvl = player.level;
  }
  int dmg = rand()%(6*lvl/z) + (4*lvl/z);
  int exp = rand()%(6*lvl/z) + (4*lvl/z);
  int hp = rand()%(20*lvl/z) + (10*lvl/z);
  string names[4] = {"Rat","Goon","Wizzard","Mage"};
  int n = rand()%3;
  enemy monster = {names[n],dmg,hp,lvl,exp};
  cout << "You have encountered a wild " << monster.name << " LVL : " << monster.level << endl;
  while(monster.health > 0){
    int choice;
    cout << "Your Current HP : " << player.health << endl << "Enemy Current HP : " << monster.health << endl << "HP potions : " << player.potion_ammount << endl << endl << "What do you do :\n1.Attack\n2.Defend\n3.Use HP potion\n4.Try to run\nNumber : ";
    cin >> choice;
    cout << endl;
    if(choice == 1){
      monster.health -= player.current_weapon.damage;
      if(monster.health <=0){
          cout << "You hit the " << monster.name << " for " << player.current_weapon.damage << " DMG and killed it." << endl;
      }
      else{
        player.health -= round(monster.damage - monster.damage*0.02*player.current_armor.value);
        cout << "You hit the " << monster.name << " for " << player.current_weapon.damage << " DMG" << endl;
        cout << "It hit You back for " <<  round(monster.damage - monster.damage*0.02*player.current_armor.value) << " DMG" << endl << endl;
      }
      if(player.health < 0){
        cout << "You died" << endl;
        break;
      }
    }
    else if(choice == 2){
      player.health -= round((monster.damage * 0.4) - (monster.damage * 0.4*0.02*player.current_armor.value));
      cout << "The enemy hit you for " << round((monster.damage * 0.4) - (monster.damage * 0.4*0.02*player.current_armor.value)) << " DMG" << endl;
      if(player.health < 0){
        cout << "You died" << endl;
        break;
      }
    }
    else if(choice == 3){
      HPpotion hp;
      if(trigger == 0){
        player.health += hp.value;
        cout << "You have healed for " << hp.value << endl;
        trigger = 1;
      }
      else{
        cout << "You already used one" << endl;
      }
    }
    else if(choice == 4){
      int chance = rand()%100 + 1;
      if(chance < 40){
        player.health -= monster.damage * 0.4;
        cout << "You didn't escape and the enemy hit you for " << monster.damage << " DMG" << endl;
      }
      else{
        cout << "You ran away" << endl;
        go = 0;
        monster.health = 0;
      }
      cout << endl;
    }
  }
  if(go != 0){
    cout << "You killed " << monster.name << " and gained : " << monster.experience << " EXP" << endl;
    player.experience +=  monster.experience;
    drop(player);
  }
  if(player.experience == player.next_level){
    level_up(player);
  }
  else if(player.experience > player.next_level){
    int exp = player.experience - player.next_level;
    level_up(player);
    player.experience += exp;
  }
}

void exploring(player player){

}

void saver(player &player,const char *file_name){
  ofstream save(file_name, ios::out | ios::binary);
  if(!save){
    cout << "Something went wrong\n\n";
  }
  else{
    save.write((char*)&player,sizeof(struct player));
    save.close();
  }
}

void loader(player &player,const char *file_name){
  ifstream save (file_name, ios::in | ios::binary);
  if(!save){
    cout << "Something went wrong\n\n";
  }
  else{
    player = {};
    save.read((char*)&player,sizeof(struct player));
    save.close();
  }
}

//Add more things to do(explorin,quests,etc)
void menu(player &player){
  int go = 1;
  int save;
  while(go){
    int x;
    cout << "What do you want to do :\n1.Save Game\n2.Load Game\n3.Browse equipment\n4.See stats\n5.Fight a monster\n6.End Game\nNumber : ";
    cin >> x;
    cout << endl;
    switch(x){
      case 1:
        cout << "Choose where to save\n1.SAVE1\n2.SAVE2\n3.SAVE3\n4.SAVE4\nNumber : ";
        cin >> save;
        cout << endl;
        switch(save){
          case 1:
            saver(player,"C:\\ProgramData\\Programming\\Projects\\C++\\1stSemester\\Gierka\\out\\SAVE1.dat");
            break;
          case 2:
            saver(player,"C:\\ProgramData\\Programming\\Projects\\C++\\1stSemester\\Gierka\\out\\SAVE2.dat");
            break;
          case 3:
            saver(player,"C:\\ProgramData\\Programming\\Projects\\C++\\1stSemester\\Gierka\\out\\SAVE3.dat");
            break;
          case 4:
            saver(player,"C:\\ProgramData\\Programming\\Projects\\C++\\1stSemester\\Gierka\\out\\SAVE4.dat");
            break;
          default:
            cout << "Not an option\n";
            break;
        }
        break;
      case 2:
        cout << "Choose which save to load:\n1.SAVE1\n2.SAVE2\n3.SAVE3\n4.SAVE4\nNumber : ";
        cin >> save;
        cout << endl;
        switch(save){
          case 1:
            loader(player,"C:\\ProgramData\\Programming\\Projects\\C++\\1stSemester\\Gierka\\out\\SAVE1.dat");
            break;
          case 2:
            loader(player,"C:\\ProgramData\\Programming\\Projects\\C++\\1stSemester\\Gierka\\out\\SAVE2.dat");
            break;
          case 3:
            loader(player,"C:\\ProgramData\\Programming\\Projects\\C++\\1stSemester\\Gierka\\out\\SAVE3.dat");
            break;
          case 4:
            loader(player,"C:\\ProgramData\\Programming\\Projects\\C++\\1stSemester\\Gierka\\out\\SAVE4.dat");
            break;
          default:
            cout << "Not an option\n";
            break;
        }
        break;
      case 3:
        equipment(player);
        break;
      case 4:
        stats(player);
        break;
      case 5:
        fight(player);
        break;
      case 6:
        cout << "Thanks for playing :)" << endl;
        go = 0;
        break;
      default:
        cout << "That's not an option" << endl << endl;
    }
  }
}





int main(){
  player player;
  player_creation(player);
  weapon w1 = {"Wooden Sword","Sword",10};
  armor a1 = {"Basic Clothes","Light",10};
  player.weapon_eq[0] = w1;
  player.armor_eq[0] = a1;
  player.weapon_ammount++;
  player.armor_ammount++;
  player.current_weapon = w1;
  player.current_armor = a1;
  menu(player);

}
