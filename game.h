#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game() : Game(800, 600) {}
  Game(const int &width, const int &height) {
    gamescreen.Initialize(width, height);
  }

  int GetScore() const { return score_; }
  bool HasLost() const { return Game_lost_; }

  void CreateOpponents();

  void OnMouseEvent(const graphics::MouseEvent &mouseEvent) override;

  void Init() {
    player_.SetX(350);
    player_.SetY(280);
    gamescreen.AddMouseEventListener(*this);
    gamescreen.AddAnimationEventListener(*this);
  }

  void FilterIntersections() {
    for (int i = 0; i < opponent_.size(); i++) {
      if ((*opponent_[i]).GetIsActive() && player_.GetIsActive() &&
          player_.IntersectsWith(opponent_[i].get())) {
        (*opponent_[i]).SetIsActive(false);
        player_.SetIsActive(false);
        Game_lost_ = true;
      } else {
        for (int j = 0; j < player_projectile_.size(); j++) {
          if ((*opponent_[i]).GetIsActive() &&
              (*player_projectile_[j]).GetIsActive() &&
              (*player_projectile_[j]).IntersectsWith(opponent_[i].get())) {
            (*opponent_[i]).SetIsActive(false);
            (*player_projectile_[j]).SetIsActive(false);
            if (player_.GetIsActive()) {
              score_ += 1;
            }
          }
        }
      }
    }
    for (int i = 0; i < opponent_projectile_.size(); i++) {
      if ((*opponent_projectile_[i]).GetIsActive() && player_.GetIsActive() &&
          player_.IntersectsWith(opponent_projectile_[i].get())) {
        (*opponent_projectile_[i]).SetIsActive(false);
        player_.SetIsActive(false);
        Game_lost_ = true;
      }
    }
  }
  void MoveGameElements();

  void RemoveInactive();

  void LaunchProjectiles();

  void UpdateScreen();

  void Start();

  void OnAnimationStep() override;

  graphics::Image &GetGameScreen() { return gamescreen; }
  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles() {
    return player_projectile_;
  }
  std::vector<std::unique_ptr<Opponent>> &GetOpponents() { return opponent_; }
  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles() {
    return opponent_projectile_;
  }
  Player &GetPlayer() { return player_; }

 private:
  graphics::Image gamescreen;
  std::vector<std::unique_ptr<Opponent>> opponent_;
  std::vector<std::unique_ptr<OpponentProjectile>> opponent_projectile_;
  std::vector<std::unique_ptr<PlayerProjectile>> player_projectile_;
  Player player_;
  bool Game_lost_ = false;
  int score_ = 0;
};
#endif
