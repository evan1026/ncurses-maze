#ifndef RENDER_TYPE_H
#define RENDER_TYPE_H

/**************************************************************************
 * ~~~~~~~~~~~~~~                                                         *
 * ~ RenderType ~                                                         *
 * ~~~~~~~~~~~~~~                                                         *
 *                                                                        *
 * An enumeration that keeps track of the type of render (i.e. whether or *
 * not to use colors).                                                    *
 *                                                                        *
 * TODO merge into renderer                                               *
 **************************************************************************/

enum class RenderType {
    CONSOLE_RENDER_COLOR,
    CONSOLE_RENDER_NO_COLOR,
    CONSOLE_RENDER_DEFAULT
};

#endif
