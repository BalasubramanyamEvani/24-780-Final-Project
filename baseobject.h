#ifndef BASEOBJECT_H_IS_INCLUDED
#define BASEOBJECT_H_IS_INCLUDED

class BaseObject {
   public:
    int x, y;   // location of the object
    int state;  // state of the object

    BaseObject();
    BaseObject(int init_x, int init_y, int init_state);
    ~BaseObject();
};

#endif
