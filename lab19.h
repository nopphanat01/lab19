#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<iomanip>

using namespace std;

class Unit{
		string name;
		string type;		
		int hp;
		int hpmax;
		int atk;
		int def;
		bool guard_on;		
	public:			
		void create(string);
		void showStatus();
		void newTurn();
		int attack(Unit &);
		int beAttacked(int);
		int heal();	
		void guard();
		bool isDead();	
};

void Unit::create(string t){ 
	if(t == "Hero"){
		type = "Hero";
		cout << "Please input your name: ";
		getline(cin,name);
		hpmax = rand()%20+90;
		atk = rand()%5+14;
		def = rand()%3+9;
	}else if(t == "Monster"){
		type = "Monster";
		name = "Kraken";
		hpmax = rand()%20+200;
		atk = rand()%5+25;
		def = rand()%3+5;
	}
	hp = hpmax;
	guard_on = false;
}

void Unit::showStatus(){
	if(type == "Hero"){
		cout << "---------------------------------------\n"; 
		cout << name << "\n"; 
		cout << "HP: " << hp << "/" << hpmax << "\tATK: "<< atk << "\t\tDEF: "<< def;		
		cout << "\n---------------------------------------\n";
	}	
	else if(type == "Monster"){
		cout << "\t\t\t\t---------------------------------------\n"; 
		cout << "\t\t\t\t" << name << "\n"; 
		cout << "\t\t\t\tHP: " << hp << "\t\tATK: "<< atk << "\t\tDEF: "<< def;
		cout << "\n\t\t\t\t---------------------------------------\n";
	}
}

void Unit::newTurn(){
	guard_on = false;
}



/////////////////////////////////////////////////////////////////////////////////////
//Write function members isDead(), guard(), heal(), beAttacked(), and attack() here//
/////////////////////////////////////////////////////////////////////////////////////
bool Unit::isDead() {
    return hp <= 0;  // ถ้า hp น้อยกว่าหรือเท่ากับ 0 จะ return true, ถ้าไม่จะ return false
}

void Unit::guard() {
    guard_on = true;  // เมื่อเรียกใช้ฟังก์ชัน guard() จะทำให้ guard_on เป็น true
}

int Unit::beAttacked(int enemyAtk) {
    int damage;
    
    // ถ้าตัวละครไม่ได้ป้องกัน
    if (!guard_on) {
        damage = enemyAtk - def;  // ความเสียหาย = atk ของศัตรู - def ของตัวละคร
    } 
    // ถ้าตัวละครป้องกัน
    else {
        damage = (enemyAtk - def) / 3;  // ความเสียหาย = (atk ของศัตรู - def ของตัวละคร) / 3
    }
    
    // ตรวจสอบถ้าความเสียหายเป็นลบ (ไม่สามารถติดลบได้) ให้กำหนดเป็น 0
    if (damage < 0) {
        damage = 0;
    }

    // ลด hp ของตัวละครที่ถูกโจมตี
    hp -= damage;

    // คืนค่าความเสียหายที่ได้รับ
    return damage;
}

int Unit::attack(Unit &target) {
    return target.beAttacked(atk);  // เรียกใช้ beAttacked() ของ target (Unit ที่ถูกโจมตี) และส่งค่าพลังโจมตี (atk) ไป
}

int Unit::heal() {
    int healAmount = rand() % 21 + 10;  // สุ่มค่าระหว่าง 10 ถึง 30
    int actualHeal = 0;
    
    // คำนวณค่าฟื้นฟูจริงที่สามารถทำได้
    if (hp < hpmax) {
        actualHeal = min(healAmount, hpmax - hp);  // ฟื้นฟูไม่ให้เกินค่า hpmax
        hp += actualHeal;  // เพิ่มค่า hp ตามที่ฟื้นฟูได้
    }
    
    return actualHeal;  // คืนค่าการฟื้นฟูที่เกิดขึ้นจริง
}




void drawScene(char p_action,int p,char m_action,int m){
	cout << "                                                       \n";
	if(p_action == 'A'){
	cout << "                                       "<< -p <<"\n";
	}else{
	cout << "                                                       \n";	
	}	
	cout << "                                *               *      \n";
	cout << "                                **  *********  **      \n";
	cout << "                                ****         ****      \n";
	if(m_action == 'A'){
	cout << "                 " << setw(5) << -m << "           *** **   ** ***       Attack!\n";
	}else if(m_action == 'G'){
	cout << "                                 *** **   ** ***       Guard!\n";
	}else{
	cout << "                                 *** **   ** ***       \n";	
	}
	cout << "                                  ** **   ** **        \n";
	cout << "                   ***             *         *         \n";
	if(p_action == 'A'){
	cout << "        Attack!    ***  *           *********          \n";		
	}else if(p_action == 'H'){
	cout << "      Heal! +" << setw(2) << p << "    ***  *           *********          \n";
	}else if(p_action == 'G'){
	cout << "         Guard!    ***  *           *********          \n";
	}else{
	cout << "                   ***  *           *********          \n";	
	}
	cout << "                    *  *       ***  *  *  *            \n";
	cout << "                  *****           **   *   *           \n";
	cout << "                    *                  *    ***        \n";
	cout << "                   * *               **        *       \n";
	cout << "                  *   *                                \n";
	cout << "                                                       \n";
};


void playerWin(){	
	cout << "*******************************************************\n";
	for(int i = 0; i < 3; i++) cout << "*                                                     *\n";
	cout << "*                   YOU WIN!!!                        *\n";
	for(int i = 0; i < 3; i++) cout << "*                                                     *\n";
	cout << "*******************************************************\n";
};


void playerLose(){
	cout << "*******************************************************\n";
	cout << "*                                                     *\n";
	cout << "*                   YOU LOSE!!!                       *\n";
	cout << "*                                                     *\n";
	cout << "*******************************************************\n";
};
