#include "player.h"
#include <iostream>
#include <string>
#include "cpputils/graphics/image.h"

void Player::Draw(graphics::Image &gamescreen) {
  gamescreen.DrawRectangle(40 + x_, 5 + y_, 5, 44, 0, 0, 0);
  gamescreen.DrawRectangle(5 + x_, 5 + y_, 5, 44, 0, 0, 0);
  gamescreen.DrawRectangle(10 + x_, 21 + y_, 30, 15, 27, 172, 57);
  gamescreen.DrawRectangle(24 + x_, 13 + y_, 3, 8, 0, 0, 0);
}

void PlayerProjectile::Draw(graphics::Image &gamescreen) {
  gamescreen.DrawRectangle(0 + x_, 0 + y_, 5, 5, 27, 172, 57);
}

void Player::Move(const graphics::Image &gamescreen) {}

void PlayerProjectile::Move(const graphics::Image &gamescreen) {
  if (IsOutOfBounds(gamescreen)) {
    is_active = false;
  } else {
    SetX(x_ + 1);
    SetY(y_ - 3);
  }
}
