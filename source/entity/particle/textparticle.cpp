#include "textparticle.h"

TextParticle::TextParticle(Serializer &serializer)
: Particle(serializer)
{
  size_t length;
  serializer.loadFromFile(&length);
  char *string = new char[length];
  serializer.loadFromFile_Fields(string, string + (length - 1));
  msg = std::string(string, length);
  delete[] string;
  serializer.loadFromFile_Fields(&xa, &zz);
}

TextParticle::TextParticle(std::string msg, int x, int y, int col)
: Particle(PK_TEXT, x, y, 60)
{
  this->msg = msg;
  this->col = col;
  xx = x;
  yy = y;
  zz = 2;
  xa = random.nextGaussian() * 0.3;
  ya = random.nextGaussian() * 0.2;
  za = random.nextFloat() * 0.7 + 2;
}

void TextParticle::tick(Game &game, Level &level, std::shared_ptr<Entity> self)
{
  Particle::tick(game, level, self);
  xx += xa;
  yy += ya;
  zz += za;
  if (zz < 0)
  {
    zz = 0;
    za *= -0.5;
    xa *= 0.6;
    ya *= 0.6;
  }
  za -= 0.15;
  x = (int)xx;
  y = (int)yy;
}

void TextParticle::render(Screen &screen)
{
  screen.renderText(msg, x - msg.length() * 4 + 1, y - (int)(zz) + 1, Color::get(-1, 0, 0, 0));
  screen.renderText(msg, x - msg.length() * 4, y - (int)(zz), col);
}

void TextParticle::serialize(Serializer &serializer)
{
  size_t length;
  serializer.saveToFile(&length);
  const char *string = msg.c_str();
  serializer.saveToFile_Fields(string, string + (length - 1));
  serializer.saveToFile_Fields(&xa, &zz);
}
