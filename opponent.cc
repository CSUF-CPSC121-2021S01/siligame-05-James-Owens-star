#include "opponent.h"
#include <iostream>

void Opponent::Draw(graphics::Image &gamescreen) {
  gamescreen.DrawRectangle(40 + x_, 5 + y_, 5, 44, 0, 0, 0);
  gamescreen.DrawRectangle(5 + x_, 5 + y_, 5, 44, 0, 0, 0);
  gamescreen.DrawRectangle(10 + x_, 21 + y_, 30, 15, 255, 0, 0);
  gamescreen.DrawRectangle(24 + x_, 36 + y_, 3, 8, 0, 0, 0);
}

void OpponentProjectile::Draw(graphics::Image &gamescreen) {
  gamescreen.DrawRectangle(0 + x_, 0 + y_, 5, 5, 255, 0, 0);
}

void Opponent::Move(const graphics::Image &gamescreen) {
  if (IsOutOfBounds(gamescreen)) {
    is_active = false;
  } else {
    SetX(x_ + 1);
    SetY(y_ + 2);
  }
}

void OpponentProjectile::Move(const graphics::Image &gamescreen) {
  if (IsOutOfBounds(gamescreen)) {
    is_active = false;
  } else {
    SetX(x_ + 1);
    SetY(y_ + 4);
  }
}

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  blaster_counter += 1;
  if (blaster_counter % 20 == 0) {
    std::unique_ptr<OpponentProjectile> new_blaster =
        std::make_unique<OpponentProjectile>(GetX(), GetY());
    return std::move(new_blaster);
  } else {
    return nullptr;
  }
}
