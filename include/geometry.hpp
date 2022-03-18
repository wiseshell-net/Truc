/*
 * geometry.hpp
 *
 * Copyright 2018 Raphaël SEBAN <raphael.seban@laposte.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#ifndef _GEOMETRY_HPP
#define _GEOMETRY_HPP

/**
 * \file
 * \brief General purpose geometry tools.
 *
 * This header file declares many general purpose geometry structures
 * and utility tools.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <cmath>
#include <cstdint>
#include <cstdlib>

#include "array.hpp"


/* preprocessor macro defs */


#ifndef PI
    #ifdef M_PI
        #define PI  M_PI
    #else
        #define PI  3.141592653589793f
    #endif
#endif


/* basic types */


typedef int         Integer;
typedef double_t    Number;


/* enumerations */


/**
 * \brief Generic rectangle anchorage enumeration.
 */
enum AnchorageEnum
{
    ANCHOR_CENTER = 0,

    ANCHOR_NORTH =  1 << 0,
    ANCHOR_SOUTH =  1 << 1,
    ANCHOR_EAST =   1 << 2,
    ANCHOR_WEST =   1 << 3,

    ANCHOR_NORTH_EAST = ANCHOR_NORTH | ANCHOR_EAST,
    ANCHOR_NORTH_WEST = ANCHOR_NORTH | ANCHOR_WEST,
    ANCHOR_SOUTH_EAST = ANCHOR_SOUTH | ANCHOR_EAST,
    ANCHOR_SOUTH_WEST = ANCHOR_SOUTH | ANCHOR_WEST,
};


/**
 * \brief Generic angle unit enumeration.
 */
enum AngleUnitEnum
{
    ANGLE_DEGREES,
    ANGLE_RADIANS
};


/* angles */


/**
 * \brief Generic angle structure (floating point dimension).
 */
struct Angle
{
    Number          value;
    AngleUnitEnum   unit;
};


/* polars */


/**
 * \brief Generic polar vector structure (floating point dimensions).
 */
struct PolarVector
{
    Number  magnitude;   /* aka length or radius */
    Angle   direction;   /* aka angle */
};


/* points */


/**
 * \brief Generic anchorage point structure (floating point
 * coordinates).
 */
struct AnchoragePoint
{
    Number  x;
    Number  y;

    AnchorageEnum   anchorage;
};


/**
 * \brief Generic anchorage point structure (integer coordinates).
 */
struct IAnchoragePoint
{
    Integer x;
    Integer y;

    AnchorageEnum   anchorage;
};


/**
 * \brief Generic point structure (floating point coordinates).
 */
struct Point
{
    Number x;
    Number y;
};


/**
 * \brief Generic vector structure (floating point coordinates).
 */
typedef struct Point Vector;


/**
 * \brief Generic array of points (floating point coordinates).
 */
struct PointArray : public Array<Point> {};


/**
 * \brief Generic polygon array of points (floating point coordinates).
 */
typedef struct PointArray Polygon;


/**
 * \brief Generic shape array of points (floating point coordinates).
 */
typedef struct PointArray Shape;


/**
 * \brief Generic array of vectors (floating point coordinates).
 */
typedef struct PointArray VectorArray;


/**
 * \brief Generic point structure (integer coordinates).
 */
struct IPoint
{
    Integer x;
    Integer y;
};


/**
 * \brief Generic vector structure (integer coordinates).
 */
typedef struct IPoint IVector;


/**
 * \brief Generic array of points (integer coordinates).
 */
struct IPointArray : public Array<IPoint> {};


/**
 * \brief Generic polygon array of points (integer coordinates).
 */
typedef struct IPointArray IPolygon;


/**
 * \brief Generic shape array of points (integer coordinates).
 */
typedef struct IPointArray IShape;


/**
 * \brief Generic array of vectors (integer coordinates).
 */
typedef struct IPointArray IVectorArray;


/* lines */


/**
 * \brief Generic line structure (floating point coordinates).
 */
struct Line
{
    Number x0;
    Number y0;
    Number x1;
    Number y1;
};


/**
 * \brief Generic line structure (integer coordinates).
 */
struct ILine
{
    Integer x0;
    Integer y0;
    Integer x1;
    Integer y1;
};


/* point-to-point lines */


