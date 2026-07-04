#include<iostream>
#include<random>
#include<stdlib.h>
#include<vector>
#include<string>

struct CharacterParams
{
	std::string name;
	int hp;
	int attack;
	bool isDead;
};

void DispParameter(int hp,int attack)
{
	printf("HP: %d\n", hp);
	printf("Attack: %d\n", attack);
}

void start()
{
	std::random_device rd;

	std::uniform_int_distribution<> dist_hp(50, 100);
	std::uniform_int_distribution<> dist_attack(50, 100);

	CharacterParams player;
	CharacterParams slime;
	CharacterParams goblin;

	int player_hp = dist_hp(rd);
	int player_attack = dist_attack(rd);
	printf("Player\n");
	DispParameter(player_hp, player_attack);

	int slime_hp = dist_hp(rd);
	int slime_attack = dist_attack(rd);
	printf("Slime\n");
	DispParameter(slime_hp, slime_attack);

	int goblin_hp = dist_hp(rd);
	int goblin_attack = dist_attack(rd);
	printf("Goblin\n");
	DispParameter(goblin_hp, goblin_attack);

	std::unique_ptr<Character> player(new Character("Player", player_hp, player_attack));
}

class TurnManager {
public:
	// 要件6: メンバ変数にインスタンスを持たせず、引数で受け取る
	void executeTurn(Character& player, Character& enemy) {
		if (!player.isDead()) {
			player.attack(enemy);
		}
		if (!enemy.isDead()) {
			enemy.attack(player);
		}
	}
};



class Character 
{
private:
	CharacterParams params;
public:
	Character(std::string name, int hp, int attack) {
		params.name = name;
		params.hp = hp;
		params.attack = attack;
		params.isDead = false;
	}

	void attack(Character& target) {
		if (params.isDead) return;
		std::cout << params.name << " の攻撃\n";
		target.takeDamage(params.attack);
	}

	void takeDamage(int damage) {
		if (params.isDead) return;
		params.hp -= damage;
		std::cout << params.name << " は " << damage << " のダメージ (残りHP: " << params.hp << ")\n";
		if (params.hp <= 0) die();
	}

	void die() {
		params.hp = 0;
		params.isDead = true;
		std::cout << params.name << " は倒された\n";
	}

	bool isDead() const { return params.isDead; }
};

void DispParameter(std::string name, int hp, int attack) {
	std::cout << name << "\n";
	std::cout << "HP: " << hp << "\n";
	std::cout << "Attack: " << attack << "\n\n";
}





int main()
{
	start();

	return 0;

}