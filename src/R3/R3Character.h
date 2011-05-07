#ifndef __R3CHARACTER_H__
#define __R3CHARACTER_H__

class R3Character {
  public:
    R3Character(void);
  
  public:
    int Health;
    int MaxHealth;
    R3Item item;
    R3Vector velocity;
    R3Point position;
    int number_items[8];
    R3ItemType belt[8];
};

#endif