/**
 * \brief Generic point-to-point line structure (floating point
 * dimensions).
 */
struct PointToPointLine
{
    Point p0;
    Point p1;
};


/**
 * \brief Generic point-to-point line structure (integer dimensions).
 */
struct IPointToPointLine
{
    IPoint p0;
    IPoint p1;
};


/* rectangles */


/**
 * \brief Generic rectangle structure (floating point dimensions).
 */
struct Rectangle
{
    Number x;
    Number y;
    Number w;
    Number h;
};


/**
 * \brief Geometrical utility tools namespace.
 */
namespace Geometry
{

    /**
     * \brief Resets rectangle coordinates along an anchorage point and
     * anchorage indications (floating point dimensions).
     *
     * \param rectangle_left_x - rectangle left side X coordinate.
     * \param rectangle_top_y - rectangle top side Y coordinate.
     * \param rectangle_width - rectangle width.
     * \param rectangle_height - rectangle height.
     * \param anchor_x - anchor point X coordinate.
     * \param anchor_y - anchor point Y coordinate.
     * \param anchorage - anchorage enumeration value.
     */
    void anchorRectangle (
        Number& rectangle_left_x,
        Number& rectangle_top_y,
        const Number& rectangle_width,
        const Number& rectangle_height,
        const Number& anchor_x,
        const Number& anchor_y,
        const AnchorageEnum& anchorage
    );


    /**
     * \brief Resets rectangle object coordinates along an anchorage
     * point object (floating point dimensions).
     *
     * \param rectangle - rectangle object.
     * \param anchor - anchorage point object.
     */
    void anchorRectangle (
        Rectangle& rectangle,
        const AnchoragePoint& anchor
    );


    /**
     * \brief Gets a new rectangle object along size and anchorage
     * indications (floating point dimensions).
     *
     * \param rectangle_width - rectangle width.
     * \param rectangle_height - rectangle height.
     * \param anchor_x - anchor point X coordinate.
     * \param anchor_y - anchor point Y coordinate.
     * \param anchorage - anchorage enumeration value.
     *
     * \return rectangle object.
     */
    Rectangle getAnchoredRectangle (
        const Number& rectangle_width,
        const Number& rectangle_height,
        const Number& anchor_x,
        const Number& anchor_y,
        const AnchorageEnum& anchorage
    );


    /**
     * \brief Gets a new rectangle object along size and anchorage
     * indications (floating point dimensions).
     *
     * \param rectangle - rectangle object.
     * \param anchor - anchorage point object.
     *
     * \return rectangle object.
     */
    Rectangle getAnchoredRectangle (
        const Rectangle& rectangle,
        const AnchoragePoint& anchor
    );

} /* namespace */


/**
 * \brief Generic rectangle structure (integer dimensions).
 */
struct IRectangle
{
    Integer x;
    Integer y;
    Integer w;
    Integer h;
};


namespace Geometry
{

    /**
     * \brief Resets rectangle coordinates along an anchorage point and
     * anchorage indications (integer dimensions).
     *
     * \param rectangle_left_x - rectangle left side X coordinate.
     * \param rectangle_top_y - rectangle top side Y coordinate.
     * \param rectangle_width - rectangle width.
     * \param rectangle_height - rectangle height.
     * \param anchor_x - anchor point X coordinate.
     * \param anchor_y - anchor point Y coordinate.
     * \param anchorage - anchorage enumeration value.
     */
    void anchorRectangle (
        Integer& rectangle_left_x,
        Integer& rectangle_top_y,
        const Integer& rectangle_width,
        const Integer& rectangle_height,
        const Integer& anchor_x,
        const Integer& anchor_y,
        const AnchorageEnum& anchorage
    );


    /**
     * \brief Resets rectangle object coordinates along an anchorage
     * point object (integer dimensions).
     *
     * \param rectangle - rectangle object.
     * \param anchor - anchorage point object.
     */
    void anchorRectangle (
        IRectangle& rectangle,
        const IAnchoragePoint& anchor
    );


