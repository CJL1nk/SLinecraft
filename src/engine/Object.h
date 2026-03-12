//
// Created by CJ on 3/11/26.
//

#ifndef SLINECRAFT_OBJECT_H
#define SLINECRAFT_OBJECT_H


class Object {

    public:
        Object();

    private:
        float origin[3];
        const float* vertices;
        const float* indices;
};


#endif //SLINECRAFT_OBJECT_H