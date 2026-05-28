//
// Created by CJ on 5/27/26.
//

#ifndef SLINECRAFT_EVENT_H
#define SLINECRAFT_EVENT_H

inline bool quit = false;

inline bool W = false;
inline bool S = false;
inline bool A = false;
inline bool D = false;
inline bool P = false;
inline bool SPACE = false;
inline bool LCTRL = false;
inline bool RIGHT = false;
inline bool LEFT = false;
inline bool UP = false;
inline bool DOWN = false;

void pollEvents();

#endif //SLINECRAFT_EVENT_H