    /**
     * \brief Gets a new rectangle object along size and anchorage
     * indications (integer dimensions).
     *
     * \param rectangle_width - rectangle width.
     * \param rectangle_height - rectangle height.
     * \param anchor_x - anchor point X coordinate.
     * \param anchor_y - anchor point Y coordinate.
     * \param anchorage - anchorage enumeration value.
     *
     * \return rectangle object.
     */
    IRectangle getAnchoredRectangle (
        const Integer& rectangle_width,
        const Integer& rectangle_height,
        const Integer& anchor_x,
        const Integer& anchor_y,
        const AnchorageEnum& anchorage
    );


    /**
     * \brief Gets a new rectangle object along size and anchorage
     * indications (integer dimensions).
     *
     * \param rectangle - rectangle object.
     * \param anchor - anchorage point object.
     *
     * \return rectangle object.
     */
    IRectangle getAnchoredRectangle
    (
        const IRectangle& rectangle,
        const IAnchoragePoint& anchor
    );

} /* namespace */


/* anchored rectangles */


/**
 * \brief Generic anchored rectangle structure (floating point
 * dimensions).
 */
struct AnchoredRectangle
{
    Number  x;
    Number  y;
    Number  w;
    Number  h;

    AnchorageEnum   anchorage;
};


/**
 * \brief Generic anchored rectangle structure (integer dimensions).
 */
struct IAnchoredRectangle
{
    Integer x;
    Integer y;
    Integer w;
    Integer h;

    AnchorageEnum   anchorage;
};


/* anchorage point rectangles */


/**
 * \brief Generic anchorage point rectangle structure (floating point
 * dimensions).
 */
struct AnchoragePointRectangle
{
    AnchoragePoint  anchor;

    Number  w;
    Number  h;
};


/**
 * \brief Generic anchorage point rectangle structure (integer
 * dimensions).
 */
struct IAnchoragePointRectangle
{
    IAnchoragePoint anchor;

    Integer w;
    Integer h;
};


/* point-to-point rectangles */


/**
 * \brief Generic point-to-point rectangle structure (floating point
 * dimensions).
 */
struct PointToPointRectangle
{
    Point p0;
    Point p1;
};


/**
 * \brief Generic point-to-point rectangle structure (integer
 * dimensions).
 */
struct IPointToPointRectangle
{
    IPoint p0;
    IPoint p1;
};


/* circles */


/**
 * \brief Generic circle structure (floating point dimensions).
 */
struct Circle
{
    Number center_x;
    Number center_y;
    Number radius;
};


namespace Geometry
{

    /**
     * \brief Fills an array of points along circle indications
     * (floating point dimensions).
     *
     * \param array - array of points.
     * \param nb_points - requested number of points to create into
     * array (circle resolution).
     * \param center_x - circle center point X coordinate.
     * \param center_y - circle center point Y coordinate.
     * \param radius - circle radius.
     *
     * \return true if all went OK, false otherwise.
     */
    bool fillPointArrayAsCircle (
        PointArray& array,
        const ArraySize& nb_points,
        const Number& center_x,
        const Number& center_y,
        const Number& radius
    );

} /* namespace */


/**
 * \brief Generic circle structure (integer dimensions).
 */
struct ICircle
{
    Integer center_x;
    Integer center_y;
    Integer radius;
};


namespace Geometry
{

    /**
     * \brief Fills an array of points along circle indications
     * (integer dimensions).
     *
     * \param array - array of points.
     * \param nb_points - requested number of points to create into
     * array (circle resolution).
     * \param center_x - circle center point X coordinate.
     * \param center_y - circle center point Y coordinate.
     * \param radius - circle radius.
     *
     * \return true if all went OK, false otherwise.
     */
    bool fillPointArrayAsCircle (
        IPointArray& array,
        const ArraySize& nb_points,
        const Integer& center_x,
        const Integer& center_y,
        const Integer& radius
    );

} /* namespace */


/* center-point circles */


/**
 * \brief Generic center point circle structure (floating point
 * dimensions).
 */
struct CenterPointCircle
{
    Point   center;
    Number  radius;
};


/**
 * \brief Generic center point circle structure (integer dimensions).
 */
struct ICenterPointCircle
{
    IPoint  center;
    Integer radius;
};


/* generic sizes */


/**
 * \brief Generic size structure (floating point dimensions).
 */
struct Size
{
    Number w;
    Number h;
};


/**
 * \brief Generic size structure (integer dimensions).
 */
struct ISize
{
    Integer w;
    Integer h;
};


#endif /* _GEOMETRY_HPP */
