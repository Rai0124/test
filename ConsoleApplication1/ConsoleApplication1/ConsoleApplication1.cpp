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

class TurnManager {
public:
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

void start()
{
	std::random_device rd;

	std::uniform_int_distribution<> dist_hp(50, 100);
	std::uniform_int_distribution<> dist_attack(50, 100);

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

	std::vector<std::unique_ptr<Character>> enemies;
	enemies.push_back(std::unique_ptr<Character>(new Character("Slime", slime_hp, slime_attack)));
	enemies.push_back(std::unique_ptr<Character>(new Character("Goblin", goblin_hp, goblin_attack)));

	std::cout << "--- バトル開始 ---\n";
	TurnManager turnManager;
	int turn = 1;

	while (!player->isDead() && !enemies.empty()) {
		std::cout << "\n[ ターン " << turn << " ]\n";

		Character& currentEnemy = *enemies.front();

		turnManager.executeTurn(*player, currentEnemy);


		if (currentEnemy.isDead()) {
			enemies.erase(enemies.begin());
			std::cout << "敵を倒した！ 残りの敵: " << enemies.size() << "体\n";
		}

		turn++;
	}

	std::cout << "\n--- バトル終了 ---\n";
	if (player->isDead()) {
		std::cout << "ゲームオーバー...\n";
	}
	else {
		std::cout << "すべての敵を倒した！\n";
	}
}

int main()
{
	start();

	return 0;

}

//動かないです！
//わからないところが多くAIを使っているところがあります；；